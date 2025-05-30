#include <Servo.h> 



Servo servo1, servo2, servo3, servo4, servo5, servo6;


const int servoPins[] = {3, 5, 6, 9, 10, 11};


const int positions[][6] = {
  {0, 360, 360, 360, 500, 0},     // a
  {0, 0, 0, 0, 0, 0},             // b
  {360, 360, 360, 360, 500, 105}, // c
  {360, 360, 0, 360, 500, 100},   // d
  {360, 0, 0, 0, 0, 0},           // e
  {0, 500, 0, 0, 0, 0},           // f
  {0, 0, 500, 0, 0, 0},           // g
  {0, 0, 0, 360, 0, 0},           // h
  {0, 0, 0, 0, 500, 0},           // i
  {0, 0, 500, 360, 0, 0},         // j
  {360, 0, 0, 360, 500, 105},     // k
};


char lastRpsCommand = '\0'; 

void runCommand(char command) {
  int numCommands = sizeof(positions) / sizeof(positions[0]);

  if (command >= 'a' && command < 'a' + numCommands) {
    int index = command - 'a';
    Serial.print("Setting position: ");
    Serial.println(command);

    
    servo1.write(positions[index][0]);
    servo2.write(positions[index][1]);
    servo3.write(positions[index][2]);
    servo4.write(positions[index][3]);
    servo5.write(positions[index][4]);
    servo6.write(positions[index][5]);
  } else {
    Serial.println("Invalid command! Use a to j...");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Control via Serial (Direct PWM)");
  Serial.println("Send: a, b, c... or rps");

  // Attach servos to PWM pins
  servo1.attach(servoPins[0]);
  servo2.attach(servoPins[1]);
  servo3.attach(servoPins[2]);
  servo4.attach(servoPins[3]);
  servo5.attach(servoPins[4]);
  servo6.attach(servoPins[5]);

  randomSeed(analogRead(0)); // Seed RNG
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "rps") {
      char options[] = {'b', 'c', 'k'};
      char selected;

      // Ensure different selection from last time
      do {
        selected = options[random(0, 3)];
      } while (selected == lastRpsCommand);

      lastRpsCommand = selected;

      Serial.print("RPS selected: ");
      Serial.println(selected);
      runCommand(selected);

    } else if (input.length() == 1) {
      char command = input.charAt(0);
      runCommand(command);
    } else {
      Serial.println("Invalid input! Use a single character (a to k) or 'rps'.");
    }
  }
}

