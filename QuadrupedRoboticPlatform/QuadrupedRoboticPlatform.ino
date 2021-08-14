#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <vector>
#include <SPIFFS.h>

#include "Actuator.h"
#include "JsonHandler.h"

#define RX2 16
#define TX2 17
#define EN2 15
#define CoxaLength 55
#define FemurLength 90
#define TibiaLength 140

AsyncWebServer server(80);
vector<Actuator> actuators;

size_t size = 2048;

void setup() {
  //Initiate Serial
  Serial.begin(115200);
  Serial2.begin(RX2, TX2);
  Hub.setSerial(&Serial2);
  Hub.begin(500000, EN2);
  
  //Initiate SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("Error: mounting SPIFFS");
    return;
  }

  //Getting Network Credentials
  String _ssid = JsonHandler::getJsonElement("ssid", "credentials.json");
  String _password = JsonHandler::getJsonElement("password", "credentials.json");
  const char *ssid = _ssid.c_str();
  const char *password = _password.c_str();

  //Initiating WIFI
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println(WiFi.localIP());

  //Setting actuators
  actuators = JsonHandler::getJsonActuators();

  //Starting Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/js/popper.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/popper.min.js", "text/javascript");
  });

  server.on("/js/bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/bootstrap.min.js", "text/javascript");
  });

  server.on("/js/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/jquery.min.js", "text/javascript");
  });

  server.on("/css/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/css/bootstrap.min.css", "text/css");
  });

  server.on("/js/script.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/js/script.js", "text/javascript");
  });

  server.on("/js/nipplejs.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/js/nipplejs.js", "text/javascript");
  });

  server.on("/data/actuator.json", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", JsonHandler::updateActuators(actuators));
  });

  server.on("/save", HTTP_POST, [](AsyncWebServerRequest * request) {
    AsyncWebParameter *p_id = request->getParam("id");
    AsyncWebParameter *p_min_pos = request->getParam("min_pos");
    AsyncWebParameter *p_max_pos = request->getParam("max_pos");
    request->send(200);

    int id = p_id->value().toInt();
    int min_pos = p_min_pos->value().toInt();
    int max_pos = p_max_pos->value().toInt();
    actuators[id - 1].setMinPosition(min_pos);
    actuators[id - 1].setMaxPosition(max_pos);
    Hub.setPosLimitMin(id, min_pos);
    Hub.setPosLimitMax(id, max_pos);
    JsonHandler::saveActuators(actuators);

    Serial.print("id: ");
    Serial.print(id);
    Serial.print(" min: ");
    Serial.print(min_pos);
    Serial.print(" max: ");
    Serial.println(max_pos);
  });

  server.on("/move", HTTP_POST, [](AsyncWebServerRequest * request) {
    AsyncWebParameter *p_id = request->getParam("id");
    AsyncWebParameter *p_pos = request->getParam("pos");
    request->send(200);
    int id = p_id->value().toInt();
    int pos = p_pos->value().toInt();
    Hub.move(id, pos);
    Serial.print("id: ");
    Serial.print(id);
    Serial.print(" pos: ");
    Serial.println(pos);
  });

    server.on("/gait", HTTP_POST, [](AsyncWebServerRequest *request) {
    AsyncWebParameter *p_gait = request->getParam("dir");
    AsyncWebParameter *p_speed = request->getParam("speed");
    request->send(200);

    String gait = p_gait ->value();
    int speed = p_speed->value().toInt();

    Serial.print("Direction: ");
    Serial.print(gait);
    Serial.print(" Speed: ");
    Serial.println(speed);
    
    //if(gait == "up") //GaitHanler::ExecuteGait("forward");
    //else if(gait == "down") //GaitHanler::ExecuteGait("back");
    //else if(gait == "left") //GaitHanler::ExecuteGait("left");
    //else if(gait == "right") //GaitHanler::ExecuteGait("right");
  });

  server.begin();
}

void loop() {

}

void printActuators() {
  for (Actuator item : actuators) {
    Serial.print("id: ");
    Serial.print(item.getId());
    Serial.print(" -leg: ");
    Serial.print(item.getLeg());
    Serial.print("joint: ");
    Serial.print(item.getJoint());
    Serial.print(" -joint_name: ");
    Serial.print(item.getJointName().c_str());
    Serial.print(" -max_pos: ");
    Serial.print(item.getMaxPosition());
    Serial.print(" -min_pos: ");
    Serial.print(item.getMinPosition());
    Serial.print(" -current_pos: ");
    Serial.print(item.getPosition());
    Serial.print(" -voltage: ");
    Serial.print(item.getVoltage());
    Serial.print(" -temperature: ");
    Serial.println(item.getTemperature());
  }
}
