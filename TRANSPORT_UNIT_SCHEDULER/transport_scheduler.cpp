#include "transport_scheduler.hpp"

CircularQueue::CircularQueue()
{
    front = rear = -1;
    count = 0;
}

bool CircularQueue::addVehicle(string id)
{
    if (id.empty())
    {
        cout << "ERROR: Vehicle ID cannot be empty.\n";
        return false;
    }
    if (count == MAX)
    {
        cout << "ERROR: Schedule full. Cannot add vehicle.\n";
        return false;
    }
    if (front == -1)
        front = 0;
    rear = (rear + 1) % MAX;
    vehicles[rear] = id;
    count++;
    cout << "SUCCESS: Vehicle " << id << " added to schedule.\n";
    return true;
}

bool CircularQueue::rotateVehicle()
{
    if (count == 0)
    {
        cout << "ERROR: No vehicles to rotate.\n";
        return false;
    }
    string rotated = vehicles[front];
    front = (front + 1) % MAX;
    rear = (rear + 1) % MAX;
    vehicles[rear] = rotated;
    cout << "SUCCESS: Vehicle " << rotated << " rotated to end.\n";
    return true;
}

bool CircularQueue::displayVehicles()
{
    if (count == 0)
    {
        cout << "WARNING: No vehicles scheduled.\n";
        return false;
    }
    cout << "SUCCESS: Displaying Current Vehicle Schedule:\n";
    cout << "+----------+------------------+\n";
    cout << "| Position |    Vehicle ID    |\n";
    cout << "+----------+------------------+\n";

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        cout << "| " << (i + 1);
        // Pad Position to 8 characters
        for (int j = to_string(i + 1).length(); j < 8; j++)
            cout << " ";
        cout << " | " << vehicles[index];
        // Pad Vehicle ID to 16 characters
        for (int j = vehicles[index].length(); j < 16; j++)
            cout << " ";
        cout << " |\n";
    }
    cout << "+----------+------------------+\n";
    return true;
}
