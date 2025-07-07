# app.py
from flask import Flask, request, jsonify
from flask_cors import CORS
import os

def _calculate_lcs_lengths(s: str, t: str) -> list[int]:
    n = len(s)
    m = len(t)
    dp = [0] * (n + 1)
    for i in range(m):
        prev_dp_j = dp[0]
        for j in range(n):
            prev_dp_j_plus_1 = dp[j+1]
            if t[i] == s[j]:
                dp[j + 1] = prev_dp_j + 1
            else:
                dp[j + 1] = max(prev_dp_j_plus_1, dp[j])
            prev_dp_j = prev_dp_j_plus_1
    return dp

def _lcs_recursive_optimized(s: str, t: str) -> str:
    n, m = len(s), len(t)
    if n == 0: return ""
    if m == 0: return ""
    if m == 1: return t[0] if t[0] in s else ""
    mid = m // 2
    t1, t2 = t[:mid], t[mid:]
    lcs_lengths1 = _calculate_lcs_lengths(s, t1)
    s_rev, t2_rev = s[::-1], t2[::-1]
    lcs_lengths2 = _calculate_lcs_lengths(s_rev, t2_rev)
    max_len, split_index = -1, -1
    for i in range(n + 1):
        current_len = lcs_lengths1[i] + lcs_lengths2[n - i]
        if current_len > max_len:
            max_len, split_index = current_len, i
    part1 = _lcs_recursive_optimized(s[:split_index], t1)
    part2 = _lcs_recursive_optimized(s[split_index:], t2)
    return part1 + part2

def find_lcs_optimized(s: str, t: str) -> str:
    if len(s) > len(t):
        return _lcs_recursive_optimized(t, s)
    else:
        return _lcs_recursive_optimized(s, t)


# Flaskアプリケーションの初期化
app = Flask(__name__)
# フロントエンドからのリクエストを許可する (CORS設定)
CORS(app)

# '/api/lcs' というURLへのリクエストを処理するAPIエンドポイント
@app.route('/api/lcs', methods=['POST'])
def get_lcs():
    # フロントエンドから送られてきたJSONデータを取得
    data = request.get_json()
    if not data or 's1' not in data or 's2' not in data:
        return jsonify({'error': 'Invalid input'}), 400

    s1 = data['s1']
    s2 = data['s2']

    # LCSを計算
    lcs_result = find_lcs_optimized(s1, s2)

    # 結果をJSON形式でフロントエンドに返す
    return jsonify({
        'lcs': lcs_result,
        'length': len(lcs_result)
    })

# このファイルが直接実行された場合にサーバーを起動
if __name__ == '__main__':
    port = int(os.environ.get('PORT', 5000))
    # debug=Trueは開発時のみ有効にし、本番環境ではFalseにするのが望ましい
    app.run(host='0.0.0.0', port=port, debug=os.environ.get('ENV') != 'production')
