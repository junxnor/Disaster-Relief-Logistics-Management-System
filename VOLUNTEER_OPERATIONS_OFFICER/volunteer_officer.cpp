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

bool VolunteerQueue::registerVolunteer(string name, string contact, string skill)
{
    if (name.empty() || contact.empty() || skill.empty())
    {
        cout << "ERROR: All fields (name, contact, skill) must be provided.\n";
        return false;
    }

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
    cout << "SUCCESS: Volunteer Registered: " << name << "\n";
    return true;
}

bool VolunteerQueue::deployVolunteer()
{
    if (front == NULL)
    {
        cout << "ERROR: No volunteers to deploy.\n";
        return false;
    }
    Volunteer *temp = front;
    cout << "SUCCESS: Deploying Volunteer: " << temp->name << "\n";
    front = front->next;
    if (front == NULL)
        rear = NULL;
    delete temp;
    return true;
}

bool VolunteerQueue::viewVolunteers()
{
    if (front == NULL)
    {
        cout << "WARNING: No registered volunteers.\n";
        return false;
    }
    cout << "SUCCESS: Displaying Registered Volunteers:\n";
    cout << "+------------------+------------------+------------------+\n";
    cout << "|       Name       |     Contact      |      Skill       |\n";
    cout << "+------------------+------------------+------------------+\n";

    Volunteer *temp = front;
    while (temp != NULL)
    {
        cout << "| " << temp->name;
        // Pad Name to 16 characters
        for (int i = temp->name.length(); i < 16; i++)
            cout << " ";
        cout << " | " << temp->contact;
        // Pad Contact to 16 characters
        for (int i = temp->contact.length(); i < 16; i++)
            cout << " ";
        cout << " | " << temp->skill;
        // Pad Skill to 16 characters
        for (int i = temp->skill.length(); i < 16; i++)
            cout << " ";
        cout << " |\n";
        temp = temp->next;
    }
    cout << "+------------------+------------------+------------------+\n";
    return true;
}
