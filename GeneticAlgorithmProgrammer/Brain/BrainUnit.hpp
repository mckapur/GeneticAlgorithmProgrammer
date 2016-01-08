//
//  BrainUnit.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 13/11/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

// TODO: Sophisticated tree data structure to store memories?

#ifndef BrainUnit_cpp
#define BrainUnit_cpp

#include <stdio.h>
#include <vector>

#include "Memory.hpp"

/*
 This class, a brain unit, stores a
 collection of previous successful,
 converged evolution of programs, as
 Memory units. These can be used to derive
 new populations for the algorithm to run
 */
class BrainUnit {
    public:
        std::vector<Chromosome> derivePopulation(std::string output); // Derives a population to evolve to (specified output) based on previous memories
        void remember(Memory memory); // "Remembers" a new memory by appending it to the array of memories, and recalculating the normalized foundation indexes
        void clear(); // Clears all retained memories
        BrainUnit(); // Initializes a new BrainUnit with preloaded saved (if exists) memories
    private:
        std::vector<Memory> memories; // Collection of memory units
        void remember_(int memoryIndex); // "Remembers" an existing memory by recalculating its foundation index
        void normalizeFoundationIndexes();
        void save(); // Retains memories by saving them
        void load(); // Fetches back existing memories (if exists)
        void printMemories(); // Prints a text version of each memory in the brain unit
};

#endif /* BrainUnit_cpp */