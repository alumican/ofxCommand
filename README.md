# ofxCommand

ofxCommandは複雑な処理を直感的に記述するためのopenFrameworksアドオンです。  
Progression(AS3)のCommandライブラリに似た使い勝手になっています。  

## Install
1. `openFrameworks/addons/`に`ofxCommand`フォルダごと配置します。
2. projectGeneratorの`Addons`から`ofxCommand`を選択してGenerateもしくはUpdateします。
3. ヘッダファイルにincludeします。
4. ofxCommandは`cmd`名前空間に定義されているので、必要であれば`cmd`名前空間を`using`します。  
```cpp
#include "ofxCommand.h"
using namespace cmd;
```
   
## フロー制御

### Serial

### Parallel

### Loop

## イベント制御

### Listen

### Notify

## アニメーション制御

### Wait

### Tween

## 変数 / 関数制御

### Var

### Function

## その他

### Log
