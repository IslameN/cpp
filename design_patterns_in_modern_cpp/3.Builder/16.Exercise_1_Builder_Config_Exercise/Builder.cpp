#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

class CodeBuilder;

class Code {
    std::string name;
    std::string type;

   public:
    Code(){};
    Code(const std::string& type, const std::string& name) : type(type), name(name){};

    std::vector<Code> codes;

    friend ostream& operator<<(ostream& os, const Code& obj) {
        os << obj.type << " " << obj.name << ";";
        return os;
    };
};

class CodeBuilder {
    std::string class_name;
    Code code;

   public:
    CodeBuilder(const string& class_name) {
        this->class_name = class_name;
    }

    CodeBuilder& add_field(const string& name, const string& type) {
        code.codes.emplace_back(Code(type, name));
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj) {
        os << "class " << obj.class_name << std::endl
           << "{" << std::endl;

        for (const auto& pair : obj.code.codes) {
            os << "  " << pair << std::endl;
        }

        os << "};";
        return os;
    }

    operator Code() const {
        return code;
    }
};

int main() {
    auto cb = CodeBuilder("Person").add_field("name", "string").add_field("age", "int");
    std::cout << cb;

    Code code = CodeBuilder("Person").add_field("name", "string").add_field("age", "int");
    std::cout << code;
}