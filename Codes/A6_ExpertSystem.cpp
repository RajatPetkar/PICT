// Assignment 6: Expert System - Medical Diagnosis
// No global variables | STL friendly | Parameter passing style
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Patient {
    string name;
    int age;
    bool fever, cough, cold, soreThroat;
    bool bodyPain, headache, fatigue;
    bool chestPain, breathShort;
    bool stomachPain, vomiting, diarrhea;
};

bool ask(string question) {
    char c;
    cout << question << " (y/n): ";
    cin >> c;
    return (c == 'y' || c == 'Y');
}

Patient getPatientInfo() {
    Patient p;
    cout << "Enter patient name: ";
    cin >> p.name;
    cout << "Enter patient age: ";
    cin >> p.age;

    cout << "\nAnswer the following symptoms:\n";
    p.fever       = ask("Fever");
    p.cough       = ask("Cough");
    p.cold        = ask("Cold / Runny Nose");
    p.soreThroat  = ask("Sore Throat");
    p.bodyPain    = ask("Body Pain");
    p.headache    = ask("Headache");
    p.fatigue     = ask("Fatigue / Tiredness");
    p.chestPain   = ask("Chest Pain");
    p.breathShort = ask("Shortness of Breath");
    p.stomachPain = ask("Stomach Pain");
    p.vomiting    = ask("Vomiting");
    p.diarrhea    = ask("Diarrhea");

    return p;
}

void diagnose(Patient& p) {
    cout << "\n=========================================\n";
    cout << "Patient: " << p.name << " | Age: " << p.age << "\n";
    cout << "-----------------------------------------\n";

    bool diagnosed = false;

    // Rule 1: Flu
    if(p.fever && p.bodyPain && p.fatigue && p.cough) {
        cout << "Diagnosis : Influenza (Flu)\n";
        cout << "Advice    : Rest, drink fluids.\n";
        cout << "Medicine  : Paracetamol, Antihistamine\n\n";
        diagnosed = true;
    }

    // Rule 2: Common Cold
    if(!p.fever && p.cold && p.cough && p.soreThroat) {
        cout << "Diagnosis : Common Cold\n";
        cout << "Advice    : Hot fluids, stay warm.\n";
        cout << "Medicine  : Cetirizine, Vitamin C\n\n";
        diagnosed = true;
    }

    // Rule 3: Viral Infection
    if(p.fever && p.cough && p.breathShort && p.fatigue) {
        cout << "Diagnosis : Possible Viral Infection\n";
        cout << "Advice    : Isolate and consult a doctor.\n";
        cout << "Medicine  : See a doctor immediately.\n\n";
        diagnosed = true;
    }

    // Rule 4: Cardiac Emergency
    if(p.chestPain && p.breathShort) {
        cout << "Diagnosis : POSSIBLE CARDIAC ISSUE - EMERGENCY!\n";
        cout << "Advice    : Go to ER immediately!\n";
        cout << "Medicine  : Do NOT self-medicate.\n\n";
        diagnosed = true;
    }

    // Rule 5: Food Poisoning
    if(p.stomachPain && p.vomiting && p.diarrhea) {
        cout << "Diagnosis : Food Poisoning / Gastroenteritis\n";
        cout << "Advice    : ORS, light diet, stay hydrated.\n";
        cout << "Medicine  : ORS, Ondansetron\n\n";
        diagnosed = true;
    }

    // Rule 6: Migraine
    if(p.headache && !p.fever && !p.cough) {
        cout << "Diagnosis : Migraine / Tension Headache\n";
        cout << "Advice    : Rest in dark room, avoid screens.\n";
        cout << "Medicine  : Ibuprofen\n\n";
        diagnosed = true;
    }

    if(!diagnosed) {
        cout << "Diagnosis : Unclear. Please consult a doctor.\n\n";
    }

    if(p.age > 60 || p.age < 5)
        cout << "WARNING: High-risk patient (age). Immediate care advised!\n";

    cout << "=========================================\n";
}

int main() {
    char again;
    do {
        Patient p = getPatientInfo();
        diagnose(p);
        cout << "\nCheck another patient? (y/n): ";
        cin >> again;
        cout << "\n";
    } while(again == 'y' || again == 'Y');

    cout << "Thank you for using the Medical Expert System.\n";
    return 0;
}
