// lcs.cpp
#include "lcs.hpp" // 対応するヘッダーをインクルード
#include <algorithm> // std::max, std::reverse のため

// ヘルパー関数の実装
std::vector<int> calculate_lcs_lengths(const std::string& s, const std::string& t) {
    int n = s.length();
    int m = t.length();
    std::vector<int> dp(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        std::vector<int> next_dp = dp;
        for (int j = 0; j < n; ++j) {
            if (t[i] == s[j]) {
                next_dp[j + 1] = std::max(next_dp[j + 1], dp[j] + 1);
            } else {
                next_dp[j + 1] = std::max(dp[j + 1], next_dp[j]);
            }
        }
        dp = next_dp;
    }
    return dp;
}

// 再帰関数の実装
std::string lcs_recursive_optimized(const std::string& s, const std::string& t) {
    int n = s.length();
    int m = t.length();

    if (n == 0 || m == 0) return "";
    if (m == 1) return (s.find(t[0]) != std::string::npos) ? t.substr(0, 1) : "";

    int mid = m / 2;
    std::string t1 = t.substr(0, mid);
    std::string t2 = t.substr(mid);

    std::vector<int> lcs_lengths1 = calculate_lcs_lengths(s, t1);

    std::string s_rev = s;
    std::reverse(s_rev.begin(), s_rev.end());
    std::string t2_rev = t2;
    std::reverse(t2_rev.begin(), t2_rev.end());
    std::vector<int> lcs_lengths2 = calculate_lcs_lengths(s_rev, t2_rev);

    int max_len = -1, split_index = -1;
    for (int i = 0; i <= n; ++i) {
        int current_len = lcs_lengths1[i] + lcs_lengths2[n - i];
        if (current_len > max_len) {
            max_len = current_len;
            split_index = i;
        }
    }

    std::string part1 = lcs_recursive_optimized(s.substr(0, split_index), t1);
    std::string part2 = lcs_recursive_optimized(s.substr(split_index), t2);

    return part1 + part2;
}

// 呼び出し元の関数の実装
std::string find_lcs_optimized(const std::string& s, const std::string& t) {
    if (s.length() > t.length()) {
        return lcs_recursive_optimized(t, s);
    } else {
        return lcs_recursive_optimized(s, t);
    }
}
