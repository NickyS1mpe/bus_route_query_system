#pragma once
#ifndef MAP_H
#define MAP_H

void CreateMap();
int FindBus(char *bus);
int GetBus(char *bus);
int FindStation(char *station);
int GetStation(char *station);
void AddBus(int bus, int pStart, int pEnd);
void AddRoute(int pBus, int pStart, int pEnd, int distance);
void LoadMapDate();
int CheckSame(int *buses, int name, int n);
void QueryBus(char *pBus);
int QueryStation(char *station);
void ClearVisited();
void QueryPath(char *pStart, char *pEnd);

#endif // !MAP_H
