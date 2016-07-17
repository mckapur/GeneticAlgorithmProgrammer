//
//  FitnessHeuristic.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "FitnessFunction.hpp"
#include "FitnessBaselineScoringSystemStringToStringSimilarity.hpp"
#include "FitnessBaselineScoringSystemStringToStringSimilaritySE.hpp"
#include "Prediction.hpp"

#include <iostream>
#include <float.h>
#include <math.h>

#pragma mark - Init

FitnessFunction::FitnessFunction() {
}

FitnessFunction::FitnessFunction(Interpreter *_languageInterpreter, FitnessBaselineScoringSystem *_fitnessBaselineScoringSystem, TrainingSet _trainingSet) {
    FitnessHeuristic();
    languageInterpreter = _languageInterpreter;
    fitnessBaselineScoringSystem = _fitnessBaselineScoringSystem;
    trainingSet = _trainingSet;
}

#pragma mark - Computations

void FitnessFunction::prepareToScore(std::vector<Chromosome> chromosomes) {
    scoringPool.erase(scoringPool.begin(), scoringPool.end());
    std::vector<Prediction> predictions;
    // TODO: Implement validation set
    for (int i = 0; i < chromosomes.size(); i++) {
        std::vector<Prediction> predictions;
        for (int j = 0; j < trainingSet.size(); j++) {
            GoalState goalState = trainingSet.trainingSet[j];
            std::string outputPrediction = outputForChromosome(chromosomes[i], goalState.inputs);
            Prediction prediction = Prediction(goalState.inputs, outputPrediction, goalState);
            predictions.push_back(prediction);
        }
        if (trainingSet.validationSet.size() > 0) {
            // Note - validation set with a size of 1 is useless because it will just be deterministic and effectively a training set!
            double randomIndex = rand() % trainingSet.validationSet.size();
            Prediction prediction = Prediction(trainingSet.validationSet[randomIndex].inputs, outputForChromosome(chromosomes[i], trainingSet.validationSet[randomIndex].inputs), trainingSet.validationSet[randomIndex]);
            predictions.push_back(prediction);
        }
        scoringPool[chromosomes[i]] = predictions;
    }
}

// TODO: Implement heuristics
std::vector<Chromosome> FitnessFunction::scoreChromosomes() {
    std::vector<Chromosome> scoredChromosomes;
    for (auto const& iter : scoringPool) {
        Chromosome first = iter.first;
        std::vector<Prediction> predictions = iter.second;
        fitnessBaselineScoringSystem->setScoringData(predictions);
        std::vector<double> individualCosts = fitnessBaselineScoringSystem->computeCosts();
        double aggregatedCost = 0;
        for (int i = 0; i < individualCosts.size(); i++)
            aggregatedCost += individualCosts[i];
        first.fitness = aggregatedCost;
        scoredChromosomes.push_back(first);
    }
    return scoredChromosomes;
}

#pragma mark - Input -> Output

// TODO: Add support for inputs
std::string FitnessFunction::outputForChromosome(Chromosome chromosome, std::vector<char> inputs) {
    std::string output = languageInterpreter->outputFromProgram(chromosome.genome, inputs);
    return output;
}