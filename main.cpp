// main.cpp
#include "libs/httplib.h"
#include "libs/json.hpp"
#include "lcs.hpp"
#include <cstdlib> // getenvのため
#include <iostream> // coutのため

// nlohmann::json を json という別名で使う
using json = nlohmann::json;

int main() {

    // ポート番号の決定
    int port = 8080; // デフォルトポート
    if (const char* env_port = std::getenv("PORT")) {
        try {
            port = std::stoi(env_port);
        } catch (const std::exception& e) {
            std::cerr << "PORT環境変数の読み取りに失敗しました: " << e.what() << std::endl;
            // エラーの場合はデフォルトポートを使用
        }
    }

    // HTTPサーバーのインスタンスを作成
    httplib::Server svr;

    // CORSの事前確認(Preflight)リクエストに対応するための設定
    svr.Options("/api/lcs", [](const httplib::Request&, httplib::Response& res) {
        // どのオリジン（ドメイン）からのリクエストを許可するか
        res.set_header("Access-Control-Allow-Origin", "*");
        // 実際にリクエストで許可するHTTPヘッダー
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        // 実際のリクエストで許可するHTTPメソッド
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.status = 200;
    });

    // POSTリクエストを処理するハンドラを設定
    svr.Post("/api/lcs", [](const httplib::Request& req, httplib::Response& res) {
        try {
            // リクエストボディからJSONをパース(構文解析)
            // 例）"{\"s1\":\"hello\",\"s2\":\"world\"}" → {"s1": "hello", "s2": "world"}
            json data = json::parse(req.body);
            std::string s1 = data["s1"];
            std::string s2 = data["s2"];

            // LCSを計算
            std::pair<std::string, int> lcs_result = find_lcs_optimized(s1, s2);

            json response_json;
            response_json["lcs"] = lcs_result.first;
            response_json["length"] = lcs_result.second;

            // レスポンスデータのアクセス許可
            res.set_header("Access-Control-Allow-Origin", "*");
            // シリアライズ（パースの逆），Content-Type を application/json に設定
            res.set_content(response_json.dump(), "application/json");

        } catch (const std::exception& e) {
            res.status = 400; // Bad Request
            res.set_content(e.what(), "text/plain");
        }
    });

    std::cout << "Server is starting on port " << port << "..." << std::endl;
    svr.listen("0.0.0.0", port);

    return 0;
}
