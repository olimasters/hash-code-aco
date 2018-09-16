#ifndef VEHICLE_H
#define VEHICLE_H
#include <Ride.h>
#include <vector>
class Vehicle
{
    public:
        Vehicle();
        Ride getLastRide() const;
        bool canComplete(const Ride &ride) const;
        bool canCompleteWithBonus(const Ride &ride) const;
        bool isFree(const unsigned &currentTime) const;
        void assignRide(Ride ride, const unsigned &currentTime);
        std::vector<Ride> getRideList() const;
    private:
        Coordinate getDepartureLocation() const;
        std::vector<Ride> rides;
        unsigned freeTime; // Time at which this vehicle will become free
};
#endif
