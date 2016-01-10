//
//  BrainfuckInterpreter.cpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 9/1/16.
//  Copyright © 2016 Rohan Kapur. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>

#include "Constants.h"

#pragma mark - Input -> Output

class BrainfuckInterpreter {
    private:
        // Verifies if a Brainfuck program has valid syntax
        static bool verifyBrainfuckProgram(std::string program) {
            std::stack<int> loopStack;
            for (unsigned int commandIndex = 0; commandIndex < program.size(); commandIndex++) {
                if (program[commandIndex] == '[')
                    loopStack.push(commandIndex);
                else if (program[commandIndex] == ']') {
                    if (loopStack.size())
                        loopStack.pop();
                }
            }
            return loopStack.size() == 0;
        }
    
    public:
        // Validates & executes the Brainfuck program, whilst returning the output
        static std::string outputFromProgram(std::string program) {
            std::string output = "";
            if (!verifyBrainfuckProgram(program))
                return output;
            unsigned char tape[30000] = {0};
            unsigned char *ptr = tape;
            std::stack<int> loopStack;
            bool skippingToClauseEnd = false;
            int loopCounter = 0;
            for (unsigned int commandIndex = 0; commandIndex < program.size(); commandIndex++) {
                if (program[commandIndex] == '[') {
                    if (*ptr == 0)
                        skippingToClauseEnd = true;
                    else
                        loopStack.push(commandIndex);
                }
                else if (program[commandIndex] == ']') {
                    if (skippingToClauseEnd)
                        skippingToClauseEnd = false;
                    else {
                        if (loopStack.size()) {
                            if (*ptr == 0)
                                loopStack.pop();
                            else if (loopCounter < constants::MAX_BRAINFUCK_LOOP_ITERATIONS) {
                                commandIndex = loopStack.top();
                                loopCounter++;
                            }
                        }
                    }
                }
                else if (!skippingToClauseEnd) {
                    switch (program[commandIndex]) {
                        case '+':
                            ++*ptr;
                            break;
                        case '-':
                            --*ptr;
                            break;
                        case '>':
                            ++ptr;
                            break;
                        case '<':
                            --ptr;
                            break;
                        case '.':
                            output.push_back(*ptr);
                            break;
                            //            case ',':
                            //                std::cin >> ptr;
                            //                break;
                    }
                }
            }
            return output;
        }
};