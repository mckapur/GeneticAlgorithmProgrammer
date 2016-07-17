//
//  FitnessBaselineScoringSystem.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 30/1/16.
//  Copyright © 2016 Rohan Kapur. All rights reserved.
//

#ifndef FitnessBaselineScoringSystem_hpp
#define FitnessBaselineScoringSystem_hpp

#include "Constants.h"
#include "Prediction.hpp"
#include "GoalState.hpp"

#include <vector>
#include <stdio.h>

/* The FitnessBaselineScoringSystem class
 is an incomplete interface that should
 be subclassed (do not call any functions
 on this specific class/file - only the
 subclasses). It is a baseline scoring system,
 meaning the primary component of a given
 fitness function that measures accuracy or
 cost. It can be then layered with heuristics.
 Each fitness baseline scoring system instance
 contains a "goal state" that is the criteria of
 the accuracy function, and you pass "predictions"
 on that goal state which will be scored.
 */
class FitnessBaselineScoringSystem {
    public:
        FitnessBaselineScoringSystem() { // Default initializer - initialize with empty output
        }
        constants::FitnessBaselineScoringSystemType scoringSystemType; // The type of baseline scoring system of the subclass
        virtual void setScoringData(std::vector<Prediction> predictions) {} // Set the data to be scored (which includes a set of predictions for different goal states); overloaded by subclasses
        virtual std::vector<double> computeCosts() { return std::vector<double>(); } // Computes and returns the costs based on attributes of the subclass
};

#endif /* FitnessBaselineScoringSystem_hpp */
