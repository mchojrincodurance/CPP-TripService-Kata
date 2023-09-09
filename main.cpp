#include "TripService/TripService.h"
#include "TripService/User.h"
#include <gtest/gtest.h>

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