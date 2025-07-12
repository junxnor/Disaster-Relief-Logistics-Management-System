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

void SupplyStack::packSupplyBox(int id, string type, int quantity)
{
    SupplyBox *newBox = new SupplyBox{id, type, quantity, top};
    top = newBox;
    cout << "Supply Box Packed (ID: " << id << ", Type: " << type << ", Qty: " << quantity << ")\n";
}

void SupplyStack::sendSupplyPackage()
{
    if (top == NULL)
    {
        cout << "No supply boxes to dispatch.\n";
        return;
    }
    SupplyBox *temp = top;
    cout << "Dispatching Supply Box (ID: " << temp->id << ")\n";
    top = top->next;
    delete temp;
}

void SupplyStack::viewPackedSupplies()
{
    if (top == NULL)
    {
        cout << "No supplies currently packed.\n";
        return;
    }
    cout << "Packed Supply Boxes:\n";
    SupplyBox *temp = top;
    while (temp != NULL)
    {
        cout << "ID: " << temp->id << ", Type: " << temp->type << ", Qty: " << temp->quantity << "\n";
        temp = temp->next;
    }
}
