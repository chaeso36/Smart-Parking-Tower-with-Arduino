#include <Servo.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define BTSerial Serial1

Servo servo;

LiquidCrystal lcd(44, 45, 46, 47, 48, 49);    // LCD 연결

int motor = 11;                                 // 서보모터 핀

int Enable1 = 38;                               // 모터 1
int PWM1 = 9;
int DIR1 = 39;

int sensorIn = 12;                              // 들어오는 차량 감지 핀
int sensorOut = 13;                             // 나가는 차량 감지 핀
int valIn, valOut;

int sensor1 = 2;                               // 주차자리 1번 핀
int sensor2 = 3;                               // 주차자리 2번 핀
int sensor3 = 4;                               // 주차자리 3번 핀
int sensor4 = 5;                               // 주차자리 4번 핀
int left = 4;                                 // 주차장 남는 자리

int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;

int parking[4] = {0, 0, 0, 0};                // 주차 자리 위치

void setup() {
  servo.attach(motor);                    // 서보모터 연결

  lcd.begin(16, 2);                      // LCD 초기화
  lcd.print("Welcome");                  // 문자열 출력

  pinMode(Enable1, OUTPUT);
  digitalWrite(Enable1, LOW);           // 모터 제어 불가능 상태
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  
  pinMode(sensorIn, INPUT);
  pinMode(sensorOut, INPUT);
  
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
}

int plus(int i) {
  if(i < 0){
    int j = 4+i;
    return j;
  }
  return i;
}

void loop() {

  if(digitalRead(sensor1) == 0) {        // 1번 자리에 차량이 있으면
    value1 += 1;                              // loop를 돌면서 밑의 코드가 한번만 작동하도록 value1+
    if(value1 == 1){                          // value1이 1이 되는 순간은 한번 뿐이므로 if문은 한번만 작동
      left -= 1;                              // 남는 자리 -1
      parking[0] = 1;                         // 0번자리(주차타워 가장 밑)에 주차 번호 부여
      for(int i = 0; i < 4; i++){               // 가장 가까운 빈 자리 찾기
        if(parking[i] == 0){
          int temp0 = parking[0];
          int temp1 = parking[1];
          int temp2 = parking[2];
          int temp3 = parking[3];
          parking[plus(0-i)] = temp0;                       // i만큼 회전
          parking[plus(1-i)] = temp1;
          parking[plus(2-i)] = temp2;
          parking[plus(3-i)] = temp3;                  // 가장 가까운 빈 자리로 옮기기
          Serial.println("1");
          digitalWrite(Enable1, HIGH);
          digitalWrite(DIR1, HIGH);                 // 정방향 회전
          analogWrite(PWM1, 100);                      // 회전 속도 설정 필요
          delay(i*1000);                                 // 변수 i에 비례해서 회전
          digitalWrite(PWM1, HIGH);                 // 모터 속도 0
          break;
        }  
      }
    }
  }
  if(value1 > 0){                           // 1번 자리에 차량이 있는 중
    if(digitalRead(sensor1) == 1) {         // 1번 자리에서 차량이 나가면
      left += 1;                            // 남는 자리 +1
      parking[0] = 0;                       // 0번자리에 빈 자리 표시
      value1 = 0;                           // value1 초기화
    }  
  }
  
  if(digitalRead(sensor2) == 0) {        // 2번 자리에 차량이 있으면
    value2 += 1;
    if(value2 == 1){
      left -= 1;                              // 남는 자리 -1
      parking[0] = 2;                         // 0번자리(주차타워 가장 밑)에 주차 번호 부여
      for(int i = 0; i < 4; i++){               // 가장 가까운 빈 자리 찾기
        if(parking[i] == 0){
          int temp0 = parking[0];
          int temp1 = parking[1];
          int temp2 = parking[2];
          int temp3 = parking[3];
          parking[plus(0-i)] = temp0;                       // i만큼 회전
          parking[plus(1-i)] = temp1;
          parking[plus(2-i)] = temp2;
          parking[plus(3-i)] = temp3;                  // 가장 가까운 빈 자리로 옮기기
          Serial.println("2");
          digitalWrite(Enable1, HIGH);
          digitalWrite(DIR1, HIGH);                 // 정방향 회전
          analogWrite(PWM1, 100);                      // 회전 속도 설정 필요
          delay(i*1000);                                 // 변수 i에 비례해서 회전
          digitalWrite(PWM1, HIGH);                 // 모터 속도 0
          break;
        }  
      }
    }
  }
  if(value2 > 0){  
    if(digitalRead(sensor2) == 1) {         // 2번 자리에서 차량이 나가면
      left += 1;                            // 남는 자리 +1
      parking[0] = 0;                       // 0번자리에 빈 자리 표시
      value2 = 0;
    }  
  }
  
  if(digitalRead(sensor3) == 0) {        // 3번 자리에 차량이 있으면
    value3 += 1;
    if(value3 == 1){
      left -= 1;                              // 남는 자리 -1
      parking[0] = 3;                         // 0번자리(주차타워 가장 밑)에 주차 번호 부여
      for(int i = 0; i < 4; i++){               // 가장 가까운 빈 자리 찾기
        if(parking[i] == 0){
          int temp0 = parking[0];
          int temp1 = parking[1];
          int temp2 = parking[2];
          int temp3 = parking[3];
          parking[plus(0-i)] = temp0;                       // i만큼 회전
          parking[plus(1-i)] = temp1;
          parking[plus(2-i)] = temp2;
          parking[plus(3-i)] = temp3;                  // 가장 가까운 빈 자리로 옮기기
          Serial.println("3");
          digitalWrite(Enable1, HIGH);
          digitalWrite(DIR1, HIGH);                 // 정방향 회전
          analogWrite(PWM1, 100);                      // 회전 속도 설정 필요
          delay(i*1000);                                 // 변수 i에 비례해서 회전
          digitalWrite(PWM1, HIGH);                 // 모터 속도 0
          break;
        }  
      }
    }
  }
  if(value3 > 0){  
    if(digitalRead(sensor3) == 1) {         // 1번 자리에서 차량이 나가면
      left += 1;                            // 남는 자리 +1
      parking[0] = 0;                       // 0번자리에 빈 자리 표시
      value3 = 0;
    }  
  }
  
  if(digitalRead(sensor4) == 0) {        // 1번 자리에 차량이 있으면
    value4 += 1;
    if(value4 == 1){
      left -= 1;                              // 남는 자리 -1
      parking[0] = 4;                         // 0번자리(주차타워 가장 밑)에 주차 번호 부여
      for(int i = 0; i < 4; i++){               // 가장 가까운 빈 자리 찾기
        if(parking[i] == 0){
          int temp0 = parking[0];
          int temp1 = parking[1];
          int temp2 = parking[2];
          int temp3 = parking[3];
          parking[plus(0-i)] = temp0;                       // i만큼 회전
          parking[plus(1-i)] = temp1;
          parking[plus(2-i)] = temp2;
          parking[plus(3-i)] = temp3;                  // 가장 가까운 빈 자리로 옮기기
          Serial.println("4");
          digitalWrite(Enable1, HIGH);
          digitalWrite(DIR1, HIGH);                 // 정방향 회전
          analogWrite(PWM1, 100);                      // 회전 속도 설정 필요
          delay(i*1000);                                 // 변수 i에 비례해서 회전
          digitalWrite(PWM1, HIGH);                 // 모터 속도 0
          break;
        }  
      }
    }
  }
  if(value4 > 0){  
    if(digitalRead(sensor4) == 1) {         // 1번 자리에서 차량이 나가면
      left += 1;                            // 남는 자리 +1
      parking[0] = 0;                       // 0번자리에 빈 자리 표시
      value4 = 0;
    }  
  }
  for(int i = 0; i<4; i++){
    Serial.print(parking[i]);
    }
  Serial.println("");

  Serial.println(left);
  
  lcd.setCursor(0, 1);                 // 커서의 위치 변경
  lcd.print("Left : ");
  lcd.setCursor(7, 1);
  lcd.print(left);                      // 남는 자리 출력

  if(left != 0){                        
    valIn = digitalRead(sensorIn);      
    delay(50); 
    if(valIn == 0){                     
      delay(100);
      if(digitalRead(sensorIn) == 0){ 
            servo.write(0);
            delay(3000);
            servo.write(90);
      }
    }
  }
    
  valOut = digitalRead(sensorOut);
  delay(2000);
  if(valOut == 0){
    servo.write(90);
    delay(3000);
    servo.write(0);
  }

  if (BTSerial.available()) {              // 블루투스 연결 중
    char parkingLotchar = BTSerial.read();  // 블루투스로부터 자리번호 입력받음 
    int parkingLot = parkingLotchar - '0';
    Serial.println(parkingLot);
    for(int i = 0; i < 4; i++){             // 자리검색
      if(parking[i] == parkingLot){
        int temp0 = parking[0];
        int temp1 = parking[1];
        int temp2 = parking[2];
        int temp3 = parking[3];
        parking[plus(0-i)] = temp0;                       // i만큼 회전
        parking[plus(1-i)] = temp1;
        parking[plus(2-i)] = temp2;
        parking[plus(3-i)] = temp3;                  // 가장 가까운 빈 자리로 옮기기
        
        digitalWrite(Enable1, HIGH);
        digitalWrite(DIR1, HIGH);                 // 정방향 회전
        analogWrite(PWM1, 100);                      // 회전 속도 설정 필요
        delay(i*1000);                                 // 변수 i에 비례해서 회전
        digitalWrite(PWM1, HIGH);                 // 모터 속도 0
        Serial.println(i);
      }
    }
  }
  delay(500);
}
