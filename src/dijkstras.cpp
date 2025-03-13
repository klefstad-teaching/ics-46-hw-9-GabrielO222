#include "dijkstras.h"
#include <algorithm>
#include <queue>

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous) {
    int numVertices = G.numVertices;
    vector<int> distances (numVertices, INF);
    vector<bool> explored (numVertices, false);
    previous.assign(numVertices, -1);

    priority_queue<int, vector<int>, greater<int>> pq;
    distances[source] = 0;
    pq.emplace(source);

    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();

        if (explored[v]) continue;

        explored[v] = true;

        for (const Edge &e : G[v]) {
            if (!explored[e.dst] && distances[v] + e.weight < distances[e.dst]) {
                distances[e.dst] = distances[v] + e.weight;
                previous[e.dst] = v;
                pq.emplace(e.dst);
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int> &, const vector<int> &previous, int destination) {
    vector<int> path;
    int curr = destination;
    while (curr != -1) {
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int> &v, int total) {
    for (int vertex : v) {
        cout << vertex << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}