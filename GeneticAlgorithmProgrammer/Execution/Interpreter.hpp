//
//  Interpreter.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 28/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef Interpreter_cpp
#define Interpreter_cpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "Constants.h"

/* An interface for any arbitrary language 
 interpreter to implement. This is for
 interpreting a string (as a program), and
 returning any results it outputs. You should
 only instantiate subclasses of this class and
 call methods on them.
 */
class Interpreter {
    public:
        virtual std::string outputFromProgram(std::string program, std::vector<char> inputs) {return "";}; // Takes some input string as the program genome with respect to some inputs provided, and returns the output (if any, else null).
        virtual std::string charset() {return "";}; // Gets all the code characters that are available in a given language
};

#endif /* Interpreter_cpp */