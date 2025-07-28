#include "supply_manager.hpp"
#include "../EMERGENCY_REQUEST_COORDINATOR/emergency_requests.hpp"
#include <cctype>

SupplyStack::SupplyStack()
{
    top = NULL;
}

SupplyStack::~SupplyStack()
{
    while (top != NULL)
    {
        SupplyBox *temp = top;
        top = top->next;
        delete temp;
    }
}

bool SupplyStack::packSupplyBox(int id, string type, int quantity)
{
    if (quantity <= 0)
    {
        cout << "ERROR: Invalid quantity. Must be greater than 0.\n";
        return false;
    }
    if (type.empty())
    {
        cout << "ERROR: Supply type cannot be empty.\n";
        return false;
    }
    if (id <= 0)
    {
        cout << "ERROR: Invalid ID. Must be greater than 0.\n";
        return false;
    }

    SupplyBox *newBox = new SupplyBox{id, type, quantity, top};
    top = newBox;
    cout << "SUCCESS: Supply Box Packed (ID: " << id << ", Type: " << type << ", Qty: " << quantity << ")\n";
    return true;
}

bool SupplyStack::sendSupplyPackage()
{
    if (top == NULL)
    {
        cout << "ERROR: No supply boxes to dispatch.\n";
        return false;
    }
    SupplyBox *temp = top;
    cout << "SUCCESS: Dispatching Supply Box (ID: " << temp->id << ")\n";
    top = top->next;
    delete temp;
    return true;
}

bool SupplyStack::viewPackedSupplies()
{
    if (top == NULL)
    {
        cout << "WARNING: No supplies currently packed.\n";
        return false;
    }
    cout << "\n========== Packed Supplies Storage ==========\n";

    SupplyBox *temp = top;
    while (temp != NULL)
    {
        cout << "ID: " << temp->id
             << " | Type: " << temp->type
             << " | Quantity: " << temp->quantity
             << endl;
        temp = temp->next;
    }
    return true;
}

bool SupplyStack::saveToCSV()
{
    ofstream file("supply_data.csv");
    if (!file.is_open())
    {
        return false;
    }

    file << "ID,Type,Quantity\n";

    SupplyBox *temp = top;
    while (temp != NULL)
    {
        file << temp->id << "," << temp->type << "," << temp->quantity << "\n";
        temp = temp->next;
    }

    file.close();
    return true;
}

bool SupplyStack::loadFromCSV()
{
    ifstream file("supply_data.csv");
    if (!file.is_open())
    {
        return true;
    }

    string line;
    getline(file, line);

    while (top != NULL)
    {
        SupplyBox *temp = top;
        top = top->next;
        delete temp;
    }

    SupplyBox *tempHead = NULL;

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, type, quantityStr;

        if (getline(ss, idStr, ',') &&
            getline(ss, type, ',') &&
            getline(ss, quantityStr, ','))
        {
            int id = stoi(idStr);
            int quantity = stoi(quantityStr);

            SupplyBox *newBox = new SupplyBox{id, type, quantity, tempHead};
            tempHead = newBox;
        }
    }

    while (tempHead != NULL)
    {
        SupplyBox *temp = tempHead;
        tempHead = tempHead->next;

        temp->next = top;
        top = temp;
    }

    file.close();
    return true;
}

bool SupplyStack::viewPackedSuppliesWithSelection()
{
    if (top == NULL)
    {
        cout << "WARNING: No supplies currently packed.\n";
        return false;
    }
    cout << "\n========== Available Supply Boxes ==========\n";
    cout << "ID\t| Type\t\t| Quantity\n";
    cout << "----------------------------------------\n";

    SupplyBox *temp = top;
    while (temp != NULL)
    {
        cout << temp->id << "\t| " << temp->type << "\t\t| " << temp->quantity << endl;
        temp = temp->next;
    }
    return true;
}

bool SupplyStack::removeSupplyBoxById(int id)
{
    if (top == NULL)
    {
        return false;
    }

    if (top->id == id)
    {
        SupplyBox *temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    SupplyBox *current = top;
    while (current->next != NULL && current->next->id != id)
    {
        current = current->next;
    }

    if (current->next != NULL && current->next->id == id)
    {
        SupplyBox *temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    return false;
}

bool SupplyStack::assignSupplyToEmergency()
{
    loadFromCSV();

    cout << "\n=== Assign Supply to Emergency Request ===\n";

    EmergencyPriorityQueue emergency;
    emergency.loadFromCSV();

    cout << "\n--- Pending Emergency Requests (by Priority) ---\n";
    if (!emergency.viewRequestsWithSelection())
    {
        cout << "No pending emergency requests found.\n";
        return false;
    }

    cout << "\n--- Available Supply Boxes ---\n";
    if (!viewPackedSuppliesWithSelection())
    {
        cout << "No supply boxes available.\n";
        return false;
    }

    int supplyId;
    string input;
    cout << "\nEnter Supply Box ID to assign: ";
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

    if (removeSupplyBoxById(supplyId))
    {
        cout << "SUCCESS: Supply Box ID " << supplyId << " has been assigned to emergency request.\n";
        saveToCSV();
        return true;
    }
    else
    {
        cout << "ERROR: Supply Box ID " << supplyId << " not found.\n";
        return false;
    }
}
