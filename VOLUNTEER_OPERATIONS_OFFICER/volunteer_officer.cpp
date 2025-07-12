#include "volunteer_officer.hpp"

VolunteerQueue::VolunteerQueue()
{
    front = rear = NULL;
}

VolunteerQueue::~VolunteerQueue()
{
    while (front != NULL)
    {
        Volunteer *temp = front;
        front = front->next;
        delete temp;
    }
}

void VolunteerQueue::registerVolunteer(string name, string contact, string skill)
{
    Volunteer *newVol = new Volunteer{name, contact, skill, NULL};
    if (rear == NULL)
    {
        front = rear = newVol;
    }
    else
    {
        rear->next = newVol;
        rear = newVol;
    }
    cout << "Volunteer Registered: " << name << "\n";
}

void VolunteerQueue::deployVolunteer()
{
    if (front == NULL)
    {
        cout << "No volunteers to deploy.\n";
        return;
    }
    Volunteer *temp = front;
    cout << "Deploying Volunteer: " << temp->name << "\n";
    front = front->next;
    if (front == NULL)
        rear = NULL;
    delete temp;
}

void VolunteerQueue::viewVolunteers()
{
    if (front == NULL)
    {
        cout << "No registered volunteers.\n";
        return;
    }
    Volunteer *temp = front;
    cout << "Registered Volunteers:\n";
    while (temp != NULL)
    {
        cout << temp->name << " | " << temp->contact << " | " << temp->skill << "\n";
        temp = temp->next;
    }
}
