#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "Person.h"
#include "PersonAddressBuilder.h"
#include "PersonBuilder.h"
#include "PersonJobBuilder.h"

int main() {
    Person p = Person::create()
                   .lives()
                   .at("123 London Road")
                   .with_postcode("SW1 1GB")
                   .in("London")
                   .works()
                   .at("PragmaSoft")
                   .as_a("Consultant")
                   .earning(10e6);

    cout << p << endl;
    getchar();
    return 0;
}