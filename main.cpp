#include "lib/searches.hpp"

// GLOBAL VARIABLES
World world;
map<string, double> dist;

// NUMBER OF EDGES AND NODES
int n, m;
string origin, destiny;

void ReadInput()
{
    cin >> n;

    For (i, 0, n)
    {
        string city;
        double x, y;

        cin >> city >> x >> y;

        // ROUTE BETWEEN A AND B
        world.city[city].x = x;
        world.city[city].y = y;
    }

    cin >> m >> origin >> destiny;
    
    For (i, 0, m)
    {
        // READ NODE A AND B
        string a, b;
        double price;
        cin >> a >> b >> price;

        // DATA
        RouteData rd;
        rd.price = price;

        // EUCLIDIAN DISTANCE
        rd.distance = sqrtf(pow(world.city[a].x - world.city[b].x, 2) + pow(world.city[a].y - world.city[b].y, 2));

        // ROUTE BETWEEN A AND B
        world.route[a].push_back({b, rd});
        world.route[b].push_back({a, rd});
    }
}

int main()
{
    // FAST INPUT OUTPUT (cin/cout)
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ReadInput();
    
    // BFS(world.route, dist, origin);
    AStar(world.city, world.route, dist, origin, destiny);
    return 0;
}