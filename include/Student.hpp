//
// Copyright 2020 Avakimyanc Levon <avakimyanc.levon.01@mail.ru>
//

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_
#include <any>
#include <exception>
#include <nlohmann/json.hpp>
#include <string>

using nlohmann::json;

class Student {
 public:
  Student();
  explicit Student(const json &j);
  const std::string &getName() const;
  const std::any &getGroup() const;
  double getAvg() const;
  const std::any &getDebt() const;
  ~Student();

 private:
  std::string Name;
  std::any Group;
  double Avg;
  std::any Debt;
};
#endif  // INCLUDE_STUDENT_HPP_"
