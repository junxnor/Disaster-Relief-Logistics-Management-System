#include "transport_scheduler.hpp"

CircularQueue::CircularQueue()
{
    front = rear = -1;
    count = 0;
}

void CircularQueue::addVehicle(string id)
{
    if (count == MAX)
    {
        cout << "Schedule full. Cannot add vehicle.\n";
        return;
    }
    if (front == -1)
        front = 0;
    rear = (rear + 1) % MAX;
    vehicles[rear] = id;
    count++;
    cout << "Vehicle " << id << " added to schedule.\n";
}

void CircularQueue::rotateVehicle()
{
    if (count == 0)
    {
        cout << "No vehicles to rotate.\n";
        return;
    }
    string rotated = vehicles[front];
    front = (front + 1) % MAX;
    rear = (rear + 1) % MAX;
    vehicles[rear] = rotated;
    cout << "Vehicle " << rotated << " rotated to end.\n";
}

void CircularQueue::displayVehicles()
{
    if (count == 0)
    {
        cout << "No vehicles scheduled.\n";
        return;
    }
    cout << "Current Vehicle Schedule:\n";
    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        cout << vehicles[index] << "\n";
    }
}
