#include <Adafruit_NeoPixel.h>

//  Ultrasonic Sensor Pins 
#define TRIG_PIN 6
#define ECHO_PIN 5
const long TIMEOUT_US = 30000; // 30ms timeout for pulseIn

//  RGB LED Strip Setup 
#define LED_PIN 4
#define LED_COUNT 8
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
const int MAX_DIST = 100; 
const int MIN_DIST = 10;  

void setup() {
  Serial.begin(115200);-- 
  pinMode(ECHO_PIN, INPUT);

  strip.begin(); // Initialize LED strip
  strip.show();  // Turn off all pixels
  strip.setBrightness(50); // 
}

// Function to read distance from the ultrasonic sensor
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);
  
  if (duration == 0) {
    return MAX_DIST; 
  }

  // Calculate distance in centimeters: Speed of sound (343 m/s = 0.0343 cm/µs)
  float distance = (duration * 0.0343) / 2; 

  // Clamp the distance to our visualization range
  if (distance > MAX_DIST) return MAX_DIST;
  if (distance < MIN_DIST) return MIN_DIST - 1; 
  
  return distance;
}


void loop() {
  float current_distance = readDistance();//get distance value
  if (current_distance >= MIN_DIST) {// if greater than 10cm, then turn on led lights according to the distance (map function to determine how many leds are turned on)
    int leds_on = map((int)current_distance, MIN_DIST, MAX_DIST, 1, LED_COUNT);
    for(int i = 0; i < LED_COUNT; i++) {
      if (i < leds_on) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      } else {
        strip.setPixelColor(i, 0); 
      }
    }
    strip.show();
    
    Serial.printf("Distance: %.02fcm | LEDs ON: %d\n", current_distance, leds_on);
    
  } 
  else { // if less than 10 cm, show led alert by blinking all leds
    for(int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(50); 

    // Turn off
    for(int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, 0); 
    }
    strip.show();
    delay(50); 

    Serial.printf("Distance is below %.0fcm\n", (float)MIN_DIST, "Distance:", current_distance);
  }


  delay(100); 
}