//
//  Interpreter.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#include "Interpreter.hpp"
#include "BrainfuckInterpreter.cpp"

#include <iostream>
#include <stack>

#pragma mark - Init

Interpreter::Interpreter() {
}

#pragma mark - Input -> Output

std::string Interpreter::outputFromProgram(std::string program, constants::LanguageInterpreterType languageInterpreterType) {
    std::string output = "";
    switch (languageInterpreterType) {
        case constants::IntrepreterLanguageTypeBrainfuck:
            output = BrainfuckInterpreter::outputFromProgram(program);
            break;
        default:
            break;
    }
    return output;
}