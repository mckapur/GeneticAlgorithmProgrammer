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

/* This class handles all the
 evolutionary processes that
 chromosomes undertake when evolving
 in a pool, for example mating and
 mutating. */
class ChromosomePopulationProcesses {
    public:
        static std::vector<Chromosome> mateChromosomes(Chromosome chromosome1, Chromosome chromosome2); // Mate the chromosomes by taking their genomes and crossing the first/second halves over, producing two new children chromosomes (one deterministic pair and one random pair).
        static Chromosome randomlyMutateChromosome(Chromosome chromosome); // Mutate (randomly adjust the genome) a chromosome with some probability defined in the Constants file. Thus, not all chromosomes will be mutated as a result of this method call.
        static Chromosome generateRandomChromosome(int preferredLength); // Generate a chromosome with a random genome of some preferred length
};

#endif /* ChromosomePopulationProcesses_cpp */
