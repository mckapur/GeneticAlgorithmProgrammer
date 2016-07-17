//
//  TrainingSet.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 31/1/16.
//  Copyright © 2016 Rohan Kapur. All rights reserved.
//

#include "TrainingSet.hpp"

#include <math.h>

#pragma mark - Init

TrainingSet::TrainingSet() {
    validationPartition = 0.30;
}

TrainingSet::TrainingSet(std::vector<GoalState> _trainingSet, double _validationPartition) {
    if (_validationPartition > 0 || _validationPartition < 1)
        validationPartition = _validationPartition;
    trainingSet = _trainingSet;
    partitionTrainingSet();
}

#pragma mark - Partitioning

void TrainingSet::partitionTrainingSet() {
    unsigned long trainingSetSize = trainingSet.size();
    unsigned long validationSize = 0;
    if (trainingSetSize > 1)
        validationSize = ceil(trainingSetSize * validationPartition);
    trainingSetSize -= validationSize;
    while (validationSet.size() != validationSize) {
        unsigned long pos = trainingSet.size() - 1;
        GoalState goal = trainingSet[pos];
        trainingSet.erase(trainingSet.begin() + pos);
        validationSet.push_back(goal);
    }
}