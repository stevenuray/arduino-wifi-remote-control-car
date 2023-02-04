void printMovementCommandToSerial(struct MovementCommand movementCommand){
  Serial.print("x is: ");
  Serial.print(movementCommand.x);
  Serial.print(" y is: ");
  Serial.print(movementCommand.y);
  Serial.print(" speed is: ");
  Serial.println(movementCommand.speed);
}
