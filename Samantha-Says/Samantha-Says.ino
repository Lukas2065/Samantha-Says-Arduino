// Define Pins
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 3
#define YELLOW_LED 2
#define RED_SWITCH 11
#define GREEN_SWITCH 12
#define BLUE_SWITCH 8
#define YELLOW_SWITCH 9

enum {start_game, random_LED, wait_for_response} current_state;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  
  pinMode(RED_SWITCH, INPUT_PULLUP);
  pinMode(GREEN_SWITCH, INPUT_PULLUP);
  pinMode(BLUE_SWITCH, INPUT_PULLUP);
  pinMode(YELLOW_SWITCH, INPUT_PULLUP);

  current_state = start_game;
  
}

void loop() {
  switch (current_state) {
    case start_game:
      start_game_sequence();
      current_state = random_LED;
      break;
    case random_LED:
      light_up_random_led();
      current_state = wait_for_response;
      break;
    case wait_for_response:
      if(light_led_with_switch() != -1) {
        current_state = random_LED;
      }
      break;
  }

}

void light_up_random_led() {
  int random_num = random(0,4);
  Serial.println(random_num);

  switch (random_num) {
    case 0:
      digitalWrite(RED_LED, HIGH);
      delay(200);
      all_led_states(false);
      break;
    case 1:
      digitalWrite(GREEN_LED, HIGH);
      delay(200);
      all_led_states(false);
      break;
    case 2:
      digitalWrite(BLUE_LED, HIGH);
      delay(200);
      all_led_states(false);
      break;
    case 3:
      digitalWrite(YELLOW_LED, HIGH);
      delay(200);
      all_led_states(false);
      break;
  }
}

int light_led_with_switch() {
  if (digitalRead(RED_SWITCH) == LOW)
  {
    digitalWrite(RED_LED, HIGH);
    return 0;
  }
  if (digitalRead(RED_SWITCH) == HIGH)
  {
    digitalWrite(RED_LED, LOW);
  }
  
  if (digitalRead(GREEN_SWITCH) == LOW)
  {
    digitalWrite(GREEN_LED, HIGH);
    return 1;
  }
  if (digitalRead(GREEN_SWITCH) == HIGH)
  {
    digitalWrite(GREEN_LED, LOW);
  }
  
  if (digitalRead(BLUE_SWITCH) == LOW)
  {
    digitalWrite(BLUE_LED, HIGH);
    return 2;
  }
  if (digitalRead(BLUE_SWITCH) == HIGH)
  {
    digitalWrite(BLUE_LED, LOW);
  }
  
  if (digitalRead(YELLOW_SWITCH) == LOW)
  {
    digitalWrite(YELLOW_LED, HIGH);
    return 3;
  }
  if (digitalRead(YELLOW_SWITCH) == HIGH)
  {
    digitalWrite(YELLOW_LED, LOW);
  }

  return -1;
}

void start_game_sequence() {
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(BLUE_LED, HIGH);
  delay(100);
  digitalWrite(YELLOW_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(BLUE_LED, LOW);
  delay(100);
  digitalWrite(YELLOW_LED, LOW);
  delay(100);

  digitalWrite(YELLOW_LED, HIGH);
  delay(100);
  digitalWrite(BLUE_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(YELLOW_LED, LOW);
  delay(100);
  digitalWrite(BLUE_LED, LOW);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, LOW);
  delay(200);

  all_led_states(true);
  delay(200);

  all_led_states(false);
  delay(200);

  all_led_states(true);
  delay(200);

  all_led_states(false);
  delay(100);
}

void all_led_states(bool isOn) {
  if(isOn) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
  }
}
