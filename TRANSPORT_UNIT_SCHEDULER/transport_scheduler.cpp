#include "transport_scheduler.hpp"
#include "../SUPPLY_BASE_MANAGER/supply_manager.hpp"
#include <cctype>

CircularQueue::CircularQueue()
{
    head = NULL;
    count = 0;
    maxSize = 10;
}

CircularQueue::~CircularQueue()
{
    while (head != NULL)
    {
        Vehicle *temp = head;
        if (head->next == head)
        {
            head = NULL;
        }
        else
        {
            Vehicle *last = head;
            while (last->next != head)
            {
                last = last->next;
            }
            last->next = head->next;
            head = head->next;
        }
        delete temp;
        count--;
    }
}

bool CircularQueue::addVehicle(string id)
{
    if (id.empty())
    {
        cout << "ERROR: Vehicle ID cannot be empty.\n";
        return false;
    }
    if (count == maxSize)
    {
        cout << "ERROR: Schedule full. Cannot add vehicle.\n";
        return false;
    }

    Vehicle *newVehicle = new Vehicle{id, NULL};

    if (head == NULL)
    {
        head = newVehicle;
        newVehicle->next = head;
    }
    else
    {
        Vehicle *last = head;
        while (last->next != head)
        {
            last = last->next;
        }
        last->next = newVehicle;
        newVehicle->next = head;
    }

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

    string rotated = head->id;
    head = head->next;
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

    Vehicle *current = head;
    for (int i = 0; i < count; i++)
    {
        cout << "Position: " << (i + 1)
             << " | Vehicle ID: " << current->id
             << endl;
        current = current->next;
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

    if (count > 0)
    {
        Vehicle *current = head;
        for (int i = 0; i < count; i++)
        {
            file << (i + 1) << "," << current->id << "\n";
            current = current->next;
        }
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

    while (head != NULL)
    {
        Vehicle *temp = head;
        if (head->next == head)
        {
            head = NULL;
        }
        else
        {
            Vehicle *last = head;
            while (last->next != head)
            {
                last = last->next;
            }
            last->next = head->next;
            head = head->next;
        }
        delete temp;
        count--;
    }

    count = 0;

    while (getline(file, line) && count < maxSize)
    {
        stringstream ss(line);
        string positionStr, vehicleID;

        if (getline(ss, positionStr, ',') &&
            getline(ss, vehicleID, ','))
        {
            addVehicle(vehicleID);
        }
    }

    file.close();
    return true;
}

bool CircularQueue::scheduleVehicleForSupplyDelivery()
{
    loadFromCSV();

    cout << "\n=== Schedule Vehicle for Supply Delivery ===\n";

    cout << "\n--- Available Vehicles in Rotation ---\n";
    if (!displayVehicles())
    {
        cout << "No vehicles available in rotation.\n";
        return false;
    }

    SupplyStack supply;
    supply.loadFromCSV();

    cout << "\n--- Packed Supply Boxes ---\n";
    if (!supply.viewPackedSuppliesWithSelection())
    {
        cout << "No supply boxes available.\n";
        return false;
    }

    int supplyId;
    string input;
    cout << "\nEnter Supply Box ID to deliver: ";
    cin >> input;

    bool isValid = true;
    if (input.empty())
    {
        isValid = false;
    }
    else
    {
        for (char c : input)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }
    }

    if (!isValid)
    {
        cout << "ERROR: Invalid input. Please enter a valid numeric ID.\n";
        return false;
    }

    supplyId = stoi(input);

    if (count == 0)
    {
        cout << "ERROR: No vehicles available for delivery.\n";
        return false;
    }

    string assignedVehicle = head->id;

    if (supply.removeSupplyBoxById(supplyId))
    {
        cout << "SUCCESS: Supply Box ID " << supplyId << " has been assigned to Vehicle \""
             << assignedVehicle << "\" for delivery.\n";
        rotateVehicle();
        supply.saveToCSV();
        saveToCSV();
        return true;
    }
    else
    {
        cout << "ERROR: Supply Box ID " << supplyId << " not found.\n";
        return false;
    }
}
