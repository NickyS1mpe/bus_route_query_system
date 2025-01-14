#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "menu.cpp"
using namespace std;

int main()
{
    read_file();
    route_map_generate();
    int s = 1;
    char bus[20];
    while (true)
    {
        menu();
        cin >> s;
        if (s == 0)
            break;
        switch (s)
        {
        case 1:
            system("clear");
                query_bus_routes();
            break;
        case 2:
            system("clear");
                query_station_info();
            break;
        case 3:
            system("clear");
                query_two_stations();
            break;
        case 4:
            system("clear");
                write_menu();
                route_map_generate();
            break;
        default:
            cout << "Option does not exist" << endl;
        }
        system("read -n 1 -s -p 'Press any key to continue...'");
        system("clear");
    }
    cout << "Exit successful!" << endl;
    return 0;
}
