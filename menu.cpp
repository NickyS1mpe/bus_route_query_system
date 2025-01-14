#include <string>
#include <iostream>
#include "menu.h"
#include "map.cpp"

using namespace std;

void query_bus_routes() // Query Bus Routes
{
    int a;
    string bus;
    while (true) {
        cout << "======Bus Route Query System=====" << endl;
        cout << "1. Continue querying bus routes" << endl;
        cout << "0. Exit bus route query" << endl;
        cout << "Enter your choice: ";
        cin >> a;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (a == 0)
            break;
        else {
            cout << "Enter the bus name to query:";
            getline(cin, bus);
            if (find_bus(bus.c_str()) == -1)
                cout << "Incorrect bus name entered!" << endl
                     << endl;
            else
                query_bus(bus.c_str());
            system("read -n 1 -s -p 'Press any key to continue...'");
            system("clear");
        }
    }
}

void query_station_info() // Query Station Information
{
    string station;
    int a;
    while (true) {
        cout << "======Station Information Query System======" << endl;
        cout << "1. Continue querying station information" << endl;
        cout << "0. Exit station information query" << endl;
        cout << "Enter your choice: ";
        cin >> a;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (a == 0)
            break;
        else {
            cout << "Enter the station name to query:";
            getline(cin, station);
            if (find_station(station.c_str()) == -1)
                cout << "Incorrect station name entered!" << endl
                     << endl;
            else
                query_station(station.c_str());
            system("read -n 1 -s -p 'Press any key to continue...'");
            system("clear");
        }
    }
}

void query_two_stations() // Query Bus Routes between Two Stations (At most 1 transfer)
{
    int a;
    string start, end;
    while (true) {
        cout << "======Query Bus Routes between Two Stations (At most 1 transfer)======" << endl;
        cout << "1. Continue querying bus routes between two stations" << endl;
        cout << "0. Exit query for bus routes between two stations" << endl;
        cout << "Enter your choice: ";
        cin >> a;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (a == 0)
            break;
        else {
            cout << "Enter the starting point to query:";
            getline(cin, start);
            cout << "Enter the destination to query:";
            getline(cin, end);
            if (find_station(start.c_str()) == -1) {
                cout << endl
                     << "Incorrect starting point entered!" << endl;
                return;
            }
            if (find_station(end.c_str()) == -1) {
                cout << endl
                     << "Incorrect destination entered!" << endl;
                return;
            }
            clear_visited();
            init(path, start.c_str());
            cout << "Routes from " << start << " to " << end << " are as follows:" << endl;
            query_path(start.c_str(), end.c_str());
            if (sum != 0) {
                cout << "There are a total of " << sum << " routes" << endl;
                sum = 0;
            } else
                cout << "No routes found that meet the requirements!" << endl
                     << endl;
            free(path);
            system("read -n 1 -s -p 'Press any key to continue...'");
            system("clear");
        }
    }
}

void route_map_generate() // Generate Bus Route Map
{
    create_map();
    load_map_data();
}

void menu() {
    cout << "----------Bus Management System----------" << endl;
    cout << "1. Query Bus Routes" << endl
         << "2. Query Station Information" << endl
         << "3. Query Bus Routes between Two Stations (At most 1 transfer)" << endl
         << "4. Modify Data" << endl
         << "0. Exit" << endl;
    cout << "Enter operation number:";
}
