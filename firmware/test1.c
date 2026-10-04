// Use Espressif ESP32 board package URL https://espressif.github.io/arduino-esp32/package_esp32_index.json
// Files --> Preferences --> Additional Board Manager URLs
// HW only uses the ESP32 module and IR  with the remote to test if ESP32 can see the remotes IR signal 
// through the receiver

const int IR_PIN = 4;

void setup() {
  Serial.begin(115200);

  pinMode(IR_PIN, INPUT);

  Serial.println("IR receiver test");
  Serial.println("Press a button on the remote...");
}

void loop() {
  static int lastState = HIGH;

  int state = digitalRead(IR_PIN);

  if (state != lastState) {
    Serial.print("IR state changed: ");
    Serial.println(state);

    lastState = state;
  }
}
