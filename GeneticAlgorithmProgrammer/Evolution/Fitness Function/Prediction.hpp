//
//  Prediction.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 31/1/16.
//  Copyright © 2016 Rohan Kapur. All rights reserved.
//

#ifndef Prediction_hpp
#define Prediction_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "GoalState.hpp"

/**
 A prediction is an input and
 output pair that was generated
 by the program/chromosome. The
 input is the input to the program,
 or the "prediction function", and the
 output is the resulting prediction.
 */
class Prediction {
    public:
        GoalState goalState; // What the prediction is aiming to accurately predict
        std::vector<char> inputs; // The inputs to the program (each is a char)
        std::string outputPrediction; // The single output from the program
    
        Prediction(std::string _outputPrediction, GoalState _goalState)
        : goalState(_goalState.inputs, _goalState.output) {
            outputPrediction = _outputPrediction;
        }; // Initialize with the output (no inputs required)
        Prediction(std::vector<char> _inputs, std::string outputPrediction, GoalState goalState)
        : Prediction(outputPrediction, goalState) {
            inputs = _inputs;
        } // Initialize with the inputs and output
};

#endif /* Prediction_hpp */
