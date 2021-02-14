#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Forward declaring the builder
class EmailBuilder;

class Email {
   public:
    friend class EmailBuilder;  // the builder can access Email's privates

    static EmailBuilder make();

    // Bonus example!
    friend std::ostream& operator<<(std::ostream& stream, const Email& email) {
        stream << email.to_string();
        return stream;
    }

    string to_string() const {
        stringstream stream;
        stream << "from: " << m_from
               << "\nto: " << m_to
               << "\nsubject: " << m_subject
               << "\nbody: " << m_body;
        return stream.str();
    }

   private:
    Email() = default;  // restrict construction to builder

    string m_from;
    string m_to;
    string m_subject;
    string m_body;
};