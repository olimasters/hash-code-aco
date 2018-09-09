#ifndef ANT_H
#define ANT_H

#include <Solution.h>
#include <Ride.h>
#include <Vehicle.h>
#include <PheremoneTrail.h>
#include <random>
#include <vector>

class Ant
{
    public:
        Ant(const std::vector<Ride> &ridesToComplete, double pheremoneWeighting, const std::vector<std::vector<double>> &pheremoneMatrix, unsigned T, unsigned F, unsigned B);
        void walkToSolution();
        Solution getSolution() const;
        PheremoneTrail getPheremoneTrail() const;
        unsigned getScore() const;

    private:
        std::vector<Vehicle> getFreeVehicles() const;
        std::vector<Ride> getPossibleRides(const Vehicle &vehicle, const std::vector<Ride> &ridesToChooseFrom);
        Ride pickRide(const std::vector<double> &probabilitiesOfPickingRides, const std::vector<Ride> &possibleRides);
        std::vector<double> getProbabilities(const Vehicle &vehicle, const std::vector<Ride> &rideChoices) const;
        // TODO: fix this, if it needs to know about all this stuff then wrap it up into a Parameters struct
        unsigned T;
        unsigned B;

        unsigned score;
        unsigned currentTime;
        std::vector<Vehicle> fleet;
        const std::vector<Ride> &ridesToComplete;
        double pheremoneWeighting;
        PheremoneTrail pheremoneTrail;
        const std::vector<std::vector<double>> &pheremoneMatrix;
        std::mt19937 rng;
};

#endif
