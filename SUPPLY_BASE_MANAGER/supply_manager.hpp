#ifndef SUPPLY_MANAGER_HPP
#define SUPPLY_MANAGER_HPP

#include <iostream>
using namespace std;

struct SupplyBox
{
    int id;
    string type;
    int quantity;
    SupplyBox *next;
};

class SupplyStack
{
private:
    SupplyBox *top;

public:
    SupplyStack();
    ~SupplyStack();
    bool packSupplyBox(int id, string type, int quantity); // Push
    bool sendSupplyPackage();                              // Pop
    bool viewPackedSupplies();                             // Display
};

#endif
