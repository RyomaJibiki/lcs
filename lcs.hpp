// lcs.hpp
#pragma once // ヘッダーが複数回インクルードされるのを防ぐおまじない

#include <string>
#include <vector>

// LCS計算アルゴリズムの関数宣言
std::string find_lcs_optimized(const std::string& s, const std::string& t);
