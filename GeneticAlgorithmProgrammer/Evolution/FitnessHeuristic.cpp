//
//  FitnessHeuristic.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "StringToStringSE.hpp"
#include "StringToStringMSE.hpp"
#include "StringToStringMAE.hpp"
#include "StringToStringRMSE.hpp"
#include "FitnessHeuristic.hpp"

#include <float.h>

#pragma mark - Init

FitnessHeuristic::FitnessHeuristic() {
    languageInterpreter = Interpreter();
    outputGoalState = "";
}

FitnessHeuristic::FitnessHeuristic(Interpreter _languageInterpreter, std::string _outputGoalState) {
    FitnessHeuristic();
    languageInterpreter = _languageInterpreter;
    outputGoalState = _outputGoalState;
}

#pragma mark - Computations

double FitnessHeuristic::fitnessForChromosome(Chromosome chromosome, constants::StringToStringFitnessFunctionType fitnessFunctionType) {
    std::string outputPredictionState = outputForChromosome(chromosome);
    double cost = DBL_MAX;
    switch (fitnessFunctionType) {
        case constants::StringToStringFitnessFunctionType::StringToStringFitnessFunctionSE:
            cost = StringToStringSE::computeStringToStringCost(outputPredictionState, outputGoalState);
            break;
        case constants::StringToStringFitnessFunctionType::StringToStringFitnessFunctionMAE:
            cost = StringToStringMAE::computeStringToStringCost(outputPredictionState, outputGoalState);
            break;
        case constants::StringToStringFitnessFunctionType::StringToStringFitnessFunctionMSE:
            cost = StringToStringMSE::computeStringToStringCost(outputPredictionState, outputGoalState);
            break;
        case constants::StringToStringFitnessFunctionType::StringToStringFitnessFunctionRMSE:
            cost = StringToStringRMSE::computeStringToStringCost(outputPredictionState, outputGoalState);
            break;
        default:
            // Error, so cost will be left as maximum DLB_MAX.
            break;
    }
    return cost;
}

#pragma mark - Input -> Output

std::string FitnessHeuristic::outputForChromosome(Chromosome chromosome) {
    return languageInterpreter.outputFromProgram(chromosome.genome, constants::PREFERRED_LANGUAGE_INTERPRETER);
}