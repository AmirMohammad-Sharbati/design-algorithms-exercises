#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    string input_str;
    cin >> n >> input_str;

    vector<vector<int>> dp(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++)
            dp[i][j] = j - i + 1;
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = 1; k <= j - i; k++) {
                bool flag = true;
                string str;
                if ((j - i + 1) % k == 0) {
                    for (int q = 1; q < (j - i + 1) / k; q++) {
                        for (int x = 0; x < k; x++) {
                            if (input_str[i + x] != input_str[i + q * k + x]) {
                                flag = false;
                                break;
                            }
                        }
                    }
                    if (flag)
                        dp[i][j] = dp[i][i + k - 1];
                }
            }

            for (int mid = i; mid < j; mid++)
                dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
        }
    }

    cout << dp[0][n - 1];

    return 0;
}