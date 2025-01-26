#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <limits>

using namespace std;

mutex traffic_mutex;

bool north_south_green = false;
bool east_west_green = false;

void controlTraffic(const string& direction, bool& current_green, bool& other_green, int cycles) {
    for (int i = 0; i < cycles; ++i) {
        {
            lock_guard<mutex> lock(traffic_mutex);
            if (current_green) {
                cout << direction << " Lanes: Green Light\n";
                this_thread::sleep_for(chrono::seconds(30)); // Green light duration
                cout << direction << " Lanes: Yellow Light\n";
                this_thread::sleep_for(chrono::seconds(5));  // Yellow light duration
                cout << direction << " Lanes: Red Light\n";

                current_green = false;
                other_green = true;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100)); // Small buffer for realism
    }
}

int main() {
    string start_direction;
    int cycles;

    // Choose which road goes first
    while (true) {
        cout << "Which road should go first? (north-south / east-west): ";
        cin >> start_direction;

        if (start_direction == "north-south") {
            north_south_green = true;
            east_west_green = false;
            break;
        } else if (start_direction == "east-west") {
            north_south_green = false;
            east_west_green = true;
            break;
        } else {
            cout << "Invalid input. Please enter 'north-south' or 'east-west'.\n";
        }
    }

    // Number of cycles
    while (true) {
        cout << "Enter the number of cycles for the simulation: ";
        cin >> cycles;

        if (cin.fail() || cycles <= 0) {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            break;
        }
    }

    thread north_south_thread(controlTraffic, "Espana Blvd - North-South", ref(north_south_green), ref(east_west_green), cycles);
    thread east_west_thread(controlTraffic, "Lacson Ave - East-West", ref(east_west_green), ref(north_south_green), cycles);

    north_south_thread.join();
    east_west_thread.join();

    cout << "Traffic simulation ended.\n";
    return 0;
}
