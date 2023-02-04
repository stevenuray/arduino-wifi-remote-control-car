struct MovementCommand getLatestMovementCommand() {
  MovementCommand latestCommand = {0, TEST_PWM_RANGE};
  return latestCommand;
}

/*Originally the mixed movement commands were tried from roboclaw.
Controlling each individually like is done below proved more reliable.
*/
void executeMovementCommand(struct MovementCommand command) {
  float speedRatio = getSpeedRatio(command);
  
  Serial.print("Speed Ratio: ");
  Serial.println(speedRatio);

  Serial.print("Speed: ");
  Serial.println(command.speed);

  //stop if needed
  if(command.speed == 0){
    Serial.println("Stop");
    roboclaw.ForwardM1(0x80, 0);
    roboclaw.ForwardM2(0x80, 0);
    return;
  }

  if(speedRatio == 1){
    //straight forward
    Serial.println("Straight Forward");
    roboclaw.BackwardM1(0x80, command.speed);
    roboclaw.ForwardM2(0x80, command.speed);    
    
    return;
  } else if(speedRatio == -1){
    //straight backward
    int modifiedSpeed = (int) round(abs(command.speed));
    Serial.print("Modified Speed: ");
    Serial.println(modifiedSpeed);
    Serial.println("Straight Backward");
    roboclaw.ForwardM1(0x80, modifiedSpeed);
    roboclaw.BackwardM2(0x80, modifiedSpeed);    
    return;
  }
  
  if(command.speed > 0){
    //forward
    if(speedRatio >= 0){
      //right
      int modifiedSpeed = (int) round(command.speed * speedRatio);
      Serial.print("Modified Speed: ");
      Serial.println(modifiedSpeed);
      Serial.println("Forward Right");
      roboclaw.BackwardM1(0x80, command.speed);
      roboclaw.ForwardM2(0x80, modifiedSpeed);
    } else{
      //left
      int modifiedSpeed = (int) round(abs(command.speed * speedRatio));
      Serial.print("Modified Speed: ");
      Serial.println(modifiedSpeed);
      Serial.println("Forward Left");
      roboclaw.BackwardM1(0x80, modifiedSpeed);
      roboclaw.ForwardM2(0x80, command.speed);
    }
  } else {
    //backward
    if(speedRatio < 0){
      //right
      int modifiedSpeed = (int) round(abs(command.speed * speedRatio));
      Serial.print("Modified Speed: ");
      Serial.println("Backward Right");
      roboclaw.ForwardM1(0x80, modifiedSpeed);
      roboclaw.BackwardM2(0x80, abs(command.speed));      
    } else{
      //left
      int modifiedSpeed = (int) round(abs(command.speed * speedRatio));
      Serial.print("Modified Speed: ");
      Serial.println("Backward Left");
      roboclaw.ForwardM1(0x80, abs(command.speed));
      roboclaw.BackwardM2(0x80, modifiedSpeed);      
    }
  }
}

float getSpeedRatio(struct MovementCommand command) {
  if(command.x == 0){
    //if 0,0, should go no where so I think that case doesn't need to be covered here
    if(command.y > 0){
      //forward
      return 1;
    } else {
      //backward
      return -1;
    }
  }
  if(command.x > 0){
    if(command.y >= 0){
      //top right quadrant
      float radians = atan2(command.x, command.y);
      float degrees = radians * 180/3.14159265;
      return mapFloat(degrees, 90, 0, 0, 1);
    } else {
      //bottom right quadrant
      float radians = atan2(command.x, command.y);
      float degrees = radians * 180/3.14159265;
      return mapFloat(degrees, 90, 180, 0, 1);
    }
  } else {
    if(command.y >= 0){
      //top left quadrant
      float radians = atan2(command.x, command.y);
      float degrees = radians * 180/3.14159265;
      return mapFloat(degrees, 0, -90, -1, 0);
    } else {
      //bottom left quadrant
      float radians = atan2(command.x, command.y);
      float degrees = radians * 180/3.14159265;
      return mapFloat(degrees, -90, -180, -1, 0);
    }
  }
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
