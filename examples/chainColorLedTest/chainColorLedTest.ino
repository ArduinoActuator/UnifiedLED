/*
 * NanoやMKRをClassic (UNO)のシールドを使えるようにするための変換基板を使うか否かの選択
 */
//#define USE_CONVERTER

#include "UnifiedLED.h"
#include "detectArduinoHardware.h"

#ifdef USE_CONVERTER
#include "ArduinoShieldConverter.h"
#endif /* USE_CONVERTER */

/*
 * マイコン制御フルカラーLEDの選択
 */
//#define USE_P98X3
#define USE_NEO_PIXEL

/*
 * P98X3のピンやLED数の定義
 */
#ifdef USE_P98X3
#define NUM_LED  3

#ifdef USE_CONVERTER
#define P98X3_PIN_A DIGITAL_2
#define P98X3_PIN_B DIGITAL_3
#else /* USE_CONVERTER */
// MKR
//#define P98X3_PIN_A D5
//#define P98X3_PIN_B D6
// other
#define P98X3_PIN_A D2
#define P98X3_PIN_B D3
#endif /* USE_CONVERTER */
#endif /* USE_P98X3 */

/*
 * NeoPixelのピンやLED数の定義
 */

#ifdef USE_NEO_PIXEL
#define NUM_LED 10
#ifdef USE_CONVERTER
#define NEO_PIXEL_PIN DIGITAL_4
#else /* USE_CONVERTER */
#define NEO_PIXEL_PIN D4
#endif /* USE_CONVERTER */
#endif /* USE_NEO_PIXEL */

#ifdef USE_P98X3
#define LED_TYPE_NUM P98X3_LED
ChainableLED chain(P98X3_PIN_A, P98X3_PIN_B, NUM_LED);
UnifiedLED ledChain(&(chain), P98X3_LED, NUM_LED);
#endif /* USE_P98X3 */

#ifdef USE_NEO_PIXEL
#define LED_TYPE_NUM NEO_PIXEL_LED

Adafruit_NeoPixel strip(NUM_LED, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
UnifiedLED neoPixel(&(strip), NEO_PIXEL_LED, NUM_LED);
#endif /* USE_NEO_PIXEL */

#define MAX_BUFF_SIZE 256
#define MAX_TEST 2
struct testResultEntity {
  bool result;
  //String about;
  char about[MAX_BUFF_SIZE];
  //String comment;
  char comment[MAX_BUFF_SIZE];
} testResult[MAX_TEST];

void printStartMessage(String about, uint8_t testNumber){
  char message[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE ; i++ ){
    message[i]=0;
  }
  sprintf(message,"Wait for start test No.%d (%s)",testNumber+1, about.c_str());
  Serial.println(message);
}

void waitForStart(void){
  Serial.print("Please press Enter key to start test : ");
  int count =0;
  while (true) {
    if (Serial.available() > 0) {
      char input = Serial.read();
      if (input == '\n') {
        break;
      } else {
        Serial.print(input);
      }
    }
  }
  Serial.println("");
}

void checkTestResult(String about, uint8_t testNumber){
  char message[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE ; i++ ){
    message[i]=0;
    testResult[testNumber].about[i]=0;
    testResult[testNumber].comment[i]=0;
  }
  sprintf(message,"Please input the failure of test No.%d (%s), if the test is succeeded, press Enter : ",testNumber+1, about.c_str());
  sprintf(testResult[testNumber].about,"%s", about.c_str());
  testResult[testNumber].result = true;
  Serial.print(message);
  int count =0;
  while (true) {
    if (Serial.available() > 0) {
      char input = Serial.read();
      if ((input != -1) && (input != '\n')) {
        testResult[testNumber].comment[count]=input;
        testResult[testNumber].result = false;
        count++;
        Serial.print(input);
      }
      if ((count == MAX_BUFF_SIZE-2) || (input == '\n')) break;
    }
  }
  Serial.println("");
}

void sumTestResult(void){
  int count = 0;
  Serial.println("======== summary of tests ========");
  for (int i=0 ; i<MAX_TEST ; i++ ) {
    char message[MAX_BUFF_SIZE];
    for (int i=0; i<MAX_BUFF_SIZE; i++) {
      message[i]=0;
    }
    if (testResult[i].result) {
      sprintf(message,"Test result of test No.%d (%s) : Success.",i+1, testResult[i].about);
    } else {
      count++;
      sprintf(message,"Test result of test No.%d (%s) : %s",i+1, testResult[i].about, testResult[i].comment);
    }
    Serial.println(message);
  }
  Serial.println("");
  char finalMessage[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE; i++) {
    finalMessage[i]=0;
  }
  sprintf(finalMessage, "Test result : all(%d) , success(%d) , fail(%d)", MAX_TEST, MAX_TEST-count, count);
  Serial.println(finalMessage);
  Serial.println("");
}

enum functionList {
  FUNCTION_SET_LEVEL = 0,
  FUNCTION_SET_MODE,
  FUNCTION_SET_LED_NUM,
  FUNCTION_SET_LED,
  FUNCTION_SET_ONCE,
  FUNCTION_BEGIN
};

String functionName[6] = {
  "setLevel()",
  "setMode()",
  "setLedNum()",
  "setLed()",
  "setOnce()",
  "begin()"
};

void checkReturnValue(ledFunctionReturnValue val, uint8_t funcType) {
  char buff[MAX_BUFF_SIZE];
  memset(buff,0,MAX_BUFF_SIZE);
  if (val == LED_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == LED_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void test1() {
  String about = "test1";
  printStartMessage(about, 0);
  // テスト内容の説明
  Serial.println("=== action ===");
  char message[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE ; i++) {
    message[i]=0;
  }
  sprintf(message,"led type check, outputshould be : %d",LED_TYPE_NUM);
  Serial.println(message);
  Serial.println("");
  waitForStart();

  Serial.println("test2 start.");

  Serial.print("led type = ");
#ifdef USE_P98X3
  Serial.println(ledChain.getType());
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
  Serial.println(neoPixel.getType());
#endif /* USE_NEO_PIXEL */

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");
}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("change color : r,g,b,white using setLed()");
  Serial.println("=== 2nd action ===");
  Serial.println("change color : white using setOnce()");
  Serial.println("");
  waitForStart();

  Serial.println("test2 start.");

  ledFunctionReturnValue value;

  for (int i=0; i<NUM_LED; i++) {
    for (int j=0; j<256;j++) {
#ifdef USE_P98X3
      value = ledChain.setLed(i,j,0,0);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
      value = neoPixel.setLed(i,j,0,0);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_NEO_PIXEL */
    }
    for (int j=0; j<256;j++) {
#ifdef USE_P98X3
      value = ledChain.setLed(i,0,j,0);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
      value = neoPixel.setLed(i,0,j,0);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_NEO_PIXEL */
    }
    for (int j=0; j<256;j++) {
#ifdef USE_P98X3
      value = ledChain.setLed(i,0,0,j);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
      value = neoPixel.setLed(i,0,0,j);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_NEO_PIXEL */
    }
    for (int j=0; j<256;j++) {
#ifdef USE_P98X3
      value = ledChain.setLed(i,j,j,j);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
      value = neoPixel.setLed(i,j,j,j);
      checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_NEO_PIXEL */
    }
  }

  uint32_t max=1;
  for (int i=0; i<NUM_LED; i++) {
    max = max*2;
  }

  for (uint32_t i=0; i<max; i++) {
    for (int j=0; j<255; j+=5) {
#ifdef USE_P98X3
      value = ledChain.setOnce(i,j,j,j);
      checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
      value = neoPixel.setOnce(i,j,j,j);
      checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* USE_NEO_PIXEL */
    }
  }

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");

  for (int i=0; i<NUM_LED; i++) {
#ifdef USE_P98X3
    value = ledChain.setLed(i,0,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
    value = neoPixel.setLed(i,0,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* USE_NEO_PIXEL */
  }

}

void setup() {
  Serial.begin(9600);

  if (SERIAL_RESET) {
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  } else {
    delay(3000);
  }

  Serial.println("");
  Serial.println("");
  Serial.println("color chain led device driver test.");
  Serial.println("");

  ledFunctionReturnValue value;

#ifdef USE_P98X3
  value = ledChain.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  for (int i=0; i< NUM_LED; i++) {
    value = ledChain.setLed(i,0,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
  }
#endif /* USE_P98X3 */
#ifdef USE_NEO_PIXEL
  value = neoPixel.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  for (int i=0; i< NUM_LED; i++) {
    value = neoPixel.setLed(i,0,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
  }
#endif /* USE_NEO_PIXEL */

  test1();
  test2();
  sumTestResult();
}

void loop() {


  delay(100);

}

