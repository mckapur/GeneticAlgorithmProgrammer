//
//  StringToStringFitnessFunction.h
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 29/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef StringToStringFitnessFunction_h
#define StringToStringFitnessFunction_h

#include <stdio.h>
#include <math.h>
#include <string>
#include <cmath>

/* An interface for string->string
 fitness function classes. Strings
 are quantified by their ASCII indexes.
 DO NOT call this function on this class
 (use the subclasses).
 */
class StringToStringFitnessFunction {
    public:
        static double computeStringToStringCost(std::string string1, std::string string2); // Computes the cost of string1 based on its similarity to string2 based on some arbitrary fitness function
};

#endif /* StringToStringFitnessFunction_h */