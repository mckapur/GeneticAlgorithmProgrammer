//
//  TrainingSet.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 31/1/16.
//  Copyright © 2016 Rohan Kapur. All rights reserved.
//

#ifndef TrainingSet_hpp
#define TrainingSet_hpp

#include <stdio.h>
#include <vector>

#include "GoalState.hpp"

/**
 The training set holds a collection
 of goal states that must be satisfied
 by the predictions of the program. If
 the training set holds multiple goal
 states, then only one may have no inputs
 - the rest need inputs such that a valid
 program can be deduced.
 */
class TrainingSet {
    private:
        void partitionTrainingSet(); // Takes the training set and partitions into a training set and validation set with respect to the validationPartition value
    public:
        double size() {
            return trainingSet.size(); // For convenience
        }
    
        std::vector<GoalState> trainingSet; // The goal states that must be satisfied by the program predictions
        std::vector<GoalState> validationSet; // The validation set is a partition of the training set that is used at random to ensure the candidate programs are not overfitting
        double validationPartition; // The percentage (from 0 to 1) of the training set that is partitioned into the validation set (used at random to ensure the program is not overfitting)
    
    TrainingSet();
        TrainingSet(std::vector<GoalState> goalStates, double validationPartition); // Initialize with goal states and a validation partition
};

#endif /* TrainingSet_hpp */
