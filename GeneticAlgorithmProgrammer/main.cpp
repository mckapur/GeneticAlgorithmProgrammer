//
//  main.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 9/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include <float.h>
#include <iostream>

#include "Constants.h"

#include "BrainUnit.hpp"
#include "Chromosome.hpp"
#include "ChromosomePopulation.hpp"

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    BrainUnit brain = BrainUnit();
    ChromosomePopulation population;
    while (true) {
        std::string spec = "";
        std::getline(std::cin, spec);
        std::vector<Chromosome> initialPopulation = brain.derivePopulation(spec);
        population = ChromosomePopulation(initialPopulation, spec);
        brain.remember(Memory(population.evolve()));
    }
    return 0;
}
