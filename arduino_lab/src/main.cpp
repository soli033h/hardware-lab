#include <Arduino.h>

// 사용 중인 디지털 핀 (2번~8번, 총 7개)
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8}; 
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // 핀 개수 자동 계산 (7개)

// 버튼 핀, 내부 풀업 사용
const int btnFasterPin = 9;  // 속도 증가 버튼
const int btnSlowerPin = 10; // 속도 감소 버튼

// 속도 관련 설정 
int currentDelay = 70;       // 기본 대기 시간 
const int MIN_DELAY = 10;    // 최고 속도 한계 
const int MAX_DELAY = 250;   // 최저 속도 한계 
const int SPEED_STEP = 5;    // 버튼 1회 누름당 증감 폭 

bool lastFasterState = HIGH;
bool lastSlowerState = HIGH;

void checkButtons();
void customDelay(int ms);

void setup() 
{
  for (int i = 0; i < numLeds; i++) 
  {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // 버튼 핀 설정 (내부 풀업 저항 사용: 안 누르면 HIGH, 누르면 LOW)
  pinMode(btnFasterPin, INPUT_PULLUP);
  pinMode(btnSlowerPin, INPUT_PULLUP);
}

void loop() 
{
  // 오른쪽 -> 왼쪽 이동
  for (int i = 0; i < numLeds; i++) 
  {
    digitalWrite(ledPins[i], HIGH);
    customDelay(currentDelay);
    digitalWrite(ledPins[i], LOW);
  }

  // 왼쪽 -> 오른쪽 이동 
  for (int i = numLeds - 2; i > 0; i--) 
  {
    digitalWrite(ledPins[i], HIGH);
    customDelay(currentDelay);
    digitalWrite(ledPins[i], LOW);
  }
}

// 버튼 눌림 감지 함수 (디바운스 및 범위를 벗어난 입력 무시 로직)
void checkButtons() 
{
  bool currentFasterState = digitalRead(btnFasterPin);
  bool currentSlowerState = digitalRead(btnSlowerPin);

  // 9번 버튼: delay 감소
  if (lastFasterState == HIGH && currentFasterState == LOW) 
  {
    if (currentDelay - SPEED_STEP >= MIN_DELAY) 
    {
      currentDelay -= SPEED_STEP;
    } 
    delay(50); 
  }
  lastFasterState = currentFasterState;

  // 10번 버튼: delay 증가
  if (lastSlowerState == HIGH && currentSlowerState == LOW) 
  {
    if (currentDelay + SPEED_STEP <= MAX_DELAY) 
    {
      currentDelay += SPEED_STEP;
    }     
    delay(50); 
  }
  lastSlowerState = currentSlowerState;
}

// 대기 시간 동안에도 버튼 입력을 계속 감지하는 함수
void customDelay(int ms) 
{
  unsigned long start = millis();
  
  while (millis() - start < (unsigned long)ms) 
  {
    checkButtons();
  }
}