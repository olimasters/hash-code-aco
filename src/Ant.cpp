#include <Ant.h>
#include <Vehicle.h>
#include <PheremoneTrail.h>
#include <Utils.h>
#include <random>
#include <algorithm>

Ant::Ant(const std::vector<Ride> &ridesToComplete, double pheremoneWeighting, const std::vector<std::vector<double>> &pheremoneMatrix, unsigned T, unsigned F, unsigned B) :
    T(T),
    B(B),
    score(0),
    currentTime(0),
    ridesToComplete(ridesToComplete),
    pheremoneWeighting(pheremoneWeighting),
    pheremoneMatrix(pheremoneMatrix),
    rng(std::random_device{}())
{
    fleet.reserve(F);
    std::generate_n(std::back_inserter(fleet), F, [&](){return Vehicle(currentTime);});
}

unsigned Ant::getScore() const
{
    return score;
}

Solution Ant::getSolution() const
{
    Solution solution;
    std::transform(fleet.begin(), fleet.end(), std::back_inserter(solution), [](const Vehicle &vehicle){return vehicle.getRideList();});
    return solution;
}

std::vector<Vehicle> Ant::getFreeVehicles() const
{
    std::vector<Vehicle> freeVehicles;
    std::copy_if(fleet.begin(), fleet.end(), std::back_inserter(freeVehicles), [](const Vehicle &vehicle){return vehicle.isFree();});
    return freeVehicles;
}

std::vector<double> Ant::getProbabilities(const Vehicle &vehicle, const std::vector<Ride> &rideChoices) const
{
    unsigned indexOfPreviousRide = vehicle.getLastRide().index;
    std::vector<double> probabilities;

    for(unsigned i = 0; i < rideChoices.size(); ++i)
    {
        double pheremoneQuantity = pheremoneMatrix[indexOfPreviousRide][rideChoices[i].index];
        double scoreFromRide = rideChoices[i].distance() + B * vehicle.canCompleteWithBonus(rideChoices[i]);
        probabilities[i] = pheremoneQuantity * scoreFromRide;
    }
    normalise(probabilities); // Make their sum equal to 1
    return probabilities;
}

// Get all of the rides that the vehicle could possibly complete if it embarked upon them now
std::vector<Ride> Ant::getPossibleRides(const Vehicle &vehicle, const std::vector<Ride> &ridesToChooseFrom)
{
    std::vector<Ride> possibleRides;
    std::copy_if(ridesToChooseFrom.begin(),
            ridesToChooseFrom.end(),
            std::back_inserter(possibleRides),
            [&vehicle](const Ride &ride){return vehicle.canComplete(ride);}
            );
    return possibleRides;
}

void Ant::walkToSolution()
{
    std::vector<Ride> remainingRides{ridesToComplete};
    for(unsigned currentTime = 0; currentTime < T && !remainingRides.empty(); ++currentTime)
    {
        std::vector<Vehicle> freeVehicles{getFreeVehicles()};
        for(auto &vehicle : freeVehicles)
        {
            std::vector<Ride> possibleRides{getPossibleRides(vehicle, remainingRides)}; // exclude those which cannot be completed in time

            if(possibleRides.empty())
                continue; // This vehicle's henceforth useless if we're in here -- just let it stew

            std::vector<double> probabilitiesOfPickingRides{getProbabilities(vehicle, remainingRides)};
            Ride assignedRide = pickRide(probabilitiesOfPickingRides, possibleRides);
            remainingRides.erase(
                    std::remove_if(
                        remainingRides.begin(),
                        remainingRides.end(),
                        [&](const Ride &ride){return ride.index == assignedRide.index;}),
                    remainingRides.end());

            pheremoneTrail.push_back(std::pair<unsigned, unsigned>{vehicle.getLastRide().index, assignedRide.index});

            score += assignedRide.distance();
            if(vehicle.canCompleteWithBonus(assignedRide))
                score += B;

            vehicle.assignRide(assignedRide);
        }
    }
}

PheremoneTrail Ant::getPheremoneTrail() const
{
    return pheremoneTrail;
}

Ride Ant::pickRide(const std::vector<double> &probabilitiesOfPickingRides, const std::vector<Ride> &possibleRides)
{
    std::discrete_distribution distribution(probabilitiesOfPickingRides.begin(), probabilitiesOfPickingRides.end());
    unsigned indexWithinPossibleRidesVector = distribution(rng);
    return possibleRides[indexWithinPossibleRidesVector];
}
