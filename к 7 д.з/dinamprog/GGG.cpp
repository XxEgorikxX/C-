#include <iostream>
#include <vector>

using namespace std;

int main() {
    int m, n;
    cin >> m;
    cin >> n;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    vector<long long> dp(m + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int sum = coin; sum <= m; sum++) {
            dp[sum] += dp[sum - coin];
        }
    }

    cout << dp[m] << endl;

    return 0;
}