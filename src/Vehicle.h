#ifndef VEHICLE_H
#define VEHICLE_H
#include <Ride.h>
#include <vector>
class Vehicle
{
    public:
        Vehicle(unsigned &currentTime);
        bool canComplete(const Ride &ride) const;
        bool canCompleteWithBonus(const Ride &ride) const;
        bool isFree() const;
        void assignRide(Ride ride);
        Ride getLastRide() const;
        std::vector<Ride> getRideList() const;
    private:
        Coordinate getDepartureLocation() const;
        std::vector<Ride> rides;
        unsigned &currentTime;
        unsigned freeTime; // Time at which this vehicle will become free
};
#endif
