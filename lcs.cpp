// lcs.cpp
#include "lcs.hpp" // 対応するヘッダーをインクルード
#include <algorithm> // std::max, std::reverse のため


// string (UTF-8) から wstring へ
std::wstring string_to_wstring_linux(const std::string& str) {
    // UTF-8とwchar_tを変換するコンバータを作成
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    // from_bytesメソッドでバイト文字列からワイド文字列へ変換
    return converter.from_bytes(str);
}

// wstring から string (UTF-8) へ
std::string wstring_to_string_linux(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    // to_bytesメソッドでワイド文字列からバイト文字列へ変換
    return converter.to_bytes(wstr);
}


// lcsを動的計画法で計算
// 動的計画法のテーブルの右端の列を返す
std::vector<int> calculate_lcs_lengths(const std::wstring& s, const std::wstring& t) {
    int n = s.length();
    int m = t.length();
    std::vector<int> dp(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int preb_dp_j = dp[0];
        for (int j = 0; j < n; ++j) {
            int preb_dp_j_plus_1 = dp[j + 1];
            if (t[i] == s[j]) {
                //next_dp[j + 1] = std::max(next_dp[j + 1], dp[j] + 1);
                dp[j + 1] = preb_dp_j + 1;
            } else {
                dp[j + 1] = std::max(dp[j + 1], dp[j]);
            }
        }
        preb_dp_j = preb_dp_j_plus_1;
    }
    return dp;
}

// 再帰関数の実装
// Hirschberg's algorithm を用いて，lcsを計算
std::wstring lcs_recursive_optimized(const std::wstring& s, const std::wstring& t) {
    int n = s.length();
    int m = t.length();

    // 与えられた文字列のどちらか（もしくは両方）が空であるとき，""を返す
    if (n == 0 || m == 0) return L"";
    // 文字列tが一文字であるとき，文字列sにその文字含まれていれば，その文字を返し，そうでなければ""を返す
    if (m == 1) return (s.find(t[0]) != std::wstring::npos) ? t.substr(0, 1) : L"";
 
    int mid = m / 2;
    std::wstring t1 = t.substr(0, mid);
    std::wstring t2 = t.substr(mid);

    std::vector<int> lcs_lengths1 = calculate_lcs_lengths(s, t1);

    std::wstring s_rev = s;
    std::reverse(s_rev.begin(), s_rev.end());
    std::wstring t2_rev = t2;
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

    std::wstring part1 = lcs_recursive_optimized(s.substr(0, split_index), t1);
    std::wstring part2 = lcs_recursive_optimized(s.substr(split_index), t2);

    return part1 + part2;
}

// string型を wstring型に変更して，lcsとその長さを計算
// lcs を string型に直して，lcs とその長さを返す 
std::pair<std::string, int> find_lcs_optimized(const std::string& s, const std::string& t) {

    std::wstring ws = string_to_wstring_linux(s);
    std::wstring wt = string_to_wstring_linux(t);

    if (ws.length() > wt.length()) {
        std::wstring ans = lcs_recursive_optimized(wt, ws);
        return {wstring_to_string_linux(ans), ans.length()};
    } else {
        std::wstring ans = lcs_recursive_optimized(ws, wt);
        return {wstring_to_string_linux(ans), ans.length()};
    }
}
