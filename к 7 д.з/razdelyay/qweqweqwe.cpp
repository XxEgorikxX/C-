#include <iostream>
#include <vector>

using namespace std;

int binarySearchOccurrence(const vector<int>& a, int x, bool first) {
    int l = 0;
    int r = a.size() - 1;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == x) {
            ans = mid;
            if (first)
                r = mid - 1;
            else
                l = mid + 1;
        }
        else if (a[mid] < x) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int target;
    cin >> target;
    int first = binarySearchOccurrence(nums, target, true);
    if (first == -1) {
        cout << "n/a" << endl;
        return 0;
    }

    int last = binarySearchOccurrence(nums, target, false);
    cout << first << " " << last << endl;

    return 0;
}