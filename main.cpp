// main.cpp
#include "libs/httplib.h"
#include "libs/json.hpp"
#include "lcs.hpp"

using json = nlohmann::json;

int main() {
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

    std::cout << "Server is starting on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}