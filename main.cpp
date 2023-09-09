#include "TripService/TripService.h"
#include "TripService/User.h"
#include <gtest/gtest.h>

class TestableTripService : public TripService {
public:
    User *getLoggedUser() const override {
        return nullptr;
    }
};

TEST(TripServiceShould, validate_the_logged_in_user)
{
    auto *tripService = new TestableTripService;
    EXPECT_THROW(tripService->GetTripsByUser(nullptr), const char *);
}