#include "searches.hpp"

#define NOTVIS 1000000000

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

    // PRINT DISTANCES
    for (auto it = dist.begin(); it != dist.end(); it++) 
    {
        cout << "Distance to " << it->first << ": " << it->second << endl;
    }
}

void AStar(map<string, Coord> city, map<string, vector<pair<string, RouteData>>> edge, map<string, double> &dist, string origin, string destiny)
{
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    map<string, double> cost;

    // INITIALIZE DISTANCES
    for (auto it = edge.begin(); it != edge.end(); it++) cost[it->first] = NOTVIS;

    pred[origin] = "";
    cost[origin] = 0;

    pq.push({0, origin});

    while (!pq.empty())
    {
        string u = pq.top().second;
        pq.pop();

        if (u == destiny) 
        {
            while (!pq.empty()) cost[pq.top().second] = NOTVIS, pq.pop();
            break;
        }
        
        // GET ALL CONNECTIONS WITH CITY U
        For(i, 0, len(edge[u]))
        {
            // NEXT CITY
            string v = edge[u][i].first;               // CITY NAME
            double w = edge[u][i].second.price;        // TRAVELL COST

            // EUCLIDIAN DISTANCE
            double heuristic = EuclidianDistance(city, v, destiny) / 2;
            
            // BETTER SOLUTION
            if (cost[v] > cost[u] + w)
            {
                cost[v] = cost[u] + w;
                dist[v] = cost[v] + heuristic;

                pq.push({dist[v], v});            // ADD TO QUEUE
                pred[v] = u;
            }
        }
    }

END:
    cout << "Path: ";
    PrintPath(destiny);
    cout << endl;

    cout << fixed << setprecision(2) << "Cost: " << cost[destiny] << endl << endl;

    cout << "Not visited: ";

    for (auto it = cost.begin(); it != cost.end(); it++) 
    {
        if (it->second == NOTVIS)
            cout << it->first << ' ';
    }

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