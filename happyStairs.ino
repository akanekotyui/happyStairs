#include <Stepper.h>

#define STEPS 200

//motor data
//direction 12 13
//speed 3 11
//brake 9 8
//current sensing 0 1

Stepper myStepper(STEPS, 12, 13);
const int dirA = 12;
const int dirB = 13;
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;


void setup() {
  //9600から変更
  Serial.begin(1200);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

  myStepper.setSpeed(256);
}

void loop() {

  //1~5までのランダムを発生させる
  int  randNumber = random(1, 4);
  Serial.print("randNumber = ");
  Serial.println(randNumber);

  int i = 0;
  //"あたり"の数をかぞえる
  int count = 0;
  //"あたり"がでたらflagが1になる
  int flag[5];

  while (flag[i] != 1) {
    while (randNumber > count) {
      // アナログ入力の値を電圧(V)に変換
      float voltage = (analogRead(i) / 1024.0) * 5.0;

      // 誤差を除去
      if (voltage >= 4.9) {
        voltage = 4.99;
      }

      Serial.print("入力電圧：");
      Serial.print(voltage);
      Serial.print("V 抵抗値：");

      // 圧力センサーの抵抗値を出力する
      if (voltage >= 4.9) {
        Serial.println("1MΩ ");
      } else {
        float val = voltage / (5.0 - voltage);
        if (val >= 2.3) {
          Serial.print(val, 0);
          Serial.println("Ω ");
          Serial.println("あたり");
          flag[i] = 1;
          Serial.print("count = ");
          Serial.print(count);
          Serial.print("flag = ");
          Serial.println(flag[i]);
          count++;
          i++;
        } else {
          Serial.print(val, 0);
          Serial.println("Ω ");
        }
      }
      delay(100);
    }
  }
  delay(100);

  //ここから出力

  myStepper.step(STEPS);

  while (1) {
    delay(2000);
  }
}

