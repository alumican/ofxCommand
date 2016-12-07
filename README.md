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

## Author
**Yukiya Okuda**  
Twitter: [@alumican_net](https://twitter.com/alumican_net)  
Website: <http://alumican.net>

## License
> The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).
> 
> Copyright (c) 2016 Yukiya Okuda
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
