# UnifiedLED

以下の種類のLEDを統一的に扱うためのHardware Abstraction Layer.

- モノクロLED
- カソード/アノードコモンカラーLED
- [Grove LED Barライブラリ][Grove_LED_Bar]対応LED
- [ChainableLEDライブラリ][ChainableLED]対応LED
- [Adafruit NeoPixelライブラリ][AdafruitNeoPixelLibrary]対応LED

## 動作確認済みデバイス

### モノクロLED
- [Grove LED 赤 Arduino用][GroveRedLED]

### マイコン制御モノクロLED
- [Grove - Circular LED][GroveCircularLED]
- [Grove - LED Bar][GroveLEDBar]

### カラーLED
- [RGBフルカラーLED 5mm OSTA5131A カソードコモン][OSTA5131A]

### マイコン制御カラーLED
- [チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]
- [Grove RGB LED スティック][Grove_RGB_LEDスティック]

## 使い方
このライブラリは，マイコン制御のLEDに関するデバイスドライバをライブラリとして取り込むため，
不要なデバイスに関するデバイスドライバが取り込まれないように，不要なデバイスに関する定義を
無効化する．

```UnifiedLED_config.h```の```#undef```を有効化することで該当するデバイスドライバの
取り込みが防止できる．


```C:UnifiedLED_config.h
//#undef LED_HAL_USE_P98X3 // Grove CHAINABLE LED etc.
//#undef LED_HAL_USE_MY9221　// MY9221で制御されるLED
//#undef LED_HAL_USE_NEO_PIXEL // Adaruit Neo Pixelライブラリ
```

<!-- 以下は，外部リンクの定義 
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
-->

<!-- Grove LED 赤 Arduino用 -->
[GroveRedLED]: https://jp.seeedstudio.com/Grove-Red-LED.html
<!-- Grove RGB LED スティック -->
[Grove_RGB_LEDスティック]: https://jp.seeedstudio.com/Grove-RGB-LED-Stick-10-WS2813-Mini.html
<!-- チェーン接続可能 Grove RGB LED -->
[GroveChainableRGB_Led]: https://jp.seeedstudio.com/Grove-Chainable-RGB-Led-V2-0.html
<!-- Grove - LED Bar -->
[GroveLEDBar]: https://wiki.seeedstudio.com/Grove-LED_Bar/
<!-- Grove - Circular LED -->
[GroveCircularLED]: https://wiki.seeedstudio.com/Grove-Circular_LED/
<!-- マイコン内蔵RGBLED 5mm PL9823-F5 -->
[PL9823F5]: https://akizukidenshi.com/catalog/g/g108411/
<!-- RGBフルカラーLED 5mm OSTA5131A カソードコモン -->
[OSTA5131A]: https://akizukidenshi.com/catalog/g/g102476/
<!-- Grove LED Bar -->
[Grove_LED_Bar]: https://github.com/Seeed-Studio/Grove_LED_Bar
<!-- Grove RGB LED chainable -->
[ChainableLED]: https://github.com/pjpmarques/ChainableLED
<!-- Adafruit NeoPixel Library -->
[AdafruitNeoPixelLibrary]: https://github.com/adafruit/Adafruit_NeoPixel


<!-- 以下は，外部リンクの定義 -->
[GroveBarometerSensorBMP180]:http://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP180/
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[AdafruitUSD]:https://github.com/adafruit/Adafruit_Sensor
[shield]:https://www.seeedstudio.com/Base-Shield-V2-p-1378.html
[M0Pro]:https://store.arduino.cc/usa/arduino-m0-pro
[Due]:https://store.arduino.cc/usa/arduino-due
[Uno]:https://store.arduino.cc/usa/arduino-uno-rev3
[UnoWiFi]:https://store.arduino.cc/usa/arduino-uno-wifi-rev2
[Mega]:https://store.arduino.cc/usa/arduino-mega-2560-rev3
[LeonardoEth]:https://store.arduino.cc/usa/arduino-leonardo-eth
[ProMini]:https://www.sparkfun.com/products/11114
[ESPrDev]:https://www.switch-science.com/catalog/2652/
[ESPrDevShield]:https://www.switch-science.com/catalog/2811/
[ESPrOne]:https://www.switch-science.com/catalog/2620/
[ESPrOne32]:https://www.switch-science.com/catalog/3555/
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[Arduino]:http://https://www.arduino.cc/
[Sparkfun]:https://www.sparkfun.com/
[SwitchScience]:https://www.switch-science.com/
[AusExGrove3AxisDigitalAccelerometer1_5g]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/
[AusExGrove3AxisDigitalAccelerometer16g]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-16g/
[AusExGrove3AxisDigitalGyro]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Gyro/
[AusExGroveI2cTouchSensor]:http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/
[AusExGroveAnalog1AxisGyro]:http://wiki.seeedstudio.com/Grove-Single_Axis_Analog_Gyro/
[AusExGroveAnalogCurrentSensor]:http://wiki.seeedstudio.com/Grove-Electricity_Sensor/
[AusExGroveAnalogTemperatureSensor]:http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
[AusExGroveGsr]:http://wiki.seeedstudio.com/Grove-GSR_Sensor/
[AusExGroveRotaryAngleSensor]:http://wiki.seeedstudio.com/Grove-Rotary_Angle_Sensor/
[AusExGroveSimpleLight]:http://wiki.seeedstudio.com/Grove-Light_Sensor/
[AusExGroveSimpleMoisture]:http://wiki.seeedstudio.com/Grove-Moisture_Sensor/
[AusExGroveSimpleSound]:http://wiki.seeedstudio.com/Grove-Loudness_Sensor/
[AusExDigitalSwitch]:http://wiki.seeedstudio.com/Grove-Switch-P/
[AusExGroveDustSensor]:http://wiki.seeedstudio.com/Grove-Dust_Sensor/
[AusExGroveInfraredDistanceSensor]:http://wiki.seeedstudio.com/Grove-IR_Distance_Interrupter_v1.2/
[AusExGroveInfraredReflectiveSensor]:http://wiki.seeedstudio.com/Grove-Infrared_Reflective_Sensor/
[AusExGroveTouchSensor]:http://wiki.seeedstudio.com/Grove-Touch_Sensor/
[AusExGroveUltrasonicRanger]:http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
[AusExGroveWaterSensor]:http://wiki.seeedstudio.com/Grove-Water_Sensor/
[AusExGrovePirSensor]:http://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/


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
