#include "Actuator.h"

Actuator::Actuator()
{
}

Actuator::Actuator(int id, int leg, int joint, string jointName, double temperature, double voltage, double position, double max_position, double min_position)
{
	setId(id);
	setLeg(leg);
	setJoint(joint);
	setJointName(jointName);
	setTemperature(temperature);
	setVoltage(voltage);
	setPosition(position);
	setMaxPosition(max_position);
	setMinPosition(min_position);
}

// Getters and Setters
void Actuator::setId(int _id) {
	id = _id;
}
int Actuator::getId() {
	return this->id;
}

void Actuator::setLeg(int _leg) {
	leg = _leg;
}

int Actuator::getLeg() {
	return this->leg;
}

void Actuator::setJoint(int _joint) {
	joint = _joint;
}

int Actuator::getJoint() {
	return this->joint;
}

void Actuator::setJointName(string _joint_name) {
	jointName = _joint_name;
}

string Actuator::getJointName() {
	return this->jointName;
}

void Actuator::setTemperature(double _temperature)
{
	temperature = _temperature;
}

double Actuator::getTemperature()
{
	return this->temperature;
}

void Actuator::setVoltage(double _voltage)
{
	voltage = _voltage;
}

double Actuator::getVoltage()
{
	return this->voltage;
}

void Actuator::setPosition(double _position) {
	position = _position;
}

double Actuator::getPosition() {
	return this->position;
}

void Actuator::setMaxPosition(double _max_position) {
	max_position = _max_position;
}

double Actuator::getMaxPosition() {
	return this->max_position;
}

void Actuator::setMinPosition(double _min_position) {
	min_position = _min_position;
}

double Actuator::getMinPosition() {
	return this->min_position;
}
