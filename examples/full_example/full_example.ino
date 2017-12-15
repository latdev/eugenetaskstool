#include <ectask.h>

TasksTool timelib;

void Once30sec() {
  Serial.println("This will run once 30 seconds from Arduino starts");
  timelib.once(1000, ThisWillRunOnceAfter30SecondOnce);
}

void Every15sec() {
  Serial.println("This will runs every 15 seconds");
}

void Every40sec() {
  Serial.println("This will runs every 40 seconds");
  timelib.once(1000, ThisWillRunNotOnceAfter40SecondOnce);
}

void ThisWillRunNotOnceAfter40SecondOnce() {
  Serial.println("One second after 40 passed");
}

void ThisWillRunOnceAfter30SecondOnce() {
  Serial.println("One second after 30 passed");
}

void setup() {
  Serial.begin(9600);
  timelib.once(30000, Once30sec);
  timelib.every(15000, Every15sec);
  timelib.every(40000, Every40sec);
}

void loop() {
  timelib.loop(); // This is important part of timers
}
