/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "<WIFI SSID>";
const char* password = "WIFI PW!";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";
String output8State = "off";

// Assign output variables to GPIO pins
const int output1 = D1;
const int output2 = D2;
const int output3 = D3;
const int output4 = D4;
const int output5 = D5;
const int output6 = D6;
const int output7 = D7;
const int output8 = D8;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output8, OUTPUT);
  delay(200);
  // ... und erstmal auf LOW setzen
  digitalWrite(output1, LOW);
  delay(200);
  digitalWrite(output2, LOW);
  delay(200);
  digitalWrite(output3, LOW);
  delay(200);
  digitalWrite(output4, LOW);
  delay(200);
  digitalWrite(output5, LOW);
  delay(200);
  digitalWrite(output6, LOW);
  delay(200);
  digitalWrite(output7, LOW);
  delay(200);
  digitalWrite(output8, LOW);
  delay(200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  

}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Hier werden die GPIO Pins ein- oder ausgeschaltet
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
			
			} else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
			
			} else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 6 on");
              output6State = "on";
              digitalWrite(output6, HIGH);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 6 off");
              output6State = "off";
              digitalWrite(output6, LOW);
			
			} else if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("GPIO 7 on");
              output7State = "on";
              digitalWrite(output7, HIGH);
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("GPIO 7 off");
              output7State = "off";
              digitalWrite(output7, LOW);
			
			} else if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("GPIO 8 on");
              output8State = "on";
              digitalWrite(output8, HIGH);
            } else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("GPIO 8 off");
              output8State = "off";
              digitalWrite(output8, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #008CBA; border: none; color: white; padding: 10px 15px;");
            client.println("text-decoration: none; font-size: 15px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #195B6A;}");
			client.println("body {background-color: #5ee0aa;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Gartenbewaesserung</h1>");
            
            // Das gleiche für GPIO 1
            client.println("<p>Sprinkler Beete und Tomatenhaus</p>");
            // Wenn output1State = off, zeige den EIN Button       
            if (output1State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">AUS</button></a></p>");
            }

            // Das gleiche für GPIO 2
            client.println("<p>Sprinkler Terassenbeete und Gartenhaus</p>");
            // Wenn output2State = off, zeige den EIN Button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">AUS</button></a></p>");
            }

            // Das gleiche für GPIO 3
            client.println("<p>Sprinkler Steingarten</p>");
            // Wenn output3State = off, zeige den EIN Button       
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">AUS</button></a></p>");
            }

            // Das gleiche für GPIO 4
            client.println("<p>Versenkregner Rasen unterer Garten</p>");
            // Wenn output4State = off, zeige den EIN Button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">AUS</button></a></p>");
            }
			
			// Das gleiche für GPIO 5
            client.println("<p>Versenkregner Rasen oberer Garten</p>");
            // Wenn output5State = off, zeige den EIN Button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">AUS</button></a></p>");
            }
			
			// Das gleiche für GPIO 6
            client.println("<p>Sprinkler Deko-Feld zur Strasse</p>");
            // Wenn output6State = off, zeige den EIN Button       
            if (output6State=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">AUS</button></a></p>");
            }
			
			// Das gleiche für GPIO 7
            client.println("<p>Sprinkler Einfahrt-Bereich</p>");
            // Wenn output7State = off, zeige den EIN Button       
            if (output7State=="off") {
              client.println("<p><a href=\"/7/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">AUS</button></a></p>");
            }
			
			// Das gleiche für GPIO 8
            client.println("<p>Reserve</p>");
            // Wenn output8State = off, zeige den EIN Button       
            if (output8State=="off") {
              client.println("<p><a href=\"/8/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/8/off\"><button class=\"button button2\">AUS</button></a></p>");
            }
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}