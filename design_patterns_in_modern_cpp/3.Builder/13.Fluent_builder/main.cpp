#include "EmailBuilder.hpp"
#include "PersonBuilder.hpp"

using namespace std;

int main() {
    Person p = Person::create("John")
                   .lives()
                   .at("123 London Road")
                   .with_postcode("SW1 1GB")
                   .in("London")
                   .works()
                   .with("PragmaSoft")
                   .as_a("Consultant")
                   .earning("10e6");

    cout << p << endl;

    Email mail = Email::make().from("me@mail.com").to("you@mail.com").subject("C++ builders").body("I like this API, don't you?");

    cout << mail << endl;

    return EXIT_SUCCESS;
}