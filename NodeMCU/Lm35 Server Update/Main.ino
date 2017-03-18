#include<ESP8266WiFi.h>

const char* ssid = "CELBITS";
const char* password = "celbits@123";

float temp = 0;
int analog = 0;
WiFiServer server(80);  // Create a server that listens for incoming connections on the specified port

void setup()
{
  Serial.begin(115200);
  delay(10);


  Serial.println();
  Serial.println();
  Serial.print("Connecting to  ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);  // Initializes the WiFi library's network settings and provides the current status

  while(WiFi.status() != WL_CONNECTED) // If not connected..
  {

    delay(500);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");


  // start the server
  server.begin(); // Tells the server to begin listening for incoming connections
  Serial.println("Server Started");

  // print the ip address
  Serial.print("Use this URL to connect : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); // Get the wifi shield's IP address
  Serial.print("/");

  }

void loop()
{
  // check if client has connected
  WiFiClient client = server.available();  // The client class creates clients that can connect to servers and send and receive data
  if(!client){
    return;
  }

  //Wait until the client sends some data
  Serial.println("New client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();  // Waits until all outgoing characters in buffer have been sent

  // return the response
  client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
    client.println("");
     client.println("<!DOCTYPE HTML>");
      client.println("<html>");
       client.println("<meta http-equiv=\"refresh\" content\"10\">");
        client.print("LM35 Temp Sensor");
        client.println("<br><br>");
        client.println("temperature");
        analog = analogRead(17);
        temp = analog*0.322265625;
        client.print(temp);
        client.println("<br><br>");
         client.println("<html>");

  delay(1);
  Serial.println("Client gone");
  Serial.println("");
}

  
 
  

