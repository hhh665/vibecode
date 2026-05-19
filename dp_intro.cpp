#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// ============================================================
// 动态规划（Dynamic Programming）核心思想：
// 1. 将原问题分解为重叠的子问题
// 2. 用表格/数组存储子问题的解，避免重复计算
// 3. 自底向上（bottom-up）或自顶向下（memoization）求解
// ============================================================

// ------------------- 示例一：斐波那契数列 -------------------
// F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
// 朴素递归会重复计算大量子问题，复杂度 O(2^n)
// DP 解法：用数组记录已算过的值，复杂度降为 O(n)

int fib_dp(int n) {
    vector<int> dp(n + 1);
    dp[0] = 0;
    if (n >= 1) dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// 空间优化：只需保留前两个状态，O(1) 空间
int fib_opt(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1, cur = 0;
    for (int i = 2; i <= n; ++i) {
        cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return cur;
}

// ------------------- 示例二：01 背包问题 -------------------
// 题目：有 n 件物品，每件有重量 w[i] 和价值 v[i]，
//       背包容量为 C，每件物品至多选一次，求最大总价值。
// 状态定义：dp[i][j] = 前 i 件物品、容量 j 时的最大价值
// 转移方程：
//   选第 i 件：dp[i-1][j-w[i]] + v[i]  (需 j >= w[i])
//   不选：     dp[i-1][j]
//   取两者最大值

int knapsack(const vector<int>& w, const vector<int>& v, int C) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(C + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= C; ++j) {
            if (j >= w[i - 1]) {
                // 能放下：比较选与不选
                dp[i][j] = max(dp[i - 1][j],
                               dp[i - 1][j - w[i - 1]] + v[i - 1]);
            } else {
                // 放不下，只能不选
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][C];
}

// 空间优化：滚动数组，逆序更新以避免覆盖未使用的状态
int knapsack_1d(const vector<int>& w, const vector<int>& v, int C) {
    vector<int> dp(C + 1, 0);
    for (int i = 0; i < (int)w.size(); ++i) {
        for (int j = C; j >= w[i]; --j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[C];
}

// ------------------- 示例三：最长公共子序列 (LCS) -------------------
// 题目：给定两个字符串 s1 和 s2，求最长公共子序列的长度
//       （子序列不要求连续，但保持原始顺序）
// 状态定义：dp[i][j] = s1 前 i 个字符与 s2 前 j 个字符的 LCS 长度
// 转移方程：
//   s1[i]==s2[j] → dp[i][j] = dp[i-1][j-1] + 1
//   s1[i]!=s2[j] → dp[i][j] = max(dp[i-1][j], dp[i][j-1])

int lcs_length(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// 回溯还原 LCS 字符串（技巧延伸）
string get_lcs(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    // 从终点回溯到起点
    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs;  // 匹配字符加入结果
            --i; --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    return lcs;
}

void hello_world() {
    cout << "Hello, World!" << endl;
}

// ------------------- 测试用例 -------------------
int main() {
    hello_world();
    cout << "=== Fibonacci DP ===" << endl;
    cout << "fib(10) = " << fib_dp(10) << " (DP array)" << endl;
    cout << "fib(10) = " << fib_opt(10) << " (O(1) space)" << endl;

    cout << "\n=== 01 Knapsack ===" << endl;
    // 物品：重量 {2,3,4,5}，价值 {3,4,5,6}，容量 8
    vector<int> w = {2, 3, 4, 5};
    vector<int> v = {3, 4, 5, 6};
    int C = 8;
    cout << "Max value = " << knapsack(w, v, C)
         << " (2D DP, expect 10)" << endl;
    cout << "Max value = " << knapsack_1d(w, v, C)
         << " (1D optimized, expect 10)" << endl;

    cout << "\n=== LCS ===" << endl;
    string s1 = "ABCBDAB", s2 = "BDCABA";
    cout << "LCS length of \"" << s1 << "\" and \"" << s2 << "\" = "
         << lcs_length(s1, s2) << " (expect 4)" << endl;
    cout << "LCS string = \"" << get_lcs(s1, s2)
         << "\" (expect \"BCBA\" or \"BDAB\")" << endl;

    return 0;
}
