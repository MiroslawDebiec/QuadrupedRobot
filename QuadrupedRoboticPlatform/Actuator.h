#pragma once
#include <string>
using namespace std;
class Actuator
{
public:
	Actuator();
	Actuator(int, int, int, string, double, double, double, double, double);

	void setId(int);
	int getId();

	void setLeg(int);
	int getLeg();

	void setJoint(int);
	int getJoint();

	void setJointName(string);
	string getJointName();

	void setTemperature(double);
	double getTemperature();

	void setVoltage(double);
	double getVoltage();

	void setPosition(double);
	double getPosition();

	void setMaxPosition(double);
	double getMaxPosition();

  void setMinPosition(double);
	double getMinPosition();

private:
	int id ;
	int leg;
	int joint;
	string jointName;
	double temperature;
	double voltage; 
	double position;
	double max_position;
	double min_position;
};
