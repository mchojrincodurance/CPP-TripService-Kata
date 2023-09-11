#include "TripService/TripService.h"
#include "TripService/User.h"
#include "TripService/TripDAO.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#define FIRST_USER_ID 1
#define SECOND_USER_ID 2
#define GUEST nullptr

class TestableTripService : public TripService {
public:
    explicit TestableTripService(User *loggedUser, TripDAO * tripDAO) : loggedUser(loggedUser), tripDAO(tripDAO) {}

    User *getLoggedUser() const override {
        return loggedUser;
    }

    list<Trip> getTripList(User *user) const override {
        return user->Trips();
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

class TripServiceShould : public ::testing::Test {
protected:
    User *loggedUser = new User(FIRST_USER_ID);
    User *anotherUser = new User(SECOND_USER_ID);
    Trip tripToBrazil = Trip("Brazil");
    Trip tripToLondon = Trip("London");
    TripDAO * tripDAO = new TripDAOMock();
    list<Trip> tripsByUser = { tripToBrazil, tripToLondon };
    TripService *tripService = new TestableTripService(loggedUser, tripDAO);

    void SetUp() override {
        anotherUser->AddTrip(tripToBrazil);
        anotherUser->AddTrip(tripToLondon);
    }

    void TearDown() override {
        delete loggedUser;
        delete anotherUser;
        delete tripDAO;
    }
};

TEST_F(TripServiceShould, validate_the_logged_in_user)
{
    TripService * tripService = new TestableTripService(GUEST, new TripDAOMock);

    EXPECT_THROW(tripService->GetTripsByUser(anotherUser), const char *);
}

TEST_F(TripServiceShould, return_no_trips_when_users_are_not_friends)
{
    auto trips = tripService->GetTripsByUser(anotherUser);

    EXPECT_TRUE(trips.empty());
}

TEST_F(TripServiceShould, return_trips_when_users_are_friends)
{
    anotherUser->AddFriend(*loggedUser);

    try {
        auto trips = tripService->GetTripsByUser(anotherUser);
        EXPECT_THAT(trips, ::testing::Contains(tripToLondon));
        EXPECT_THAT(trips, ::testing::Contains(tripToBrazil));
        EXPECT_EQ(trips.size(), 2);
    } catch (const char * exception) {
        FAIL() << exception;
    }
}