#include <iostream>
#include "SUPPLY_BASE_MANAGER/supply_manager.hpp"
#include "VOLUNTEER_OPERATIONS_OFFICER/volunteer_officer.hpp"
#include "EMERGENCY_REQUEST_COORDINATOR/emergency_requests.hpp"
#include "TRANSPORT_UNIT_SCHEDULER/transport_scheduler.hpp"

using namespace std;

void supplyMenu(SupplyStack &supply)
{
    int choice;
    do
    {
        cout << "\n--- Supply Base Manager Menu ---\n";
        cout << "1. Pack Supply Box\n";
        cout << "2. Send Supply Package\n";
        cout << "3. View Packed Supplies\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id, quantity;
            string type;
            cout << "Enter Box ID: ";
            cin >> id;
            cout << "Enter Type (e.g., Food, Medical): ";
            cin >> type;
            cout << "Enter Quantity: ";
            cin >> quantity;
            supply.packSupplyBox(id, type, quantity);
        }
        else if (choice == 2)
        {
            supply.sendSupplyPackage();
        }
        else if (choice == 3)
        {
            supply.viewPackedSupplies();
        }
    } while (choice != 0);
}

void volunteerMenu(VolunteerQueue &volunteer)
{
    int choice;
    do
    {
        cout << "\n--- Volunteer Operations Officer Menu ---\n";
        cout << "1. Register Volunteer\n";
        cout << "2. Deploy Volunteer to Field\n";
        cout << "3. View Registered Volunteers\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, contact, skill;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Contact: ";
            cin >> contact;
            cout << "Enter Skill Area: ";
            cin >> skill;
            volunteer.registerVolunteer(name, contact, skill);
        }
        else if (choice == 2)
        {
            volunteer.deployVolunteer();
        }
        else if (choice == 3)
        {
            volunteer.viewVolunteers();
        }
    } while (choice != 0);
}

void emergencyMenu(EmergencyPriorityQueue &emergency)
{
    int choice;
    do
    {
        cout << "\n--- Emergency Request Coordinator Menu ---\n";
        cout << "1. Log Emergency Request\n";
        cout << "2. Process Most Critical Request\n";
        cout << "3. View Pending Requests\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string location, type;
            int urgency;
            cout << "Enter Location: ";
            cin >> location;
            cout << "Enter Type (e.g., Medical, Food): ";
            cin >> type;
            cout << "Enter Urgency (1-10): ";
            cin >> urgency;
            emergency.logRequest(location, type, urgency);
        }
        else if (choice == 2)
        {
            emergency.processCritical();
        }
        else if (choice == 3)
        {
            emergency.viewRequests();
        }
    } while (choice != 0);
}

void transportMenu(CircularQueue &transport)
{
    int choice;
    do
    {
        cout << "\n--- Transport Unit Scheduler Menu ---\n";
        cout << "1. Add Vehicle to Schedule\n";
        cout << "2. Rotate Vehicle Shift\n";
        cout << "3. Display Vehicle Schedule\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string id;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            transport.addVehicle(id);
        }
        else if (choice == 2)
        {
            transport.rotateVehicle();
        }
        else if (choice == 3)
        {
            transport.displayVehicles();
        }
    } while (choice != 0);
}

int main()
{
    SupplyStack supply;
    VolunteerQueue volunteer;
    EmergencyPriorityQueue emergency;
    CircularQueue transport;

    int mainChoice;
    do
    {
        cout << "\n==== Disaster Relief Logistics Management System ====\n";
        cout << "1. Supply Base Manager\n";
        cout << "2. Volunteer Operations Officer\n";
        cout << "3. Emergency Request Coordinator\n";
        cout << "4. Transport Unit Scheduler\n";
        cout << "0. Exit System\n";
        cout << "Select a role to manage: ";
        cin >> mainChoice;

        switch (mainChoice)
        {
        case 1:
            supplyMenu(supply);
            break;
        case 2:
            volunteerMenu(volunteer);
            break;
        case 3:
            emergencyMenu(emergency);
            break;
        case 4:
            transportMenu(transport);
            break;
        case 0:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (mainChoice != 0);

    return 0;
}