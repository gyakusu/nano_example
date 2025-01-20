# nano example

このプロジェクトは，pythonのライブラリ，`nanobind` を用いてC++17で作成した関数・クラスをpythonから呼び出せるようにするサンプルプロジェクトです．以下の特徴を持ちます．

- C++17準拠であるため `<optional>` などのstdライブラリを使用できます．
- CMakeファイルを編集することにより，`Eigen` などのincludeがあるヘッダーをそのまま使うことができます．
- サブディレクトリ，`nanoDBRAIN` に関係ファイルを詰め込むことによって，プロジェクトへの変更を最小限に抑えています．

## 使い方

### main.cpp ファイルによる動作確認

```sh
cmake -S . -B build
cmake --build build
./build/MAIN
```

### venvの作成

```sh
~/.pyenv/versions/3.8.17/bin/python3.8 -m venv .env
```

nanobindの使用にはpython3.8が推奨されています．

### nanobindを用いたインストール

```sh
pip install nanobind scikit-build-core
pip install --no-build-isolation -ve .
```
