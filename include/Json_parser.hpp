//
// Copyright 2020 Avakimyanc Levon <avakimyanc.levon.01@mail.ru>
//

#ifndef INCLUDE_JSON_PARSER_HPP_
#define INCLUDE_JSON_PARSER_HPP_

#include <any>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Student.hpp"

using nlohmann::json;

class Json_parser {
 public:
  explicit Json_parser(const std::string& Json_path);
  friend std::ostream& operator<<(std::ostream& out, Json_parser& j);

 private:
  std::vector<size_t> length_of_fields{20, 10, 7, 15};
  std::vector<std::string> columns{"name", "group", "avg", "debt"};
  std::vector<Student> students;
};
#endif  // INCLUDE_JSON_PARSER_HPP_"
