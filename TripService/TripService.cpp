#ifndef TRIPSERVICE_CPP
#define TRIPSERVICE_CPP

#include "TripService.h"
#include "TripDAO.h"
#include "UserSession.h"
#include "../UserNotLoggedInException.h"
#include <iostream>
#include <list>

using namespace std;

UserSession *UserSession::oneUserSession = 0;

list<Trip> TripService::GetTripsByUser(User *user) {
    User *loggedUser = getLoggedUser();
    if (!loggedUser) {
        throw UserNotLoggedInException();
    }

    return isFriendOf(user, loggedUser) ? getTriplist(user) : list<Trip>{};
}

bool TripService::isFriendOf(User *user, User *loggedUser) const {
    bool isFriend;
    list<User>::iterator i;
    for (i = user->GetFriends().begin(); i != user->GetFriends().end(); ++i) {
        if (*i == *loggedUser) {
            isFriend = true;
            break;
        }
    }
    return isFriend;
}

list<Trip> TripService::getTriplist(User *user) const { return TripDAO::FindTripsByUser(user); }

User *TripService::getLoggedUser() const { return UserSession::GetInstance()->GetLoggedUser(); }

#endif