/*
 * NanoやMKRをClassic (UNO)のシールドを使えるようにするための変換基板を使うか否かの選択
 */
//#define USE_CONVERTER

/*
 * LEDの種類の選択
 */

#define GROVE_LED_CIRCULAR
//#define GROVE_LED_BAR

/*
 * Grove LED BarのピンやLED数の定義
 */
#ifdef GROVE_LED_BAR
#define LED_NUM 10
#ifdef USE_CONVERTER
#define LED_BAR_PIN_A DIGITAL_13
#define LED_BAR_PIN_B DIGITAL_10
#else /* USE_CONVERTER */
#define LED_BAR_PIN_A D13
#define LED_BAR_PIN_B D10
#endif /* USE_CONVERTER */
#endif /* GROVE_LED_BAR */

/*
 * Grove LED CircularのピンやLED数の定義
 */
#ifdef GROVE_LED_CIRCULAR
#define LED_NUM 24
#ifdef USE_CONVERTER
#define LED_CIRCULAR_PIN_A DIGITAL_7
#define LED_CIRCULAR_PIN_B DIGITAL_8
#else /* USE_CONVERTER */
// MKR
//#define LED_CIRCULAR_PIN_A D5
//#define LED_CIRCULAR_PIN_B D6
// Nano
#define LED_CIRCULAR_PIN_A D4
#define LED_CIRCULAR_PIN_B D5
// other
//#define LED_CIRCULAR_PIN_A D7
//#define LED_CIRCULAR_PIN_B D8
#endif /* USE_CONVERTER */
#endif /* GROVE_LED_CIRCULAR */

#include "UnifiedLED.h"
#include "detectArduinoHardware.h"

#ifdef USE_CONVERTER
#include "ArduinoShieldConverter.h"
#endif /* USE_CONVERTER */



#ifdef GROVE_LED_BAR
#define LED_TYPE LED_BAR
Grove_LED_Bar bar(LED_BAR_PIN_A, LED_BAR_PIN_B, 0, LED_BAR_10);
UnifiedLED ledBar(&(bar),LED_BAR, LED_NUM, LED_FORWARD);
#endif /* GROVE_LED_BAR */

#ifdef GROVE_LED_CIRCULAR
#define LED_TYPE LED_CIRCULAR
Grove_LED_Bar circle(LED_CIRCULAR_PIN_A, LED_CIRCULAR_PIN_B, 0, LED_CIRCULAR_24);
UnifiedLED ledCircle(&(circle),LED_CIRCULAR, LED_NUM, LED_FORWARD);
#endif /* GROVE_LED_CIRCULAR */


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
  Serial.println("=== 1st action ===");
  char message[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE ; i++) {
    message[i]=0;
  }
  sprintf(message,"led type check, outputshould be : %d",LED_TYPE);
  Serial.println(message);
  Serial.println("");
  waitForStart();
  Serial.print("led type = ");

#ifdef GROVE_LED_BAR
  Serial.println(ledBar.getType());
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  Serial.println(ledCircle.getType());
#endif /* GROVE_LED_CIRCULAR */

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");
}


void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("put on led forward direction.");
  Serial.println("=== 2nd action ===");
  Serial.println("put on led reverse direction.");
  Serial.println("=== 3rd action ===");
  Serial.println("put on led according to binary digits number.");
  Serial.println("");
  waitForStart();

  ledFunctionReturnValue value;

  Serial.println("1st action.");

#ifdef GROVE_LED_BAR
  value = ledBar.setMode(LED_FORWARD);
  checkReturnValue(value, FUNCTION_SET_MODE);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  value = ledCircle.setMode(LED_FORWARD);
  checkReturnValue(value, FUNCTION_SET_MODE);
#endif /* GROVE_LED_CIRCULAR */

  for (int i=0; i<LED_NUM; i++) {
#ifdef GROVE_LED_BAR
    value = ledBar.setLed(i,1.0);
    checkReturnValue(value, FUNCTION_SET_LED);
    delay(100);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
    value = ledCircle.setLed(i,1.0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_CIRCULAR */
    delay(10);
  }

  for (int i=0; i<LED_NUM; i++) {
#ifdef GROVE_LED_BAR
    value = ledBar.setLed(i,0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
    value = ledCircle.setLed(i,0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_CIRCULAR */
  }

  delay(3000);
  Serial.println("2nd action.");

#ifdef GROVE_LED_BAR
  value = ledBar.setMode(LED_REVERSE);
  checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  value = ledCircle.setMode(LED_REVERSE);
  checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_CIRCULAR */

  for (int i=0; i<LED_NUM; i++) {
#ifdef GROVE_LED_BAR
    value = ledBar.setLed(i,1.0);
    checkReturnValue(value, FUNCTION_SET_LED);
    delay(100);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
    value = ledCircle.setLed(i,1.0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_CIRCULAR */
    delay(10);
  }

  for (int i=0; i<LED_NUM; i++) {
#ifdef GROVE_LED_BAR
    value = ledBar.setLed(i,0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
    value = ledCircle.setLed(i,0);
    checkReturnValue(value, FUNCTION_SET_LED);
#endif /* GROVE_LED_CIRCULAR */
  }

  delay(3000);
  Serial.println("3rd action.");

#ifdef GROVE_LED_BAR
  value = ledBar.setOnce(0);
  checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  value = ledCircle.setOnce(0);
  checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* GROVE_LED_CIRCULAR */

  uint32_t max=1;
  for (int i=0; i<LED_NUM; i++) {
    max = max*2;
  }

  for (int i=0; i<max; i++) {
#ifdef GROVE_LED_BAR
    value = ledBar.setOnce(i);
    checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
    value = ledCircle.setOnce(i);
    checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* GROVE_LED_CIRCULAR */
    delay(10);
  }

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");

#ifdef GROVE_LED_BAR
  value = ledBar.setOnce(0);
  checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  value = ledCircle.setOnce(0);
  checkReturnValue(value, FUNCTION_SET_ONCE);
#endif /* GROVE_LED_CIRCULAR */


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
  Serial.println("mono-chain-led device driver test.");
  Serial.println("");

  ledFunctionReturnValue value;

#ifdef GROVE_LED_BAR
  value = ledBar.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  //ledBar.setMode(LED_REVERSE);
  value = ledBar.setMode(LED_FORWARD);
  checkReturnValue(value, FUNCTION_SET_MODE);
  //ledBar.setLedNum(7);
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  value = ledCircle.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  //ledCircle.setMode(LED_REVERSE);
  value = ledCircle.setMode(LED_FORWARD);
  checkReturnValue(value, FUNCTION_SET_MODE);
  //ledCircle.setLedNum(7);
#endif /* GROVE_LED_CIRCULAR */


  test1();
  test2();
  sumTestResult();
}

void loop() {


  delay(100);

}

