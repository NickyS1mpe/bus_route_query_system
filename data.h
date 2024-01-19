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

void Read1();
void Read2();
void Read3();
void Read4();
void ReadFile();
void Write1();
void Write2();
void Write3();
void Write4();
void Writefile1();
void Writefile2();
void Writefile3();
void Writefile4();
void WriteMenu();

#endif // !DATA_H
