#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <RoboClaw.h>
#include <SoftwareSerial.h>
#include <WiFiNINA.h>

static unsigned int RE_SHIELD_PIN_1 = 10;
static unsigned int RE_SHIELD_PIN_2 = 9;
static unsigned int RE_SHIELD_PIN_3 = 8;

static unsigned int TEST_PWM_RANGE = 30;

static unsigned int MOTOR_CONTROLLER_TRANSMIT_PIN_1 = 11;
static unsigned int MOTOR_CONTROLLER_TRANSMIT_PIN_2 = 12;

static unsigned int MOTOR_CONTROLLER_SERIAL_TIMEOUT = 10000;
static unsigned int MOTOR_CONTROLLER_BAUD_RATE = 38400;

static int WIFI_CONNECTION_SUCCESS_LED_PIN = 3;
static int WIFI_CONNECTION_FAILURE_LED_PIN = 4;

static unsigned int MAX_MILLISECONDS_SINCE_LAST_MOVEMENT_COMMAND = 1000;

//Must be at or below 1, intended to make turns harder
static float TURN_FACTOR = 1;

#define address 0x80

SoftwareSerial serial = SoftwareSerial(MOTOR_CONTROLLER_TRANSMIT_PIN_1,MOTOR_CONTROLLER_TRANSMIT_PIN_2);
RoboClaw roboclaw = RoboClaw(&serial, MOTOR_CONTROLLER_SERIAL_TIMEOUT);
long lastReceivedCommandMillis = 0;

char targetSSID[] = "YOUR_NETWORK_SSID_HERE";
char targetNetworkPassword[] = "YOUR_NETWORK_PASSWORD_HERE";
int connectionStatus =  WL_IDLE_STATUS;
static unsigned int CONNECTION_WAIT_MILLISECONDS = 5000;

static unsigned int serverPort = 80;
WiFiServer server(serverPort);

struct MovementCommand {
  int x;
  int y;
  int speed;
};

void setup()
{
  pinMode(WIFI_CONNECTION_SUCCESS_LED_PIN, OUTPUT);
  pinMode(WIFI_CONNECTION_FAILURE_LED_PIN, OUTPUT);
  setWifiConnectionPinsToFailure();
  Serial.begin(9600); 
  
  while (connectionStatus != WL_CONNECTED){
    connectionStatus = tryConnectionToWifi();
  }
  setWifiConnectionPinsToSuccess();
  Serial.println("Connection success!!");  
  server.begin();
  roboclaw.begin(MOTOR_CONTROLLER_BAUD_RATE);
  Serial.println("Initialized, ready for requests");
}

void loop()
{
  if(millis() - lastReceivedCommandMillis > MAX_MILLISECONDS_SINCE_LAST_MOVEMENT_COMMAND){
    executeMovementCommand(getStopCommand());
  }

  if(WiFi.status() == WL_CONNECTED){
    setWifiConnectionPinsToSuccess();
  } else {
    setWifiConnectionPinsToFailure();
    tryConnectionToWifi();
  }

  // listen for incoming clients
  WiFiClient client = server.available();
  String jsonString = "";
  if (client) {
    //Serial.println("new client");
    // an HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean currentLineIsJSON = false;    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '{'){
          currentLineIsJSON = true;
        }

        if (currentLineIsJSON) {
          jsonString += c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          currentLineIsJSON = false;
          // send a standard HTTP response header 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    StaticJsonDocument<100> doc;
    DeserializationError deserializationError = deserializeJson(doc, jsonString);
    StaticJsonDocument<50> movementCommandJSON = doc["movementCommand"];
    struct MovementCommand currentCommand = getMovementCommandFromJSON(movementCommandJSON);
    client.stop();
    //printMovementCommandToSerial(currentCommand);
    lastReceivedCommandMillis = (long) millis();    
    executeMovementCommand(currentCommand);
    
    // give the web browser time to receive the data
    delay(1);
  }  
}
