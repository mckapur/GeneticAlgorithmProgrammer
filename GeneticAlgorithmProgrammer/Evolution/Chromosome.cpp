//
//  Chromosome.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "Chromosome.hpp"

#include <float.h>

#pragma mark - Init

Chromosome::Chromosome() {
    fitness = DBL_MAX; // Default
}

Chromosome::Chromosome(std::string _genome) {
    Chromosome();
    genome = _genome;
}