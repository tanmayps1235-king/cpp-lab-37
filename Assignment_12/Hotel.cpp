#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <stdexcept>
using namespace std;

const int SIZE = 60;
const int MAX_GUESTS = 180;

// Safe integer input
int readInt(const string& prompt, int low, int high) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= low && value <= high) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) throw runtime_error("Input ended");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Try again.\n";
    }
}

// Date class
class Date {
public:
    int day, month, year;

    Date(int d = 0, int m = 0, int y = 0)
        : day(d), month(m), year(y) {}

    static bool leap(int y) {
        return y % 400 == 0 ||
               (y % 4 == 0 && y % 100 != 0);
    }

    bool valid() const {
        if (year < 1 || year > 9999 ||
            month < 1 || month > 12)
            return false;

        int days[] = {
            31,28,31,30,31,30,31,31,30,31,30,31
        };

        if (leap(year)) days[1] = 29;

        return day >= 1 && day <= days[month - 1];
    }

    long toDays() const {
        int y = year - 1;
        long total = 365L * y + y / 4 - y / 100 + y / 400;

        int days[] = {
            31,28,31,30,31,30,31,31,30,31,30,31
        };

        if (leap(year)) days[1] = 29;

        for (int m = 1; m < month; ++m)
            total += days[m - 1];

        return total + day;
    }

    // Operator overloading
    bool operator<(const Date& other) const {
        return toDays() < other.toDays();
    }

    void show() const {
        cout << day << "/" << month << "/" << year;
    }
};

// Input date
Date inputDate() {
    while (true) {
        int d = readInt("Enter Day: ", 1, 31);
        int m = readInt("Enter Month: ", 1, 12);
        int y = readInt("Enter Year: ", 1, 9999);

        Date date(d, m, y);

        if (date.valid())
            return date;

        cout << "Invalid calendar date. Please enter again.\n";
    }
}

// Inheritance and virtual function
class BillingPolicy {
public:
    virtual double gst(double subtotal) const = 0;
    virtual ~BillingPolicy() {}
};

class StandardBilling : public BillingPolicy {
public:
    double gst(double subtotal) const override {
        return subtotal * 0.18;
    }
};

// Hotel class
class Hotel {
private:
    int type, roomNumber;
    char status;
    string guestName;
    Date checkInDate, checkOutDate;
    double charge, bill;

public:
    // Constructor
    Hotel()
        : type(0), roomNumber(0), status('A'),
          charge(0), bill(0) {}

    void setRoom(int t, int number, double rate) {
        type = t;
        roomNumber = number;
        charge = rate;
        status = 'A';
    }

    int getType() const {
        return type;
    }

    int getNumber() const {
        return roomNumber;
    }

    char getStatus() const {
        return status;
    }

    double getCharge() const {
        return charge;
    }

    const string& getName() const {
        return guestName;
    }

    Date getCheckIn() const {
        return checkInDate;
    }

    Date getCheckOut() const {
        return checkOutDate;
    }

    double getBill() const {
        return bill;
    }

    void occupy() {
        status = 'O';
    }

    void release() {
        status = 'A';
    }

    void setGuest(int t, int number,
                  const string& name,
                  Date date, double rate) {
        type = t;
        roomNumber = number;
        guestName = name;
        checkInDate = date;
        checkOutDate = Date();
        charge = rate;
        bill = 0;
        status = 'O';
    }

    void finish(Date date, double total) {
        checkOutDate = date;
        bill = total;
        status = 'A';
    }

    bool checkedOut() const {
        return checkOutDate.valid();
    }
};

// Hotel Management class
class HotelManagement {
private:
    Hotel Consumers[MAX_GUESTS];

    Hotel single_Room[SIZE];
    Hotel double_Room[SIZE];
    Hotel suits_Room[SIZE];

    int n;
    StandardBilling billing;

    Hotel& selectedRoom(int type, int number) {
        if (type == 1)
            return single_Room[number - 1];

        if (type == 2)
            return double_Room[number - 1];

        return suits_Room[number - 1];
    }

    // Find guest by name
    int findGuest(const string& name, bool activeOnly) const {
        for (int i = n - 1; i >= 0; --i) {
            if (Consumers[i].getName() == name &&
                (!activeOnly || !Consumers[i].checkedOut())) {
                return i;
            }
        }

        return -1;
    }

    // Function overloading
    int calculateDays(long inDays, long outDays) const {
        return static_cast<int>(outDays - inDays);
    }

    int calculateDays(const Date& inDate,
                      const Date& outDate) const {
        return calculateDays(
            inDate.toDays(),
            outDate.toDays()
        );
    }

public:
    // Constructor
    HotelManagement() : n(0) {
        room_assigning();
    }

    // Assign 180 rooms
    void room_assigning() {
        for (int i = 0; i < SIZE; ++i) {
            single_Room[i].setRoom(1, i + 1, 2500);
            double_Room[i].setRoom(2, i + 1, 3500);
            suits_Room[i].setRoom(3, i + 1, 4500);
        }
    }

    // Book room
    void consumer_Input() {
        cout << "\n<------------Booking------------>\n";

        if (n >= MAX_GUESTS) {
            cout << "Guest record limit reached (180).\n";
            return;
        }

        int type = readInt(
            "Enter Type of room (1.Single 2.Double 3.Suite): ",
            1, 3
        );

        string name;

        cout << "Enter Guest name: ";
        getline(cin, name);

        if (name.find_first_not_of(" \t") == string::npos) {
            cout << "Guest name cannot be empty.\n";
            return;
        }

        int number;

        while (true) {
            number = readInt(
                "Enter Number Of Room For Booking (1-60): ",
                1, 60
            );

            if (selectedRoom(type, number).getStatus() == 'A')
                break;

            cout << "Room is already occupied! "
                 << "Choose another room.\n";
        }

        Hotel& room = selectedRoom(type, number);

        cout << "Charge of Room: Rs."
             << fixed << setprecision(2)
             << room.getCharge()
             << "\nEnter Check In Date\n";

        Date date = inputDate();

        Consumers[n].setGuest(
            type, number, name, date, room.getCharge()
        );

        room.occupy();
        ++n;

        cout << "Room type-" << type
             << " number " << number << " - O\n";

        cout << "<------------Added successfully------------>\n";
    }

    // Checkout
    void check_Out() {
        cout << "\n<------------Checking Out------------>\n";

        if (n == 0) {
            cout << "Guest is zero\n";
            return;
        }

        string name;
        int index;

        while (true) {
            cout << "Enter Guest Name (or return): ";
            getline(cin, name);

            if (name == "return")
                return;

            index = findGuest(name, true);

            if (index >= 0)
                break;

            cout << "Guest not found among occupied bookings!\n";
        }

        Hotel& guest = Consumers[index];

        cout << "Room number: "
             << guest.getNumber() << '\n';

        cout << "Enter Check Out Date\n";

        Date out = inputDate();

        // Operator overloading
        if (!(guest.getCheckIn() < out)) {
            throw invalid_argument(
                "Check Out Date must be after Check In Date."
            );
        }

        int days = calculateDays(
            guest.getCheckIn(), out
        );

        double subtotal = days * guest.getCharge();

        // Runtime polymorphism
        const BillingPolicy& policy = billing;

        double tax = policy.gst(subtotal);
        double total = subtotal + tax;

        guest.finish(out, total);

        selectedRoom(
            guest.getType(),
            guest.getNumber()
        ).release();

        cout << fixed << setprecision(2)
             << "Without GST bill: Rs." << subtotal
             << "\nGST: Rs." << tax
             << "\nBill: Rs." << total
             << "\nRoom is Now Available\n"
             << "<------Check out Successfully------>\n";
    }

    // Display occupied rooms
    void display_Occupied_room() const {
        cout << "\n<------------Occupied Room------------>\n";

        cout << "Single - Occupied Room: ";

        bool found = false;

        for (int i = 0; i < SIZE; ++i) {
            if (single_Room[i].getStatus() == 'O') {
                cout << single_Room[i].getNumber() << ' ';
                found = true;
            }
        }

        if (!found)
            cout << "None";

        cout << "\nDouble - Occupied Room: ";

        found = false;

        for (int i = 0; i < SIZE; ++i) {
            if (double_Room[i].getStatus() == 'O') {
                cout << double_Room[i].getNumber() << ' ';
                found = true;
            }
        }

        if (!found)
            cout << "None";

        cout << "\nSuite - Occupied Room: ";

        found = false;

        for (int i = 0; i < SIZE; ++i) {
            if (suits_Room[i].getStatus() == 'O') {
                cout << suits_Room[i].getNumber() << ' ';
                found = true;
            }
        }

        if (!found)
            cout << "None";

        cout << "\n";
    }

    // Display room charges
    void charges() const {
        cout << "\n<------------Charges------------>\n";

        cout << fixed << setprecision(2)
             << "Single room: Rs."
             << single_Room[0].getCharge()
             << "\nDouble room: Rs."
             << double_Room[0].getCharge()
             << "\nSuite room : Rs."
             << suits_Room[0].getCharge()
             << "\nGST: 18% (project example)\n";
    }

    // Guest information
    void consumer_info() const {
        cout << "\n<------------Consumer Information------------>\n";

        if (n == 0) {
            cout << "No guest records.\n";
            return;
        }

        string name;
        int index;

        while (true) {
            cout << "Enter Guest Name (or return): ";
            getline(cin, name);

            if (name == "return")
                return;

            index = findGuest(name, false);

            if (index >= 0)
                break;

            cout << "Guest not found!\n";
        }

        const Hotel& guest = Consumers[index];

        cout << "Room number: "
             << guest.getNumber()
             << "\nType: "
             << guest.getType()
             << "\nCheck in date: ";

        guest.getCheckIn().show();

        if (guest.checkedOut()) {
            cout << "\nCheck out date: ";
            guest.getCheckOut().show();

            cout << "\nBill: Rs."
                 << fixed << setprecision(2)
                 << guest.getBill();
        }
        else {
            cout << "\nGuest doesn't check out yet."
                 << "\nBill doesn't exist.";
        }

        cout << "\n";
    }
};

// Main function
int main() {
    HotelManagement hotel;

    try {
        while (true) {
            cout << "\n<------------Booking------------>\n"
                 << "1.Book Room.\n"
                 << "2.Check Out.\n"
                 << "3.Occupied Room.\n"
                 << "4.Charges.\n"
                 << "5.Consumer Info.\n"
                 << "6.Exit\n";

            int choice = readInt("Enter choice: ", 1, 6);

            if (choice == 6) {
                cout << "<------------Exit successfully------------>\n";
                break;
            }

            try {
                switch (choice) {
                    case 1:
                        hotel.consumer_Input();
                        break;

                    case 2:
                        hotel.check_Out();
                        break;

                    case 3:
                        hotel.display_Occupied_room();
                        break;

                    case 4:
                        hotel.charges();
                        break;

                    case 5:
                        hotel.consumer_info();
                        break;
                }
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << '\n';
            }
        }
    }
    catch (const exception& e) {
        cout << "Program stopped: "
             << e.what() << '\n';
    }

    return 0;
}