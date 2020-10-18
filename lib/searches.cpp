#include "searches.hpp"

map<string, string> pred;

void PrintPath(string end);
double EuclidianDistance(map<string, Coord> city, string origin, string destiny);

// BREADTH FIRST SEARCH
// @ param edge: Vetex connections
// @ param dist: Function output
// @ param s: Starter Node

void BFS(map<string, vector<pair<string, RouteData>>> edge, map<string, double> &dist, string s)
{
    // INITIALIZE DISTANCES
    for (auto it = edge.begin(); it != edge.end(); it++) dist[it->first] = -1;
    dist[s] = 0;

    queue<string> q;
    q.push(s);

    while (!q.empty())
    {
        string u = q.front();
        q.pop();

        // GET ALL CONNECTIONS WITH CITY U
        For (i, 0, len(edge[u]))
        {
            string v = edge[u][i].first;

            // NOT VISITED YET
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;  // UPDATE DISTANCE
                q.push(v);
            }
        }
    }
}

void AStar(map<string, Coord> city, map<string, vector<pair<string, RouteData>>> edge, map<string, double> &dist, string origin, string destiny)
{
    // INITIALIZE DISTANCES
    for (auto it = edge.begin(); it != edge.end(); it++) dist[it->first] = 1000000000;
    dist[origin] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, origin});

    pred[origin] = "";

    while (!pq.empty())
    {
        string u = pq.top().second;
        pq.pop();

        For (i, 0, len(edge[u]))
        {
            // NEXT CITY
            string v = edge[u][i].first;        // CITY NAME
            double w = edge[u][i].second.price; // TRAVELL COST

            // EUCLIDIAN DISTANCE
            double heuristic = EuclidianDistance(city, v, destiny);

            // BETTER ROUTE
            if (dist[v] > dist[u] + w + heuristic)
            {
                dist[v] = dist[u] + w + heuristic;  // UPDATE DISTANCE
                pq.push({dist[v], v});              // ADD TO QUEUE

                pred[v] = u;
            }

            if (v == destiny) goto END;
        }
    }

END:
    cout << "Path: ";
    PrintPath(destiny);
    cout << endl;

    return;
}

void PrintPath(string end)
{
    if (!pred.count(end)) return;

    PrintPath(pred[end]);
    cout << end << ' ';
}

double EuclidianDistance(map<string, Coord> city, string origin, string destiny)
{
    return sqrt(pow(city[origin].x - city[destiny].x, 2) + pow(city[origin].y - city[destiny].y, 2));
}