//determine how long signal was high or low, which is needed to reproduce command
//see if each number reproduces the same signal each time or if it changes

const int IR_PIN = 4;

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);

  Serial.println("IR timing capture");
  Serial.println("Press a button...");
}

void loop() {
  // Wait for the beginning of a signal
  if (digitalRead(IR_PIN) == LOW) {

    unsigned long startTime = micros();
    int lastState = LOW;

    Serial.println("---- COMMAND START ----");

    while (true) {
      int state = digitalRead(IR_PIN);

      if (state != lastState) {
        unsigned long now = micros();
        unsigned long duration = now - startTime;

        Serial.print(lastState ? "HIGH: " : "LOW:  ");
        Serial.print(duration);
        Serial.println(" us");

        startTime = now;
        lastState = state;
      }

      // Stop after the signal has been idle for a while
      if (state == HIGH && (micros() - startTime) > 10000) {
        break;
      }
    }

    Serial.println("---- COMMAND END ----");
    delay(500);
  }
}
