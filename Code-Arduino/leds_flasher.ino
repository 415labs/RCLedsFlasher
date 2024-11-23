/*
  Reads signal from R/C receiver and blinks LEDs based on signal threshold
  
  Input:
    R/C channel: pin#5 (PB0) - PWM signal from receiver
  Output:
    LED1: pin#2 (PB3)
    LED2: pin#3 (PB4)
  
  Signal threshold: 1500μs (standard servo center position)
  LED blink pattern: Alternating blinks when signal exceeds threshold
  
  ATTINY85 pinout: https://medium.com/jungletronics/attiny85-easy-flashing-through-arduino-b5f896c48189
*/

// Pin definitions
const uint8_t RC_PIN = PB0;
const uint8_t LED1_PIN = PB3;
const uint8_t LED2_PIN = PB4;

// Configuration
const unsigned int SIGNAL_THRESHOLD = 1500; // microseconds
const unsigned int PULSE_TIMEOUT = 25000;   // microseconds
const unsigned int BLINK_DURATION = 30;     // milliseconds
const unsigned int BLINK_DELAY = 500;       // milliseconds
const uint8_t STARTUP_BLINKS = 10;

void setup() {
  // Configure pins
  pinMode(RC_PIN, INPUT);    // PWM input from receiver
  pinMode(LED1_PIN, OUTPUT); // LED1 output
  pinMode(LED2_PIN, OUTPUT); // LED2 output

  // Startup indicator blink sequence
  for (int i = 0; i < STARTUP_BLINKS; i++) {
    blinkLeds(100);
  }
}

void blinkLeds(int duration_ms) {
  // Blink LED1
  digitalWrite(LED1_PIN, HIGH);
  delay(duration_ms);
  digitalWrite(LED1_PIN, LOW);

  // Blink LED2
  digitalWrite(LED2_PIN, HIGH); 
  delay(duration_ms);
  digitalWrite(LED2_PIN, LOW);
}

void loop() {
  // Read PWM signal from receiver
  int pwmSignal = pulseIn(RC_PIN, HIGH, PULSE_TIMEOUT);

  // Blink LEDs if signal exceeds threshold
  if (pwmSignal > SIGNAL_THRESHOLD) {
    blinkLeds(BLINK_DURATION);
    delay(BLINK_DELAY);
  }
}
