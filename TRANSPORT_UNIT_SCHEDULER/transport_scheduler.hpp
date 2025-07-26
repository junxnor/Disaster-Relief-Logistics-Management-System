#ifndef TRANSPORT_SCHEDULER_HPP
#define TRANSPORT_SCHEDULER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Vehicle
{
    string id;
    Vehicle *next;
};

class CircularQueue
{
private:
    Vehicle *head;
    int count;
    int maxSize;

public:
    CircularQueue();
    ~CircularQueue();
    bool addVehicle(string id);              // Enqueue
    bool rotateVehicle();                    // Dequeue + Enqueue
    bool displayVehicles();                  // Display all vehicles
    bool saveToCSV();                        // Save to CSV
    bool loadFromCSV();                      // Load from CSV
    bool scheduleVehicleForSupplyDelivery(); // Integration function
};

#endif
