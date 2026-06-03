#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    vector<vector<long long>> dp(n + 1, vector<long long>(2, 1e18));
    vector<vector<int>> used_coupon(n + 1, vector<int>(2, 0));
    dp[n][0] = 0;
    dp[n][1] = 1e18;
    for (int i = n - 1; i >= 0; i--) {
        for (int k = 0; k <= 1; k++) {
            int new_k = k;
            if (p[i] > 500) new_k = 1;
            dp[i][k] = p[i] + dp[i + 1][new_k];
            used_coupon[i][k] = 0;
            if (k == 1 && dp[i + 1][0] < dp[i][k]) {
                dp[i][k] = dp[i + 1][0];
                used_coupon[i][k] = 1;
            }
        }
    }
    vector<int> coupon_days;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (used_coupon[i][k] == 1) {
            coupon_days.push_back(i + 1);
            k = 0;
        }
        else {
            if (p[i] > 500) {
                k = 1; 
            }
        }
    }
    cout << dp[0][0] << endl;
    cout << coupon_days.size() << endl;
    for (int day : coupon_days) {
        cout << day << " ";
    }
    cout << endl;
    return 0;
}