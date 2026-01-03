## C++ 高速ログ解析ツール
大量ログファイルからエラーを抽出・集計しランキング表示とCSV出力を行うCLIツールです。

### ビルド
g++ -std=c++17 -o analyze analyze.cpp

### 実行
./analyze ./logs/

### 特徴
- ERROR / Exception キーワード抽出
- 発生頻度ランキング
- CSV出力（Excelで閲覧可能）
- 企業依存データなし（個人開発サンプル）
