/*

   Pushover sketch by M.J. Meijer 2014

   Send pushover.net messages from the arduino
   
   Updated for Arduino YUN by Martin Hollywood 2015

*/

#include <Bridge.h>
#include <YunClient.h>

// Pushover settings. Register at https://pushover.net
char pushoversite[] = "api.pushover.net";
char apitoken[] = "your30characterapitokenhere123";
char userkey [] = "your30characteruserkeygoeshere";

int length;

// Initialize the client library
YunClient client;

void setup() {
  // Bridge takes about two seconds to start up
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);

 // I comment this out when running on a battery & wifi
// while (!Serial); // wait for a serial connection
}

void loop() {
  pushover("OMG, Yes it works!!!",0);  
  delay(60000); 
}



byte pushover(char *pushovermessage, int priority)
{
  String message = pushovermessage;

  length = 113 + message.length();
  // more info on parameters https://pushover.net/api 
  if(client.connect(pushoversite,80))
  {
    client.println("POST /1/messages.json HTTP/1.1");
    client.println("Host: api.pushover.net");
    client.println("Connection: close\r\nContent-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.print(length);
    client.println("\r\n");;
    client.print("token=");
    client.print(apitoken);
    client.print("&user=");
    client.print(userkey);
    client.print("&message=");
    client.print(message);
    client.print("&priority=");
    client.print(priority);
    client.print("&retry=60");
    client.print("&expire=3600");
    
    while(client.connected())  
    {
      while(client.available())
      {
        char ch = client.read();
        Serial.write(ch);
      }
    }
    client.stop();
  }  
}
