//
//  Chromosome.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef Chromosome_cpp
#define Chromosome_cpp

#include <stdio.h>
#include <string>

/* A chromosome is an object that stores the
 piece of data (the "genome") that is being
 evolved (via mating and random mutations)
 to match some desired output. Each chromosome
 is a species in its population (breed), and
 is either killed from the system or evolved
 further due to natural selection in the population,
 based on the fitness function and how it compares
 to its competitors. */
class Chromosome {
    public:
        double fitness; // The fitness (cost) of the chromosome in the population
        std::string genome; // The data/value of the chromosome as an arbitrary string
        
        Chromosome(); // The default initializer
        Chromosome(std::string _genome); // Initialize a new chromosome with a specified genome
    
        bool operator<(const Chromosome& foe) const;
};

#endif /* Chromosome_cpp */