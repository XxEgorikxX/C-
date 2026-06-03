#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i = i + 1;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void parallelQuickSort(vector<int>& arr, int low, int high, int num_threads) {
    if (low >= high) return;
    if (high - low + 1 < 10000 || num_threads <= 1) {
        quickSort(arr, low, high);
        return;
    }
    int pivotIndex = partition(arr, low, high);
    int left_threads = num_threads / 2;
    thread left_thread(parallelQuickSort, ref(arr), low, pivotIndex - 1, left_threads);
    parallelQuickSort(arr, pivotIndex + 1, high, num_threads - left_threads);
    left_thread.join();
}

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    auto result = func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    double duration_ms = duration_ns / 1000000.0;
    return std::make_pair(result, duration_ms);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int size = 10000;
    int num_threads = 8;
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 50000);
    for (int& x : arr) {
        x = distrib(gen);
    }
    vector<int> arr_seq = arr;
    auto [result_seq, time_seq] = measure_execution_time(
        [](vector<int>& a) { quickSort(a, 0, a.size() - 1); return a; },
        arr_seq
    );
    cout << "Быстрая сортировка: " << time_seq << " мс" << endl;
    vector<int> arr_par = arr;
    auto [result_par, time_par] = measure_execution_time(
        [](vector<int>& a, int threads) { parallelQuickSort(a, 0, a.size() - 1, threads); return a; },
        arr_par, num_threads
    );
    cout << "Параллельная быстрая сортировка (параллельная): " << time_par << " мс" << endl;
    std::cin.get();
    return 0;
}