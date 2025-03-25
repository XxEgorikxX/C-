#include <iostream>
#include <set>
using namespace std;


void findMaxInSet(const set<int> my_set, int& el) {
    el = *prev(my_set.end());

}

void findMaxOfSetDifference(set<int> mySet1, const set<int> mySet2) {
    int maxA = 0;

    for(int i: mySet2) {
        mySet1.erase(i);
    }

    findMaxInSet(mySet1, maxA);

    std::cout << "Max element of difference A - B: " << maxA << std::endl;

    std::cout << std::endl;
}

int main() {
    set<int> A;
    set<int> B;

    

    std::cout << "Enter " << 5 << " elements for set A:" << std::endl;
    int input;
    for (int i = 0; i < 5; i++) {
        cin >> input;
        A.insert(input);
    }

    std::cout << "Enter " << 4 << " elements for set B:" << std::endl;
    for (int i = 0; i < 4; i++) {
        cin >> input;
        B.insert(input);
    }

    findMaxOfSetDifference(A, B);

    system("pause");

    return 0;
}