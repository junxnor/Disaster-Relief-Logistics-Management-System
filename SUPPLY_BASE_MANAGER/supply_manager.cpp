#include "supply_manager.hpp"

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

            SupplyBox *newBox = new SupplyBox{id, type, quantity, top};
            top = newBox;
        }
    }

    file.close();
    return true;
}
