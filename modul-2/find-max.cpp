#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cassert>
#include <iomanip>

std::vector<int> read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> data;
    int num;
    while (file >> num) {
        data.push_back(num);
    }
    return data;
}

int find_max_single_thread(const std::vector<int>& data) {
    return *std::max_element(data.begin(), data.end());
}

void find_max_part(const std::vector<int>& data, size_t start, size_t end, int& max_value) {
    max_value = *std::max_element(data.begin() + start, data.begin() + end);
}

int find_max_multiple_threads(const std::vector<int>& data, int num_threads) {
    std::vector<std::thread> threads;
    std::vector<int> results(num_threads);
    size_t chunk_size = data.size() / num_threads; 
    for (int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? data.size() : (i + 1) * chunk_size;
        threads.push_back(std::thread(find_max_part, std::ref(data), start, end, std::ref(results[i])));
    }

    for (auto& t : threads) {
        t.join();
    }

    return *std::max_element(results.begin(), results.end());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " -M <number of threads>\n";
        return 1;
    }

    int num_threads = std::stoi(argv[1]);
    std::vector<int> data = read_file("random.txt");

    auto start_single = std::chrono::high_resolution_clock::now();
    int max_single = find_max_single_thread(data);
    auto end_single = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_single = end_single - start_single;

    auto start_multi = std::chrono::high_resolution_clock::now();
    int max_multi = find_max_multiple_threads(data, num_threads);
    auto end_multi = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_multi = end_multi - start_multi;

    std::cout << "Numbers count: " << data.size() << std::endl;
    std::cout << "Maximum value: " << max_single << std::endl;
    std::cout << "Single thread time: " << std::fixed << std::setprecision(3) << duration_single.count() << "s" << std::endl;
    std::cout << "Multiple threads time: " << std::fixed << std::setprecision(3) << duration_multi.count() << "s" << std::endl;
    std::cout << "Results match: " << (max_single == max_multi ? "yes" : "no") << std::endl;

    return 0;
}
