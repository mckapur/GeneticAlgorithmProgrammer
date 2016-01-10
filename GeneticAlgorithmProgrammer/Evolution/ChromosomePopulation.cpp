//
//  ChromosomePopulation.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "ChromosomePopulation.hpp"
#include "ChromosomePopulationProcesses.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>

#pragma mark - Init

void ChromosomePopulation::randomlyFillPopulation() {
    for (int i = (int)(memberPool.size() - 1); i < constants::CHROMOSOME_POPULATION_POOL_SIZE; i++)
        memberPool.push_back(ChromosomePopulationProcesses::generateRandomChromosome((int)goal.length()));
}

void ChromosomePopulation::killExcessPopulation() {
    sortMembersByFitness();
    unsigned long size = memberPool.size();
    for (unsigned long i = size; i--;) {
        if (i >= constants::CHROMOSOME_POPULATION_POOL_SIZE) { // Need to retain diversity
            unsigned long iteration = memberPool.size() / 10 + rand() % (memberPool.size() / 10);
            memberPool.erase(memberPool.begin() + (iteration - 2), memberPool.begin() + (iteration - 1)); // TODO: Double check
        }
        else
            break;
    }
}

ChromosomePopulation::ChromosomePopulation() {
    generationIndex = 0;
    goalReached = false;
}

ChromosomePopulation::ChromosomePopulation(std::vector<Chromosome> _memberPool, std::string _goal) {
    ChromosomePopulation();
    goal = _goal;
    fitnessHeuristic = FitnessHeuristic(Interpreter(), goal);
    memberPool = _memberPool;
    if (memberPool.size() != constants::CHROMOSOME_POPULATION_POOL_SIZE) {
        randomlyFillPopulation();
    }
}

#pragma mark - Natural Selection & Generation Advancement

void ChromosomePopulation::computeMemberFitnesses() {
    unsigned long length = memberPool.size();
    for (int i = 0; i < length; i++) {
        Chromosome chromosome = memberPool[i];
        chromosome.fitness = fitnessHeuristic.fitnessForChromosome(chromosome, constants::PREFERRED_FITNESS_FUNCTION);
        chromosome.output = fitnessHeuristic.outputForChromosome(chromosome);
        memberPool[i] = chromosome;
    }
}

void ChromosomePopulation::sortMembersByFitness() {
    computeMemberFitnesses();
    std::sort(std::begin(memberPool), std::end(memberPool), compareChromosomeOnFitness);
}

Chromosome ChromosomePopulation::evolve() {
    performNaturalSelection();
    return memberPool[0];
}

/**
 Steps in natural selection:
 1. Sort members by fitness (descending order, smaller = better)
 2. Extract fittest Pk percent of members that survive, denote as k members
 3. Place these children in a new population pool
 4. Extract Pj percent of members that compete for survival, Pj >> Pk, denote as j members
 5. Determine their survival with respect to mating probability Pma
 6. Mate (j*Pma)-1 pairs of (j+k)*Pma members randomly
 7. Place these children in the new population pool
 8. Kill off other unfit children: 1-(Pk+Pj) percent
 9. Select Pmu percent of members in the new pool to mutate (addition, subtraction, or modification is chosen)
 10. If there is space in the pool, fill it with randomly generated new chromosomes
 11. Advance generation
 */
void ChromosomePopulation::performNaturalSelection() {
    while (advanceGeneration()) {
        int numberSurvived = constants::CHROMOSOME_POPULATION_SURVIVE_RATE * memberPool.size();
        int numberCompeting = constants::CHROMOSOME_POPULATION_COMPETITION_RATE * memberPool.size();
        std::vector<Chromosome> newMemberPool;
        std::vector<Chromosome> competitors;
        for (int i = 0; i < (numberSurvived + numberCompeting); i++) {
            if (i < numberSurvived)
                newMemberPool.push_back(memberPool[i]);
            else
                competitors.push_back(memberPool[i]);
        }
        std::vector<Chromosome> competitorsAndSurvivors;
        competitorsAndSurvivors.insert(competitorsAndSurvivors.end(), newMemberPool.begin(), newMemberPool.end());
        competitorsAndSurvivors.insert(competitorsAndSurvivors.end(), competitors.begin(), competitors.end());
        for (int i = 0; i < numberSurvived - 1; i++) {
            double randomValue = ((double)random()/(RAND_MAX));
            if (randomValue <= constants::CHROMOSOME_POPULATION_MATE_PROBABILITY) { // Idea of competition due to probability here
                std::vector<Chromosome> children = ChromosomePopulationProcesses::mateChromosomes(newMemberPool[i], newMemberPool[(int)(randomValue*newMemberPool.size())]);
                newMemberPool.insert(newMemberPool.end(), children.begin(), children.end());
            }
        }
        for (int i = 0; i < numberCompeting - 1; i++) {
            double randomValue = ((double)random()/(RAND_MAX));
            if (randomValue <= constants::CHROMOSOME_POPULATION_MATE_PROBABILITY) { // Idea of competition due to probability here
                std::vector<Chromosome> children = ChromosomePopulationProcesses::mateChromosomes(competitors[i], competitorsAndSurvivors[(int)(randomValue*competitorsAndSurvivors.size())]);
                newMemberPool.insert(newMemberPool.end(), children.begin(), children.end());
            }
        }
        for (int i = 0; i < newMemberPool.size(); i++)
            newMemberPool[i] = ChromosomePopulationProcesses::randomlyMutateChromosome(newMemberPool[i]);
        memberPool = newMemberPool;
        killExcessPopulation();
        randomlyFillPopulation();
    }
    sortMembersByFitness();
}

bool ChromosomePopulation::advanceGeneration() {
    sortMembersByFitness();
    bool shouldAdvance = true;
    generationIndex++;
    if (!memberPool[0].fitness) {
        goalReached = true;
        shouldAdvance = false;
        std::cout << "Goal Reached at Generation " << generationIndex + 1 << " -> " << memberPool[0].genome << "\n";
    }
    if ((generationIndex + 1) >= constants::MAX_POPULATION_POOL_GENERATIONS) {
        shouldAdvance = false;
        std::cout << "Terminating: max. number of evolutions reached.\n";
    }
    if (constants::IS_DEBUGGING_MODE)
        std::cout << "======================\n" << "Generation Index: " << generationIndex << "\nLowest Fitness: " << memberPool[0].fitness << "\nBest Genome: " << memberPool[0].genome << "\nRespective Output: " << memberPool[0].output << "\n" << memberPool.size() << " Members\n";
    return shouldAdvance;
}
