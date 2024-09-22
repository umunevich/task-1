// Random.cpp
// created by Yana Utochkina

#include "Random.h"

Random::Random() {
    std::random_device rd;
    generator = std::mt19937(rd());
}

void Random::set_distribution(const std::vector<int>& probabilities) {
    distribution = std::discrete_distribution<int>(probabilities.begin(), probabilities.end());
}

void Random::set_numbers(const std::vector<int>& numbers) {
    this->numbers = std::vector<int>(numbers);
}

int Random::operator()() {
    return this->numbers[distribution(generator)];
}
