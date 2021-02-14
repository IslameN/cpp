#include <iostream>
#include <sstream>
#include <string>

#include "Email.hpp"

class EmailBuilder {
   public:
    EmailBuilder& from(const string& from) {
        m_email.m_from = from;
        return *this;
    }

    EmailBuilder& to(const string& to) {
        m_email.m_to = to;
        return *this;
    }

    EmailBuilder& subject(const string& subject) {
        m_email.m_subject = subject;
        return *this;
    }

    EmailBuilder& body(const string& body) {
        m_email.m_body = body;
        return *this;
    }

    operator Email&&() {
        return std::move(m_email);  // notice the move
    }

   private:
    Email m_email;
};