//
//  StringToStringMAE.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 29/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef StringToStringMAE_cpp
#define StringToStringMAE_cpp

#include <iostream>

#include "StringToStringFitnessFunction.h"

/* The StringToStringMAE fitness function
 is an MAE (mean absolute error) cost function
 that summates the absolute value of the
 discrepancy between the ASCII indexes of each
 respective character in the strings, and divides
 it by two times the strings' size.
 */
class StringToStringMAE : public StringToStringFitnessFunction {
    public:
        static double computeStringToStringCost(std::string string1, std::string string2) {
            int sum = 0;
            unsigned long iterationSize = 0;
            unsigned long comparisonSize = 0;
            unsigned long size1 = string1.size();
            unsigned long size2 = string2.size();
            // Check if strings are different sizes, which is important for the cost function
            if (size2 > size1) {
                iterationSize = size1;
                comparisonSize = size2;
            }
            else if (size1 > size2) {
                iterationSize = size2;
                comparisonSize = size1;
            }
            else {
                iterationSize = size1; // Doesn't matter - they are the same size.
                comparisonSize = iterationSize; // Doesn't matter in the same fashion.
            }
            // Iterate over shared size
            for (unsigned int i = 0; i < iterationSize; i++) {
                sum += std::fabs((int)string1[i] - (int)string2[i]);
            }
            // Iterate over the remaining values
            for (unsigned long i = iterationSize; i < comparisonSize; i++) {
                if (size1 > size2)
                    sum += (int)string1[i];
                else
                    sum += (int)string2[i];
            }
            double cost = ((double)sum)/comparisonSize;
            return cost;
    }
};

#endif /* StringToStringMAE_cpp */
