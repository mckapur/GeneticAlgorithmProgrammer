//
//  FitnessBaselineScoringSystemStringToStringSimilarity.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 29/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef FitnessBaselineScoringSystemStringToStringSimilarity_cpp
#define FitnessBaselineScoringSystemStringToStringSimilarity_cpp

#include <stdio.h>
#include <math.h>
#include <string>
#include <cmath>
#include <iostream>

#include "FitnessBaselineScoringSystem.hpp"

/* An interface for string->string
 fitness function classes. Strings
 are quantified by their ASCII indexes.
 DO NOT call any function on this class
 as it is essentially an interface (use
 the available subclasses).
 */
class FitnessBaselineScoringSystemStringToStringSimilarity : public FitnessBaselineScoringSystem {
    protected:
        std::vector<Prediction> predictions; // The predictions of the output goal state
    public:
        FitnessBaselineScoringSystemStringToStringSimilarity()
        : FitnessBaselineScoringSystem() {
            scoringSystemType = constants::FitnessBaselineScoringSystemTypeStringToStringSimilarityScoring;
        } // Default init
        void setScoringData(std::vector<Prediction> _predictions) {
            predictions = _predictions;
        }
        std::vector<double> computeCosts() {
            return std::vector<double>();
        }
};

#endif /* FitnessBaselineScoringSystemStringToStringSimilarity_cpp */