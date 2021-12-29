#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#define left 4
#define right 5
#define fwd   12
#define rev   13
int motor_left[] = {4, 5};
int motor_right[] = {12, 13};
const char *ssid = "ESP_05BFFE";
const char *password = "espap8266";
int stateLED = LOW;
int statefwd = LOW;
int staterev = LOW;
int stateleft = LOW;
int stateright = LOW;
int stateoff = LOW;


ESP8266WebServer server(80);

void move_stop()
{
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], LOW);
delay(25);
}
void move_fwd()
{
     digitalWrite(motor_left[0], HIGH);
     digitalWrite(motor_left[1], LOW);

      digitalWrite(motor_right[0], HIGH);
      digitalWrite(motor_right[1], LOW);

  
 }

 void move_left()
 {
     digitalWrite(motor_left[0], LOW);
     digitalWrite(motor_left[1], HIGH);

     digitalWrite(motor_right[0], HIGH);
     digitalWrite(motor_right[1], LOW);

  
 }

 void move_right()
 {
     digitalWrite(motor_left[0], HIGH);
     digitalWrite(motor_left[1], LOW);

     digitalWrite(motor_right[0], LOW);
     digitalWrite(motor_right[1], HIGH);

  
 }

void move_reverse()
 {
    digitalWrite(motor_left[0], LOW);
    digitalWrite(motor_left[1], HIGH);
    
    digitalWrite(motor_right[0], LOW);
    digitalWrite(motor_right[1], HIGH);

 }



void handleRoot() {
    response();
}

void handlemotorOn() {

  statefwd = HIGH;
  move_fwd();
  response();
   statefwd = LOW;
}

void handlemotorRev() {
 
  staterev= HIGH;
  move_reverse();
  response();
  staterev= LOW;
}

void handlemotorOff() {
 
  stateoff= HIGH;
  move_stop();
  response();
  stateoff= LOW;
}
void handlemotorrightOn()
{
  
   stateright = HIGH;
  move_right();
  response();
  stateright= LOW;
}

void handlemotorleftOn()
{
   
   stateleft = HIGH;
  move_left();
  response();
  stateleft= LOW;
}


const String HtmlHtml = "<html><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>Motor</h1><br/>\n";
const String HtmlMotorfwd = "<big>Motor is now <b>Forward</b></big><br/>\n";
const String HtmlMotorrev = "<big>Motor is now <b>Reverse</b></big><br/>\n";
const String HtmlMotorLeft = "<big>Motor is now <b>Left</b></big><br/>\n";
const String HtmlMotorRight = "<big>Motor is now <b>Right</b></big><br/>\n";
const String HtmlMotorOff = "<big>Motor is now <b>Off</b></big><br/>\n";
const String HtmlButtons = 
    "<a href=\"MotorForward\"><button style=\"display: block; width: 40%;\">Forward</button></a><br/>"
    "<a href=\"MotorReverse\"><button style=\"display: block; width: 40%;\">Reverse</button></a><br/>"
     "<a href=\"MotorLeft\"><button style=\"display: block; width: 40%;\">Left</button></a><br/>"
    "<a href=\"MotorRight\"><button style=\"display: block; width: 40%;\">Right</button></a><br/>"
    "<a href=\"MotorOff\"><button style=\"display: block; width: 40%;\">Off</button></a><br/>";
   

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(statefwd == HIGH){
    htmlRes += HtmlMotorfwd;
  }
    else if (staterev == HIGH)
    {
      htmlRes += HtmlMotorrev;
    }
    else if (stateleft == HIGH)
    {
      htmlRes += HtmlMotorLeft;  
    }
  else if (stateright == HIGH){
    htmlRes += HtmlMotorRight;
  }
   else if (stateoff == HIGH){
    htmlRes += HtmlMotorOff;
  }

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();

    //WiFi.softAP(ssid, password);
    WiFi.softAP(ssid);
    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/MotorForward", handlemotorOn);
    server.on("/MotorReverse", handlemotorRev);
    server.on("/MotorLeft", handlemotorleftOn);
    server.on("/MotorRight", handlemotorrightOn);
    server.on("/MotorOff", handlemotorOff);
    server.begin();
    Serial.println("HTTP server beginned");
    int i;
     for(i = 0; i < 2; i++)
     {
     pinMode(motor_left[i], OUTPUT);
     pinMode(motor_right[i], OUTPUT);
  
     }
      move_stop();

    digitalWrite(LED_BUILTIN, stateLED);
}

void loop() {
    server.handleClient();
}
