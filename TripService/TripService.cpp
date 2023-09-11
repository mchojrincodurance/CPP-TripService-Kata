#ifndef TRIPSERVICE_CPP
#define TRIPSERVICE_CPP

#include "TripService.h"
#include "TripDAO.h"
#include "UserSession.h"
#include <list>

using namespace std;

UserSession *UserSession::oneUserSession = 0;

list<Trip> TripService::GetTripsByUser(User *user) {
    validateLoggedUser();

    return isFriendOf(user, getLoggedUser()) ? getTripList(user) : noTrips();
}

void TripService::validateLoggedUser() const {
    if (!getLoggedUser()) {
        throw "UserNotLoggedInException";
    }
}

list<Trip> TripService::noTrips() const { return list<Trip>{}; }

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

list<Trip> TripService::getTripList(User *user) const { return TripDAO::FindTripsByUser(user); }

User *TripService::getLoggedUser() const { return UserSession::GetInstance()->GetLoggedUser(); }

#endif