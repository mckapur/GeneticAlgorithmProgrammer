//
//  BrainUnit.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 13/11/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "FitnessFunction.hpp"
#include "BrainUnit.hpp"
#include "BrainfuckInterpreter.hpp"
#include "FitnessBaselineScoringSystemStringToStringSimilaritySE.hpp"

#include <math.h>
#include <iostream>
#include <fstream>
#include <iterator>

// TODO: In current dir and constants file
std::string BRAIN_UNIT_SAVE_FILE_PATH = "/Users/rohankapur/Library/GA_BrainUnit_Data.txt";

#pragma mark - Init

BrainUnit::BrainUnit() {
    if (constants::IS_PERSISTANCE_MODE)
        load();
}

#pragma mark - Saving and Loading

void BrainUnit::clear() {
    // TODO: Clear saved data
    std::ofstream os(BRAIN_UNIT_SAVE_FILE_PATH, std::ios::binary | std::ofstream::out | std::ofstream::trunc);
    os.close();
}

void BrainUnit::save() {
    clear();
    std::ofstream os(BRAIN_UNIT_SAVE_FILE_PATH, std::ios::binary);
    for (int i = 0; i < memories.size(); i++) {
        os << memories[i].toString();
        os << "\n";
    }
    os.close();
}

void BrainUnit::printMemories() {
    for (int i = 0; i < memories.size(); i++)
        std::cout << memories[i].toString() << "\n";
}

void BrainUnit::load() {
    std::vector<Memory> _memories;
    std::ifstream is(BRAIN_UNIT_SAVE_FILE_PATH, std::ios::binary);
    std::string encodedMemory;
    while (std::getline(is, encodedMemory))
        _memories.push_back(Memory(encodedMemory));
    memories = _memories;
}

#pragma mark - Population Derivation

bool static compareMemoriesOnSimilarity(const Memory& a, const Memory& b) { // Compare two memories based on their similarity
    return a.tentativeSimilarity < b.tentativeSimilarity;
}

bool static compareMemoriesOnSimilarityAndFoundationIndex(const Memory& a, const Memory& b) { // Compare two memories based on their similarity and foundation index
    return (a.foundationIndex/a.tentativeSimilarity) < (a.foundationIndex/b.tentativeSimilarity);
}

std::vector<Chromosome> BrainUnit::derivePopulation(std::string output) {
    if (!constants::IS_PERSISTANCE_MODE)
        return std::vector<Chromosome>();
    // TODO: What about inputs? Store inputs in brain unit!
    // TODO: Properly check over effectiveness & function of following process:
    /*
     Steps:
     1. Compute tentative similarity between each memory and the respective output
     2. Sort memories by this similarity and extract 15% to use as derivation resources
     3. Sort these filtered memories by similarity AND memory foundation index, extracting 25% to use as derivation resources.
     */
    GoalState goalState = GoalState(output);
    Interpreter *interpreter;
    switch (constants::PREFERRED_LANGUAGE_INTERPRETER) {
        case constants::IntrepreterLanguageTypeBrainfuck:
            interpreter = new BrainfuckInterpreter();
            break;
        default:
            break;
    }
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
    std::vector<Memory> tempPopulation = memories;
    std::vector<Prediction> predictions;
    for (int j = 0; j < tempPopulation.size(); j++) {
        Prediction prediction = Prediction(interpreter->outputFromProgram(tempPopulation[j].chromosome.genome, std::vector<char>()), goalState);
        predictions.push_back(prediction);
    }
    scoringSystem->setScoringData(predictions);
    std::vector<double> costs = scoringSystem->computeCosts();
    for (int j = 0; j < costs.size(); j++) {
        Memory *memory = &tempPopulation[j];
        (*memory).tentativeSimilarity = costs[j];
    }
    if (tempPopulation.size() > 1) {
        std::sort(std::begin(tempPopulation), std::end(tempPopulation), compareMemoriesOnSimilarity);
        tempPopulation.erase(tempPopulation.begin() + (tempPopulation.size() - ceil(tempPopulation.size() * 0.85)), tempPopulation.end());
        if (tempPopulation.size() > 4) {
            std::sort(std::begin(tempPopulation), std::end(tempPopulation), compareMemoriesOnSimilarityAndFoundationIndex);
            tempPopulation.erase(tempPopulation.end() + (tempPopulation.size() - ceil(tempPopulation.size() * 0.25)), tempPopulation.end());
        }
    }
    std::vector<Chromosome> derivedPopulation;
    for (int i = 0; i < tempPopulation.size(); i++) {
        remember_(i);
        derivedPopulation.push_back(tempPopulation[i].chromosome);
    }
    return derivedPopulation;
}

# pragma mark - Memory Unit Handling

void BrainUnit::remember_(int memoryIndex) {
    memories[memoryIndex].foundationIndex += 0.1;
    normalizeFoundationIndexes();
}

void BrainUnit::remember(Memory memory) {
    bool existingMemory = false;
    for (int i = 0; i < memories.size(); i++) {
        if (memories[i].chromosome.genome == memory.chromosome.genome) {
            remember_(i);
            existingMemory = true;
            break;
        }
    }
    if (existingMemory)
        return;
    memories.push_back(memory);
    remember_((int)(memories.size() - 1));
}

void BrainUnit::normalizeFoundationIndexes() {
    // Two loops: one to count total sum of memory foundation indexes, and then one to normalize them; O(n).
    double foundationIndexSummation = 0;
    for (int i = 0; i < memories.size(); i++)
        foundationIndexSummation += memories[i].foundationIndex;
    for (int i = 0; i < memories.size(); i++) { // Divide each foundation index by the sum
        memories[i].foundationIndex = memories[i].foundationIndex / foundationIndexSummation;
    }
    if (constants::IS_PERSISTANCE_MODE)
        save();
}

void BrainUnit::normalizeFoundationIndexesWithEvenDistribution() {
    for (int i = 0; i < memories.size(); i++) // Divide 1 by the total size to get even distribution
        memories[i].foundationIndex = 1 / memories.size();
    if (constants::IS_PERSISTANCE_MODE)
        save();
}
