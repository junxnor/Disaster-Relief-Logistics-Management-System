#include "emergency_requests.hpp"

EmergencyPriorityQueue::EmergencyPriorityQueue()
{
    head = NULL;
}

EmergencyPriorityQueue::~EmergencyPriorityQueue()
{
    while (head != NULL)
    {
        EmergencyRequest *temp = head;
        head = head->next;
        delete temp;
    }
}

bool EmergencyPriorityQueue::logRequest(string location, string type, int urgency)
{
    if (location.empty() || type.empty())
    {
        cout << "ERROR: Location and type must be provided.\n";
        return false;
    }
    if (urgency < 1 || urgency > 10)
    {
        cout << "ERROR: Urgency must be between 1-10.\n";
        return false;
    }

    EmergencyRequest *newReq = new EmergencyRequest{location, type, urgency, NULL};

    if (head == NULL || urgency > head->urgency)
    {
        newReq->next = head;
        head = newReq;
    }
    else
    {
        EmergencyRequest *temp = head;
        while (temp->next != NULL && temp->next->urgency >= urgency)
            temp = temp->next;
        newReq->next = temp->next;
        temp->next = newReq;
    }

    cout << "SUCCESS: Emergency Request Logged: " << location << ", Type: " << type << ", Urgency: " << urgency << "\n";
    return true;
}

bool EmergencyPriorityQueue::processCritical()
{
    if (head == NULL)
    {
        cout << "ERROR: No emergency requests to process.\n";
        return false;
    }
    EmergencyRequest *temp = head;
    cout << "SUCCESS: Processing Critical Request: " << temp->location << ", Type: " << temp->type << "\n";
    head = head->next;
    delete temp;
    return true;
}

bool EmergencyPriorityQueue::viewRequests()
{
    if (head == NULL)
    {
        cout << "WARNING: No pending emergency requests.\n";
        return false;
    }
    cout << "SUCCESS: Displaying Pending Emergency Requests:\n";
    cout << "+------------------+------------------+----------+\n";
    cout << "|     Location     |       Type       | Urgency  |\n";
    cout << "+------------------+------------------+----------+\n";

    EmergencyRequest *temp = head;
    while (temp != NULL)
    {
        cout << "| " << temp->location;
        // Pad Location to 16 characters
        for (int i = temp->location.length(); i < 16; i++)
            cout << " ";
        cout << " | " << temp->type;
        // Pad Type to 16 characters
        for (int i = temp->type.length(); i < 16; i++)
            cout << " ";
        cout << " | " << temp->urgency;
        // Pad Urgency to 8 characters
        for (int i = to_string(temp->urgency).length(); i < 8; i++)
            cout << " ";
        cout << " |\n";
        temp = temp->next;
    }
    cout << "+------------------+------------------+----------+\n";
    return true;
}
