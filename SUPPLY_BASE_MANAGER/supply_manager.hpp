#ifndef SUPPLY_MANAGER_HPP
#define SUPPLY_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
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
    bool saveToCSV();                                      // Save to CSV
    bool loadFromCSV();                                    // Load from CSV
    bool assignSupplyToEmergency();                        // Integration function
    bool viewPackedSuppliesWithSelection();                // Helper for integration
    bool removeSupplyBoxById(int id);                      // Helper for integration
};

#endif
