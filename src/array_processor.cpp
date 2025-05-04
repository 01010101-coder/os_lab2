#include <vector>
#include <iostream>
#include <cmath>
#include <mutex>
#include <thread>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iomanip>

class ArrayProcessor {
public:
    struct ProcessResults {
        int minimum;
        int maximum;
        int avg;
    };

private:
    static std::mutex print_mutex;
    static ProcessResults computation_results;

public:
    static void ValidateArray(const std::vector<int>& data);
    static void ProcessArray(std::vector<int>& data);

private:
    static void FindMinMax(const std::vector<int>& data);
    static void CalculateAverage(const std::vector<int>& data);
};

std::mutex ArrayProcessor::print_mutex;
ArrayProcessor::ProcessResults ArrayProcessor::computation_results;

void ArrayProcessor::ValidateArray(const std::vector<int>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Array cannot be empty");
    }
}

void ArrayProcessor::FindMinMax(const std::vector<int>& data) {
    int min_value = data[0], max_value = data[0];

    for (int num : data) {
        if (num < min_value) min_value = num;
        if (num > max_value) max_value = num;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "Min value: " << min_value << ", Max value: " << max_value << std::endl;
    }

    computation_results.minimum = min_value;
    computation_results.maximum = max_value;
}

void ArrayProcessor::CalculateAverage(const std::vector<int>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double average = sum / data.size();
    int rounded_avg = static_cast<int>(std::round(average));

    {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "Average value: " << std::fixed << std::setprecision(2) << average
                  << " (rounded: " << rounded_avg << ")" << std::endl;
    }

    computation_results.avg = rounded_avg;
}

void ArrayProcessor::ProcessArray(std::vector<int>& data) {
    ValidateArray(data);

    std::thread min_max_thread(FindMinMax, std::ref(data));
    std::thread avg_thread(CalculateAverage, std::ref(data));

    min_max_thread.join();
    avg_thread.join();

    for (int& num : data) {
        if (num == computation_results.minimum || num == computation_results.maximum) {
            num = computation_results.avg;
        }
    }
}

int main() {
    std::vector<int> arr = {1, 4, 2, 8, 5, 3};

    try {
        ArrayProcessor::ProcessArray(arr);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
