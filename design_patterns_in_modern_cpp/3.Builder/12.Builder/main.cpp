#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct HtmlBuilder;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text)
        : name(name),
          text(text) {
    }

    string str(int indent = 0) const {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0) {
            oss << string(indent_size * (indent + 1), ' ') << text << endl;
        }

        for (const auto& e : elements) {
            oss << e.str(indent + 1);
        }

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlBuilder> build(string root_name) {
        return make_unique<HtmlBuilder>(root_name);
    }
};

struct HtmlBuilder {
    HtmlBuilder(string root_name) {
        root.name = root_name;
    }

    // void to start with
    HtmlBuilder& add_child(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    // pointer based
    HtmlBuilder* add_child_2(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }

    string str(int i = 0) { return root.str(i); }

    operator HtmlElement() const { return root; }
    HtmlElement root;
};

int main() {
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;

    // auto builder2 = HtmlElement::build("ul"); // this crashes
    unique_ptr<HtmlBuilder> builder2 = HtmlElement::build("ul");
    builder2->add_child_2("li", "hello")->add_child_2("li", "world");
    cout << builder2->str(4) << endl;

    getchar();
    return 0;
}