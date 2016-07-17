//
//  ChromosomePopulationProcesses.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef ChromosomePopulationProcesses_cpp
#define ChromosomePopulationProcesses_cpp

#include <stdio.h>
#include <vector>

#include "Chromosome.hpp"
#include "Interpreter.hpp"

/* This class handles all the
 evolutionary processes that
 chromosomes undertake when evolving
 in a pool, for example mating and
 mutating. */
class ChromosomePopulationProcesses {
    public:
        // All of these methods require a charset to use as seed for the program modifications
        static std::vector<Chromosome> mateChromosomes(std::string charset, Chromosome chromosome1, Chromosome chromosome2); // Mate the chromosomes by taking their genomes and crossing the first/second halves over, producing two new children chromosomes (one deterministic pair and one random pair).
        static Chromosome randomlyMutateChromosome(std::string charset, Chromosome chromosome); // Mutate (randomly adjust the genome) a chromosome with some probability defined in the Constants file. Thus, not all chromosomes will be mutated as a result of this method call.
        static Chromosome generateRandomChromosome(std::string charset, int preferredLength); // Generate a chromosome with a random genome of some preferred length
};

#endif /* ChromosomePopulationProcesses_cpp */
