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
    cout << "\n========== Pending Emergency Requests ==========\n";

    EmergencyRequest *temp = head;
    while (temp != NULL)
    {
        cout << "Location: " << temp->location
             << " | Type: " << temp->type
             << " | Urgency: " << temp->urgency
             << endl;
        temp = temp->next;
    }
    return true;
}

bool EmergencyPriorityQueue::saveToCSV()
{
    ofstream file("emergency_data.csv");
    if (!file.is_open())
    {
        return false;
    }

    file << "Location,Type,Urgency\n";

    EmergencyRequest *temp = head;
    while (temp != NULL)
    {
        file << temp->location << "," << temp->type << "," << temp->urgency << "\n";
        temp = temp->next;
    }

    file.close();
    return true;
}

bool EmergencyPriorityQueue::loadFromCSV()
{
    ifstream file("emergency_data.csv");
    if (!file.is_open())
    {
        return true;
    }

    string line;
    getline(file, line);

    while (head != NULL)
    {
        EmergencyRequest *temp = head;
        head = head->next;
        delete temp;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string location, type, urgencyStr;

        if (getline(ss, location, ',') &&
            getline(ss, type, ',') &&
            getline(ss, urgencyStr, ','))
        {
            int urgency = stoi(urgencyStr);

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
        }
    }

    file.close();
    return true;
}
