//
//  Interpreter.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "Interpreter.hpp"
#include "Constants.h"

#include <iostream>

#pragma mark - Init

Interpreter::Interpreter() {
}

#pragma mark - Input -> Output

std::string Interpreter::outputFromProgram(std::string program) {
    std::string output = "";
    bool bracketOpen = false;
    int plusCounter = 0;
    for (int i = 0; i < program.size(); i++) {
        if (program[i] == '(') {
            if (bracketOpen)
                break;
            else {
                bracketOpen = true;
                plusCounter = 0;
            }
        }
        else if (program[i] == ')') {
            if (bracketOpen) {
                bracketOpen = false;
                output.push_back((char)(plusCounter));
            }
            else
                break;
        }
        else if (program[i] == '+') {
            if (bracketOpen)
                plusCounter++;
            else
                break;
        }
        else {
//            break;
        }
    }
    return output;
}