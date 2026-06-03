#include <iostream>
#include <vector>

using namespace std;

int firstOccurrence(const vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == x) {
            ans = mid;
            r = mid - 1;
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

int lastOccurrence(const vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == x) {
            ans = mid;
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
    return 0;
}