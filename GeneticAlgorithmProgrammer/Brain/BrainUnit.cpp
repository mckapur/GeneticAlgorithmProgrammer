//
//  BrainUnit.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 13/11/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "FitnessHeuristic.hpp"
#include "BrainUnit.hpp"

#include <iostream>
#include <fstream>
#include <iterator>

// TODO: In current dir and constants file
std::string BRAIN_UNIT_SAVE_FILE_PATH = "/Users/rohankapur/Library/GA_BrainUnit_Data.txt";

#pragma mark - Init

BrainUnit::BrainUnit() {
    if (constants::IS_PERSISTANCE_MODE)
        load();
    printMemories();
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
//
bool static compareMemoriesOnSimilarity(const Memory& a, const Memory& b) { // Compare two memories based on their similarity
    return a.tentativeSimilarity > b.tentativeSimilarity;
}

bool static compareMemoriesOnSimilarityAndFoundationIndex(const Memory& a, const Memory& b) { // Compare two memories based on their similarity and foundation index
    return (a.foundationIndex * a.tentativeSimilarity) > (a.foundationIndex * b.tentativeSimilarity);
}

std::vector<Chromosome> BrainUnit::derivePopulation(std::string output) {
    // TODO: Properly check over effectiveness & function of following process:
    /*
     Steps:
     1. Compute tentative similarity between each memory and the respective output
     2. Sort memories by this similarity and extract 25% to use as derivation resources
     3. Sort these filtered memories by similarity AND memory foundation index, extracting 50% to use as derivation resources.
     */
    std::vector<Memory> tempPopulation = memories;
    for (int j = 0; j < memories.size(); j++) {
        Memory memory = memories[j];
        memory.tentativeSimilarity = 1/FitnessHeuristic().fitnessForChromosome(memory.chromosome, constants::PREFERRED_FITNESS_FUNCTION);
    }
    std::sort(std::begin(tempPopulation), std::end(tempPopulation), compareMemoriesOnSimilarity);
    tempPopulation.erase(tempPopulation.begin() + (tempPopulation.size() / 4), tempPopulation.end());
    std::sort(std::begin(tempPopulation), std::end(tempPopulation), compareMemoriesOnSimilarityAndFoundationIndex);
    tempPopulation.erase(tempPopulation.begin() + (tempPopulation.size() / 2), tempPopulation.end());
    std::vector<Chromosome> derivedPopulation;
    for (int i = 0; i < memories.size(); i++) {
        remember_(i);
        derivedPopulation.push_back(tempPopulation[i].chromosome);
    }
    return derivedPopulation;
}

# pragma mark - Memory Unit Handling

void BrainUnit::remember_(int memoryIndex) {
    memories[memoryIndex].foundationIndex += 1;
    normalizeFoundationIndexes();
    if (constants::IS_PERSISTANCE_MODE)
        save();
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
}
