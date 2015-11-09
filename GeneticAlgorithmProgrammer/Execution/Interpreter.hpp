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

/* An interface for any arbitrary language 
 interpreter to implement. This is for
 interpreting a string (as a program), and
 returning any results it outputs.
 */
class Interpreter {
    public:
        Interpreter(); // Default initializer
        virtual std::string outputFromProgram(std::string program); // Takes some input string as the program genome, and returns the output (if any, else null). Subclasses should override this. By default - this will be an identity interpreter.
};

#endif /* Interpreter_cpp */