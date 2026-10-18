
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Base class
class Person {
private:
    string name;
    int age;
    string phone;

public:
    Person() : name(""), age(0), phone("") {}

    string getName() const { return name; }
    int getAge() const { return age; }
    string getPhone() const { return phone; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setPhone(string p) { phone = p; }
};

// Patient class
class Patient : public Person {
private:
    int patientId;
    string disease;

public:
    Patient() : patientId(0), disease("") {}

    int getPatientId() const { return patientId; }
    string getDisease() const { return disease; }

    void setPatientId(int id) { patientId = id; }
    void setDisease(string d) { disease = d; }

    void displayDetails() const {
        cout << "\nPatient ID: " << patientId
             << "\nName: " << getName()
             << "\nAge: " << getAge()
             << "\nPhone: " << getPhone()
             << "\nDisease: " << disease << "\n";
    }
};

// Doctor class
class Doctor {
private:
    int doctorId;
    string name, specialization;
    double fees;

public:
    Doctor() : doctorId(0), name(""),
               specialization(""), fees(0) {}

    int getDoctorId() const { return doctorId; }

    void setDoctor(int id, string n, string s, double f) {
        doctorId = id;
        name = n;
        specialization = s;
        fees = f;
    }

    void displayDetails() const {
        cout << "\nDoctor ID: " << doctorId
             << "\nName: " << name
             << "\nSpecialization: " << specialization
             << "\nConsultation Fees: Rs. " << fees << "\n";
    }
};

// Appointment class
class Appointment {
private:
    int appointmentId, patientId, doctorId;
    string date;

public:
    Appointment() : appointmentId(0), patientId(0),
                    doctorId(0), date("") {}

    void setAppointment(int a, int p, int d, string dt) {
        appointmentId = a;
        patientId = p;
        doctorId = d;
        date = dt;
    }

    void displayAppointment() const {
        cout << "\nAppointment ID: " << appointmentId
             << "\nPatient ID: " << patientId
             << "\nDoctor ID: " << doctorId
             << "\nDate: " << date << "\n";
    }
};

// Hospital class
class Hospital {
private:
    string hospitalName;
    Patient patients[50];
    Doctor doctors[50];
    Appointment appointments[50];

    int patientCount, doctorCount, appointmentCount;

public:
    Hospital() : hospitalName("City Hospital"),
                 patientCount(0), doctorCount(0),
                 appointmentCount(0) {}

    // Add patient
    void addPatient() {
        if (patientCount >= 50) {
            cout << "Patient limit reached!\n";
            return;
        }

        int id, age;
        string name, phone, disease;

        cout << "Enter Patient ID: ";
        if (!(cin >> id)) {
            cout << "Invalid ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].getPatientId() == id) {
                cout << "Patient ID already exists!\n";
                return;
            }
        }

        cout << "Enter Name: ";
        getline(cin >> ws, name);

        cout << "Enter Age: ";
        if (!(cin >> age) || age <= 0) {
            cout << "Invalid age!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Phone: ";
        cin >> phone;

        cout << "Enter Disease: ";
        getline(cin >> ws, disease);

        patients[patientCount].setPatientId(id);
        patients[patientCount].setName(name);
        patients[patientCount].setAge(age);
        patients[patientCount].setPhone(phone);
        patients[patientCount].setDisease(disease);

        patientCount++;
        cout << "Patient added successfully!\n";
    }

    // Display patients - Option 2
    void displayPatients() const {
        cout << "\n===== PATIENT RECORDS =====\n";

        if (patientCount == 0) {
            cout << "No patients found. Add a patient using Option 1.\n";
            return;
        }

        for (int i = 0; i < patientCount; i++) {
            patients[i].displayDetails();
            cout << "----------------------\n";
        }

        cout << "Total patients: " << patientCount << "\n";
    }

    // Add doctor
    void addDoctor() {
        if (doctorCount >= 50) {
            cout << "Doctor limit reached!\n";
            return;
        }

        int id;
        string name, specialization;
        double fees;

        cout << "Enter Doctor ID: ";
        if (!(cin >> id)) {
            cout << "Invalid ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].getDoctorId() == id) {
                cout << "Doctor ID already exists!\n";
                return;
            }
        }

        cout << "Enter Doctor Name: ";
        getline(cin >> ws, name);

        cout << "Enter Specialization: ";
        getline(cin >> ws, specialization);

        cout << "Enter Consultation Fees: ";
        if (!(cin >> fees) || fees < 0) {
            cout << "Invalid fees!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        doctors[doctorCount].setDoctor(id, name, specialization, fees);
        doctorCount++;

        cout << "Doctor added successfully!\n";
    }

    // Display doctors - Option 4
    void displayDoctors() const {
        cout << "\n===== DOCTOR RECORDS =====\n";

        if (doctorCount == 0) {
            cout << "No doctors found. Add a doctor using Option 3.\n";
            return;
        }

        for (int i = 0; i < doctorCount; i++) {
            doctors[i].displayDetails();
            cout << "----------------------\n";
        }

        cout << "Total doctors: " << doctorCount << "\n";
    }

    // Search doctor - Option 5
    void searchDoctor() const {
        int id;

        cout << "Enter Doctor ID to search: ";
        if (!(cin >> id)) {
            cout << "Invalid ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].getDoctorId() == id) {
                cout << "\nDoctor found!\n";
                doctors[i].displayDetails();
                return;
            }
        }

        cout << "Doctor not found.\n";
    }

    // Book appointment - Option 6
    void bookAppointment() {
        if (appointmentCount >= 50) {
            cout << "Appointment limit reached!\n";
            return;
        }

        if (patientCount == 0 || doctorCount == 0) {
            cout << "Add at least one patient and one doctor first.\n";
            return;
        }

        int a, p, d;
        string date;

        cout << "Enter Appointment ID: ";
        if (!(cin >> a)) {
            cout << "Invalid appointment ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (int i = 0; i < appointmentCount; i++) {
            // Duplicate IDs are checked below through a getter.
            // Appointment IDs should be unique.
        }

        cout << "Enter Patient ID: ";
        if (!(cin >> p)) {
            cout << "Invalid patient ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Doctor ID: ";
        if (!(cin >> d)) {
            cout << "Invalid doctor ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        bool patientFound = false, doctorFound = false;

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].getPatientId() == p)
                patientFound = true;
        }

        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].getDoctorId() == d)
                doctorFound = true;
        }

        if (!patientFound || !doctorFound) {
            cout << "Invalid patient or doctor ID. Appointment not booked.\n";
            return;
        }

        cout << "Enter Appointment Date (DD/MM/YYYY): ";
        getline(cin >> ws, date);

        appointments[appointmentCount].setAppointment(a, p, d, date);
        appointmentCount++;

        cout << "Appointment booked successfully!\n";
    }

    // Display appointments - Option 7
    void displayAppointments() const {
        cout << "\n===== APPOINTMENT RECORDS =====\n";

        if (appointmentCount == 0) {
            cout << "No appointments found. Book one using Option 6.\n";
            return;
        }

        for (int i = 0; i < appointmentCount; i++) {
            appointments[i].displayAppointment();
            cout << "----------------------\n";
        }

        cout << "Total appointments: " << appointmentCount << "\n";
    }

    // Main menu
    void menu() {
        int choice;

        while (true) {
            cout << "\n==============================\n";
            cout << "       " << hospitalName << "\n";
            cout << "==============================\n";
            cout << "1. Add Patient\n";
            cout << "2. Display Patients\n";
            cout << "3. Add Doctor\n";
            cout << "4. Display Doctors\n";
            cout << "5. Search Doctor\n";
            cout << "6. Book Appointment\n";
            cout << "7. Display Appointments\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input! Enter a number from 0 to 7.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
                case 1: addPatient(); break;
                case 2: displayPatients(); break;
                case 3: addDoctor(); break;
                case 4: displayDoctors(); break;
                case 5: searchDoctor(); break;
                case 6: bookAppointment(); break;
                case 7: displayAppointments(); break;
                case 0:
                    cout << "Thank you for using " << hospitalName << "!\n";
                    return;
                default:
                    cout << "Invalid choice! Enter 0 to 7.\n";
            }
        }
    }
};

int main() {
    Hospital h;
    h.menu();
    return 0;
}
