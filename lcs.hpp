// lcs.hpp
#pragma once // ヘッダーが複数回インクルードされるのを防ぐおまじない

#include <string>
#include <clocale>
#include <vector>
#include <locale>
#include <codecvt>

// LCS計算アルゴリズムの関数宣言
std::string find_lcs_optimized(const std::string& s, const std::string& t);
