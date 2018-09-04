#include <Ant.h>

Ant::Ant(const std::vector<Ride> &ridesToComplete, double pheremoneWeighting, const std::vector<std::vector<double>> &pheremoneMatrix) :
    T(T),
    F(F),
    B(B),
    fleet(F)
    currentTime(currentTime),
    ridesToComplete(ridesToComplete),
    pheremoneWeighting(pheremoneWeighting),
    pheremoneMatrix(pheremoneMatrix),
{
}

unsigned Ant::getScore() const
{
}

Solution Ant::getSolution() const
{
}

std::vector<Vehicle> getFreeVehicles() const
{
    std::vector<Vehicle> freeVehicles;
    std::copy_if(ridesToComplete.begin(), ridesToComplete.end(), std::back_inserter(freeVehicles), [](const Vehicle &vehicle){return vehicle.isFree();});
    return freeVehicles;
}

std::vector<double> getProbabilities(unsigned indexOfPreviousRide, const std::vector<Ride> rideChoices)
{
    std::vector<double> probabilities;

    for(unsigned i = 0; i < rideChoices.size(); ++i)
    {
        double pheremoneQuantity = pheremoneMatrix[indexOfPreviousRide][rideChoices[i].index];
        double scoreFromRide = ride.distance() + B;
        probabilities[i] = pheremoneQuantity * scoreFromRide;
    }
    normalise(probabilities); // Make their sum equal to 1
    return probabilities;
}

bool Ant::isPossible(const Vehicle &vehicle, const Ride &ride)
{
    // TODO: weak or strict?
    return dist(vehicle.getPosition(), ride.startPosition) + dist(ride.startPosition, endPosition) < currentTime + ride.latestFinish;
}

// Get all of the rides that the vehicle could possibly complete if it embarked upon them now
std::vector<Ride> Ant::getPossibleRides(const Vehicle &vehicle, const std::vector<Ride> &ridesToChooseFrom)
{
    std::vector<Ride> possibleRides;
    std::copy_if(ridesToChooseFrom.begin(),
            ridesToChooseFrom.end(),
            std::back_inserter(possibleRides),
            [&vehicle](const Ride &ride){return isPossible(vehicle, ride);}
            );
    return possibleRides;
}

void Ant::walkToSolution()
{
    std::vector<Ride> remainingRides{ridesToComplete};
    for(unsigned currentTime = 0; currentTime < T; ++currentTime)
    {
        std::vector<Vehicle> freeVehicles{getFreeVehicles()};
        for(const auto &vehicle : freeVehicles)
        {
            std::vector<Ride> possibleRides{getPossibleRides(vehicle, remainingRides)}; // exclude those which cannot be completed in time
            std::vector<double> probabilitiesOfPickingRides{getProbabilities(vehicle.getLastRide().index, remainingRides)};
            Ride assignedRide = pickRide(probabilitiesOfPickingRides, possibleRides);
            // TODO: continue here, probably remove assignedRide from remainingRides
        }
    }
}

Ride Ant::pickRide(const std::vector<double> &probabilitiesOfPickingRides, const std::vector<Ride> &possibleRides)
{
    std::discrete_distribution distribution(probabilitiesOfPickingRides.begin(), probabilitiesOfPickingRides.end());
    unsigned indexWithinPossibleRidesVector = distribution(generator);
    return possibleRides[indexWithinPossibleRidesVector];
}
