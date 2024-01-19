#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "map.h"
#include "data.cpp"
#include "model.h"
using namespace std;

Path *path; // Global variable

void CreateMap() // Create bus route map
{
    int i;
    g_BusMap.bus_num = BUS_NUM;
    g_BusMap.buses = (Bus *)malloc(sizeof(Bus) * BUS_NUM);
    for (i = 0; i < BUS_NUM; i++)
    {
        g_BusMap.buses[i].name = BUS_NAME[i];
        g_BusMap.buses[i].start = -1;
        g_BusMap.buses[i].end = -1;
    }
    g_BusMap.station_num = STATION_NUM;
    g_BusMap.stations = (Station *)malloc(sizeof(Station) * STATION_NUM);
    for (i = 0; i < STATION_NUM; i++)
    {
        g_BusMap.stations[i].station = STATION[i];
        g_BusMap.stations[i].routes = NULL;
    }
}

int FindBus(char *bus) // Check if the bus exists, return its index if it does
{
    for (int i = 0; i < g_BusMap.bus_num; i++)
    {
        if (strcmp(g_BusMap.buses[i].name, bus) == 0)
            return i;
    }
    return -1;
}

int GetBus(char *bus) // If the bus does not exist, create it and return its index
{
    int nBus = FindBus(bus);
    if (nBus == -1)
    {
        g_BusMap.buses = (Bus *)realloc(g_BusMap.buses, sizeof(Bus) * (g_BusMap.bus_num + 1));
        Bus *pBus = g_BusMap.buses + g_BusMap.bus_num;
        pBus->name = bus;
        pBus->start = -1;
        pBus->end = -1;
        nBus = g_BusMap.bus_num;
        g_BusMap.bus_num++;
    }
    return nBus;
}

int FindStation(char *station) // Check if the station exists
{
    for (int i = 0; i < g_BusMap.station_num; i++)
    {
        if (strcmp(g_BusMap.stations[i].station, station) == 0)
            return i;
    }
    return -1;
}

int GetStation(char *station) // If the station does not exist, create it and return its index
{
    int nStation = FindStation(station);
    if (nStation == -1)
    {
        g_BusMap.stations = (Station *)realloc(g_BusMap.stations, sizeof(Station) * (g_BusMap.station_num + 1));
        Station *pStation = g_BusMap.stations + g_BusMap.station_num;
        pStation->station = station;
        pStation->routes = NULL;
        nStation = g_BusMap.station_num;
        g_BusMap.station_num++;
    }
    return nStation;
}

void AddBus(int bus, int pStart, int pEnd) // Add a bus
{
    int nBus = GetBus(BUS_NAME[bus]);
    int nStart = GetStation(STATION[pStart]);
    int nEnd = GetStation(STATION[pEnd]);
    Bus *pBus = g_BusMap.buses + nBus;
    pBus->start = nStart;
    pBus->end = nEnd;
}

void AddRoute(int pBus, int pStart, int pEnd, int distance) // Add a route segment
{
    Station *pStStation = &g_BusMap.stations[pStart];
    Route *pStRoute = pStStation->routes;
    while (pStRoute != NULL && pStRoute->next != NULL)
    {
        if (pStRoute->bus == pBus && pStRoute->station == pEnd)
            return;
        pStRoute = pStRoute->next;
    }
    Route *pNewRoute = (Route *)malloc(sizeof(Route));
    pNewRoute->bus = pBus;
    pNewRoute->station = pEnd;
    pNewRoute->distance = distance;
    pNewRoute->next = NULL;
    if (pStRoute == NULL)
        pStStation->routes = pNewRoute;
    else
        pStRoute->next = pNewRoute;
}

void LoadMapDate() // Load bus route information
{
    int i;
    for (i = 0; i < BUS_NUM; i++)
        AddBus(BUSES[i][0], BUSES[i][1], BUSES[i][2]);
    for (i = 0; i < ROUTE_NUM; i++)
        AddRoute(ROUTES[i][0], ROUTES[i][1], ROUTES[i][2], ROUTES[i][3]);
}

int CheckSame(int *buses, int name, int n) // Check if it is the same as the previous array
{
    int i;
    for (i = 0; i < n; i++)
        if (buses[i] == name)
            break;
    if (i == n)
        return 0;
    else
        return 1;
}

void QueryBus(char *pBus) // Query bus route
{
    int route[MAX], nBus = FindBus(pBus), nStart = g_BusMap.buses[nBus].start, nEnd = g_BusMap.buses[nBus].end;
    route[0] = nStart;
    Station *pStation = &g_BusMap.stations[nStart];
    Route *pRoute = pStation->routes;
    int nStation = nStart, num = 1;
    while (nStation != nEnd)
    {
        while (pRoute->bus != nBus)
        {
            pRoute = pRoute->next;
        }
        nStation = pRoute->station;
        route[num] = nStation;
        num++;
        pStation = &g_BusMap.stations[nStation];
        pRoute = pStation->routes;
    }
    cout << "Take bus " << pBus << " passing through " << num << " stations:";
    cout << g_BusMap.stations[route[0]].station;
    for (int i = 1; i < num; i++)
        cout << "---->" << g_BusMap.stations[route[i]].station;
    cout << endl;
}

int QueryStation(char *station) // Query stations
{
    int nSta = FindStation(station);
    int nBus, i;
    int bus[MAX];
    Station *pstation = &g_BusMap.stations[nSta];
    Route *pRoute = pstation->routes;
    int num = 0;
    while (pRoute != NULL)
    {
        nBus = pRoute->bus;
        pRoute = pRoute->next;
        bus[num] = nBus;
        num++;
    }
    for (i = 0; i < g_BusMap.station_num; i++)
    {
        Station *qstation = &g_BusMap.stations[i];
        Route *qRoute = qstation->routes;
        while (qRoute != NULL)
        {
            if (qRoute->station == nSta)
            {
                nBus = qRoute->bus;
                if (CheckSame(bus, nBus, num) == 0)
                {
                    *(bus + num) = nBus;
                    num++;
                }
            }
            qRoute = qRoute->next;
        }
    }
    cout << "Station " << station << " has " << num << " buses passing through:";
    for (i = 0; i < num; i++)
    {
        if (i == num - 1)
        {
            cout << g_BusMap.buses[bus[i]].name;
            break;
        }
        cout << g_BusMap.buses[bus[i]].name << "、";
    }
    cout << endl;
    return num;
}

void ClearVisited() // Initialize the visited array to false
{
    for (int i = 0; i < STATION_NUM; i++)
        visited[i] = false;
}

void Init(Path *&p, char *s) // Initialize the path segment
{
    p = (Path *)malloc(sizeof(Path));
    p->route[0].bus = -1;
    p->route[0].distance = 0;
    p->route[0].next = NULL;
    p->route[0].station = FindStation(s);
    p->trans = -1;
    p->alldist = 0;
    visited[FindStation(s)] = true;
    p->top = 0;
}

void Push(Path *&p, Route *s) // Push the path segment onto the stack
{
    if (p->route[p->top].bus != s->bus)
        p->trans++;
    p->top++;
    p->route[p->top].bus = s->bus;
    p->route[p->top].distance = s->distance;
    p->route[p->top].next = s->next;
    p->route[p->top].station = s->station;
    p->alldist = s->distance + p->alldist;
}

void Pop(Path *&p, Route *&s) // Pop the path segment from the stack
{
    s = (Route *)malloc(sizeof(Route));
    s->bus = p->route[p->top].bus;
    s->distance = p->route[p->top].distance;
    s->next = p->route[p->top].next;
    s->station = p->route[p->top].station;
    p->alldist = p->alldist - s->distance;
    p->top--;
    if (p->route[p->top].bus != s->bus)
        p->trans--;
}

void PrintPath(Path *p) // Output the route
{
    if (p->trans <= 1)
    {
        cout << g_BusMap.stations[p->route[0].station].station;
        for (int i = 1; i <= p->top; i++)
            cout << " (" << g_BusMap.buses[p->route[i].bus].name << " " << p->route[i].distance << "m)-->" << g_BusMap.stations[p->route[i].station].station;
        sum++;
        cout << endl;
        cout << "Total distance for this route: " << p->alldist << "m Transfers: " << p->trans << endl
             << endl;
    }
}

void QueryPath(char *pStart, char *pEnd)
{
    int nStart = GetStation(pStart);
    int nEnd = GetStation(pEnd);
    Station *pStation = &g_BusMap.stations[nStart];
    Route *pRoute = pStation->routes;
    if (nStart == nEnd)
        PrintPath(path);
    else
    {
        while (pRoute)
        {
            if (!visited[pRoute->station])
            {
                visited[pRoute->station] = true;
                Push(path, pRoute);
                QueryPath(g_BusMap.stations[pRoute->station].station, pEnd);
            }
            pRoute = pRoute->next;
        }
    }
    Pop(path, pRoute);
    visited[pRoute->station] = false;
}