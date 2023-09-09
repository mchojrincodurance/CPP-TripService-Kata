//
// Created by mauro on 9/09/23.
//

#ifndef TRIPSERVICEKATA_USERNOTLOGGEDINEXCEPTION_H
#define TRIPSERVICEKATA_USERNOTLOGGEDINEXCEPTION_H


#include <exception>

class UserNotLoggedInException : std::exception {
    const char * what() const noexcept override {
        return "UserNotLoggedInException";
    }
};


#endif //TRIPSERVICEKATA_USERNOTLOGGEDINEXCEPTION_H
