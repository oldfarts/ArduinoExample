/*
  Yún HTTP Client Console version for Arduino Uno using Yún Shield

 This example for the YunShield/Yún shows how create a basic
 HTTP client read and write operations,
 that connects to the internet and downloads
 content or uploads the content to internet page. 
 In this case, you'll connect to the IBM Bluemix
 website and download the name list or upload the name list.

 This example is to made to simulate the actual PDA devices...
 (Actual writing requires the POST button or similar to web page..)

 created by Jani Ärväs
 February 2017
 
 */
#include <Bridge.h>
#include <HttpClient.h>
#include <Console.h>

String tobeWritten;

void setup() {
  // put your setup code here, to run once: 
  pinMode(13, OUTPUT);                // use the ledPin 13 (led digital 13)
  digitalWrite(13, LOW);           
  Bridge.begin();
  Console.begin();
     
  while(!Console);                    // Wait for Console port to connect
}

void loop() {
    if (Console.available() > 0) {    // check if there is something on buffer
    char c = Console.read();          // read the next char received
    // look for the newline character, this is the last character in the string
    switch (c)
    {
      case '\n':
      Console.print("Hi enter 'r' to read or 'w' to write:");
      delay(2000);
      break;      

      case r:
      // Read data from IBM bluemix as ASCII data
      digitalWrite(LED_BUILTIN, LOW );   // turn the LED off by making the voltage LOW
      delay(1000);                       // wait for a second
      HttpClient clientRead;             // get data from IBM bluemix clearDB (names)
      clientRead.get("https://myhelloappdemo.mybluemix.net/viewData");
      delay(5000);                       // wait for the page to load
      while (clientRead.available()) {   // read the names if the text available
      char c = clientRead.read();        // read one character at time
      Console.print(c);                  // and print it to console
      }
      Console.flush();                   // flush the console
      delay(5000);                       // wait for 5seconds
      break;

      case w:
      // to be done after the IBM bluemix page accepts HTTP post actions
      /*digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
      delay(1000); 
      HttpClient clientWrite;
      HttpClient clientRead;
      while (clientRead.available()) {   // read the name if the text available
      char c = clientRead.read();        // read one character at time
      Console.print(c);                  // and print it to console
      tobeWritten += c;
      if(c=='\n'){                        // if CR(carriage return) then break the loop
        clientWrite.post(""https://myhelloappdemo.mybluemix.net/setData", tobeWritten); 
        delay(5000);
        break;
        }
      }*/
      break;

      default:
      Console.print("You entered wrong character, type r or w");
      delay(2000);
      break;
      }
  } else {
    delay(500);
  }
}
