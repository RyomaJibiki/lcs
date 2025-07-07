# 1. ベースとなる公式Pythonイメージを選択
# slim版は軽量で本番環境に適しています
FROM python:3.11-slim

# 2. コンテナ内での作業ディレクトリを設定
WORKDIR /app

# 3. 依存関係のファイルを先にコピー
# このファイルを先にコピーすることで、コードの変更時にもpip installの再実行をスキップでき、ビルドが速くなります
COPY requirements.txt requirements.txt

# 4. 依存関係をインストール
# --no-cache-dir オプションで不要なキャッシュを残さず、イメージサイズを小さく保ちます
RUN pip install --no-cache-dir -r requirements.txt

# 5. アプリケーションのコードをすべてコピー
COPY . .

# 6. アプリケーションを実行するコマンド (シェル形式に修正)
# Renderなどのホスティングサービスが指定する$PORT変数を展開するためにシェル形式で記述します
CMD gunicorn --bind 0.0.0.0:$PORT app:app
