# API


## API関数の返り値

```
typedef enum {
  LED_BAR =1,
  LED_CIRCULAR,
  P98X3_LED,
  NEO_PIXEL_LED,
  SIMPLE_COLOR_LED,
  SIMPLE_MONO_LED
} UnifiedLedType;

typedef enum {
  LED_FORWARD = 1,
  LED_REVERSE,
  PULL_UP,
  PULL_DOWN
} UnifiedLedMode;

typedef enum {
  LED_FUNCTION_UNSUPPORTED = 1,
  LED_FUNCTION_SUCCESS,
  LED_FUNCTION_FAIL,
} ledFunctionReturnValue;
```



## クラスオブジェクトの作成と初期化

### マイコン制御ではないモノクロLED
```
UnifiedLED(uint8_t pin, UnifiedLedMode mode);
ledFunctionReturnValue begin();
```
オブジェクトの生成の際に，モードを指定する必要があるが，以下の「``enum``」のうち，「``PULL_UP``」か「``PULL_DOWN``」かのいずれかを用いる．
「``PULL_UP``と``PULL_DOWN``」の違いは，「``pin``」で指定したArduinoの端子の電圧を``HIGH``と``LOW``のいずれの場合に点灯するかで決める．
```
typedef enum {
  LED_FORWARD = 1,
  LED_REVERSE,
  PULL_UP,
  PULL_DOWN
} UnifiedLedMode;
```

### アノードコモン/カソードコモンのフルカラーLED
```
UnifiedLED(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin, UnifiedLedMode mode);
ledFunctionReturnValue begin();
```
クラスオブジェクトを生成する際には，引数としてRGBの各ピンに接続するArduinoの端子を与える．また，モードを指定する必要があるが，
以下の「``enum``」のうち，「``PULL_UP``」か「``PULL_DOWN``」かのいずれかを用いる．
「``PULL_UP``と``PULL_DOWN``」の違いは，「``pin``」で指定したArduinoの端子の電圧を``HIGH``と``LOW``のいずれの場合に点灯するかで決める．
```
typedef enum {
  LED_FORWARD = 1,
  LED_REVERSE,
  PULL_UP,
  PULL_DOWN
} UnifiedLedMode;
```


### ``MY9221``をコントローラーとして用いるLEDの場合([Grove - Circular LED][GroveCircularLED]や[Grove - LED Bar][GroveLEDBar])
このクラスオブジェクトを使用するためには，[Grove_LED_Bar](https://github.com/Seeed-Studio/Grove_LED_Bar)を利用した
クラスオブジェクトを生成し，そのオブジェクトの本APIのオブジェクトを作成するパラメータとして利用する必要がある．(詳細は各製品や[Grove_LED_Bar](https://github.com/Seeed-Studio/Grove_LED_Bar)を参照)

[Grove - Circular LED][GroveCircularLED]の場合，以下のように定義するが，第1引数は「クロックピン」，第2引数は「データピン」，第3引数は「方向性」を指定する．
```
Grove_LED_Bar bar(6, 7, 0, LED_CIRCULAR_24);
```
同じく，[Grove - LED Bar][GroveLEDBar]の場合は下のようになる．
```
Grove_LED_Bar bar(7, 6, 0, LED_BAR_10);
```

上記のような方法で作成したクラスオブジェクト``bar``を用いて本APIのクラスオブジェクトを作成する．
```
UnifiedLED(Grove_LED_Bar* bar, UnifiedLedType type, uint32_t leds, UnifiedLedMode mode);
ledFunctionReturnValue begin();
```
ここで，第2引数はLEDの種別を指定する必要があるが，[Grove - Circular LED][GroveCircularLED]の場合は以下の``enum``の``LED_CIRCULAR``を使い，
[Grove - LED Bar][GroveLEDBar]の場合は``LED_BAR``を使う．
```
typedef enum {
  LED_BAR =1,
  LED_CIRCULAR,
  P98X3_LED,
  NEO_PIXEL_LED,
  SIMPLE_COLOR_LED,
  SIMPLE_MONO_LED
} UnifiedLedType;

```
また，第3引数では，点灯の向きを指定するため，以下の``enum``の``LED_FORWARD``もしくは``LED_REVERSE``を使用する．
```
typedef enum {
  LED_FORWARD = 1,
  LED_REVERSE,
  PULL_UP,
  PULL_DOWN
} UnifiedLedMode;
```


### ``P9813``等のICをコントローラとして内蔵しているLED([チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]等)の場合
[ChainableLED](https://github.com/pjpmarques/ChainableLED)を利用してクラスオブジェクトを生成し，そのオブジェクトを使って，
本APIのクラスオブジェクトを作成する必要がある．

```
ChainableLED leds(クロックピン, データピン, LEDの数);
```
上で作成したクラスオブジェクトを用いて，下の関数を使って，クラスオブジェクトを生成する．
```
UnifiedLED(ChainableLED* chain, UnifiedLedType type, uint32_t leds);
ledFunctionReturnValue begin();
```
第2引数では，種別を指定する必要があるため，下の``enum``の``P98X3_LED``を指定する．
```
typedef enum {
  LED_BAR =1,
  LED_CIRCULAR,
  P98X3_LED,
  NEO_PIXEL_LED,
  SIMPLE_COLOR_LED,
  SIMPLE_MONO_LED
} UnifiedLedType;

```
第3引数はLEDの個数を指定する．LEDの個数は[ChainableLED](https://github.com/pjpmarques/ChainableLED)のクラスオブジェクトを
作成する際に使っているが，こちらでも必要になる．


### ``Adafruit NeoPixel``ライブラリを利用するLEDの場合([Grove RGB LED スティック][Grove_RGB_LEDスティック]等)
本APIでのクラスオブジェクトを作成する前に，[Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)を使って
``Adafruit_NeoPixel``のクラスオブジェクトを作成しておく．下は，``Adafruit NeoPixel``ライブラリのexampleのうち，
[strandtest](https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino)の
オブジェクト生成部分である．
```
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
```

上の手順で作成した``Adafruit_NeoPixel``の
オブジェクトを利用して本APIのクラスオブジェクトを生成する．
```
UnifiedLED(Adafruit_NeoPixel* pixel, UnifiedLedType type, uint32_t leds);
ledFunctionReturnValue begin();
```
第2引数では，種別を指定する必要があるため，下の``enum``の``NEO_PIXEL_LED``を指定する．
```
typedef enum {
  LED_BAR =1,
  LED_CIRCULAR,
  P98X3_LED,
  NEO_PIXEL_LED,
  SIMPLE_COLOR_LED,
  SIMPLE_MONO_LED
} UnifiedLedType;

```
第3引数はLEDの個数を指定する．


## 動作モード設定
この機能が利用可能なのは，``MY9221``をコントローラーとして用いるLEDのみであり，それ以外の場合は``LED_FUNCTION_UNSUPPORTED``が返される．
```
ledFunctionReturnValue setMode(UnifiedLedMode mode);
```
引数で指定するのは，以下の``enum``の``LED_FORWARD``もしくは``LED_REVERSE``である．
```
typedef enum {
  LED_FORWARD = 1,
  LED_REVERSE,
  PULL_UP,
  PULL_DOWN
} UnifiedLedMode;
```

## LEDの種別を取得
このメンバ関数は，LEDオブジェクトの種類が何であるかを返す．
```
UnifiedLedType getType(void);
```
返り値は以下の``enum``のいずれかとなる．
```
typedef enum {
  LED_BAR =1,
  LED_CIRCULAR,
  P98X3_LED,
  NEO_PIXEL_LED,
  SIMPLE_COLOR_LED,
  SIMPLE_MONO_LED
} UnifiedLedType;

```

## LEDの数を変更
マイコン制御のLEDにおいて，コントローラーに設定するLED数を変更する場合に用いる．
```
ledFunctionReturnValue setLedNum(uint32_t count);
```

## ``MY9221``用いたLEDにおいて，光るLEDの個数の設定
この機能が利用可能なのは，``MY9221``をコントローラーとして用いるLEDのみであり，それ以外の場合は``LED_FUNCTION_UNSUPPORTED``が返される．
```
ledFunctionReturnValue setLevel(float level);
```
[Grove - LED Bar][GroveLEDBar]は，10個のLEDを備えており，``setLevel(float level)``で
0から10までの値を設定すると，その値に相当する数のLEDが光る．

## モノクロLEDの輝度設定
``MY9221``をコントローラーとして用いるモノクロLEDや，通常のLEDをPMW制御可能なデジタル端子に接続している場合に
この機能を用いて，特定のLEDの輝度を設定することができる．

下のメンバ関数は，``MY9221``を用いるLEDの場合に，``ledNo``番目のLEDの輝度を``brightness``(0から1の間の値)
に設定する．通常のLEDに対して，下のメンバ関数を適用する場合，``ledNo``が0の場合のみ意味がある．
```
ledFunctionReturnValue setLed(uint32_t ledNo, float brightness);
```
通常のLEDの場合は，led番号を指定するのは無意味であるため，以下のメンバ関数を用いる．こちらのメンバ関数は``MY9221``コントローラーを
用いるLEDでは利用できない．
```
ledFunctionReturnValue setLed(float brightness);
```

## カラーLEDの色設定
カソードコモン，もしくはアノードコモンのカラーLEDの場合は，r,g,bを0から255の間の値を指定して，以下のメンバ関数で色を設定する．
```
ledFunctionReturnValue setLed(byte red, byte green, byte blue);
```

[Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)や[ChainableLED](https://github.com/pjpmarques/ChainableLED)を
用いるLEDの場合は，下のメンバ関数を用いて，特定の番号のLEDの色を設定する．
このメンバ関数をカソードコモン，もしくはアノードコモンのカラーLEDに適用する場合，``ledNo``の値が0の場合のみ色設定が働く．
```
ledFunctionReturnValue setLed(uint32_t ledNo, byte red, byte green, byte blue);
```

## モノクロLEDの輝度設定(整数の利用)
[Grove - Circular LED][GroveCircularLED]や[Grove - LED Bar][GroveLEDBar]で一定の数のLEDを点灯させる場合，引数(整数)で
点灯させるLEDを2進数の各桁で指定する(1とした桁に対応するLEDが点灯する)．


[Grove LED 赤 Arduino用][GroveRedLED]のような通常のLEDに適用した場合は，引数の値が0から255までの値の場合は，
その値がPMW制御の値と解釈され，輝度として反映される．もし，255以上の値の場合は，255と見なされる．
```
ledFunctionReturnValue setOnce(uint32_t value);
```


## カラーLEDの色設定(整数の利用)
[Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)や[ChainableLED](https://github.com/pjpmarques/ChainableLED)を
用いるLEDの場合は，``value``の値を2進数として解釈し，値が1となっている桁に対応するLEDに``red``,``green``,``blue``で指定した色を設定し，
値が0になっている桁に対応しているLEDは消灯する．

カソードコモン，もしくはアノードコモンのカラーLEDに適用する場合，``value``をPMWの制御の値(0から255)に相当するとみなして，
``red``,``green``,``blue``のピンにPMW制御を用いて電圧をかける．
```
ledFunctionReturnValue setOnce(uint32_t value, byte red, byte green, byte blue);
```

<!-- LED -->

|種類|名称|コントローラ|動作電圧(V)|
|---|---|---|---|
|モノクロLED|[Grove LED 赤 Arduino用][GroveRedLED]|なし|5|
||[Grove - Circular LED][GroveCircularLED]|MY9221|5|
||[Grove - LED Bar][GroveLEDBar]|MY9221|3.3/5|
|カラーLED|[RGBフルカラーLED 5mm OSTA5131A カソードコモン][OSTA5131A]|なし|5?|
||[チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]|P9813|5|
||[Grove RGB LED スティック][Grove_RGB_LEDスティック]|WS2813(NeoPixel)|3.3/5|

<!-- Grove LED 赤 Arduino用 -->
[GroveRedLED]: https://wiki.seeedstudio.com/ja/Grove-Red_LED/
<!-- Grove RGB LED スティック -->
[Grove_RGB_LEDスティック]: https://wiki.seeedstudio.com/ja/Grove-RGB_LED_Stick-10-WS2813_Mini/
<!-- チェーン接続可能 Grove RGB LED -->
[GroveChainableRGB_Led]: https://wiki.seeedstudio.com/Grove-Chainable_RGB_LED/
<!-- Grove - LED Bar -->
[GroveLEDBar]: https://wiki.seeedstudio.com/Grove-LED_Bar/
<!-- Grove - Circular LED -->
[GroveCircularLED]: https://wiki.seeedstudio.com/Grove-Circular_LED/
<!-- マイコン内蔵RGBLED 5mm PL9823-F5 -->
[PL9823F5]: https://akizukidenshi.com/catalog/g/g108411/
<!-- RGBフルカラーLED 5mm OSTA5131A カソードコモン -->
[OSTA5131A]: https://akizukidenshi.com/catalog/g/g102476/




<!-- Arduino 本体 -->

|機種名|コア|MCU|動作電圧|
|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|Xtensa LX6|ESP32-S3|3.3V|
|[Arduino Mega 2560][Mega2560]|AVR|ATmega2560|5V|
|[Arduino M0 pro][M0Pro]|ARM Cortex-M0+|ATSAMD21G18|3.3V|
|[Arduino UNO R4 WiFi][UnoR4WiFi]|ARM Cortex-M4|RA4M1|5V|
|[Arduino UNO R4 Minima][UnoR4Minima]|ARM Cortex-M4|RA4M1|5V|
|[Arduino Nano 33 IoT][Nano33IoT]|ARM Cortex-M0+|SAMD21|3.3V|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|ARM Cortex-M7|STM32H747XI|3.3V|
|[Arduino MKR WiFi 1010][MKRWiFi1010]|ARM Cortex-M0+|SAMD21|3.3V|
|[Ardino MKR Zero][MKRZero]|ARM Cortex-M0+|SAMD21|3.3V|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|ARM Cortex-M0+|Raspberry Pi RP2040|3.3V|

<!-- Arduino Nano ESP32 -->
[NanoESP32]:https://docs.arduino.cc/hardware/nano-esp32/
<!--Arduino Mega 2560-->
[Mega2560]:https://docs.arduino.cc/hardware/mega-2560/
<!--Arduino M0 pro-->
[M0Pro]:https://docs.arduino.cc/retired/boards/arduino-m0-pro/
<!--Arduino UNO R4 WiFi-->
[UnoR4WiFi]:https://docs.arduino.cc/hardware/uno-r4-wifi/
<!--Arduino UNO R4 Minima-->
[UnoR4Minima]:https://docs.arduino.cc/hardware/uno-r4-minima/
<!--Arduino Nano 33 IoT-->
[Nano33IoT]:https://docs.arduino.cc/hardware/nano-33-iot/
<!--Arduino Giga R1 Wifi-->
[GigaR1WiFi]:https://docs.arduino.cc/hardware/giga-r1-wifi/
<!--Arduino MKR WiFi 1010-->
[MKRWiFi1010]:https://docs.arduino.cc/hardware/mkr-wifi-1010/
<!--Ardino MKR Zero-->
[MKRZero]:https://docs.arduino.cc/hardware/mkr-zero/
<!--Arduino Nano RP2040 Connect-->
[NanoRP2040Connect]:https://docs.arduino.cc/hardware/nano-rp2040-connect/




<!--- コメント
[Adafruit Unified Sensor Driver][AdafruitUSD]
[Groveシールド][shield]
[Arduino M0 Pro][M0Pro]
[Arduino Due][Due]
[Arduino Uno R3][Uno]
[Arduino Mega2560 R3][Mega]
[Arduino Leonardo Ethernet][LeonardoEth]
[Arduino Pro mini 328 - 3.3V/8MHz][ProMini]
[ESpr one][ESPrOne]
[ESPr one 32][ESPrOne32]
[Grove][Grove]
[Seed Studio][SeedStudio]
[Arduino][Arduino]
[Sparkfun][Sparkfun]
[スイッチサイエンス][SwitchScience]
--->
