#include <iostream>
using namespace std;

struct Appointment {
    int startTime;
    int endTime;
    Appointment* next;
};

class AppointmentSchedule {
private:
    Appointment* head;
    int minDuration;
    int maxDuration;
    int dayStart;
    int dayEnd;

public:
    AppointmentSchedule(int minD, int maxD, int start, int end) {
        head = nullptr;
        minDuration = minD;
        maxDuration = maxD;
        dayStart = start;
        dayEnd = end;
    }

    void displayFreeSlots() {
        Appointment* temp = head;
        int lastEnd = dayStart;
        while (temp != nullptr) {
            if (temp->startTime > lastEnd) {
                cout << "Free slot: " << lastEnd << " to " << temp->startTime << endl;
            }
            lastEnd = temp->endTime;
            temp = temp->next;
        }
        if (lastEnd < dayEnd) {
            cout << "Free slot: " << lastEnd << " to " << dayEnd << endl;
        }
    }

    bool bookAppointment(int start, int duration) {
        if (duration < minDuration || duration > maxDuration) {
            cout << "Invalid duration." << endl;
            return false;
        }

        int end = start + duration;
        if (start < dayStart || end > dayEnd) {
            cout << "Invalid time bounds." << endl;
            return false;
        }

        Appointment* newAppt = new Appointment{start, end, nullptr};
        if (head == nullptr || head->startTime > end) {
            newAppt->next = head;
            head = newAppt;
            cout << "Appointment booked." << endl;
            return true;
        }

        Appointment* temp = head;
        while (temp->next != nullptr && temp->next->startTime < start) {
            temp = temp->next;
        }

        if (temp->endTime <= start && (temp->next == nullptr || temp->next->startTime >= end)) {
            newAppt->next = temp->next;
            temp->next = newAppt;
            cout << "Appointment booked." << endl;
            return true;
        }

        cout << "Slot unavailable." << endl;
        return false;
    }

    bool cancelAppointment(int start) {
        if (head == nullptr) {
            cout << "No appointments to cancel." << endl;
            return false;
        }

        if (head->startTime == start) {
            Appointment* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Appointment canceled." << endl;
            return true;
        }

        Appointment* temp = head;
        while (temp->next != nullptr && temp->next->startTime != start) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            Appointment* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Appointment canceled." << endl;
            return true;
        }

        cout << "Appointment not found." << endl;
        return false;
    }
};

int main() {
    AppointmentSchedule schedule(30, 120, 900, 1700); // min max daystart dayend  5-9

    schedule.displayFreeSlots();
    schedule.bookAppointment(1000, 60); // start dur
    schedule.bookAppointment(1100, 30);
    schedule.displayFreeSlots();

    schedule.cancelAppointment(1000);
    schedule.displayFreeSlots();

    schedule.bookAppointment(930, 45);
    schedule.bookAppointment(1500, 60);
}
