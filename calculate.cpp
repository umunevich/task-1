// calculate.cpp
// created by Yana Utochkina

#include "calculate.h"

template <typename T>
double calculate_denominator(const std::vector<T>& nums) {
    double denominator = 0;
    for (auto it : nums)
        denominator += it;
    return denominator;
}

std::vector<double> calculate::probabilities(const std::vector<int>& probabilities_int) {
    double denominator = calculate_denominator(probabilities_int);
    std::vector<double> probabilities_double = std::vector<double>(probabilities_int.begin(), probabilities_int.end());
    convert_probabilities(probabilities_double, denominator);
    return probabilities_double;
}

void calculate::convert_probabilities(std::vector<double>& probabilities, const double& denominator) {
    for (auto &it : probabilities)
        it /= denominator;
}

std::vector<double> calculate::generated_map_to_probabilities(const std::vector<int>& numbers, std::map<int, int>& generated_map) {
    std::vector<double> probabilities_double = std::vector<double>(numbers.size(), 0);
    double denominator = 0;
    for (int i = 0; i < numbers.size(); i++) {
        probabilities_double[i] = generated_map[numbers[i]];
        denominator += probabilities_double[i];
    }
    convert_probabilities(probabilities_double, denominator);
    return probabilities_double;
}

double calculate::max_difference(const std::vector<double>& input_probabilities, const std::vector<double>& output_probabilities) {
    double max_difference = 0.0;
    double t = 0.0;
    for (int i = 0; i < input_probabilities.size(); i++) {
        t = fabs(input_probabilities[i] - output_probabilities[i]);
        if (t > max_difference)
            max_difference = t;
    }
    return max_difference;
}