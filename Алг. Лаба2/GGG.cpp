#include <iostream>
#include <cmath>

double simpson_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++; // Делаем n четным
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i += 2)
        sum += 4 * f(a + i * h);

    for (int i = 2; i < n - 1; i += 2)
        sum += 2 * f(a + i * h);

    return (h / 3) * sum;
}

double function1(double x) {
    return sin(x)+3;
}

double function2(double x) {
    return sin(x)+5;
}

double diff(double x) {
    return function2(x) - function1(x);
}

int main() {
    double a = 1.0;
    double b = 2.0;
    double area = simpson_rule(diff, a, b, 1000);
    std::cout << "Приближенное значение интеграла: " << area << std::endl;
    return 0;
}