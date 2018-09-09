#include <Vehicle.h>
#include <Ride.h>
#include <Coordinate.h>

Vehicle::Vehicle(unsigned &currentTime) :
    currentTime(currentTime),
    freeTime(currentTime)
{
}

Ride Vehicle::getLastRide() const
{
    return rides.back();
}

void Vehicle::assignRide(Ride ride)
{
    freeTime = std::min(ride.earliestStart, currentTime + dist(getLastRide().endPosition, ride.startPosition)) + ride.distance();
    rides.push_back(ride);
}

bool Vehicle::isFree() const
{
    return freeTime >= currentTime;
}

bool Vehicle::canComplete(const Ride &ride) const
{
    return freeTime + dist(getLastRide().endPosition, ride.startPosition) + ride.distance() <= ride.latestFinish;
}

bool Vehicle::canCompleteWithBonus(const Ride &ride) const
{
    return freeTime <= ride.earliestStart;
}

std::vector<Ride> Vehicle::getRideList() const
{
    return rides;
}
