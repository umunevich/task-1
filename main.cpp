// main.cpp
// created by Yana Utochkina

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>

#include "Random.h"
#include "calculate.h"

void processing_args(int argc, const char *argv[]);
std::vector<int> read_file(std::ifstream& input_file);

std::map<int, int> generate(const int& n, Random& random, const std::vector<int>& numbers);

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T>& vec);

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

        std::vector<double> input_probabilities_double = calculate::probabilities(input_probabilities_int);
        std::vector<double> output_probabilities_double = calculate::generated_map_to_probabilities(numbers, generated_map);
        double max_difference = calculate::max_difference(input_probabilities_double, output_probabilities_double);

        std::cout << numbers << input_probabilities_double << output_probabilities_double << max_difference << std::endl;

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void processing_args(int argc, const char *argv[]) {
    if (argc != 2)
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

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T>& vec) {
    output << std::fixed;
    output << std::setprecision(3);
    for (auto it : vec) {
        output << std::setw(8) << it;
    }
    output << '\n';
    return output;
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
