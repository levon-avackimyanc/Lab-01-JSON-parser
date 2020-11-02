//
// Copyright 2020 Avakimyanc Levon <avakimyanc.levon.01@mail.ru>
//
#include "Json_parser.hpp"

#include <iomanip>
#include <iostream>

#include "Student.hpp"

Json_parser::Json_parser(const std::string &Json_path) {
    json j;
    if (Json_path[0] != '{') {
        if (Json_path.empty()) {
            throw std::invalid_argument("Json path is incorrect!");
        }
        std::ifstream file{Json_path};
        if (!file) {
            throw std::runtime_error("unable to open json: " + Json_path);
        }
        file >> j;
    } else {
        j = json::parse(Json_path);
    }
    if (j.empty()) {
        throw std::invalid_argument("Object array is empty");
    }
    if (!j.at("items").is_array()) {
        throw std::invalid_argument("Json file is not array!");
    }
    if (j.at("items").size() != j.at("_meta").at("count")) {
        throw std::out_of_range(
                "count is not equal to the actual number of objects in items!");
    }
    for (auto const &student : j.at("items")) {
        Student s(student);
        students.emplace_back(s);
    }
}

std::ostream &operator<<(std::ostream &out, const Json_parser &J) {
    std::vector<int> length_of_fields{20, 10, 7, 15};
    std::vector<std::string> columns{"name", "group", "avg", "debt"};
    size_t size = 0;
    for (auto i : J.students) {
        if (i.getName().length() > size) {
            size = i.getName().length();
        }
    }

    length_of_fields[0] = size + 3;

    out << std::left;
    for (size_t i = 0; i < 4; ++i) {
        out << std::setw(length_of_fields[i]) << "| " + columns[i];
    }
    out << "|" << std::endl;
    for (size_t i = 0; i < 4; ++i) {
        out << std::setfill('-') << std::setw(length_of_fields[i]) << '|';
    }
    out << std::setfill(' ') << '|' << std::endl;
    for (size_t i = 0; i < J.students.size(); ++i) {
        out << std::left << std::setw(length_of_fields[0])
            << "| " + J.students[i].getName();
        if ((std::any_cast<json>(J.students[i].getGroup())).is_number()) {
            out << "| " << std::setw(length_of_fields[1] - 2)
                << std::any_cast<json>((J.students[i].getGroup())).get<int>();
        } else {
            out << "| " << std::setw(length_of_fields[1] - 2)
                << std::any_cast<json>((J.students[i].getGroup())).get<std::string>();
        }
        out << "| " << std::setw(length_of_fields[2] - 2) << J.students[i].getAvg();
        if ((std::any_cast<json>(J.students[i].getDebt()).is_array())) {
            if ((std::any_cast<json>(J.students[i].getDebt()).size()) > 1) {
                out << "| " << std::any_cast<json>(J.students[i].getDebt()).size()
                    << std::setw(length_of_fields[3] - 3) << " items";
            } else {
                std::vector<std::string> d =
                        std::any_cast<json>(J.students[i].getDebt())
                                .get<std::vector<std::string>>();
                out << "| " << std::setw(length_of_fields[3] - 2) << d[0];
            }
        } else if ((std::any_cast<json>(J.students[i].getDebt()).is_string())) {
            out << "| " << std::setw(length_of_fields[3] - 2)
                << std::any_cast<json>(J.students[i].getDebt()).get<std::string>();
        } else {
            out << std::setw(length_of_fields[3]) << "| null";
        }
        out << "|";
        out << std::endl;
        for (size_t t = 0; t < 4; ++t) {
            out << std::setfill('-') << std::setw(length_of_fields[t]) << "|";
        }
        out << "|" << std::endl;
        out << std::setfill(' ');
    }
    return out;
}
