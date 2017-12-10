
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // アナログ入力の値を電圧(V)に変換
  float voltage = (analogRead(0) / 1024.0) * 5.0;
 
  // 誤差を除去
  if(voltage >= 4.9){
    voltage = 4.99;
  }
  
  Serial.print("入力電圧：");
  Serial.print(voltage);
  Serial.print("V 抵抗値：");
 
  // 圧力センサーの抵抗値を出力する
  if(voltage >= 4.9){
     Serial.println("1MΩ ");
  }else{
    float val = voltage / (5.0 - voltage);
    if(val > 999){
      val = val / 1000;
      Serial.print(val,0);
      Serial.print("k");      
    }else{
      Serial.print(val, 0);
    }    
    Serial.println("Ω ");        
  }   
  
  delay(100);
}

