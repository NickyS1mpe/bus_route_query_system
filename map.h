#pragma once
#ifndef MAP_H
#define MAP_H

void create_map();

int find_bus(const char *bus);

int GetBus(const char *bus);

int find_station(const char *station);

int get_station(const char *station);

void add_bus(int bus, int pStart, int pEnd);

void add_route(int pBus, int pStart, int pEnd, int distance);

void load_map_data();

int check_same(const int *buses, int name, int n);

void query_bus(const char *pBus);

int query_station(const char *station);

void clear_visited();

void query_path(const char *pStart, const char *pEnd);

#endif // !MAP_H
