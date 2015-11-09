//
//  FitnessHeuristic.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef FitnessHeuristic_cpp
#define FitnessHeuristic_cpp

#include <stdio.h>

#include "Constants.h"
#include "Chromosome.hpp"
#include "Interpreter.hpp"

/* This class computes the fitness
 value for a specific chromsome, based
 on the class' fixed output goal
 state and language interpreter. */
class FitnessHeuristic {
    public:
        std::string outputGoalState; // The output we want to achieve and compare to (goal state)
        Interpreter languageInterpreter; // The arbitrary language interpreter we use to interpret the chromosome genome as an input program
        double fitnessForChromosome(Chromosome chromosome, constants::StringToStringFitnessFunctionType fitnessFunctionType); // Computes the fitness (cost/score) of a chromosome based on how the interpretation (based on the class' arbitrary language interpreter) of its genome compares to the class' output goal state. Also pass a fitness function type to be used by the system (eg. MAE, MSE, RMSE, etc.).
        FitnessHeuristic(); // Default initializer
        FitnessHeuristic(Interpreter _languageInterpreter, std::string _outputGoalState); // Initialize a FitnessHeuristic class with a language interpreter and an output goal state
        std::string outputForChromosome(Chromosome chromosome); // Uses the class' interpreter to retrieve the output of a given chromosome (based on its genome as the program)
};

#endif /* FitnessHeuristic_cpp */