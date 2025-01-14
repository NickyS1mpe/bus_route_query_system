#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "data.h"

using namespace std;

void read_bus_routes() // Read segment information
{
    int zi, a[4] = {0};
    ifstream in("/Users/nicklee/Projects/bus_stop/routes.txt", ios::in);
    in >> zi;
    ROUTE_NUM = zi;
    for (int i = 0; i < ROUTE_NUM; i++) {
        in >> a[0] >> a[1] >> a[2] >> a[3];
        ROUTES[i][0] = a[0];
        ROUTES[i][1] = a[1];
        ROUTES[i][2] = a[2];
        ROUTES[i][3] = a[3];
    }
    in.close();
}

void read_bus_stations() // Read station names
{
    ifstream in("/Users/nicklee/Projects/bus_stop/stations.txt", ios::in);
    char str[30];
    int i = 0;
    while (in) {
        in.getline(str, 30);
        int len = strlen(str);
        if (len > 0 && str[len - 1] == '\r') {
            str[len - 1] = '\0';
        }
        char *pstr = (char *) malloc((len + 1) * sizeof(char));
        strcpy(pstr, str);
        STATION[i] = pstr;
        i++;
    }
    STATION_NUM = i;
    in.close();
}

void read_buses() // Read bus information
{
    ifstream in("/Users/nicklee/Projects/bus_stop/buses.txt", ios::in);
    int a, b[3];
    in >> a;
    BUS_NUM = a;
    for (int i = 0; i < BUS_NUM; i++) {
        in >> b[0] >> b[1] >> b[2];
        BUSES[i][0] = b[0];
        BUSES[i][1] = b[1];
        BUSES[i][2] = b[2];
    }
    in.close();
}

void read_bus_name() // Read bus names
{
    ifstream in("/Users/nicklee/Projects/bus_stop/bus_name.txt", ios::in);
    char str[30];
    int i = 0;
    while (in) {
        in.getline(str, 30);
        int len = strlen(str);
        if (len > 0 && str[len - 1] == '\r') {
            str[len - 1] = '\0';
        }
        char *pstr = (char *) malloc((len + 1) * sizeof(char));
        strcpy(pstr, str);
        BUS_NAME[i] = pstr;
        i++;
    }
    in.close();
}

void read_file() // Read file content
{
    read_bus_routes();
    read_bus_stations();
    read_buses();
    read_bus_name();
}

void modify_station_distance() // Modify station distance
{
    int d, k[20], flag = 0, i, x = 0;
    char b[20], c[20];
    cout << "Enter the starting point to modify: ";
    cin >> b;
    cout << "Enter the end point to modify: ";
    cin >> c;
    for (i = 0; i < ROUTE_NUM; i++) {
        if ((strcmp(b, STATION[ROUTES[i][1]]) == 0 && strcmp(c, STATION[ROUTES[i][2]]) == 0) ||
            (strcmp(c, STATION[ROUTES[i][1]]) == 0 && strcmp(b, STATION[ROUTES[i][2]]) == 0)) {
            flag = 1;
            k[x] = i;
            x++;
        }
    }
    if (flag == 1) {
        cout << "Original data: " << ROUTES[k[x - 1]][3] << endl
             << "New data: ";
        cin >> d;
        for (int j = 0; j < x; j++) {
            ROUTES[k[j]][3] = d;
        }
        write_routes();
        cout << "Modification successful!" << endl;
    }
    if (flag == 0)
        cout << "Modification failed!";
}

void write_routes() // Rewrite station data to the file
{
    int i = 0;
    ofstream fout("routes.txt");
    fout << ROUTE_NUM << endl;
    while (ROUTE_NUM--) {
        fout << ROUTES[i][0] << " " << ROUTES[i][1] << " " << ROUTES[i][2] << " " << ROUTES[i][3] << endl;
        i++;
    }
    fout.close();
}

void modify_station_name() // Modify station name
{
    int a, k = 0;
    char s[100];
    while (STATION[k] != NULL) {
        cout << k << " " << STATION[k] << endl;
        k++;
    }
    cout << k << " Cancel modification" << endl;
    cout << "Choose the option to modify: ";
    cin >> a;
    if (k != a) {
        if (STATION[a] == NULL)
            cout << "Modification failed!";
        else {
            cout << "Original data: " << STATION[a] << endl;
            cout << "Modify to: ";
            cin >> s;
            STATION[a] = s;
            write_stations();
            cout << "Modification successful!" << endl;
        }
    }
}

void write_stations() // Rewrite data to the file
{
    int i = 0;
    ofstream fout("stations.txt");
    while (STATION[i] != NULL) {
        fout << STATION[i] << endl;
        i++;
    }
    fout.close();
}

void modify_bus_route() // Modify bus route
{
    int a, x, l, flag = 0, n = 0, m = 0, k = 0, v = 0, s, bus[100], dis[100], nbus[100][4];
    while (BUS_NAME[k] != NULL) {
        cout << k << " " << BUS_NAME[k] << endl;
        k++;
    }
    cout << k << " Cancel modification" << endl;
    cout << "Choose the bus to modify: ";
    cin >> a;
    if (k != a) {
        cout << "Original bus route: " << BUSES[a][1] << " " << STATION[BUSES[a][1]];
        for (int i = 0; i < ROUTE_NUM; i++) {
            if (ROUTES[i][0] == a) {
                cout << "-->" << ROUTES[i][2] << " " << STATION[ROUTES[i][2]];
                n++;
            }
        }
        cout << endl
             << "Please enter the index of the bus route station (enter -1 to stop input):" << endl;
        while (1) {
            cout << "Station index " << v + 1 << ":";
            cin >> s;
            if (s == -1)
                break;
            else {
                bus[v] = s;
                if (v > 0) {
                    for (int i = 0; i < ROUTE_NUM; i++) {
                        if (bus[v - 1] == ROUTES[i][1] && bus[v] == ROUTES[i][2]) {
                            dis[v - 1] = ROUTES[i][3];
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0) {
                        cout << "Missing station distance data! Please enter data: ";
                        cin >> x;
                        dis[v - 1] = x;
                    }
                }
                flag = 0;
                v++;
            }
        }
        BUSES[a][1] = bus[0];
        BUSES[a][2] = bus[v - 1];
        write_buses();
        ROUTE_NUM = ROUTE_NUM - n - v + 1;
        for (int i = 0; i < ROUTE_NUM; i++) {
            if (ROUTES[i][0] == a) {
                l = i;
                break;
            }
        }
        for (int i = l; i < ROUTE_NUM; i++) // Re-sort the bus route array
        {
            if (i < l + v - 1) {
                nbus[i][0] = a;
                nbus[i][1] = bus[i];
                nbus[i][2] = bus[i + 1];
                nbus[i][3] = dis[i];
            } else {
                nbus[i][0] = ROUTES[i + n - 1][0];
                nbus[i][1] = ROUTES[i + n - 1][1];
                nbus[i][2] = ROUTES[i + n - 1][2];
                nbus[i][3] = ROUTES[i + n - 1][3];
            }
        }
        for (int i = 0; i < ROUTE_NUM - l; i++) {
            ROUTES[l + i][0] = nbus[i][0];
            ROUTES[l + i][1] = nbus[i][1];
            ROUTES[l + i][2] = nbus[i][2];
            ROUTES[l + i][3] = nbus[i][3];
        }
        write_routes();
        cout << "Modification successful!" << endl;
    }
}

void write_buses() // Rewrite data to the file
{
    int i = 0;
    ofstream fout("buses.txt");
    fout << BUS_NUM << endl;
    while (BUS_NUM--) {
        fout << BUSES[i][0] << " " << BUSES[i][1] << " " << BUSES[i][2] << endl;
        i++;
    }
    fout.close();
}

void modify_bus_name() // Modify bus name
{
    int a, k = 0;
    char s[100];
    while (BUS_NAME[k] != NULL) {
        cout << k << " " << BUS_NAME[k] << endl;
        k++;
    }
    cout << k << " Cancel modification" << endl;
    cout << "Choose the option to modify: ";
    cin >> a;
    if (k != a) {
        if (BUS_NAME[a] == NULL)
            cout << "Modification failed!";
        else {
            cout << "Original data: " << BUS_NAME[a] << endl;
            cout << "Modify to: ";
            cin >> s;
            BUS_NAME[a] = s;
            write_bus_name();
            cout << "Modification successful!" << endl;
        }
    }
}

void write_bus_name() // Rewrite data to the file
{
    int i = 0;
    ofstream fout("bus_name.txt");
    while (BUS_NAME[i] != NULL) {
        fout << BUS_NAME[i] << endl;
        i++;
    }
    fout.close();
}

void write_menu() // Information modification system
{
    int a;
    while (true) {
        cout << "======Information Modification System======" << endl;
        cout << "Choose the object to modify:" << endl
             << "1. Station distance" << endl
             << "2. Station name" << endl
             << "3. Bus route" << endl
             << "4. Bus name" << endl
             << "0. Exit modification" << endl;
        cout << "Enter operation number:";
        cin >> a;
        if (a == 0)
            break;
        switch (a) {
            case 1:
                modify_station_distance();
                break;
            case 2:
                modify_station_name();
                break;
            case 3:
                modify_bus_route();
                break;
            case 4:
                modify_bus_name();
                break;
            default:
                cout << "Option do not exist" << endl;
        }
        read_file(); // Reload modified data
        system("PAUSE");
        system("cls");
    }
    cout << "Exit successful!" << endl;
}