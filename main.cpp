#include <iostream>
#include <conio.h>
#include "SUPPLY_BASE_MANAGER/supply_manager.hpp"
#include "VOLUNTEER_OPERATIONS_OFFICER/volunteer_officer.hpp"
#include "EMERGENCY_REQUEST_COORDINATOR/emergency_requests.hpp"
#include "TRANSPORT_UNIT_SCHEDULER/transport_scheduler.hpp"

using namespace std;

void pressAnyKeyToContinue()
{
    cout << "\nPress any key to continue...";
    _getch();
    cout << "\n";
}

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

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        if (choice == 1)
        {
            int id, quantity;
            string type;
            cout << "Enter Box ID: ";
            cin >> id;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "ERROR: Invalid input for Box ID.\n";
                continue;
            }
            cout << "Enter Type (e.g., Food, Medical): ";
            cin.ignore();
            getline(cin, type);
            cout << "Enter Quantity: ";
            cin >> quantity;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "ERROR: Invalid input for Quantity.\n";
                continue;
            }
            if (!supply.packSupplyBox(id, type, quantity))
            {
                cout << "Operation failed. Please try again.\n";
            }
            else
            {
                supply.saveToCSV();
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 2)
        {
            if (!supply.sendSupplyPackage())
            {
                cout << "Operation failed. Please try again.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 3)
        {
            supply.loadFromCSV();
            if (!supply.viewPackedSupplies())
            {
                cout << "No data to display.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice != 0)
        {
            cout << "ERROR: Invalid choice. Please select 0-3.\n";
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

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        if (choice == 1)
        {
            string name, contact, skill;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Contact: ";
            getline(cin, contact);
            cout << "Enter Skill Area: ";
            getline(cin, skill);
            if (!volunteer.registerVolunteer(name, contact, skill))
            {
                cout << "Operation failed. Please try again.\n";
            }
            else
            {
                volunteer.saveToCSV();
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 2)
        {
            if (!volunteer.deployVolunteer())
            {
                cout << "Operation failed. Please try again.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 3)
        {
            volunteer.loadFromCSV();
            if (!volunteer.viewVolunteers())
            {
                cout << "No data to display.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice != 0)
        {
            cout << "ERROR: Invalid choice. Please select 0-3.\n";
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

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        if (choice == 1)
        {
            string location, type;
            int urgency;
            cout << "Enter Location: ";
            cin.ignore();
            getline(cin, location);
            cout << "Enter Type (e.g., Medical, Food): ";
            getline(cin, type);
            cout << "Enter Urgency (1-10): ";
            cin >> urgency;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "ERROR: Invalid input for Urgency.\n";
                continue;
            }
            if (!emergency.logRequest(location, type, urgency))
            {
                cout << "Operation failed. Please try again.\n";
            }
            else
            {
                emergency.saveToCSV();
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 2)
        {
            if (!emergency.processCritical())
            {
                cout << "Operation failed. Please try again.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 3)
        {
            emergency.loadFromCSV();
            if (!emergency.viewRequests())
            {
                cout << "No data to display.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice != 0)
        {
            cout << "ERROR: Invalid choice. Please select 0-3.\n";
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

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        if (choice == 1)
        {
            string id;
            cout << "Enter Vehicle ID: ";
            cin.ignore();
            getline(cin, id);
            if (!transport.addVehicle(id))
            {
                cout << "Operation failed. Please try again.\n";
            }
            else
            {
                transport.saveToCSV();
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 2)
        {
            if (!transport.rotateVehicle())
            {
                cout << "Operation failed. Please try again.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice == 3)
        {
            transport.loadFromCSV();
            if (!transport.displayVehicles())
            {
                cout << "No data to display.\n";
            }
            pressAnyKeyToContinue();
        }
        else if (choice != 0)
        {
            cout << "ERROR: Invalid choice. Please select 0-3.\n";
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

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            mainChoice = -1;
        }

        switch (mainChoice)
        {
        case 1:
            cout << "Accessing Supply Base Manager...\n";
            supplyMenu(supply);
            break;
        case 2:
            cout << "Accessing Volunteer Operations Officer...\n";
            volunteerMenu(volunteer);
            break;
        case 3:
            cout << "Accessing Emergency Request Coordinator...\n";
            emergencyMenu(emergency);
            break;
        case 4:
            cout << "Accessing Transport Unit Scheduler...\n";
            transportMenu(transport);
            break;
        case 0:
            cout << "SUCCESS: Exiting system... Goodbye!\n";
            break;
        default:
            cout << "ERROR: Invalid choice. Please select a number between 0-4.\n";
        }
    } while (mainChoice != 0);

    return 0;
}