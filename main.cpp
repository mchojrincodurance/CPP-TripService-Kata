#include "TripService/TripService.h"
#include "TripService/User.h"
#include <gtest/gtest.h>

#define A_USER_ID 1

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

TEST(TripServiceShould, do_something_with_logged_in_user)
{
    User *loggedUser = new User(A_USER_ID);
    auto *tripService = new TestableTripService(loggedUser);
    EXPECT_THROW(tripService->GetTripsByUser(nullptr), const char *);
}