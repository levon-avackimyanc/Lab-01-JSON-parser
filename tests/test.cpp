// Copyright 2020 Avakimyanc Levon <levon.avakimyanc.01@mail.ru>

#include <gtest/gtest.h>

#include <sstream>

#include "Json_parser.hpp"
#include "Student.hpp"

std::string getFullPath(const std::string &name) {
    std::string s(__FILE__);
    for (size_t i = 0; i < 8; ++i) {
        s.pop_back();
    }
    return s + name;
}

TEST(Json_parser, Throw_Exceptions) {
    ASSERT_THROW(Json_parser(""), std::invalid_argument);
    ASSERT_THROW(Json_parser("wrong.name"), std::runtime_error);
    ASSERT_THROW(Json_parser((R"({})")), std::invalid_argument);
    ASSERT_THROW(Json_parser(R"({
  "items": 5
})"),
                 std::invalid_argument);
    ASSERT_THROW(Json_parser((R"({
"items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 10
  }})")),
                 std::out_of_range);
    ASSERT_THROW(Student(json::parse(R"({})")), std::invalid_argument);
    ASSERT_THROW(Student(json::parse(R"({
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": [],
      "debt": "C++"
    }
)")),
                 std::invalid_argument);
    ASSERT_THROW(Student(json::parse(R"(
 {
      "name": 5051,
      "group": 31,
      "avg": 4,
      "debt": "C++"
    }

)")),
                 std::invalid_argument);
}

TEST(Json_parser, correct_student_values) {
    Student S1(json::parse(R"(
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt":  "C++"
    }
)"));
    ASSERT_EQ(S1.getName(), "Ivanov Petr");
    ASSERT_EQ(std::any_cast<json>(S1.getGroup()).get<std::string>(), "1");
    ASSERT_EQ(std::any_cast<json>(S1.getDebt()).get<std::string>(), "C++");
    ASSERT_DOUBLE_EQ(S1.getAvg(), 4.25);
    Student S2(json::parse(R"(
{
      "name": "Petrov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
"C++",
          "Linux",
          "Network"
      ]
  })"));
    ASSERT_EQ(S2.getName(), "Petrov Nikita");
    ASSERT_EQ(std::any_cast<json>(S2.getGroup()).get<std::string>(), "IU8-31");
    ASSERT_TRUE(std::any_cast<json>(S2.getDebt()).is_array());
    ASSERT_DOUBLE_EQ(S2.getAvg(), 3.33);
}

TEST(Json_parser, correct_output) {
    Json_parser J(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
}
)");
    std::stringstream ss;
    ss << J;
    std::string output(R"(| name          | group   | avg  | debt         |
|---------------|---------|------|--------------|
| Ivanov Petr   | 1       | 4.25 | null         |
|---------------|---------|------|--------------|
| Sidorov Ivan  | 31      | 4    | C++          |
|---------------|---------|------|--------------|
| Petrov Nikita | IU8-31  | 3.33 | 3 items      |
|---------------|---------|------|--------------|
)");
    ASSERT_EQ(ss.str(), output);
}

TEST(Json_parser, output_by_file_info) {
    std::stringstream ss;
    Json_parser J(getFullPath("Json_test"));
    ss << J;
    std::string output(R"(| name          | group   | avg  | debt         |
|---------------|---------|------|--------------|
| Ivanov Petr   | 1       | 4.25 | null         |
|---------------|---------|------|--------------|
| Sidorov Ivan  | 31      | 4    | C++          |
|---------------|---------|------|--------------|
| Petrov Nikita | IU8-31  | 3.33 | 3 items      |
|---------------|---------|------|--------------|
)");
    ASSERT_EQ(ss.str(), output);
}

TEST(Json_parser, simple_array) {
    Json_parser J(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
}
)");
    std::stringstream ss;
    ss << J;
    std::string output(R"(| name          | group   | avg  | debt         |
|---------------|---------|------|--------------|
| Ivanov Petr   | 1       | 4.25 | null         |
|---------------|---------|------|--------------|
| Sidorov Ivan  | 31      | 4    | C++          |
|---------------|---------|------|--------------|
| Petrov Nikita | IU8-31  | 3.33 | Network      |
|---------------|---------|------|--------------|
)");
    ASSERT_EQ(ss.str(), output);
}
