#include "TripService/TripService.h"
#include "TripService/User.h"
#include "TripService/TripDAO.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define FIRST_USER_ID 1
#define SECOND_USER_ID 2

class TestableTripService : public TripService {
public:
    explicit TestableTripService(User *loggedUser, TripDAO * tripDAO) : loggedUser(loggedUser), tripDAO(tripDAO) {}

    User *getLoggedUser() const override {
        return loggedUser;
    }

    list<Trip> getTriplist(User *user) const override {
        return user->Trips();//tripDAO->FindTripsByUser(user);
    }

private:
    User *loggedUser;
    TripDAO * tripDAO;
};

class TripDAOMock : public TripDAO {
    inline list<Trip> FindTripsByUser(User* user) {
        return user->Trips();
    }
};

TEST(TripServiceShould, validate_the_logged_in_user)
{
    User *notLoggedUser = nullptr;
    auto *tripService = new TestableTripService(notLoggedUser, new TripDAOMock);
    EXPECT_THROW(tripService->GetTripsByUser(nullptr), const char *);
}

TEST(TripServiceShould, return_no_trips_when_users_are_not_friends)
{
    User *loggedUser = new User(FIRST_USER_ID);
    User *anotherUser = new User(SECOND_USER_ID);

    auto tripToBrazil = Trip("Brazil");
    anotherUser->AddTrip(tripToBrazil);
    auto tripToLondon = Trip("London");
    anotherUser->AddTrip(tripToLondon);

    auto *tripService = new TestableTripService(loggedUser, new TripDAOMock);
    auto trips = tripService->GetTripsByUser(anotherUser);
    EXPECT_TRUE(trips.empty());
}

TEST(TripServiceShould, return_trips_when_users_are_friends)
{
    User *loggedUser = new User(FIRST_USER_ID);
    User *anotherUser = new User(SECOND_USER_ID);

    auto tripToBrazil = Trip("Brazil");
    anotherUser->AddTrip(tripToBrazil);
    auto tripToLondon = Trip("London");
    anotherUser->AddTrip(tripToLondon);
    anotherUser->AddFriend(*loggedUser);

    auto *tripService = new TestableTripService(loggedUser, new TripDAOMock);
    try {
        auto trips = tripService->GetTripsByUser(anotherUser);
        EXPECT_THAT(trips, ::testing::Contains(tripToLondon));
        EXPECT_THAT(trips, ::testing::Contains(tripToBrazil));
        EXPECT_EQ(trips.size(), 2);
    } catch (const char * exception) {
        FAIL() << exception;
    }
}