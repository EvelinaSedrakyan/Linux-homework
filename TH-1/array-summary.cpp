#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <atomic>

// Function to sum the array using a regular for loop
long long sum_array(const std::vector<int>& arr) {
    long long sum = 0;
    for (size_t i = 0; i < arr.size(); ++i) {  // Change int to size_t
        sum += arr[i];
    }
    return sum;
}

// Function for each thread to sum a portion of the array
void sum_portion(const std::vector<int>& arr, int start, int end, std::atomic<long long>& partial_sum) {
    for (int i = start; i < end; ++i) {
        partial_sum += arr[i];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <M>\n";
        return 1;
    }

    int N = std::stoi(argv[1]); // size of the array
    int M = std::stoi(argv[2]); // number of threads

    // Initialize the array with random values
    std::vector<int> arr(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    
    for (int i = 0; i < N; ++i) {
        arr[i] = dist(gen);
    }

    // Compute summary without threads (regular for loop)
    auto start = std::chrono::high_resolution_clock::now();
    long long sum_without_threads = sum_array(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_without_threads = end - start;

    // Output the result
    std::cout << "Sum without threads: " << sum_without_threads << std::endl;  // Added this line
    std::cout << "Time spent without threads: " << duration_without_threads.count() << " seconds\n";

    // Compute summary with threads
    std::atomic<long long> sum_with_threads(0);
    std::vector<std::thread> threads;
    int portion_size = N / M;

    start = std::chrono::high_resolution_clock::now();

    // Launch M threads
    for (int i = 0; i < M; ++i) {
        int start_index = i * portion_size;
        int end_index = (i == M - 1) ? N : (i + 1) * portion_size;  // Handle last portion
        threads.push_back(std::thread(sum_portion, std::cref(arr), start_index, end_index, std::ref(sum_with_threads)));
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_with_threads = end - start;

    // Output the results
    std::cout << "Time spent with " << M << " threads: " << duration_with_threads.count() << " seconds\n";

    return 0;
}
