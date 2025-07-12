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
    cout << "SUCCESS: Displaying Packed Supply Boxes:\n";
    cout << "+-------+---------------+----------+\n";
    cout << "|  ID   |     Type      | Quantity |\n";
    cout << "+-------+---------------+----------+\n";

    SupplyBox *temp = top;
    while (temp != NULL)
    {
        cout << "| " << temp->id;
        // Pad ID to 5 characters
        for (int i = to_string(temp->id).length(); i < 5; i++)
            cout << " ";
        cout << " | " << temp->type;
        // Pad Type to 13 characters
        for (int i = temp->type.length(); i < 13; i++)
            cout << " ";
        cout << " | " << temp->quantity;
        // Pad Quantity to 8 characters
        for (int i = to_string(temp->quantity).length(); i < 8; i++)
            cout << " ";
        cout << " |\n";
        temp = temp->next;
    }
    cout << "+-------+---------------+----------+\n";
    return true;
}
