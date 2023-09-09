#include "TripService/TripService.h"
#include "TripService/User.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define FIRST_USER_ID 1
#define SECOND_USER_ID 2

class TestableTripService : public TripService {
public:
    explicit TestableTripService(User *loggedUser) : loggedUser(loggedUser) {}

    User *getLoggedUser() const override {
        return loggedUser;
    }
private:
    User *loggedUser = nullptr;
};

TEST(TripServiceShould, validate_the_logged_in_user)
{
    User *notLoggedUser = nullptr;
    auto *tripService = new TestableTripService(notLoggedUser);
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

    auto *tripService = new TestableTripService(loggedUser);
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

    auto *tripService = new TestableTripService(loggedUser);
    try {
        auto trips = tripService->GetTripsByUser(anotherUser);
        EXPECT_THAT(trips, ::testing::ElementsAre(tripToLondon, tripToBrazil));
    } catch (const char * exception) {
        FAIL() << exception;
    }
}