#ifndef EMERGENCY_REQUESTS_HPP
#define EMERGENCY_REQUESTS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct EmergencyRequest
{
    string location;
    string type;
    int urgency; // Higher = more urgent
    EmergencyRequest *next;
};

class EmergencyPriorityQueue
{
private:
    EmergencyRequest *head;

public:
    EmergencyPriorityQueue();
    ~EmergencyPriorityQueue();
    bool logRequest(string location, string type, int urgency); // Insert sorted
    bool processCritical();                                     // Remove highest
    bool viewRequests();                                        // Display all
    bool saveToCSV();                                           // Save to CSV
    bool loadFromCSV();                                         // Load from CSV
    bool viewRequestsWithSelection();                           // Helper for integration
    bool viewCriticalRequestsWithSelection();                   // Helper for integration
};

#endif
