

#include "src/CokoinoArm.h"
#define buzzerPin 9

CokoinoArm arm;
int xL, yL, xR, yR;

const int act_max = 10;    // Default 10 action, 4 the Angle of servo
int act[act_max][4];    // Only can change the number of action
int num = 0, num_do = 0;

// Serial control flag and timeout
bool serialControl = false;
unsigned long lastSerialCommandTime = 0;
const unsigned long serialCommandTimeout = 1000; // 1 second timeout for serial control

void turnUD(void) {
  if (xL != 512) {
    if (0 <= xL && xL <= 100) { arm.up(60); return; }
    if (900 < xL && xL <= 1024) { arm.down(60); return; } 
    if (100 < xL && xL <= 200) { arm.up(60); return; }
    if (800 < xL && xL <= 900) { arm.down(60); return; }
    if (200 < xL && xL <= 300) { arm.up(60); return; }
    if (700 < xL && xL <= 800) { arm.down(60); return; }
    if (300 < xL && xL <= 400) { arm.up(60); return; }
    if (600 < xL && xL <= 700) { arm.down(60); return; }
    if (400 < xL && xL <= 480) { arm.up(70); return; }
    if (540 < xL && xL <= 600) { arm.down(70); return; }
  }
}

void turnLR(void) {
  if (yL != 512) {
    if (0 <= yL && yL <= 100) { arm.right(60); return; }
    if (900 < yL && yL <= 1024) { arm.left(60); return; }
    if (100 < yL && yL <= 200) { arm.right(60); return; }
    if (800 < yL && yL <= 900) { arm.left(60); return; }
    if (200 < yL && yL <= 300) { arm.right(60); return; }
    if (700 < yL && yL <= 800) { arm.left(50); return; }
    if (300 < yL && yL <= 400) { arm.right(60); return; }
    if (600 < yL && yL <= 700) { arm.left(60); return; }
    if (400 < yL && yL <= 480) { arm.right(70); return; }
    if (540 < yL && yL <= 600) { arm.left(70); return; }
  }
}

void turnCO(void) {
  if (xR != 512) {
    if (0 <= xR && xR <= 100) { arm.servo4.write(0); return; }
    if (900 < xR && xR <= 1024) { arm.servo4.write(180); return; }
    if (100 < xR && xR <= 200) { arm.servo4.write(30); return; }
    if (800 < xR && xR <= 900) { arm.servo4.write(150); return; }
    if (200 < xR && xR <= 300) { arm.servo4.write(60); return; }
    if (700 < xR && xR <= 800) { arm.servo4.write(120); return; }
    if (300 < xR && xR <= 400) { arm.servo4.write(90); return; }
    if (600 < xR && xR <= 700) { arm.servo4.write(90); return; }
    if (400 < xR && xR <= 480) { arm.servo4.write(110); return; }
    if (540 < xR && xR <= 600) { arm.servo4.write(90); return; }
  }
}

void date_processing(int *x, int *y) {
  if (abs(512 - *x) > abs(512 - *y)) {
    *y = 512;
  } else {
    *x = 512;
  }
}

void buzzer(int H, int L) {
  while (yR < 420) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(H);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(L);
    yR = arm.JoyStickR.read_y();
  }
  while (yR > 600) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(H);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(L);
  }
}

void C_action(void) {
  if (yR > 800) {
    int *p;
    p = arm.captureAction();
    for (char i = 0; i < 4; i++) {
      act[num][i] = *p;
      p = p + 1;     
    }
    num++;
    num_do = num;
    if (num >= act_max) {
      num = 0;
      buzzer(600, 400);
    }
    while (yR > 600) { yR = arm.JoyStickR.read_y(); }
  }
}

void Do_action(void) {
  if (yR < 220) {
    buzzer(200, 300);
    for (int i = 0; i < num_do; i++) {
      arm.do_action(act[i], 15);
    }
    num = 0;
    while (yR < 420) { yR = arm.JoyStickR.read_y(); }
    for (int i = 0; i < 2000; i++) {
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(buzzerPin, LOW);
      delayMicroseconds(300);        
    }
  }
}

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate
  arm.ServoAttach(4, 5, 6, 7); // Attach servos to pins (example pin numbers)
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  Serial.println("Setup complete");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command);
    serialControl = true; // Enable serial control
    lastSerialCommandTime = millis();
  }

  // Check if serial control should be disabled after the timeout
  if (serialControl && (millis() - lastSerialCommandTime > serialCommandTimeout)) {
    serialControl = false;
  }

  // Only process joystick inputs if serial control is disabled
  if (!serialControl) {
    // Read joystick values
    xL = analogRead(A0);
    yL = analogRead(A1);
    xR = analogRead(A2);
    yR = analogRead(A3);

    // Process joystick inputs to control the arm
    date_processing(&xL, &yL);
    date_processing(&xR, &yR);
    turnUD();
    turnLR();
    turnCO();
  }

  C_action();
  Do_action();

  delay(100); // Adjust delay as needed
}

void processCommand(String command) {
  Serial.println("Processing command: " + command);
  if (command.startsWith("RIGHT:")) {
    int angle = command.substring(6).toInt();
    Serial.println("Moving RIGHT to angle: " + String(angle));
    arm.servo1.write(angle);  
  } else if (command.startsWith("UP:")) {
    int angle = command.substring(3).toInt();
    Serial.println("Moving UP to angle: " + String(angle));
    arm.servo2.write(angle);
  } else if (command.startsWith("DOWN:")) {
    int angle = command.substring(5).toInt();
    Serial.println("Moving DOWN to angle: " + String(angle));
    arm.servo3.write(angle);
  } else if (command.startsWith("LEFT:")) {
    int angle = command.substring(5).toInt();
    Serial.println("Moving LEFT to angle: " + String(angle));
    arm.servo4.write(angle);
  } else if (command.startsWith("OPEN:")) {
    int angle = command.substring(5).toInt();
    Serial.println("Opening to angle: " + String(angle));
    arm.servo4.write(angle);  // Assuming servo4 is the gripper
  } else if (command.startsWith("CLOSE:")) {
    int angle = command.substring(6).toInt();
    Serial.println("Closing to angle: " + String(angle));
    arm.servo4.write(angle);  // Assuming servo4 is the gripper
  }
}