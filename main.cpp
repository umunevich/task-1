// main.cpp
// created by Yana Utochkina

#include <format>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>

#include "Random.h"

void processing_args(int argc, const char *argv[]);
std::vector<int> read_file(std::ifstream& input_file);
std::map<int, int> generate(const int& n, Random& random, const std::vector<int>& numbers);

std::vector<double> calculate_probabilities(const std::vector<int>& probabilities_int);
template <typename T>
double calculate_denominator(const std::vector<T>& nums);
void convert_probabilities(std::vector<double>& probabilities, const double& denominator);
std::vector<double> generated_map_to_probabilities(const std::vector<int>& numbers, std::map<int, int>& generated_map);
double calculate_max_difference(const std::vector<double>& input_probabilities, const std::vector<double>& output_probabilities);

template <typename T>
std::ofstream& operator<<(std::ofstream& output_file, const std::vector<T>& vec);

int main(int argc, const char * argv[]) {
    try {
        processing_args(argc, argv);
        std::ifstream input_file = std::ifstream(argv[1]);
        std::vector<int> input_vector = read_file(input_file);

        Random random = Random();

        std::vector<int> numbers = std::vector<int>(input_vector.begin() + 1, input_vector.begin() + (input_vector.size() - 1)/2 + 1);
        random.set_numbers(numbers);

        std::vector<int> input_probabilities_int = std::vector<int>(input_vector.begin() + (input_vector.size() - 1)/2 + 1, input_vector.end());
        random.set_distribution(input_probabilities_int);

        std::map<int, int> generated_map = generate(input_vector[0], random, numbers);

        std::vector<double> input_probabilities_double = calculate_probabilities(input_probabilities_int);
        std::vector<double> output_probabilities_double = generated_map_to_probabilities(numbers, generated_map);
        double max_difference = calculate_max_difference(input_probabilities_double, output_probabilities_double);
        std::ofstream output_file = std::ofstream(argv[2]);

        output_file << numbers << input_probabilities_double << output_probabilities_double << max_difference << std::endl;

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void processing_args(int argc, const char *argv[]) {
    if (argc != 3)
        throw std::invalid_argument("usage: task1 input_file.txt output_file.txt");
}

std::vector<int> read_file(std::ifstream& input_file) {
    if (!input_file.is_open())
        throw std::invalid_argument("Input file is not opened.");
    std::vector<int> input_vector;
    int temp;
    while (input_file >> temp) {
        input_vector.push_back(temp);
    }
    if (!input_file.eof() || input_vector[0] < 1)
        throw std::invalid_argument("Wrong nums in input file.");
    input_file.close();
    if (input_vector.size() % 2 == 0)
        throw std::invalid_argument("Wrong amount of nums in input file.");
    return input_vector;
}

std::map<int, int> generate(const int& n, Random& random, const std::vector<int>& numbers) {
    std::map<int, int> generated_map;
    for (auto it : numbers) {
        generated_map.insert(std::pair<int, int>(it, 0));
    }
    for (int i = 0; i < n; i++) {
        generated_map[random()] += 1;
    }
    return generated_map;
}

std::vector<double> calculate_probabilities(const std::vector<int>& probabilities_int) {
    double denominator = calculate_denominator(probabilities_int);
    std::vector<double> probabilities_double = std::vector<double>(probabilities_int.begin(), probabilities_int.end());
    convert_probabilities(probabilities_double, denominator);
    return probabilities_double;
}

template <typename T>
double calculate_denominator(const std::vector<T>& nums) {
    double denominator = 0;
    for (auto it : nums)
        denominator += it;
    return denominator;
}

void convert_probabilities(std::vector<double>& probabilities, const double& denominator) {
    for (auto &it : probabilities)
        it /= denominator;
}

std::vector<double> generated_map_to_probabilities(const std::vector<int>& numbers, std::map<int, int>& generated_map) {
    std::vector<double> probabilities_double = std::vector<double>(numbers.size(), 0);
    double denominator = 0;
    for (int i = 0; i < numbers.size(); i++) {
        probabilities_double[i] = generated_map[numbers[i]];
        denominator += probabilities_double[i];
    }
    convert_probabilities(probabilities_double, denominator);
    return probabilities_double;
}

template <typename T>
std::ofstream& operator<<(std::ofstream& output_file, const std::vector<T>& vec) {
    output_file << std::fixed;
    output_file << std::setprecision(3);
    for (auto it : vec) {
        output_file << std::setw(8) << it;
    }
    output_file << '\n';
    return output_file;
}

double calculate_max_difference(const std::vector<double>& input_probabilities, const std::vector<double>& output_probabilities) {
    double max_difference = 0.0;
    double t = 0.0;
    for (int i = 0; i < input_probabilities.size(); i++) {
        t = fabs(input_probabilities[i] - output_probabilities[i]);
        if (t > max_difference)
            max_difference = t;
    }
    return max_difference;
}