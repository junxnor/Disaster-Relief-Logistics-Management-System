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

void EmergencyPriorityQueue::logRequest(string location, string type, int urgency)
{
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

    cout << "Emergency Request Logged: " << location << ", Type: " << type << ", Urgency: " << urgency << "\n";
}

void EmergencyPriorityQueue::processCritical()
{
    if (head == NULL)
    {
        cout << "No emergency requests.\n";
        return;
    }
    EmergencyRequest *temp = head;
    cout << "Processing Critical Request: " << temp->location << ", Type: " << temp->type << "\n";
    head = head->next;
    delete temp;
}

void EmergencyPriorityQueue::viewRequests()
{
    if (head == NULL)
    {
        cout << "No pending emergency requests.\n";
        return;
    }
    EmergencyRequest *temp = head;
    cout << "Pending Emergency Requests:\n";
    while (temp != NULL)
    {
        cout << temp->location << " | " << temp->type << " | Urgency: " << temp->urgency << "\n";
        temp = temp->next;
    }
}
