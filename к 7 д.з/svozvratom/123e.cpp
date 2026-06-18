#include <iostream>
#include <vector>

using namespace std;

bool backtracking(int i, int sum, int k, const vector<int>& a) {
    if (sum > k) {
        return false;
    }
    if (sum == k) {
        return true;
    }
    if (i == (int)a.size()) {
        return false;
    }
    if (backtracking(i + 1, sum + a[i], k, a)) {
        return true;
    }
    if (backtracking(i + 1, sum, k, a)) {
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
    bool found = backtracking(0, 0, k, a);
    if (found) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}