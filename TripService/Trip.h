#ifndef TRIP_H
#define TRIP_H

class Trip
{
public:
    explicit Trip(const char *destination) : destination(destination) {}

    bool operator==(const Trip &rhs) const {
        return destination == rhs.destination;
    }

    bool operator!=(const Trip &rhs) const {
        return !(rhs == *this);
    }

private:
    const char * destination;
};

#endif