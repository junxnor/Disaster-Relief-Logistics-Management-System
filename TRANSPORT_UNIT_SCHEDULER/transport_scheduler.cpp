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
    cout << "\n========== Current Vehicle Schedule ==========\n";

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        cout << "Position: " << (i + 1)
             << " | Vehicle ID: " << vehicles[index]
             << endl;
    }
    return true;
}

bool CircularQueue::saveToCSV()
{
    ofstream file("transport_data.csv");
    if (!file.is_open())
    {
        return false;
    }

    file << "Position,VehicleID\n";

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        file << (i + 1) << "," << vehicles[index] << "\n";
    }

    file.close();
    return true;
}

bool CircularQueue::loadFromCSV()
{
    ifstream file("transport_data.csv");
    if (!file.is_open())
    {
        return true;
    }

    string line;
    getline(file, line);

    front = rear = -1;
    count = 0;

    while (getline(file, line) && count < MAX)
    {
        stringstream ss(line);
        string positionStr, vehicleID;

        if (getline(ss, positionStr, ',') &&
            getline(ss, vehicleID, ','))
        {
            if (front == -1)
                front = 0;
            rear = (rear + 1) % MAX;
            vehicles[rear] = vehicleID;
            count++;
        }
    }

    file.close();
    return true;
}
