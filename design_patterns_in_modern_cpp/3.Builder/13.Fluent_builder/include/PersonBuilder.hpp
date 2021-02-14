#pragma once

#include <utility>

#include "Person.hpp"

class PersonBuilder {
    Person* person;

   public:
    PersonBuilder(std::string name) { person = new Person(name); }
    operator Person() const { return *person; }
    PersonBuilder& lives();
    PersonBuilder& at(std::string street_address);
    PersonBuilder& with_postcode(std::string post_code);
    PersonBuilder& in(std::string city);
    PersonBuilder& works();
    PersonBuilder& with(std::string company_name);
    PersonBuilder& as_a(std::string position);
    PersonBuilder& earning(std::string annual_income);
};