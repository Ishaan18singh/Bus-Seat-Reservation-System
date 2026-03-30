#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Bus {
private:
    int busNumber;
    string driverName;
    string arrivalTime;
    string departureTime;
    string from;
    string to;
    string seats[32];  

public:
    Bus() : busNumber(0) {
        for (int i = 0; i < 32; i++)
            seats[i] = "";
    }

    void setInfo(int bn, string dn, string at, string dt, string f, string t) {
        busNumber = bn;
        driverName = dn;
        arrivalTime = at;
        departureTime = dt;
        from = f;
        to = t;
    }

    int getBusNumber() const { return busNumber; }
    string getFrom() const { return from; }
    string getTo() const { return to; }
    string getArrival() const { return arrivalTime; }
    string getDeparture() const { return departureTime; }
    string getDriver() const { return driverName; }

    bool reserveSeat(int seatNum, string passengerName) {
        if (seatNum < 1 || seatNum > 32) {
            cout << "Invalid seat number! Must be between 1 and 32.\n";
            return false;
        }
        if (seats[seatNum - 1] != "") {
            cout << "Seat " << seatNum << " is already booked by " << seats[seatNum - 1] << ".\n";
            return false;
        }
        seats[seatNum - 1] = passengerName;
        cout << "Seat " << seatNum << " successfully reserved for " << passengerName << ".\n";
        return true;
    }

    void displaySeats() const {
        cout << "\n========================================\n";
        cout << "  Seat Map for Bus #" << busNumber << "\n";
        cout << "========================================\n";
        cout << left << setw(8) << "Seat" << setw(25) << "Passenger" << "\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < 32; i++) {
            cout << left << setw(8) << (i + 1)
                 << setw(25) << (seats[i] == "" ? "[ Available ]" : seats[i]) << "\n";
        }
        cout << "========================================\n";
    }

    void printTableRow() const {
        cout << left
             << setw(8)  << busNumber
             << setw(18) << driverName
             << setw(12) << arrivalTime
             << setw(14) << departureTime
             << setw(15) << from
             << setw(15) << to
             << "\n";
    }
};

const int MAX_BUSES = 10;
Bus buses[MAX_BUSES];
int busCount = 0;

// ─── Helper ─────────────────────────────────────────
int findBus(int busNumber) {
    for (int i = 0; i < busCount; i++)
        if (buses[i].getBusNumber() == busNumber)
            return i;
    return -1;
}

void createBusRoute() {
    if (busCount >= MAX_BUSES) {
        cout << "Maximum bus limit reached!\n";
        return;
    }
    int bn;
    string dn, at, dt, fr, to;

    cout << "\n--- Create Bus Route ---\n";
    cout << "Bus Number     : "; cin >> bn;
    if (findBus(bn) != -1) {
        cout << "A bus with that number already exists!\n";
        return;
    }
    cin.ignore();
    cout << "Driver Name    : "; getline(cin, dn);
    cout << "Arrival Time   : "; getline(cin, at);
    cout << "Departure Time : "; getline(cin, dt);
    cout << "From           : "; getline(cin, fr);
    cout << "To             : "; getline(cin, to);

    buses[busCount].setInfo(bn, dn, at, dt, fr, to);
    busCount++;
    cout << "Bus route created successfully!\n";
}

void makeReservation() {
    if (busCount == 0) { cout << "No buses available yet.\n"; return; }

    int bn, seatNum;
    string passengerName;

    cout << "\n--- Make Reservation ---\n";
    cout << "Bus Number    : "; cin >> bn;
    int idx = findBus(bn);
    if (idx == -1) { cout << "Bus not found!\n"; return; }

    cout << "Seat Number (1-32): "; cin >> seatNum;
    cin.ignore();
    cout << "Passenger Name : "; getline(cin, passengerName);

    buses[idx].reserveSeat(seatNum, passengerName);
}

void displayBusSeats() {
    if (busCount == 0) { cout << "No buses available yet.\n"; return; }

    int bn;
    cout << "\n--- Display Seats ---\n";
    cout << "Enter Bus Number: "; cin >> bn;
    int idx = findBus(bn);
    if (idx == -1) { cout << "Bus not found!\n"; return; }

    buses[idx].displaySeats();
}

void showAvailableBuses() {
    if (busCount == 0) { cout << "No buses available yet.\n"; return; }

    cout << "\n========================================================================\n";
    cout << "                        Available Buses\n";
    cout << "========================================================================\n";
    cout << left
         << setw(8)  << "Bus#"
         << setw(18) << "Driver"
         << setw(12) << "Arrival"
         << setw(14) << "Departure"
         << setw(15) << "From"
         << setw(15) << "To"
         << "\n";
    cout << "------------------------------------------------------------------------\n";
    for (int i = 0; i < busCount; i++)
        buses[i].printTableRow();
    cout << "========================================================================\n";
}

int main() {
    int choice;
    cout << "==============================\n";
    cout << "  Bus Seat Reservation System \n";
    cout << "==============================\n";

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Create Bus Route\n";
        cout << "2. Make Reservation\n";
        cout << "3. Display Seats for a Bus\n";
        cout << "4. Show Available Buses\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1: createBusRoute();     break;
            case 2: makeReservation();    break;
            case 3: displayBusSeats();    break;
            case 4: showAvailableBuses(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
