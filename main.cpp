// main.cpp
#include "libs/httplib.h"
#include "libs/json.hpp"
#include "lcs.hpp"
#include <cstdlib> // getenvのため
#include <iostream> // coutのため

// nlohmann::json を json という別名で使う
using json = nlohmann::json;

int main() {
    // --- ★修正箇所 START★ ---
    // 環境変数 PORT からポート番号を取得します。
    // Render環境では、Renderがこの環境変数を自動で設定してくれます。
    // ローカル環境でテストする際は、この環境変数が設定されていないため、
    // デフォルト値として 8080 を使用します。
    int port = 8080; // デフォルトポート
    if (const char* env_port = std::getenv("PORT")) {
        try {
            port = std::stoi(env_port);
        } catch (const std::exception& e) {
            std::cerr << "PORT環境変数の読み取りに失敗しました: " << e.what() << std::endl;
            // エラーの場合はデフォルトポートを使用
        }
    }
    // --- ★修正箇所 END★ ---

    // HTTPサーバーのインスタンスを作成
    httplib::Server svr;

    // CORSの事前確認(Preflight)リクエストに対応するための設定
    svr.Options("/api/lcs", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.status = 200;
    });

    // POSTリクエストを処理するハンドラを設定
    svr.Post("/api/lcs", [](const httplib::Request& req, httplib::Response& res) {
        try {
            // リクエストボディからJSONをパース
            json data = json::parse(req.body);
            std::string s1 = data["s1"];
            std::string s2 = data["s2"];

            // LCSを計算
            std::pair<std::string, int> lcs_result = find_lcs_optimized(s1, s2);

            json response_json;
            response_json["lcs"] = lcs_result.first;
            response_json["length"] = lcs_result.second;

            // レスポンスヘッダーにCORS許可とJSON形式であることを設定
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(response_json.dump(), "application/json");

        } catch (const std::exception& e) {
            res.status = 400; // Bad Request
            res.set_content(e.what(), "text/plain");
        }
    });

    // --- ★修正箇所 START★ ---
    std::cout << "Server is starting on port " << port << "..." << std::endl;
    // 取得したポート番号でサーバーを起動
    svr.listen("0.0.0.0", port);
    // --- ★修正箇所 END★ ---

    return 0;
}
