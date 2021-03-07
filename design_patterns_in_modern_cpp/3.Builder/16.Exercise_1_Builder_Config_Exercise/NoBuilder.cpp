#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

class CodeBuilder {
    std::string class_name;
    std::vector<std::pair<std::string, std::string>> fields;

   public:
    CodeBuilder(const string& class_name) {
        this->class_name = class_name;
    }

    CodeBuilder& add_field(const string& name, const string& type) {
        fields.emplace_back(std::make_pair(type, name));
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj) {
        os << "class " << obj.class_name << std::endl
           << "{" << std::endl;

        for (const auto& pair : obj.fields) {
            os << "  " << pair.first << " " << pair.second << ";" << std::endl;
        }

        os << "};";
        return os;
    }
};

int main() {
    auto cb = CodeBuilder("Person").add_field("name", "string").add_field("age", "int");
    std::cout << cb;
}