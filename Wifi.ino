int tryConnectionToWifi(){
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(targetSSID);
  int connectionStatus = WiFi.begin(targetSSID, targetNetworkPassword);
  delay(CONNECTION_WAIT_MILLISECONDS);
  Serial.print("Connection status is: ");
  Serial.println(connectionStatus);  
  return connectionStatus;
}

void setWifiConnectionPinsToSuccess(){
  digitalWrite(WIFI_CONNECTION_SUCCESS_LED_PIN, HIGH);
  digitalWrite(WIFI_CONNECTION_FAILURE_LED_PIN, LOW);
}

void setWifiConnectionPinsToFailure(){
  digitalWrite(WIFI_CONNECTION_SUCCESS_LED_PIN, LOW);
  digitalWrite(WIFI_CONNECTION_FAILURE_LED_PIN, HIGH);
}

struct MovementCommand getMovementCommandFromJSON(StaticJsonDocument<50> json){
  struct MovementCommand command;
  command.x = json["x"];
  command.y = json["y"];
  command.speed = json["speed"];
  return command;
}
