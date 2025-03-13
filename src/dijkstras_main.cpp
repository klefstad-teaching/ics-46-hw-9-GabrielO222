#include "dijkstras.h"

int main() {
    Graph g;
    vector<string> filenames = {"small.txt", "medium.txt", "large.txt", "largest.txt"};
    for (auto filename : filenames) {
        cout << "Filename: " << filename << "\n" << endl;
        file_to_graph(filename, g);
        vector<int> previous;
        vector<int> paths = dijkstra_shortest_path(g, 0, previous);
        for (int i = 0; i < g.numVertices; ++i) {
           vector<int> shortest = extract_shortest_path(paths, previous, i);
           print_path(shortest, paths[i]);
        }
        cout << "\n\n";
    }   
}