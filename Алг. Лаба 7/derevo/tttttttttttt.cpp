#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int findMax(vector<int>& tree, int i) {
    if (i >= tree.size()) {
        return 0;
    }

    return max(tree[i],
        max(findMax(tree, 2 * i + 1),
            findMax(tree, 2 * i + 2)));
}

int main() {
    vector<int> tree = { 5, 3, 8, 1, 4, -1, 10 };

    cout << findMax(tree, 0);

    return 0;
}