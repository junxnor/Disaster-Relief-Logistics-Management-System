#ifndef VOLUNTEER_OFFICER_HPP
#define VOLUNTEER_OFFICER_HPP

#include <iostream>
using namespace std;

struct Volunteer {
    string name;
    string contact;
    string skill;
    Volunteer* next;
};

class VolunteerQueue {
private:
    Volunteer* front;
    Volunteer* rear;
public:
    VolunteerQueue();
    ~VolunteerQueue();
    void registerVolunteer(string name, string contact, string skill); // Enqueue
    void deployVolunteer();                                            // Dequeue
    void viewVolunteers();                                             // Display
};

#endif
