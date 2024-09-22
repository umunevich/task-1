// Random.h
// created by Yana Utochkina

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
    std::mt19937 generator;
    std::discrete_distribution<> distribution;
    std::vector<int> numbers;
public:
    Random();
    void set_distribution(const std::vector<int>& probabilities);
    void set_numbers(const std::vector<int>& numbers);
    int operator()();
};

#endif //RANDOM_H
