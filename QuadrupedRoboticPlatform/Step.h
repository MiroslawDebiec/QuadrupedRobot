#pragma once

class Step
{
public:
    Step();
    Step(int sequence, int leg_id, int x, int y, int z);
    void setSequence(int _sequence);
    int getSequence();
    void setLegId(int _leg_id);
    int getLegId();
    void setX(int _x);
    int getX();
    void setY(int _y);
    int getY();
    void setZ(int _z);
    int getZ();

private:
    int id;
    int sequence;
    int leg_id;
    int x;
    int y;
    int z;
};