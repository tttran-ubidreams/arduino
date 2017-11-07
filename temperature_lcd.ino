/*

    A
   ---
  F |   | B
  | G |
   ---
  E |   | C
  |   |
   ---
    D
*/
#include <Math.h>
// Pin 2-8 is connected to the 7 segments of the display.
float temp;
int tempPin = 0;
int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;
int P = 13;
int value;
int tmp = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(P, OUTPUT);
}

void turnOff()
{
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(P, LOW);
}

void displayNumber(int digit) {
  //Conditions for displaying segment A
  if (digit != 1 && digit != 4)
    digitalWrite(pinA, HIGH);

  //Conditions for displaying segment B
  if (digit != 5 && digit != 6)
    digitalWrite(pinB, HIGH);

  //Conditions for displaying segment C
  if (digit != 2)
    digitalWrite(pinC, HIGH);

  //Conditions for displaying segment D
  if (digit != 1 && digit != 4 && digit != 7)
    digitalWrite(pinD, HIGH);

  //Conditions for displaying segment E
  if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    digitalWrite(pinE, HIGH);

  //Conditions for displaying segment f
  if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    digitalWrite(pinF, HIGH);
  if (digit != 0 && digit != 1 && digit != 7)
    digitalWrite(pinG, HIGH);
}

void enableDigit(int num) {
  turnOff();
  int digitList[] = {D1, D2, D3, D4};
  for (int i = 0; i < 4; i++) {
    if (i == num) {
      digitalWrite(digitList[i], LOW);
    } else {
      digitalWrite(digitList[i], HIGH);
    }
  }
}

void getTemp() {
  if (tmp == 0 || tmp == 2000) {
    // convert the analog volt to its temperature equivalent
    tmp = 0;
    temp = analogRead(tempPin);
    temp = temp * 0.48828125;
    Serial.print("TEMPERATURE = ");
    Serial.print(temp); // display temperature value
    Serial.print("*C");
    Serial.println();
  }

}

void loop() {
  getTemp();
  tmp = tmp + 1;
  int IntegerPart = floor(temp);
  enableDigit(0);
  value = IntegerPart / 10;
  displayNumber(value);
  enableDigit(1);
  value = IntegerPart % 10;
  displayNumber(value);
  int DecimalPart = temp * pow(10, 2) - IntegerPart * pow(10, 2);
  enableDigit(2);
  value = DecimalPart / 10;
  displayNumber(value);
  enableDigit(3);
  value = DecimalPart % 10;
  displayNumber(value);
  enableDigit(0);
  digitalWrite(P, HIGH);
}