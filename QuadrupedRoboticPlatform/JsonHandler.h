#pragma once
#include <ArduinoJson.h>
#include "SR518.h"
#include "Actuator.h"
#include "SpiffHandler.h"
#include "Step.h"

#define SIZE 4096
#define ARRAY_SIZE 12
#define ACTUATOR_FILE_NAME "actuator.json"
#define GAIT_FILE_NAME "gaits.json"
#define START_GAIT_FILE_NAME "start_gait.json"

class JsonHandler
{
public:
    static String getJsonElement(String element, String file_name);
    static vector<Actuator> getJsonActuators();
    static String updateActuators(vector<Actuator> actuators);
    static void saveActuators(vector<Actuator> actuators);

    //static vector<vector<Step>> readGait(String gait_name);
private:
};
