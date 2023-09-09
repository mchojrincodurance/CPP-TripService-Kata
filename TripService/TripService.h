#ifndef TRIPSERVICE_H
#define TRIPSERVICE_H

#include "Trip.h"
#include "User.h"
#include <iostream>
#include <list>

using namespace std;

class TripService
{
  public:
    list<Trip> GetTripsByUser(User* user);

    virtual User *getLoggedUser() const;

    virtual list<Trip> getTriplist(User *user) const;

    bool isFriendOf(User *user, User *loggedUser) const;
};

#endif