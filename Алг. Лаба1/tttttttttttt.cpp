#include <iostream>
#include <vector>
#include <chrono>

std::vector<int> InsertIntoVector(std::vector<int> massiv, int index, int value) {
    if (index < 0 || index > massiv.size()) {
        return massiv;
    }
    massiv.insert(massiv.begin() + index, value);
    return massiv;
}

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    auto result = func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность в миллисекундах
    return std::make_pair(result, duration.count());  // Возвращаем результат и время выполнения
}


int main() {
    std::vector<int> main_massiv;
    for (int i = 0; i < 10000; i++) {
        main_massiv.push_back(i);
    }

    auto [result, execution_time] = measure_execution_time(InsertIntoVector, main_massiv, 2, 123);

    std::cout << "Результат: " << result.size() << std::endl;

    std::cout << "Время выполнения: " << execution_time << " мс" << std::endl;

    return 0;
}