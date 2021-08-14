#include "JsonHandler.h"

String JsonHandler::getJsonElement(String element, String file_name)
{
  File jsonFile = SpiffHandler::readFile(file_name);
  std::unique_ptr<char[]> buf(new char[SIZE]);
  jsonFile.readBytes(buf.get(), SIZE);
  DynamicJsonDocument doc(SIZE);
  deserializeJson(doc, buf.get());

  String value = doc[element];
  return value;
}

vector<Actuator> JsonHandler::getJsonActuators()
{
  File jsonFile = SpiffHandler::readFile(ACTUATOR_FILE_NAME);
  std::unique_ptr<char[]> buf(new char[SIZE]);
  jsonFile.readBytes(buf.get(), SIZE);
  DynamicJsonDocument doc(SIZE);
  deserializeJson(doc, buf.get());
  JsonArray root = doc.as<JsonArray>();

  vector<Actuator> actuators; 

  for (JsonObject item : root){
    Actuator actuator = Actuator(item["id"], item["leg"], item["joint"], item["joint_name"], 0, 0, 0, item["max_position"], item["min_position"]);
    actuators.push_back(actuator);
  }
  return actuators;
}

String JsonHandler::updateActuators(vector<Actuator> actuators)
{
  DynamicJsonDocument outputDoc(SIZE);
  for (Actuator actuator : actuators)
  {
    int id = actuator.getId();
    JsonObject obj = outputDoc.createNestedObject();
    obj["id"] = String(id);
    obj["leg"] = String(actuator.getLeg());
    obj["joint"] = String(actuator.getJoint());
    obj["joint_name"] = String(actuator.getJointName().c_str());
    obj["max_position"] = String(actuator.getMaxPosition());
    obj["min_position"] = String(actuator.getMinPosition());
    //obj["temperature"] = String(Hub.getTemperature(id));
    //obj["voltage"] = String(Hub.getVoltage(id));
    //obj["position"] = String(Hub.getPosition(id));
    obj["temperature"] = String(0);
    obj["voltage"] = String(0);
    obj["position"] = String(0);
  }
  String outputDocString = "";
  serializeJson(outputDoc, outputDocString);
  return outputDocString;
}

void JsonHandler::saveActuators(vector<Actuator> actuators)
{
  String outputDocString = updateActuators(actuators);
  SpiffHandler::saveFile(outputDocString, ACTUATOR_FILE_NAME);
}

/*
vector<vector<Step>> JsonHandler::readGait(String gait_file)
{
  File jsonFile = SpiffHandler::readFile(gait_file);
  std::unique_ptr<char[]> buf(new char[SIZE]);
  jsonFile.readBytes(buf.get(), SIZE);
  DynamicJsonDocument doc(SIZE);
  deserializeJson(doc, buf.get());
  JsonArray root = doc.as<JsonArray>();

  vector<vector<Step>> gait_vector;

  for (JsonObject sequence : root)
  {
    vector<Step> sequence_vector;
    int sequence_name = sequence["sequence"];
    JsonArray steps = sequence["steps"];

    for (JsonObject step : steps)
    {
      Step step_object = Step(sequence_name, step["id"], step["x"], step["y"], step["z"]);
      sequence_vector.push_back(step_object);

      Serial.print("ID: ");
      const char *id = step["id"];
      Serial.print(id);
      Serial.print(" - X: ");
      const char *x = step["x"];
      Serial.print(x);
      Serial.print(" - Y: ");
      const char *y = step["y"];
      Serial.print(y);
      const char *z = step["z"];
      Serial.print(" - Z: ");
      Serial.println(z);
    }
    gait_vector.push_back(sequence_vector);
  }
  return gait_vector;
}
*/
