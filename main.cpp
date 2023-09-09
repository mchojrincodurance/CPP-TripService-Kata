#include "TripService/TripService.h"
#include "TripService/User.h"
#include <gtest/gtest.h>

class TestableTripService : public TripService {
public:
    User *getLoggedUser() const override {
        return nullptr;
    }
};

TEST(TripServiceShould, do_something)
{
    auto *tripService = new TestableTripService;
    tripService->GetTripsByUser(nullptr);
}