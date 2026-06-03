#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    auto result = func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность
    return std::make_pair(result, duration.count());  // Возвращаем результат и время выполнения
}

std::vector<int> MergeSort(std::vector<int>& vec) {
    if (vec.size() > 1) {
        int mid = vec.size() / 2;
        std::vector<int> left(vec.begin(), vec.begin() + mid);
        std::vector<int> right(vec.begin() + mid, vec.end());
        MergeSort(left);
        MergeSort(right);
        int i = 0;
        int j = 0;
        int k = 0;
        while ((i < left.size()) and (j < right.size()))
        {
            if (left[i] < right[j]) {
                vec[k] = left[i];
                i++;
            }
            else
            {
                vec[k] = right[j];
                j++;
            }
            k++;
        }
        while (i < left.size()) {
            vec[k] = left[i];
            i++;
            k++;
        }
        while (j < right.size())
        {
            vec[k] = right[j];
            j++;
            k++;
        }
    }
    return vec;
}

std::vector<int> CombineBaskets(std::vector<std::vector<int>>& baskets) {
    std::vector<int> Combine;
    for (std::vector<int>& basket : baskets) {
        Combine.insert(Combine.end(), basket.begin(), basket.end());
    }
    return Combine;
}

void SortRad(std::vector<int>& vec, int& rad) {
    std::vector<std::vector<int>> baskets(10);
    for (int value : vec)
    {
        int indBacket = (value / rad) % 10;
        baskets[indBacket].push_back(value);
    }
    vec = CombineBaskets(baskets);
}


std::vector<int> RadixSort(std::vector<int>& vec) {
    int maxValue = *std::max_element(vec.begin(), vec.end());
    int rad = 1;
    while (maxValue / rad > 0)
    {
        SortRad(vec, rad);
        rad = rad * 10;
    }
    return vec;
}

int Separator(std::vector<int>& vec, int down, int high)
{
    int main = vec[high];
    int i = down - 1;
    for (int j = down; j <= high - 1; j++)
    {
        if (vec[j] <= main)
        {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void QuickSort(std::vector<int>& vec, int down, int high) {
    if (down < high)
    {
        int mainIndex = Separator(vec, down, high);
        QuickSort(vec, down, mainIndex - 1);
        QuickSort(vec, mainIndex + 1, high);
    }
}

std::vector<int> Data(int& n) {
    std::vector<int> vec(n);
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = std::rand() % 1000000;
    }
    return vec;
}

std::vector<int> Quick_sort(std::vector<int>& vec) {
    QuickSort(vec, 0, vec.size() - 1);
    return vec;
}

int main() {
    int base[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };
    for (int i : base) {
        std::vector<int> vec = Data(i);
        auto [result, execution_time] = measure_execution_time(RadixSort, vec);
        std::cout << execution_time << std::endl;
    }
    std::cout << "" << std::endl;
    for (int i : base) {
        std::vector<int> vec = Data(i);
        auto [result, execution_time] = measure_execution_time(MergeSort, vec);
        std::cout << execution_time << std::endl;
    }
    std::cout << "" << std::endl;
    for (int i : base) {
        std::vector<int> vec = Data(i);
        auto [result, execution_time] = measure_execution_time(Quick_sort, vec);
        std::cout << execution_time << std::endl;
    }
    return 0;
}