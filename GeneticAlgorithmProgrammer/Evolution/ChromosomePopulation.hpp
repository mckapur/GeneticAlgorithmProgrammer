//
//  ChromosomePopulation.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef ChromosomePopulation_cpp
#define ChromosomePopulation_cpp

#include <stdio.h>
#include <vector>

#include "GoalState.hpp"
#include "Constants.h"
#include "Chromosome.hpp"
#include "FitnessFunction.hpp"

/*
 A chromosome population is a population
 of chromosomes within some given generation
 or arbitrary time frame / index. The population
 deals with the spawning, mating, and killing
 (via natural selection) of chromosomes in its
 member pool. The population is constantly changing
 and derived from the fittest of the previous.
 */
class ChromosomePopulation {
    private:
        bool goalReached; // A flag that returns true if one of the chromosomes in its population pool has a fitness of 0
        FitnessFunction fitnessFunction; // The fitness function that this population will utilize for natural selection
        bool static compareChromosomeOnFitness(const Chromosome& a, const Chromosome& b) { // Compare two chromosomes based on their fitness (smaller fitness gets beats greater fitness)
            return a.fitness < b.fitness;
        }
        void killExcessPopulation(); // Kills the least fittest members in the memberPool (population) to fit the set constant population size
        void randomlyFillPopulation(); // Fills the memberPool (population) with randomly generated chromosomes
        void computeMemberFitnesses(); // Compute the fitness score for each chromosome in the member population pool
        void sortMembersByFitness(); // The natural selection process involves sorting members by their fitness, killing unfit chromosomes, and evolving
        void performNaturalSelection(); // The natural selection process involves sorting members by their fitness, killing unfit chromosomes, and evolving
        bool advanceGeneration(); // Advance the population into the next generation. Returns true if the generation advanced and natural selection should occur, returns false if the evolution should terminate.
    public:
        std::vector<Chromosome> memberPool; // The array of chromosomes members in the population pool
        std::vector<GoalState> goalStates; // The goal is the optimal state for a chromosome, and has a fitness score of 0
        unsigned long generationIndex; // The number of evolutions that caused this population pool

        ChromosomePopulation(); // Default initializer
        ChromosomePopulation(std::vector<Chromosome> _memberPool, std::vector<GoalState> goalStates); // Initializer in which you specify the pool's initial members (may be empty) and goal
    
        Chromosome evolve(); // Begin evolution by initiating first round of natural selection, return optimum chromosome
};

#endif /* ChrosomePopulation_cpp */
