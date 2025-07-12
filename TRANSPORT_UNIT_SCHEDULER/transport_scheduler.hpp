#ifndef TRANSPORT_SCHEDULER_HPP
#define TRANSPORT_SCHEDULER_HPP

#include <iostream>
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
    void addVehicle(string id);
    void rotateVehicle(); // Dequeue + Enqueue
    void displayVehicles();
};

#endif
