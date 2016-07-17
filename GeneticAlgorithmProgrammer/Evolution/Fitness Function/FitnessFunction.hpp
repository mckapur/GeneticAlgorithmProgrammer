//
//  FitnessHeuristic.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef FitnessFunction_cpp
#define FitnessFunction_cpp

#include <stdio.h>
#include <vector>
#include <map>

#include "Constants.h"
#include "Chromosome.hpp"
#include "Interpreter.hpp"
#include "TrainingSet.hpp"
#include "FitnessHeuristic.hpp"
#include "FitnessBaselineScoringSystem.hpp"

/* This class computes the fitness value
 for a specific chromsome, based on the
 class' fixed output goal state and language
 interpreter. It uses a baseline scorer to
 achieve the initial accuracy cost, and then
 applies optional weighted heuristics on top. */
class FitnessFunction {
    private:
        std::vector<FitnessHeuristic> fitnessHeuristics; // The heuristics used along with the baseline scoring in the cost function
        FitnessBaselineScoringSystem *fitnessBaselineScoringSystem; // The baseline scoring component of the fitness functions
        std::map<Chromosome, std::vector<Prediction>> scoringPool; // The current scoring pool (each chromosome and its corresponding predictions for different inputs) whose members' fitnesses will be computed
    public:
        Interpreter *languageInterpreter; // The arbitrary language interpreter we use to interpret the chromosome genome as an input program
        TrainingSet trainingSet; // The "training set" is used to score how well a program performs because it contains the information of what the program should achieve
    
        std::string outputForChromosome(Chromosome chromosome, std::vector<char> inputs); // Uses the class' interpreter to retrieve the output of a given chromosome (based on its genome as the program) with respect to optional inputs passed/provided
    
        std::vector<Chromosome> scoreChromosomes(); // Computes the fitness (cost/score) of chromosomes in the scoring pool based on how the interpretation (based on the class' arbitrary language interpreter) of its genome compares to the class' output goal state via a baseline score and a set of heuristics layered on top. Make sure to call the -prepareToScore(:) before calling this one.
        void prepareToScore(std::vector<Chromosome> chromosomes); // Places the chromosomes into the baseline function and does any further steps to prepare for fitness computation
    
        FitnessFunction(); // Default initializer
        FitnessFunction(Interpreter *_languageInterpreter, FitnessBaselineScoringSystem *fitnessBaselineScoringSystem_,  TrainingSet _trainingSet); // Initialize a FitnessHeuristic class with a language interpreter, training set, and an output goal state
};

#endif /* FitnessHeuristic_cpp */