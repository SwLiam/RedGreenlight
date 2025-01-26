#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;

mutex traffic_mutex;

bool north_south_green = true;
bool east_west_green = false;

void controlTraffic() {
    while (true) {
        {
            lock_guard<mutex> lock(traffic_mutex);
            
           
            cout << "Espana Blvd - North-South Lanes: Green Light\n";
            cout << "Lacson Ave - East-West Lanes: Red Light\n\n";
                this_thread::sleep_for(chrono::seconds(15));

           
            cout << "Espana Blvd - North-South Lanes: Yellow Light\n";
            cout << "Lacson Ave - East-West Lanes: Yellow Light\n\n";
                this_thread::sleep_for(chrono::seconds(3));

            cout << "Lacson Ave - East-West Lanes: Green Light\n";
            cout << "Espana Blvd - North-South Lanes: Red Light\n\n";
                this_thread::sleep_for(chrono::seconds(15));

          
            cout << "Lacson Ave - East-West Lanes: Yellow Light\n";
            cout << "Espana Blvd - North-South Lanes: Yellow Light\n\n";
                this_thread::sleep_for(chrono::seconds(3));
        }

        this_thread::sleep_for(chrono::milliseconds(25));
    }
}

int main() {
    thread traffic_thread(controlTraffic);
    
    this_thread::sleep_for(chrono::minutes(1));

    cout << "Traffic Simulation ended.\n";
    cout << "\n --- Group 8 activity 1 --- .\n";

    traffic_thread.detach();
    return 0;
}
