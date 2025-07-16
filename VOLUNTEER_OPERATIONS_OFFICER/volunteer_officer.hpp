#ifndef VOLUNTEER_OFFICER_HPP
#define VOLUNTEER_OFFICER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Volunteer
{
    string name;
    string contact;
    string skill;
    Volunteer *next;
};

class VolunteerQueue
{
private:
    Volunteer *front;
    Volunteer *rear;

public:
    VolunteerQueue();
    ~VolunteerQueue();
    bool registerVolunteer(string name, string contact, string skill); // Enqueue
    bool deployVolunteer();                                            // Dequeue
    bool viewVolunteers();                                             // Display
    bool saveToCSV();                                                  // Save to CSV
    bool loadFromCSV();                                                // Load from CSV
};

#endif
