// calculate.h
// created by Yana Utochkina

#ifndef CALCULATE_H
#define CALCULATE_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

namespace calculate {
    std::vector<double> probabilities(const std::vector<int>& probabilities_int);
    void convert_probabilities(std::vector<double>& probabilities, const double& denominator);
    std::vector<double> generated_map_to_probabilities(const std::vector<int>& numbers, std::map<int, int>& generated_map);
    double max_difference(const std::vector<double>& input_probabilities, const std::vector<double>& output_probabilities);
}

#endif //CALCULATE_H
