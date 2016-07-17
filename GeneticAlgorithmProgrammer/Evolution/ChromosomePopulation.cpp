//
//  ChromosomePopulation.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "BrainfuckInterpreter.hpp"
#include "ChromosomePopulation.hpp"
#include "ChromosomePopulationProcesses.hpp"
#include "FitnessBaselineScoringSystemStringToStringSimilaritySE.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <math.h>

#pragma mark - Init

void ChromosomePopulation::randomlyFillPopulation() {
    for (int i = (int)(memberPool.size()); i < constants::CHROMOSOME_POPULATION_POOL_SIZE; i++)
        memberPool.push_back(ChromosomePopulationProcesses::generateRandomChromosome(fitnessFunction.languageInterpreter->charset(), 10));
}

void ChromosomePopulation::killExcessPopulation() {
    sortMembersByFitness();
    unsigned long size = memberPool.size();
    for (unsigned long i = size; i--;) {
        if (i >= constants::CHROMOSOME_POPULATION_POOL_SIZE)
            memberPool.erase(memberPool.begin() + i); // TODO: Double check
        else
            break;
    }
}

ChromosomePopulation::ChromosomePopulation() {
    generationIndex = 0;
    goalReached = false;
}

ChromosomePopulation::ChromosomePopulation(std::vector<Chromosome> _memberPool, std::vector<GoalState> _goalStates) {
    ChromosomePopulation();
    goalStates = _goalStates;
    memberPool = _memberPool;
    /* Setup Fitness Function */
    FitnessBaselineScoringSystem *scoringSystem;
    switch (constants::PREFERRED_SCORING_SYSTEM) {
        case constants::FitnessBaselineScoringSystemTypeStringToStringSimilarityScoring:
            switch (constants::PREFERRED_STRING_SIMILARITY_SCORING_FUNCTION) {
                case constants::FitnessBaselineScoringSystemTypeStringToStringSimilarityScoringTypeSE:
                    scoringSystem = new FitnessBaselineScoringSystemStringToStringSimilaritySE();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    Interpreter *interpreter;
    switch (constants::PREFERRED_LANGUAGE_INTERPRETER) {
        case constants::IntrepreterLanguageTypeBrainfuck:
            interpreter = new BrainfuckInterpreter();
            break;
        default:
            break;
    }
    fitnessFunction = FitnessFunction(interpreter, scoringSystem, TrainingSet(goalStates, constants::TRAINING_SET_VALIDATION_PARTITION));
    /* Fill population pool */
    if (memberPool.size() != constants::CHROMOSOME_POPULATION_POOL_SIZE)
        randomlyFillPopulation();
}

#pragma mark - Natural Selection & Generation Advancement

void ChromosomePopulation::computeMemberFitnesses() {
    fitnessFunction.prepareToScore(memberPool);
    memberPool = fitnessFunction.scoreChromosomes();
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
 3. Place these children in a new population pool, mate them with each other randomly
 4. Extract Pj percent of members that compete for survival, Pj >> Pk, denote as j members
 5. Determine their survival with respect to mating probability Pma
 6. Mate (j*Pma)-1 pairs of (j+k)*Pma members randomly
 7. Place these children in the new population pool
 8. Kill off other unfit children: 1-(Pk+Pj) percent
 9. Select Pmu percent of members in the new pool to mutate (addition, subtraction, or modification is chosen)
 10. If there is space in the pool, fill it with randomly generated new chromosomes
 11. Kill any excess members (sorted by fitness) in the pool
 12. Advance generation and repeat steps
 */
void ChromosomePopulation::performNaturalSelection() {
    while (advanceGeneration()) {
        int numberSurvived = constants::CHROMOSOME_POPULATION_SURVIVE_RATE * constants::CHROMOSOME_POPULATION_POOL_SIZE;
        int numberCompeting = constants::CHROMOSOME_POPULATION_COMPETITION_RATE * constants::CHROMOSOME_POPULATION_POOL_SIZE;
        std::vector<Chromosome> newMemberPool;
        std::vector<Chromosome> competitors;
        for (int i = 0; i < (numberSurvived + numberCompeting); i++) {
            if (i < numberSurvived)
                newMemberPool.push_back(memberPool[i]);
            else
                competitors.push_back(memberPool[i]);
        }
        std::vector<Chromosome> competitorsAndSurvivors;
        competitorsAndSurvivors.insert(competitorsAndSurvivors.begin(), newMemberPool.begin(), newMemberPool.end());
        competitorsAndSurvivors.insert(competitorsAndSurvivors.end(), competitors.begin(), competitors.end());
        for (int i = 0; i < numberSurvived - 1; i++) {
            double randomValue = ((double)random()/(RAND_MAX));
            if (randomValue <= constants::CHROMOSOME_POPULATION_MATE_PROBABILITY) {
                std::vector<Chromosome> children = ChromosomePopulationProcesses::mateChromosomes(fitnessFunction.languageInterpreter->charset(), newMemberPool[i], newMemberPool[(int)(randomValue*newMemberPool.size())]);
                newMemberPool.insert(newMemberPool.end(), children.begin(), children.end());
            }
        }
        for (int i = 0; i < numberCompeting - 1; i++) {
            double randomValue = ((double)random()/(RAND_MAX));
            if (randomValue <= constants::CHROMOSOME_POPULATION_MATE_PROBABILITY) { // Idea of competition due to probability here
                std::vector<Chromosome> children = ChromosomePopulationProcesses::mateChromosomes(fitnessFunction.languageInterpreter->charset(), competitors[i], competitorsAndSurvivors[(int)(randomValue*competitorsAndSurvivors.size())]);
                newMemberPool.insert(newMemberPool.end(), children.begin(), children.end());
            }
        }
        for (int i = 0; i < newMemberPool.size(); i++)
            newMemberPool[i] = ChromosomePopulationProcesses::randomlyMutateChromosome(fitnessFunction.languageInterpreter->charset(), newMemberPool[i]);
        memberPool = newMemberPool;
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
        std::cout << "======================\n" << "Generation Index: " << generationIndex << "\nLowest Fitness: " << memberPool[0].fitness << "\nBest Genome: " << memberPool[0].genome << (goalStates.size() == 1 ? ("\nRespective Output: " + fitnessFunction.languageInterpreter->outputFromProgram(memberPool[0].genome, goalStates[0].inputs)) : "") << "\n" << memberPool.size() << " Members\n";
    return shouldAdvance;
}
