

void setup() {
  //9600から変更
  Serial.begin(1200);
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

  while (flag != 1) {
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


}

