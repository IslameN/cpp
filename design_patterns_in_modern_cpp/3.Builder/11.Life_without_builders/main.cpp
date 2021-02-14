#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // <p>hello</p>
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";

    cout << output << endl;

    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for (auto w : words) {
        oss << "  <li>" << w << "</li>";
    }
    oss << "</ul>";

    cout << oss.str() << endl;
}