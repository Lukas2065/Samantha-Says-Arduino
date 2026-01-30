// Define Pins
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 3
#define YELLOW_LED 2
#define RED_SWITCH 11
#define GREEN_SWITCH 12
#define BLUE_SWITCH 8
#define YELLOW_SWITCH 9

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  
  pinMode(RED_SWITCH, INPUT_PULLUP);
  pinMode(GREEN_SWITCH, INPUT_PULLUP);
  pinMode(BLUE_SWITCH, INPUT_PULLUP);
  pinMode(YELLOW_SWITCH, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  light_led_with_switch();

}

void light_led_with_switch() {
  if (digitalRead(RED_SWITCH) == LOW)
  {
    digitalWrite(RED_LED, HIGH);
  }
  if (digitalRead(RED_SWITCH) == HIGH)
  {
    digitalWrite(RED_LED, LOW);
  }
  
  if (digitalRead(GREEN_SWITCH) == LOW)
  {
    digitalWrite(GREEN_LED, HIGH);
  }
  if (digitalRead(GREEN_SWITCH) == HIGH)
  {
    digitalWrite(GREEN_LED, LOW);
  }
  
  if (digitalRead(BLUE_SWITCH) == LOW)
  {
    digitalWrite(BLUE_LED, HIGH);
  }
  if (digitalRead(BLUE_SWITCH) == HIGH)
  {
    digitalWrite(BLUE_LED, LOW);
  }
  
  if (digitalRead(YELLOW_SWITCH) == LOW)
  {
    digitalWrite(YELLOW_LED, HIGH);
  }
  if (digitalRead(YELLOW_SWITCH) == HIGH)
  {
    digitalWrite(YELLOW_LED, LOW);
  }
}
