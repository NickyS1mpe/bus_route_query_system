#pragma once
#ifndef MODEL_H
#define MODEL_H

typedef struct Bus
{
    char *name; // Bus name
    int start;  // Starting point
    int end;    // Destination
} Bus;

typedef struct Route
{
    int station;        // Index of the targeted station
    int bus;            // Bus index
    int distance;       // Distance between two stations on the road
    struct Route *next; // Pointer to the next route
} Route;

typedef struct Station
{
    char *station;        // Station name
    struct Route *routes; // Linked list of routes
} Station;

typedef struct BusMap
{
    Bus *buses;        // Array of bus routes
    Station *stations; // Array of stations
    int station_num;   // Number of stations
    int bus_num;       // Number of bus routes
} BusMap;

BusMap g_BusMap; // Global variable

typedef struct Path
{
    Route route[MAX];
    int trans;   // Number of transfers
    int all_dist; // Total distance of the route
    int top;     // Starting point
} Path;

#endif // !MODEL_H