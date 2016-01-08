//
//  Memory.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 13/11/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef Memory_cpp
#define Memory_cpp

#include "Chromosome.hpp"

#include <vector>

/*
 This class, a memory, stores a
 previous successful, converged evolution
 of code. Memories can be used to derive
 populations pools for new evolutions to
 increase speed of convergence. This design
 mimics how memories can be used to define new
 knowledge in human brains.
 */
class Memory {
    public:
        Chromosome chromosome; // Chromosome associated with the memory
        double foundationIndex; // How essential a memory is to the brain unit (how many times it's been used to derive a new population) - it is a normalized value
        double tentativeSimilarity; // This is an optional value that represents an arbitrary and temporary similarity value between the memory and some other output/chromosome
    
        std::string toString(); // Returns a string which contains all the data of the memory
    
        Memory(Chromosome chromosome); // Initializes a new memory based on a chromosome
        Memory(std::string stringContents); // Initializes a new memory based on string contents
        Memory();
};

#endif /* Memory_cpp */
