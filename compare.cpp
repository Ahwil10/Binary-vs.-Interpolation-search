#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

// Binary Search Implementation
int binarySearch(const std::vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Interpolation Search Implementation
int interpolationSearch(const std::vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }

        // Probing the position with interpolation formula
        long long pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));

        if (arr[pos] == key) return pos;
        if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int main() {
    const int SIZE = 10000000;
    std::vector<int> numbers(SIZE);

    // 1. Generate 10,000,000 random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, SIZE * 2);

    for (int i = 0; i < SIZE; ++i) {
        numbers[i] = distrib(gen);
    }

    // Sort the array (required for both algorithms)
    std::sort(numbers.begin(), numbers.end());

    // Select a key that we know exists in the array
    int keyToFind = numbers[SIZE / 2];

    // 2. Measure Binary Search
    auto start_bs = std::chrono::high_resolution_clock::now();
    int result_bs = binarySearch(numbers, keyToFind);
    auto end_bs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed_bs = end_bs - start_bs;

    // 3. Measure Interpolation Search
    auto start_is = std::chrono::high_resolution_clock::now();
    int result_is = interpolationSearch(numbers, keyToFind);
    auto end_is = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed_is = end_is - start_is;

    // Report execution times
    std::cout << "Key found at index: " << result_bs << "\n";
    std::cout << "Binary Search Execution Time: " << elapsed_bs.count() << " microseconds\n";
    std::cout << "Interpolation Search Execution Time: " << elapsed_is.count() << " microseconds\n";

    return 0;
}
