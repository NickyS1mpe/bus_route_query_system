#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "menu.h"
#include "map.cpp"
using namespace std;

void Function1() // Query Bus Routes
{
    int a;
    char bus[20];
    while (1)
    {
        cout << "======Bus Route Query System=====" << endl;
        cout << "1. Continue querying bus routes" << endl;
        cout << "0. Exit bus route query" << endl;
        cout << "Enter your choice: ";
        cin >> a;
        if (a == 0)
            break;
        else
        {
            cout << "Enter the bus name to query:";
            cin >> bus;
            if (FindBus(bus) == -1)
                cout << "Incorrect bus name entered!" << endl
                     << endl;
            else
                QueryBus(bus);
            system("read -n 1 -s -p 'Press any key to continue...'");
            system("clear");
        }
    }
}

void Function2() // Query Station Information
{
    char station[20];
    int a;
    while (1)
    {
        cout << "======Station Information Query System======" << endl;
        cout << "1. Continue querying station information" << endl;
        cout << "0. Exit station information query" << endl;
        cout << "Enter your choice: ";
        cin >> a;
        if (a == 0)
            break;
        else
        {
            cout << "Enter the station name to query:";
            cin >> station;
            if (FindStation(station) == -1)
                cout << "Incorrect station name entered!" << endl
                     << endl;
            else
                QueryStation(station);
            system("read -n 1 -s -p 'Press any key to continue...'");
            system("clear");
        }
    }
}

void Function3() // Query Bus Routes between Two Stations (At most 1 transfer)
{
    int a;
    char start[20], end[20];
    while (1)
    {
        cout << "======Query Bus Routes between Two Stations (At most 1 transfer)======" << endl;
        cout << "1. Continue querying bus routes between two stations" << endl;
        cout << "0. Exit query for bus routes between two stations" << endl;
        cout << "Enter your choice: ";
        cin >> a;
        if (a == 0)
            break;
        else
        {
            cout << "Enter the starting point to query:";
            cin >> start;
            cout << "Enter the destination to query:";
            cin >> end;
            if (FindStation(start) == -1)
            {
                cout << endl
                     << "Incorrect starting point entered!" << endl;
                return;
            }
            if (FindStation(end) == -1)
            {
                cout << endl
                     << "Incorrect destination entered!" << endl;
                return;
            }
            ClearVisited();
            Init(path, start);
            cout << "Routes from " << start << " to " << end << " are as follows:" << endl;
            QueryPath(start, end);
            if (sum != 0)
            {
                cout << "There are a total of " << sum << " routes" << endl;
                sum = 0;
            }
            else
                cout << "No routes found that meet the requirements!" << endl
                     << endl;
            free(path);
            system("read -n 1 -s -p 'Press any key to continue...'");
            system("clear");
        }
    }
}

void CreateAndLoad() // Generate Bus Route Map
{
    CreateMap();
    LoadMapDate();
}

void Menu()
{
    cout << "----------Bus Management System----------" << endl;
    cout << "1. Query Bus Routes" << endl
         << "2. Query Station Information" << endl
         << "3. Query Bus Routes between Two Stations (At most 1 transfer)" << endl
         << "4. Modify Data" << endl
         << "0. Exit" << endl;
    cout << "Enter operation number:";
}
