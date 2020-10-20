#ifndef SEARCHES
#define SEARCHES

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <queue>
#include <map>

// MISC.
#define For(i, s, n) for (int i = s; i < n; i++)
#define len(a) (int) a.size()
#define ll long long

using namespace std;

// STANDARDS
#define MAXNODES 100

typedef struct routeData
{
	double price;
	double distance;
} RouteData;

typedef struct coord
{
	int x;
	int y;
} Coord;

typedef struct world
{
	map<string, Coord> city;
	map<string, vector<pair<string, RouteData>>> route;
} World;

void BFS(map<string, vector<pair<string, RouteData>>> edge, map<string, double> &dist, string s);
void AStar(map<string, Coord> city, map<string, vector<pair<string, RouteData>>> edge, map<string, double>& dist, string origin, string destiny);

#endif