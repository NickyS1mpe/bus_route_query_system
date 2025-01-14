#pragma once
#ifndef DATA_H
#define DATA_H

#define MAX 100

int STATION_NUM;    // Total number of stations
char *STATION[MAX]; // Store station names

int ROUTE_NUM;      // Total number of routes
int ROUTES[MAX][4]; // Store route information

int BUS_NUM;         // Total number of bus routes
char *BUS_NAME[MAX]; // Store bus route names
int BUSES[MAX][3];   // Store bus route information

bool visited[MAX]; // Record whether a station has been visited
int sum = 0;       // Record the number of routes

void read_bus_routes();
void read_bus_stations();
void read_buses();
void read_bus_name();
void read_file();
void modify_station_distance();
void modify_station_name();
void modify_bus_route();
void modify_bus_name();
void write_routes();
void write_stations();
void write_buses();
void write_bus_name();
void write_menu();

#endif // !DATA_H
