#include <Vehicle.h>
#include <Ride.h>
#include <Coordinate.h>
#include <stdexcept>

Vehicle::Vehicle() :
    freeTime(0)
{
}

Ride Vehicle::getLastRide() const
{
    if(rides.empty())
        throw std::logic_error("No rides have yet been assigned");
    return rides.back();
}

Coordinate Vehicle::getDepartureLocation() const
{
    return rides.empty() ? Coordinate{0,0} : getLastRide().endPosition;
}

void Vehicle::assignRide(Ride ride, const unsigned &currentTime)
{
    freeTime = std::max(ride.earliestStart, currentTime + dist(getDepartureLocation(), ride.startPosition)) + ride.distance();
    rides.push_back(ride);
}

bool Vehicle::isFree(const unsigned &currentTime) const
{
    return freeTime <= currentTime;
}

bool Vehicle::canComplete(const Ride &ride) const
{
    return freeTime + dist(getDepartureLocation(), ride.startPosition) + ride.distance() <= ride.latestFinish;
}

bool Vehicle::canCompleteWithBonus(const Ride &ride) const
{
    return freeTime + dist(getDepartureLocation(), ride.startPosition) <= ride.earliestStart;
}

std::vector<Ride> Vehicle::getRideList() const
{
    return rides;
}
