#include "volunteer_officer.hpp"
#include <algorithm>
#include <cctype>
#include "../EMERGENCY_REQUEST_COORDINATOR/emergency_requests.hpp"

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

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
    cout << "\n========== Registered Volunteers ==========\n";

    Volunteer *temp = front;
    while (temp != NULL)
    {
        cout << "Name: " << temp->name
             << " | Contact: " << temp->contact
             << " | Skill: " << temp->skill
             << endl;
        temp = temp->next;
    }
    return true;
}

bool VolunteerQueue::saveToCSV()
{
    ofstream file("volunteer_data.csv");
    if (!file.is_open())
    {
        return false;
    }

    file << "Name,Contact,Skill\n";

    Volunteer *temp = front;
    while (temp != NULL)
    {
        file << temp->name << "," << temp->contact << "," << temp->skill << "\n";
        temp = temp->next;
    }

    file.close();
    return true;
}

bool VolunteerQueue::loadFromCSV()
{
    ifstream file("volunteer_data.csv");
    if (!file.is_open())
    {
        return true;
    }

    string line;
    getline(file, line);

    while (front != NULL)
    {
        Volunteer *temp = front;
        front = front->next;
        delete temp;
    }
    front = rear = NULL;

    while (getline(file, line))
    {
        stringstream ss(line);
        string name, contact, skill;

        if (getline(ss, name, ',') &&
            getline(ss, contact, ',') &&
            getline(ss, skill, ','))
        {
            name = trim(name);
            contact = trim(contact);
            skill = trim(skill);

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
        }
    }

    file.close();
    return true;
}

bool VolunteerQueue::viewVolunteersWithSelection()
{
    if (front == NULL)
    {
        cout << "WARNING: No volunteers registered.\n";
        return false;
    }

    cout << "\n========== Available Volunteers ==========\n";
    cout << "Name\t\t| Contact\t\t| Skill\n";
    cout << "--------------------------------------------\n";

    Volunteer *temp = front;
    while (temp != NULL)
    {
        cout << temp->name << "\t\t| " << temp->contact << "\t\t| " << temp->skill << endl;
        temp = temp->next;
    }
    return true;
}

bool VolunteerQueue::removeVolunteerByName(string name)
{
    if (front == NULL)
    {
        return false;
    }

    name = trim(name);
    if (front->name == name)
    {
        Volunteer *temp = front;
        front = front->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        delete temp;
        return true;
    }

    Volunteer *current = front;
    while (current->next != NULL && current->next->name != name)
    {
        current = current->next;
    }

    if (current->next != NULL && current->next->name == name)
    {
        Volunteer *temp = current->next;
        current->next = temp->next;
        if (temp == rear)
        {
            rear = current;
        }
        delete temp;
        return true;
    }

    return false;
}

bool VolunteerQueue::deployVolunteerToEmergency()
{
    loadFromCSV();

    cout << "\n=== Deploy Volunteer to Emergency ===\n";
    EmergencyPriorityQueue emergency;
    emergency.loadFromCSV();

    cout << "\n--- Critical Emergency Requests ---\n";
    if (!emergency.viewCriticalRequestsWithSelection())
    {
        cout << "No critical emergency requests found.\n";
        return false;
    }

    cout << "\n--- Available Volunteers ---\n";
    if (!viewVolunteersWithSelection())
    {
        cout << "No volunteers available.\n";
        return false;
    }

    string volunteerName;
    cout << "\nEnter Volunteer Name to deploy: ";
    cin.ignore();
    getline(cin, volunteerName);

    volunteerName = trim(volunteerName);

    if (removeVolunteerByName(volunteerName))
    {
        cout << "SUCCESS: Volunteer \"" << volunteerName << "\" has been deployed to emergency location.\n";
        saveToCSV();
        return true;
    }
    else
    {
        cout << "ERROR: Volunteer \"" << volunteerName << "\" not found.\n";
        return false;
    }
}
