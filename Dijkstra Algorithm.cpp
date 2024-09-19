#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int destination;
    int weight;
};

struct Node {
    int distance;
    vector<Edge> edges;
};

vector<Node> graph;

void dijkstra(int start, int end) {
    vector<int> distances(graph.size(), numeric_limits<int>::max());
    vector<int> previous(graph.size(), -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;

    distances[start] = 0;
    queue.push({0, start});

    while (!queue.empty()) {
        int current = queue.top().second;
        queue.pop();

        for (const Edge& edge : graph[current].edges) {
            int newDistance = distances[current] + edge.weight;
            if (newDistance < distances[edge.destination]) {
                distances[edge.destination] = newDistance;
                previous[edge.destination] = current;
                queue.push({newDistance, edge.destination});
            }
        }
    }

    int current = end;
    vector<int> path;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end());

    cout << "Shortest path from " << start << " to " << end << ": ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    cout << "Cost of shortest path: " << distances[end] << endl;
}

int main() {
    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    graph.resize(numNodes);

    for (int i = 0; i < numNodes; i++) {
        int numEdges;
        cout << "Enter the number of edges for node " << i << ": ";
        cin >> numEdges;

        for (int j = 0; j < numEdges; j++) {
            int destination, weight;
            cout << "Enter the destination and weight of edge " << j << " for node " << i << ": ";
            cin >> destination >> weight;

            graph[i].edges.push_back({destination, weight});
        }
    }

    int start, end;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the ending node: ";
    cin >> end;

    dijkstra(start, end);

    return 0;
}