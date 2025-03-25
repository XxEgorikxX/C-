#include <iostream>

void findMaxInArray(const int* arr, int size, int& el, int& indexOfMax) {
    el = arr[0];
    indexOfMax = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > el) {
            el = arr[i];
            indexOfMax = i;
        }
    }
}

void findArrayWithMaxElement(const int* arrA, const int* arrB, int sizeA, int sizeB) {
    int maxA = 0, maxB = 0, indexOfMaxA = 0, indexOfMaxB = 0;

    findMaxInArray(arrA, sizeA, maxA, indexOfMaxA);
    findMaxInArray(arrB, sizeB, maxB, indexOfMaxB);

    if (maxA > maxB) {
        std::cout << "Array A with biggest value" << std::endl;
        std::cout << "Value: " << maxA << std::endl << "Index:" << indexOfMaxA << std::endl;
    } else {
        std::cout << "Array B with biggest value" << std::endl;
        std::cout << "Value: " << maxB << std::endl << "Index:" << indexOfMaxB << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    int nA = 5;
    int nB = 4;

    int* arrayA = new int[nA];
    int* arrayB = new int[nB];

    std::cout << "Enter " << nA << " elements for array A:" << std::endl;
    for (int i = 0; i < nA; i++) {
        std::cin >> arrayA[i];
    }

    std::cout << "Enter " << nB << " elements for array B:" << std::endl;
    for (int i = 0; i < nB; i++) {
        std::cin >> arrayB[i];
    }

    findArrayWithMaxElement(arrayA, arrayB, nA, nB);

    delete[] arrayA;
    delete[] arrayB;

    system("pause");

    return 0;
}