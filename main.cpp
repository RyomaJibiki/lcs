// main.cpp
#include "libs/httplib.h"
#include "libs/json.hpp"
#include "lcs.hpp"

using json = nlohmann::json;

int main() {

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


    httplib::Server svr;

    svr.Options("/api/lcs", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.status = 200;
    });

    svr.Post("/api/lcs", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json data = json::parse(req.body);
            std::string s1 = data["s1"];
            std::string s2 = data["s2"];

            std::string lcs_result = find_lcs_optimized(s1, s2);

            json response_json;
            response_json["lcs"] = lcs_result;
            response_json["length"] = lcs_result.length();

            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(response_json.dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(e.what(), "text/plain");
        }
    });

    std::cout << "Server is starting on port " << port << "..." << std::endl;
    // 取得したポート番号でサーバーを起動
    svr.listen("0.0.0.0", port);
    return 0;
}
