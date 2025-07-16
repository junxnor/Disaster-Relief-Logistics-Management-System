#ifndef TRANSPORT_SCHEDULER_HPP
#define TRANSPORT_SCHEDULER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#define MAX 10
using namespace std;

class CircularQueue
{
private:
    string vehicles[MAX];
    int front, rear;
    int count;

public:
    CircularQueue();
    bool addVehicle(string id);
    bool rotateVehicle(); // Dequeue + Enqueue
    bool displayVehicles();
    bool saveToCSV();   // Save to CSV
    bool loadFromCSV(); // Load from CSV
};

#endif
