//
//  main.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 9/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include <iostream>

#include "Constants.h"
#include "ChromosomePopulation.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    srand((int)time(NULL));
    std::vector<Chromosome> originalMemberPool;
    ChromosomePopulation population = ChromosomePopulation(originalMemberPool, "Hello World!");
    population.beginEvolution();
    std::cout << "\n";
    return 0;
}
