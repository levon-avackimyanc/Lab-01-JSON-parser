//
// Copyright 2020 Avakimyanc Levon <avakimyanc.levon.01@mail.ru>
//

#include "Student.hpp"

#include <iostream>

using nlohmann::json;

Student::Student() = default;
Student::Student(const json &j) {
  if (j.empty()) {
    throw std::invalid_argument("File is empty.");
  }
  if (!j.at("name").is_string()) {
    throw std::invalid_argument("The type of the name is incorrect");
  } else {
    Name = j.at("name").get<std::string>();
  }
  Group = std::any{j.at("group")};
  if (j.at("avg").is_string()) {
    Avg = std::stod(j.at("avg").get<std::string>());
  } else {
    if (j.at("avg").is_number()) {
      Avg = j.at("avg").get<double>();
    } else {
      throw std::invalid_argument("The type of the avg is incorrect");
    }
  }
  Debt = std::any{j.at("debt")};
}
const std::string &Student::getName() { return this->Name; }
double Student::getAvg() const { return this->Avg; }
const std::any &Student::getDebt() { return this->Debt; }
const std::any &Student::getGroup() { return this->Group; }
Student::~Student() = default;
