#include <Scorer.h>
#include <Parameters.h>
#include <Chromosome.h>
#include <Vehicle.h>
#include <numeric>
#include <algorithm>

Scorer::Scorer(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> allRides) :
    R(R),
    C(C),
    F(F),
    N(N),
    B(B),
    T(T),
    allRides(allRides)
{
}

Scorer::Scorer(const Parameters &params) :
    Scorer(
            params.R,
            params.C,
            params.F,
            params.N,
            params.B,
            params.T,
            params.allRides
          )
{
}

unsigned Scorer::getFitness(const Chromosome &chromosome) const
{
    std::vector<std::vector<Ride>> vehicleAllocationTable(makeVehicleTable(chromosome.getData()));

    unsigned fitness = 0;
    for(const auto &ridesAllottedToVehicle : vehicleAllocationTable)
    {
        Vehicle vehicle(ridesAllottedToVehicle, T);
        vehicle.runSimulation();
        fitness += getScore(vehicle.getLateCompletedRides(), vehicle.getTimelyRides());
    }
    return fitness;
}

unsigned Scorer::getScore(const std::vector<Ride> &lateCompletedRides, const std::vector<Ride> &timelyRides) const
{
    std::vector<unsigned> lateScores;
    std::vector<unsigned> timelyScores;
    const auto getDistance = [](const Ride &ride){return ride.distance();};
    std::transform(lateCompletedRides.begin(), lateCompletedRides.end(), std::back_inserter(lateScores), getDistance);
    std::transform(timelyRides.begin(), timelyRides.end(), std::back_inserter(timelyScores), getDistance);
    
    // TODO: C++17 it and use std::reduce
    return (std::accumulate(lateScores.begin(), lateScores.end(), 0) +
            std::accumulate(timelyScores.begin(), timelyScores.end(), 0) +
            timelyScores.size()*B);
}

std::vector<std::vector<Ride>> Scorer::makeVehicleTable(const std::vector<std::vector<unsigned>> bucketsOfIndices) const
{
    std::vector<std::vector<Ride>> vehicleTable;
    vehicleTable.reserve(F);
    std::transform(bucketsOfIndices.begin(),
            bucketsOfIndices.end(),
            std::back_inserter(vehicleTable),
            [&](const std::vector<unsigned> &bucketOfIndices)
            {
                std::vector<Ride> rides;
                rides.reserve(bucketOfIndices.size());
                std::transform(bucketOfIndices.begin(),
                        bucketOfIndices.end(),
                        std::back_inserter(rides),
                        [&](const unsigned &index) {return allRides[index];});
                return rides;
            });
    return vehicleTable;
}

std::vector<std::vector<Ride>> Scorer::assignmentToSetOfRideLists(const std::vector<unsigned> assignment) const
{
    std::vector<std::vector<Ride>> partitionOfRides(F);
    for(unsigned rideNumber = 0; rideNumber < assignment.size(); ++rideNumber)
    {
        partitionOfRides[assignment[rideNumber]].push_back(allRides[rideNumber]);
    }
    return partitionOfRides;
}    
