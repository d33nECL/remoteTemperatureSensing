#include <AccelStepper.h>

// Define X stepper motor connections
#define X_STEP_PIN 2
#define X_DIR_PIN 3

// Define Y stepper motor connections
#define Y_STEP_PIN 4
#define Y_DIR_PIN 5

// Create X and Y stepper motor objects
AccelStepper stepperX(1, X_STEP_PIN, X_DIR_PIN); // (driver type, step pin, direction pin)
AccelStepper stepperY(1, Y_STEP_PIN, Y_DIR_PIN); // (driver type, step pin, direction pin)

void setup() {
  // Set maximum speed and acceleration for X and Y motors
  stepperX.setMaxSpeed(1000); // Adjust as needed (steps/second)
  stepperX.setAcceleration(500); // Adjust as needed (steps/second^2)
  
  stepperY.setMaxSpeed(1000); // Adjust as needed (steps/second)
  stepperY.setAcceleration(500); // Adjust as needed (steps/second^2)

  // Set initial direction for X and Y motors
  stepperX.setSpeed(500); // Adjust speed as needed (steps/second)
  stepperY.setSpeed(500); // Adjust speed as needed (steps/second)
}

void loop() {
  // Rotate X and Y motors continuously in one direction
  stepperX.runSpeed();
  stepperY.runSpeed();
}
