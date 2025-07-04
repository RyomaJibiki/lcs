# Dockerfile
FROM gcc:latest
WORKDIR /app
COPY . .
RUN make
# RenderはPORT環境変数を設定するので、EXPOSEはドキュメントとしての意味合いが強い
EXPOSE 10000 
CMD ["./server"]
