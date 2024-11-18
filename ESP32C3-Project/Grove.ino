#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

const int led = D10;
const int target_id = 1;
const int target_score = 60;
int invoke_count = 0;
int target_invoke_count = 10;

void setup() {
  AI.begin();
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (!AI.invoke()) {
    Serial.println("invoke success");

    for (int i = 0; i < AI.boxes().size(); i++) {
      Serial.print("Box[");
      Serial.print(i);
      Serial.print("] target=");
      Serial.print(AI.boxes()[i].target);
      Serial.print(", score=");
      Serial.print(AI.boxes()[i].score);

      if (AI.boxes()[i].target == target_id && AI.boxes()[i].score > target_score && invoke_count <= 20) {
        invoke_count += 2;
      } else {
        if (invoke_count != 0) {
          invoke_count--;
        }
      }
    }
  } else {

    invoke_count--;
  }
  Serial.print("invoke_count");
  Serial.print(invoke_count);
  if (invoke_count > target_invoke_count) {
    digitalWrite(led, HIGH);  // turn the LED on
  } else {
    digitalWrite(led, LOW);  // turn the LED off
  }
}