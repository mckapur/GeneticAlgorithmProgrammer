//
//  GoalState.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 31/1/16.
//  Copyright © 2016 Rohan Kapur. All rights reserved.
//

#ifndef GoalState_hpp
#define GoalState_hpp

#include <string>
#include <stdio.h>

/**
 A goal state is the same stru-
 cture as a prediction except
 for semantic details in that
 the input and output pair is
 by definition accurate and hence
 a "goal" for the program to predict on.
 It is what the program is trying to model.
 */
class GoalState {
    public:
        std::string output;
        std::vector<char> inputs;
    
        GoalState(std::string _output) {
            output = _output;
        } // Initialize with the output (no inputs required)
        GoalState(std::vector<char> _inputs, std::string _output) {
            inputs = _inputs;
            output = _output;
        } // Initialize with the inputs and output
};

#endif /* GoalState_hpp */
