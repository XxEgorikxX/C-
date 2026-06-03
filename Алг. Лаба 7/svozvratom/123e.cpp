#include <iostream>
#include <vector>

using namespace std;

bool backtracking(const vector<int>& a, int k, int index, int sum) {
    if (sum == k) {
        return true;
    }
    if (index == a.size()) {
        return false;
    }
    if (backtracking(a, k, index + 1, sum + a[index])) {
        return true;
    }
    if (backtracking(a, k, index + 1, sum)) {
        return true;
    }
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (backtracking(a, k, 0, 0)) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    return 0;
}