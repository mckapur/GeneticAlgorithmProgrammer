//
//  ChromosomePopulationProcesses.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "ChromosomePopulationProcesses.hpp"
#include "Constants.h"

#include <cstdlib>
#include <iostream>

#pragma mark - Evolution Methods

// TODO: Look at all non (32, 127) ASCII values, too!
// TODO: Limit state space / use specific state space for specific interpreting language?
// TODO: Look properly at random value [rand()] bounds/range implications

Chromosome ChromosomePopulationProcesses::generateRandomChromosome(int preferredLength) {
    std::string genome;
    for (int i = 0; i < preferredLength; i++) {
        genome.push_back(rand() % 96 + 32);
    }
    return Chromosome(genome);
}

std::vector<Chromosome> ChromosomePopulationProcesses::mateChromosomes(Chromosome chromosome1, Chromosome chromosome2) {
    std::vector<Chromosome> children;
    std::string parentGenome1 = chromosome1.genome;
    std::string parentGenome2 = chromosome2.genome;
    // Crossover
    std::string childGenome1 = parentGenome1.substr(0, (parentGenome1.size() / 2)).append(parentGenome2.substr(parentGenome2.size() / 2, parentGenome2.size() - 1));
    std::string childGenome2 = parentGenome2.substr(0, (parentGenome2.size() / 2)).append(parentGenome1.substr(parentGenome1.size() / 2, parentGenome1.size() - 1));
    children.push_back(Chromosome(childGenome1));
    children.push_back(Chromosome(childGenome2));
    return children;
}

Chromosome ChromosomePopulationProcesses::randomlyMutateChromosome(Chromosome chromosome) {
    double randomState = ((double)rand()/(RAND_MAX));
    if (randomState > constants::POPULATION_POOL_MUTATE_PROBABILITY)
        return chromosome; // Random state says no to mutation
    randomState = ((double)rand()/(RAND_MAX)); // Reassign for next random interactions
    std::string genome = chromosome.genome;
    // TODO: Look over the accuracy of this code, and look over if addition/subtraction is a good idea
    if (randomState <= constants::POPULATION_POOL_MUTATE_ADDITION_PROBABILITY) { // Add a character
        if (genome.size() < 2)
            genome.push_back(rand() % 96 + 32); // Correct ASCII range
        else
            genome.push_back(genome[rand() % genome.size()]); // Mutation-by-addition replicates a random character
    }
    else if (randomState <= constants::POPULATION_POOL_MUTATE_SUBTRACTION_PROBABILITY + constants::POPULATION_POOL_MUTATE_ADDITION_PROBABILITY && genome.size()) { // Remove a character
        genome.erase(rand() % genome.size(), 1);
    }
    else if (randomState >= constants::POPULATION_POOL_MUTATE_SUBTRACTION_PROBABILITY + constants::POPULATION_POOL_MUTATE_ADDITION_PROBABILITY && genome.size()) { // Modify a character
        int randomIndex = rand() % genome.size();
        double directionProbability = ((double)rand()/(RAND_MAX));
        int direction = 1;
        if ((genome[randomIndex] > 32 && directionProbability < 0.5) || genome[randomIndex] == 127)
            direction = -1;
        genome[randomIndex] = genome[randomIndex] + direction;
    }
    chromosome.genome = genome;
    return chromosome;
}