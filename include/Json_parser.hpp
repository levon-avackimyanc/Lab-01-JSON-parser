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
  friend std::ostream& operator<<(std::ostream& out, const Json_parser& j);

 private:
  std::vector<Student> students;
};
#endif  // INCLUDE_JSON_PARSER_HPP_"
