//
//  main.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 9/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include <float.h>
#include <math.h>
#include <iostream>

#include "Constants.h"

#include "BrainUnit.hpp"
#include "BrainfuckInterpreter.hpp"
#include "Chromosome.hpp"
#include "ChromosomePopulation.hpp"

void prettyExecute() {
    srand(time(NULL));
    BrainUnit brain = BrainUnit();
    std::cout << "Brain unit has remembers the following programs:" << "\n";
    if (constants::IS_PERSISTANCE_MODE)
        brain.printMemories();
    ChromosomePopulation population;
    while (true) {
        std::cout << "Input an output to generate: ";
        std::string spec = "";
        std::getline(std::cin, spec);
        std::vector<Chromosome> initialPopulation = brain.derivePopulation(spec);
        std::cout << "\n" << "Beginning evolution with derived population (excluding random generations):" << "\n";
        for (int i = 0; i < initialPopulation.size(); i++)
            std::cout << initialPopulation[i].genome << "\n";
        std::vector<GoalState> goalStates;
        goalStates.push_back(GoalState(spec));
        Memory newMemory = Memory(ChromosomePopulation(initialPopulation, goalStates).evolve());
        brain.remember(newMemory);
        
        // Brainfuck to Ook
        std::string ookVersion = "";
        std::string optimalCandidate = newMemory.chromosome.genome;
        for (int i = 0; i < optimalCandidate.length(); i++) {
            switch (optimalCandidate[i]) {
                case '>':
                    ookVersion += "Ook. Ook?";
                    break;
                case '<':
                    ookVersion += "Ook? Ook.";
                    break;
                case '+':
                    ookVersion += "Ook. Ook.";
                    break;
                case '-':
                    ookVersion += "Ook! Ook!";
                    break;
                case '.':
                    ookVersion += "Ook! Ook.";
                    break;
                case ',':
                    ookVersion += "Ook. Ook!";
                    break;
                case '[':
                    ookVersion += "Ook! Ook?";
                    break;
                case ']':
                    ookVersion += "Ook? Ook!";
                    break;
                default:
                    break;
            }
        }
        std::cout << "\nOok version: " + ookVersion + "\n";

    }
}

int main(int argc, const char * argv[]) {
    prettyExecute();
    return 0;
}
