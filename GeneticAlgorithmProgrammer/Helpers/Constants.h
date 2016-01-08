//
//  Constants.h
//  GeneticAlgorithmProgrammer
//
//  Created by Rohan Kapur on 30/10/15.
//  Copyright © 2015 Rohan Kapur. All rights reserved.
//

#ifndef Constants_cpp
#define Constants_cpp

#include <stdio.h>

/**
 A file storing globally relevant
 constants.
 */
namespace constants {
    
    /* An enum representing the different string->string
     fitness functions available to use. */
    enum StringToStringFitnessFunctionType {
        StringToStringFitnessFunctionSE,
        StringToStringFitnessFunctionMAE,
        StringToStringFitnessFunctionMSE,
        StringToStringFitnessFunctionRMSE
    };
    
    /* An enum representing the different
     languages to execute with. */
    enum LanguageInterpreterType {
        IntrepreterLanguageTypeIdentity,
        IntrepreterLanguageTypeWhitespace,
        IntrepreterLanguageTypeBrainfuck,
        IntrepreterLanguageTypeIota
    };

    const int CHROMOSOME_POPULATION_POOL_SIZE = 45; // Number of chromosomes in the first pool (and perhaps subsequent ones)
    const StringToStringFitnessFunctionType PREFERRED_FITNESS_FUNCTION = StringToStringFitnessFunctionSE; // The preferred fitness function to use for chromosome fitness assignment
    const LanguageInterpreterType PREFERRED_LANGUAGE_INTERPRETER = IntrepreterLanguageTypeIdentity; // The preferred language interpreter type
    const double POPULATION_POOL_MUTATE_PROBABILITY = 0.45; // The probability that a given chromosome will be mutated
    const double CHROMOSOME_POPULATION_MATE_PROBABILITY = 0.45; // The probability that two chromosomes will mate
    const double POPULATION_POOL_MUTATE_ADDITION_PROBABILITY = 0.03; // The probability that a given chromosome which will be mutated, will be mutated by adding a new character to the end of the genome
    const double POPULATION_POOL_MUTATE_INSERTION_PROBABILITY = 0.17; // The probability that a given chromosome which will be mutated, will be mutated by adding an existing character at a random position in the genome to a random position in the genome
    const double POPULATION_POOL_MUTATE_SUBTRACTION_PROBABILITY = 0.05; // The probability that a given chromosome which will be mutated, will be mutated by removing a character from the genome
    const double POPULATION_POOL_MUTATE_MODIFICATION_PROBABILITY = (1 - POPULATION_POOL_MUTATE_ADDITION_PROBABILITY - POPULATION_POOL_MUTATE_SUBTRACTION_PROBABILITY - POPULATION_POOL_MUTATE_INSERTION_PROBABILITY); // The probability that a given chromosome which will be mutated, will be mutated by changing a character in the genome
    const double CHROMOSOME_POPULATION_DEATH_RATE = 0.2; // The fraction of chromosomes killed from the sorted member pool
    const double CHROMOSOME_POPULATION_SURVIVE_RATE = 0.1; // The fraction of chromosomes that are certainly included & survive (and hence derive) the next population pool generation
    const double CHROMOSOME_POPULATION_COMPETITION_RATE = (1.0 - CHROMOSOME_POPULATION_DEATH_RATE - CHROMOSOME_POPULATION_SURVIVE_RATE); // The fraction of chromosomes that MAY be included in the next population pool generation
    const int MAX_POPULATION_POOL_GENERATIONS = 10000000; // The maximum number of population generations we will allow before terminating evolution
    const bool IS_DEBUGGING_MODE = true; // A flag that indicates whether the program is in debugging mode; use this to only produce (most) output logs if this evaluates to true (for efficiency)
}

#endif /* Constants_h */
