// Define Pins
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 3
#define YELLOW_LED 2
#define RED_SWITCH 11
#define GREEN_SWITCH 12
#define BLUE_SWITCH 8
#define YELLOW_SWITCH 9

enum {start_game, random_LED, play_sequence, wait_for_response, game_fail, game_success} current_state;
int samantha_sequence[50];
int user_sequence[50];
int index;
bool is_getting_response;

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

  randomSeed(analogRead(0));
  current_state = start_game;
  index = 0;
}

void loop() {
  switch (current_state) {
    case start_game:
      start_game_sequence();
      current_state = random_LED;
      break;
    case random_LED:
      add_to_samantha_sequence(samantha_sequence, index);
      index++;
      current_state = play_sequence;
      break;
    case play_sequence:
      play_led_sequence(samantha_sequence, index);
      current_state = wait_for_response;
      break;
    case wait_for_response:
      if(!is_getting_response) {
        handle_player_response(0);
      }
      break;
    case game_success:
      play_success();
      current_state = random_LED;
      break;
    case game_fail:
      play_fail();
      index = 0;
      current_state = start_game;
      break;
  }
}

void handle_player_response(int player_index) {
  Serial.println(player_index);
  Serial.println(index);
  if(player_index < index) {
    Serial.println("play has more goes");
    int user_choice = light_led_with_switch();
      if (user_choice != -1) {
        delay(400);
        if(is_player_correct(user_choice, player_index)) {
          Serial.println("Correct");
          handle_player_response(player_index + 1);
        }
        else {
          Serial.println("Incorrect");
          current_state = game_fail;
          return;
        }
        current_state = game_success;
      } else {
        handle_player_response(player_index);
      }
  } 
}

bool is_player_correct(int player_choice, int index) {
  if(player_choice == samantha_sequence[index]) {
    return true;
  } else {
    return false;
  }
}

void play_led_sequence(int samantha_sequence[], int current_index) {
  int current_led;
  for (int i = 0; i < current_index; i++) {
    current_led = samantha_sequence[i];
    light_up_random_led(current_led);
  }
}

void add_to_samantha_sequence(int samantha_sequence[], int current_index) {
  int random_num = random(0, 4);
  samantha_sequence[current_index] = random_num;
}

void light_up_random_led(int led_num) {
  switch (led_num) {
    case 0:
      digitalWrite(RED_LED, HIGH);
      delay(200);
      all_led_states(false);
      delay(200);
      break;
    case 1:
      digitalWrite(GREEN_LED, HIGH);
      delay(200);
      all_led_states(false);
      delay(200);
      break;
    case 2:
      digitalWrite(BLUE_LED, HIGH);
      delay(200);
      all_led_states(false);
      delay(200);
      break;
    case 3:
      digitalWrite(YELLOW_LED, HIGH);
      delay(200);
      all_led_states(false);
      delay(200);
      break;
  }
}

int light_led_with_switch() {
  int current_switch = get_switch_pressed();
  led_state(current_switch, true);
  delay(200);
  all_led_states(false);
  return current_switch;
}


bool is_switch_released(int button) {
  switch (button) {
    case 0:
      if (digitalRead(RED_SWITCH) == HIGH)
      {
        return true;
      }
      break;
    case 1:
      if (digitalRead(GREEN_SWITCH) == HIGH)
      {
        return true;
      }
      break;
    case 2:
      if (digitalRead(BLUE_SWITCH) == HIGH)
      {
        return true;
      }
      break;
    case 3:
      if (digitalRead(YELLOW_SWITCH) == HIGH)
      {
        return true;
      }
      break;
    default:
      return false;
      break;
  }
  return false;
}

int get_switch_pressed() {
  if (digitalRead(RED_SWITCH) == LOW)
  {
    return 0;
  }

  if (digitalRead(GREEN_SWITCH) == LOW)
  {
    return 1;
  }

  if (digitalRead(BLUE_SWITCH) == LOW)
  {
    return 2;
  }

  if (digitalRead(YELLOW_SWITCH) == LOW)
  {
    return 3;
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

void led_state(int led, bool isOn) {
  if (isOn) {
    switch (led) {
      case 0:
        digitalWrite(RED_LED, HIGH);
        break;
      case 1:
        digitalWrite(GREEN_LED, HIGH);
        break;
      case 2:
        digitalWrite(BLUE_LED, HIGH);
        break;
      case 3:
        digitalWrite(YELLOW_LED, HIGH);
        break;
    }
  } else {
    switch (led) {
      case 0:
        digitalWrite(RED_LED, LOW);
        break;
      case 1:
        digitalWrite(GREEN_LED, LOW);
        break;
      case 2:
        digitalWrite(BLUE_LED, LOW);
        break;
      case 3:
        digitalWrite(YELLOW_LED, LOW);
        break;
    }
  }
}

void all_led_states(bool isOn) {
  if (isOn) {
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

void play_success() {
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
  delay(300);
  all_led_states(true);
  delay(300);
  all_led_states(false);
  delay(200);
}

void play_fail() {
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  delay(100);
}
