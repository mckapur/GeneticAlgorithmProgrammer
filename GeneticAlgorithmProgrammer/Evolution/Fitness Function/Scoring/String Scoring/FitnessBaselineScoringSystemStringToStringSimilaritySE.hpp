//
//  FitnessBaselineScoringSystemStringToStringSimilaritySE.hpp
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 29/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef FitnessBaselineScoringSystemStringToStringSimilaritySE_cpp
#define FitnessBaselineScoringSystemStringToStringSimilaritySE_cpp

#include "FitnessBaselineScoringSystemStringToStringSimilarity.hpp"

/* The FitnessBaselineScoringSystemStringToStringSimilaritySE
 class is an SE (squared error) cost function that summates the
 squared discrepancy between the ASCII indexes of each respective
 character in the strings.
 */
class FitnessBaselineScoringSystemStringToStringSimilaritySE : public FitnessBaselineScoringSystemStringToStringSimilarity {
    public:
        std::vector<double> computeCosts() {
            std::vector<double> costs;
            for (int i = 0; i < predictions.size(); i++) {
                std::string predictedString = predictions[i].outputPrediction;
                std::string goalString = predictions[i].goalState.output;
                int sum = 0;
                unsigned long iterationSize = 0;
                unsigned long comparisonSize = 0;
                unsigned long size1 = predictedString.size();
                unsigned long size2 = goalString.size();
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
                for (unsigned int j = 0; j < iterationSize; j++)
                    sum += pow((int)predictedString[j] - (int)goalString[j], 2);
                // Iterate over the remaining values
                for (unsigned long j = iterationSize; j < comparisonSize; j++) {
                    if (size1 > size2)
                        sum += pow((int)predictedString[j], 2);
                    else
                        sum += pow((int)goalString[j], 2);
                }
                costs.push_back(sum);
            }
            return costs;
        }
};

#endif /* FitnessBaselineScoringSystemStringToStringSimilaritySE_cpp */
