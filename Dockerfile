# Dockerfile

# ベースとなるイメージ（GCCコンパイラが含まれている）
FROM gcc:latest

# 作業ディレクトリを作成
WORKDIR /app

# プロジェクトのファイルをコンテナにコピー
COPY . .

# Makefileを使ってアプリケーションをビルドする
RUN make

# サーバーが使用するポートを公開
EXPOSE 10000

# コンテナ起動時に実行するコマンド
CMD ["./server"]
