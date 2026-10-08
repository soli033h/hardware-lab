## 피지컬 컴퓨팅 6주차 
```cpp
  for (int i = 0; i < numLeds; i++) 
  {
    digitalWrite(ledPins[i], HIGH);
    checkbutton();
    digitalWrite(ledPins[i], LOW);
    delay(speed);
  }
```
* 원래는 이렇게 짰고, 내가 의도했던 바는 **speed**값을 **checkbutton**()에서 
동적으로 led의 켜지고 꺼지는 속도를 조정하려는 것이었다만... 잘 안 됐다..

* 근데 생각해보니.. 이 checkbutton이 실행이 잘 안 될 수 밖에 없던 이유가 있었다.

* 애초에.. checkbutton()이 실행되는 시간이.. loop에서 극도로 짧았던 것이다. 그래서 정말 운이 좋게.. 버튼을 눌렀을 때, 컴파일러가 checkButton()을 읽고 있었다면, 입력을 인지했겠지만, 거의 대부분의 시간을 loop()에서 쓰고 있었으니 거의 인식을 못했던 것

* 그래서 찾아보니... 보통 현재 시간을 가져오는 **mills**에서 실행을 시작한 시간을 뺀 값을 가져와서 Custom으로 Delay를 구현한다고 하는 것 같다. 

* 함수로 구현한다고 했을 때, Param으로는 내가 원하는 delay값을 넣는다. 현재 시간을 받아와서 start에 할당한다. 
즉, 처음 함수 Scope에 진입했을시 시간을 기록하는 것, 그 다음에도 현재 시간을 가져오는데, 얘는 계속 지금 시간으로 업데이트가 되는 시간이다. 그리고 이 둘의 차이를 구하면, 이 함수가 처음 실행됐을 때부터 지금까지의 시간이 구해진다.. 

* 즉, 이 차이를 "millis() - start"라고 했을 때, 얘가 delay(param으로 넘겨준 값)보다 작다는 것은..? 아직 delay 중이라는 얘기가 된다. 예를 들어서 delay가 70이다 라고 하면, 아직 이 함수를 실행한지.. 70초가 안 되었다는 뜻이다. 원래 그냥? delay는 이 70초 동안 아무것도 안 하게 되어있으나.. 여기에 checkButton()을 넣으면.. 대기시간, delay()동안 버튼 입력을 확인한다.

```cpp
void customDelay(int ms) 
{
  unsigned long start = millis();
  
  while (millis() - start < (unsigned long)ms) 
  {
    checkButtons();
  }
}
```

#### 버튼 인터랙션
* 버튼 인터랙션은 간단히 두 개의 버튼을 사이드에 놓고, 오른쪽 (9번핀) 버튼을 눌렀을 시, delay값이 5씩 줄어들고, 반대로 왼쪽(10번핀) 버튼을 눌렀을 시, delay값이 5씩 늘어나는 구조이다. 