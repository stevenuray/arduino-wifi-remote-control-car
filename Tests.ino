void printGetSpeedRatioTests(){
  printForwardSpeedRatioTest();
  printBackwardSpeedRatioTest();
  printModestRightTurnSpeedRatioTest();
  printBalancedRightTurnSpeedRatioTest();
  printFullRightTurnSpeedRatioTest();
  printBalancedLeftTurnSpeedRatioTest();
  printBalancedBackRightTurnSpeedRatioTest();
  printBalancedBackLeftTurnSpeedRatioTest();
}

void printForwardSpeedRatioTest(){
  float expected = 1;
  float actual = getSpeedRatio(getForwardMovement());
  Serial.println("Forward Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printBackwardSpeedRatioTest(){
  float expected = 1;
  float actual = getSpeedRatio(getBackwardMovement());
  Serial.println("Backward Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printModestRightTurnSpeedRatioTest(){
  float expected = 0.63;
  float actual = getSpeedRatio(getModestRightTurnMovement());
  Serial.println("Modest Right Turn Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printBalancedRightTurnSpeedRatioTest(){
  float expected = 0.5;
  float actual = getSpeedRatio(getBalancedRightTurnMovement());
  Serial.println("Balanced Right Turn Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printFullRightTurnSpeedRatioTest(){
  float expected = 0;
  float actual = getSpeedRatio(getFullRightTurnMovement());
  Serial.println("Full Right Turn Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printBalancedLeftTurnSpeedRatioTest(){
  float expected = -0.5;
  float actual = getSpeedRatio(getBalancedLeftTurnMovement());
  Serial.println("Balanced Left Turn Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printBalancedBackRightTurnSpeedRatioTest(){
  float expected = 0.5;
  float actual = getSpeedRatio(getBalancedBackRightTurnMovement());
  Serial.println("Balanced Back Right Turn Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

void printBalancedBackLeftTurnSpeedRatioTest(){
  float expected = -0.5;
  float actual = getSpeedRatio(getBalancedBackLeftTurnMovement());
  Serial.println("Balanced Back Left Turn Speed Ratio Test");
  Serial.print("Expected is: ");
  Serial.print(expected);
  Serial.print(" Actual is: ");
  Serial.println(actual);
  Serial.println();
}

struct MovementCommand getForwardMovement(){
  struct MovementCommand forwardMovement;
  forwardMovement.x = 0;
  forwardMovement.y = 1023;
  forwardMovement.speed = 127;
  return forwardMovement;
}

struct MovementCommand getBackwardMovement(){
  struct MovementCommand backwardMovement;
  backwardMovement.x = 0;
  backwardMovement.y = 1;
  backwardMovement.speed = 127;
  return backwardMovement;
}

struct MovementCommand getModestRightTurnMovement(){
  struct MovementCommand movement;
  movement.x = 675;
  movement.y = 1023;
  movement.speed = 127;
  return movement;
}

struct MovementCommand getBalancedRightTurnMovement(){
  struct MovementCommand movement;
  movement.x = 1023;
  movement.y = 1023;
  movement.speed = 127;
  return movement;
}

struct MovementCommand getFullRightTurnMovement(){
  struct MovementCommand movement;
  movement.x = 1023;
  movement.y = 0;
  movement.speed = 127;
  return movement;
}

struct MovementCommand getBalancedLeftTurnMovement(){
  struct MovementCommand movement;
  movement.x = -256;
  movement.y = 256;
  movement.speed = 127;
  return movement;
}

struct MovementCommand getBalancedBackRightTurnMovement(){
  struct MovementCommand movement;
  movement.x = 256;
  movement.y = -256;
  movement.speed = -127;
  return movement;
}

struct MovementCommand getBalancedBackLeftTurnMovement(){
  struct MovementCommand movement;
  movement.x = -256;
  movement.y = -256;
  movement.speed = -127;
  return movement;
}

struct MovementCommand getStopCommand(){
  struct MovementCommand movement;
  movement.x = 0;
  movement.y = 0;
  movement.speed = 0;
  return movement;
}
