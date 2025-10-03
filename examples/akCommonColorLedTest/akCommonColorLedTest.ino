/*
 * NanoやMKRをClassic (UNO)のシールドを使えるようにするための変換基板を使うか否かの選択
 */
//#define USE_CONVERTER

#include "UnifiedLED.h"
#include "detectArduinoHardware.h"

/*
 * 接続ピンの定義
 *   注意事項 : LEDのピンは，PMWが可能なポートに接続すること
 */

#ifdef USE_CONVERTER
#define SIMPLE_COLOR_LED_RED_PIN DIGITAL_6
#define SIMPLE_COLOR_LED_GREEN_PIN DIGITAL_9
#define SIMPLE_COLOR_LED_BLUE_PIN DIGITAL_11
#else /* USE_CONVERTER */
// Mega, Uno R4, M0 pro, Giga, Nano 33 IoT, Nano ESP32
#define SIMPLE_COLOR_LED_RED_PIN D6
#define SIMPLE_COLOR_LED_GREEN_PIN D9
#define SIMPLE_COLOR_LED_BLUE_PIN D11
// MKR
//#define SIMPLE_COLOR_LED_RED_PIN D2
//#define SIMPLE_COLOR_LED_GREEN_PIN D3
//#define SIMPLE_COLOR_LED_BLUE_PIN D4
#endif /* USE_CONVERTER */




#ifdef USE_CONVERTER
#include "ArduinoShieldConverter.h"
#endif /* USE_CONVERTER */


UnifiedLED akCommon(SIMPLE_COLOR_LED_RED_PIN, SIMPLE_COLOR_LED_GREEN_PIN, SIMPLE_COLOR_LED_BLUE_PIN, PULL_UP);

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
  sprintf(message,"led type check, outputshould be : %d",SIMPLE_COLOR_LED);
  Serial.println(message);
  Serial.println("");
  waitForStart();
  Serial.print("led type = ");Serial.println(akCommon.getType());
  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");
}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("change color : r,g,b,white");
  Serial.println("");
  waitForStart();

  ledFunctionReturnValue value;
 
  for (int i=0; i<256;i++) {
    value = akCommon.setLed(i,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
    delay(50);
  }

  for (int i=0; i<256;i++) {
    value = akCommon.setLed(0,i,0);
    checkReturnValue(value, FUNCTION_SET_LED);
    delay(50);
  }

  for (int i=0; i<256;i++) {
    value = akCommon.setLed(0,0,i);
    checkReturnValue(value, FUNCTION_SET_LED);
    delay(50);
  }

  for (int i=0; i<256;i++) {
    value = akCommon.setLed(i,i,i);
    checkReturnValue(value, FUNCTION_SET_LED);
    delay(50);
  }

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");

  value = akCommon.setLed(0,0,0);
  checkReturnValue(value, FUNCTION_SET_LED);
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

  pinMode(SIMPLE_COLOR_LED_RED_PIN, OUTPUT);
  pinMode(SIMPLE_COLOR_LED_GREEN_PIN, OUTPUT);
  pinMode(SIMPLE_COLOR_LED_BLUE_PIN, OUTPUT);

  Serial.println("");
  Serial.println("");
  Serial.println("anode/cathod common color led device driver test.");
  Serial.println("");

  ledFunctionReturnValue value;
  value = akCommon.begin();
  checkReturnValue(value, FUNCTION_BEGIN);

  test1();
  test2();
  sumTestResult();
}

void loop() {


  delay(100);

}

