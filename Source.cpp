#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int MAX_BOATS = 10;
const double COST_PER_HOUR = 20.0;
const double COST_PER_HALF_HOUR = 12.0;
const int OPENING_HOUR = 10;
const int CLOSING_HOUR = 17;

struct Boat {
    bool isAvailable;
    double moneyTaken;
    double totalHoursHired;
    int returnTime;
};

void initializeBoats(vector<Boat>& boats) {
    for (int i = 0; i < MAX_BOATS; ++i) {
        boats.push_back({ true, 0.0, 0.0, 0 });
    }
}

void displayBoats(const vector<Boat>& boats) {
    for (int i = 0; i < MAX_BOATS; ++i) {
        cout << "Boat " << (i + 1) << " - Available: " << (boats[i].isAvailable ? "Yes" : "No") << endl;
    }
}

bool isBoatAvailable(const vector<Boat>& boats, int currentTime) {
    for (int i = 0; i < MAX_BOATS; ++i) {
        if (boats[i].isAvailable) {
            return true;
        }
    }
    cout << "No boats are currently available for hire." << endl;
    int nextAvailableTime = CLOSING_HOUR;
    for (int i = 0; i < MAX_BOATS; ++i) {
        if (boats[i].returnTime > currentTime && boats[i].returnTime < nextAvailableTime) {
            nextAvailableTime = boats[i].returnTime;
        }
    }
    cout << "The earliest time the next boat will be available is at " << nextAvailableTime << ":00" << endl;
    return false;
}

void hireBoat(vector<Boat>& boats, int boatNumber, int currentTime, double hireDuration) {
    if (currentTime < OPENING_HOUR || currentTime >= CLOSING_HOUR) {
        cout << "Boats can only be hired between 10:00 and 17:00." << endl;
        return;
    }

    boatNumber--; // Adjusting boat number to match the index (0-based indexing)

    if (!boats[boatNumber].isAvailable) {
        cout << "Boat " << (boatNumber + 1) << " is not available for hire at the moment." << endl;
        return;
    }

    if (hireDuration == 0.5 || hireDuration == 1.0) {
        double cost = (hireDuration == 1.0) ? COST_PER_HOUR : COST_PER_HALF_HOUR;
        double money = cost * hireDuration;
        boats[boatNumber].moneyTaken += money;
        boats[boatNumber].totalHoursHired += hireDuration;
        boats[boatNumber].returnTime = currentTime + hireDuration;
        boats[boatNumber].isAvailable = false;

        cout << "Boat " << (boatNumber + 1) << " has been hired for " << hireDuration << " hours." << endl;
    }
    else {
        cout << "Invalid duration. You can only hire for 0.5 or 1 hour." << endl;
    }
}

void calculateTotalAtEndOfDay(const vector<Boat>& boats) {
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int boatsNotUsed = 0;
    int mostUsedBoat = 0;
    double maxHours = 0.0;

    for (int i = 0; i < MAX_BOATS; ++i) {
        totalMoney += boats[i].moneyTaken;
        totalHours += boats[i].totalHoursHired;

        if (boats[i].totalHoursHired == 0) {
            boatsNotUsed++;
        }

        if (boats[i].totalHoursHired > maxHours) {
            maxHours = boats[i].totalHoursHired;
            mostUsedBoat = i + 1;
        }
    }

    cout << "Total money taken at the end of the day: $" << totalMoney << endl;
    cout << "Total hours boats were hired today: " << totalHours << " hours" << endl;
    cout << "Number of boats not used today: " << boatsNotUsed << endl;
    cout << "Boat " << mostUsedBoat << " was used the most, with " << maxHours << " hours hired." << endl;
}

int main() {
    vector<Boat> boats;
    initializeBoats(boats);

    int currentTime;
    cout << "Enter the current time (in hours): ";
    cin >> currentTime;

    // Task 1 - Calculate the money taken for one boat
    int boatNumber;
    double hireDuration;
    cout << "Enter the boat number to hire (1-10): ";
    cin >> boatNumber;
    cout << "Enter the duration to hire (0.5 or 1 hour): ";
    cin >> hireDuration;
    hireBoat(boats, boatNumber, currentTime, hireDuration);

    // Task 2 - Find the next boat available
    displayBoats(boats);
    isBoatAvailable(boats, currentTime);

    // Task 3 - Calculate the money taken for all the boats at the end of the day
    calculateTotalAtEndOfDay(boats);

    return 0;
}
