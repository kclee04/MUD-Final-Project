#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

# define SDA 13
# define SCL 14

LiquidCrystal_I2C lcd(0x3F,16,2);
WiFiClient espClient;
PubSubClient client(espClient);

IPAddress serverIP(34, 69, 169, 183);   // ip for Jimmy's GCP
const int serverPort = 8888;
WiFiUDP udp;

// define the symbols on the buttons of the keypad
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {14, 27, 26, 25};  
byte colPins[4] = {13, 21, 22, 23};

// initialize an instance of class NewKeypad
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

// mqtt variables
const char *ssid_Router = "WIN Family";
const char *password_Router = "smileycanoe824";
const char *mqtt_server = "jimmynguyen.duckdns.org";

// movement variables
const char north = '2';
const char east = '6';
const char south = '8';
const char west = '4';
const char quitChar = '0';

void setup() {
  Serial.begin(115200);   // initialize the serial port

  // LCD screen setup
  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  
  // mqtt setup
  client.setServer(mqtt_server, 1883);
  setup_wifi();
  client.setCallback(callback);
  reconnect();

  // udp setup
  udp.begin(8888);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // get the character input
  char keyPressed = myKeypad.getKey();

  if (keyPressed == north || keyPressed == west || keyPressed == east || keyPressed == south || keyPressed == quitChar) {

    if (keyPressed == quitChar) {
      Serial.println("Quitting game.");
      udp.stop();
      sendMessage(keyPressed);
      while (1) ;
    }
    // send key via UDP
    sendMessage(keyPressed);
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  // handle incoming messages here
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);    // print description of room to serial monitor - for debugging
  displayMessage(message);
}

void setup_wifi() {
  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe("mud");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void sendMessage (char direction) {
  String message;
  if (direction == north) {
    message = "north";
  } else if (direction == east) {
    message = "east";
  } else if (direction == south) {
    message = "south";
  } else if (direction == west) {
    message = "west";
  } else if (direction == quitChar) {
    message = "quit";
  }

  udp.beginPacket(serverIP, serverPort);
  udp.print(message + "\n");
  udp.endPacket();
}

void displayMessage(String message) {
  lcd.init();
  lcd.clear();

  // used to remove null terminator symbol at the end of string on LCD display
  message.remove(message.length()-1);

  // Maximum characters per line
  const int maxCharsPerLine = 16;

  // Check if the message is longer than 16 characters
  if (message.length() <= maxCharsPerLine) {
    lcd.setCursor(0, 0);
    lcd.print(message.c_str());
  } else {
    // Split the message into two lines
    String line1 = message.substring(0, maxCharsPerLine);
    String line2 = message.substring(maxCharsPerLine);

    lcd.setCursor(0, 0);
    lcd.print(line1.c_str());

    lcd.setCursor(0, 1);
    lcd.print(line2.c_str());
  }
}