//
//  Memory.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 13/11/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "Memory.hpp"

#include <sstream>
#include <iostream>

#pragma mark - Parsing Methods

std::string Memory::toString() {
    std::ostringstream stringContents;
    stringContents << foundationIndex;
    stringContents << ",";
    stringContents << chromosome.genome;
    return stringContents.str();
}

#pragma mark - Init

Memory::Memory() {
}

// Find first instance of a comma and then use the LHS and RHS as inputs to initialize data
Memory::Memory(std::string stringContents) {
    int delimeterPos = 0;
    const char *stringContentsData = stringContents.c_str();
    for (int i = 0; i < stringContents.length(); ++i) {
        if (stringContentsData[i] == ',') {
            delimeterPos = i;
            break;
        }
    }
    std::string foundationIndexString = stringContents.substr(0, delimeterPos); // LHS is the foundation index
    std::string chromosomeString = stringContents.substr(delimeterPos + 1, stringContents.length() - (delimeterPos + 1)); // RHS is the chromosome genome
    foundationIndex = std::stof(foundationIndexString);
    chromosome = Chromosome(chromosomeString);
}

Memory::Memory(Chromosome _chromosome) {
    chromosome = _chromosome;
}