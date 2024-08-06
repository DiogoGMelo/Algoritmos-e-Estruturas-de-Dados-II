//diogo gianezi de melo n12563522
//Raphael Monteiro Consoni Bonaccorsi n12563366


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

struct Graph {
    int V;
    vector<vector<Edge>> adj;
};

void dijkstra(Graph& G, int s) {
    vector<int> distance(G.V, INF);
    vector<vector<int>> parent(G.V, vector<int>(0));
    vector<bool> visited(G.V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    distance[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : G.adj[u]) {
            int v = e.to;
            int w = e.weight;
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                pq.push({distance[v], v});
                // parent[v].clear(); <-- Remover esta linha
                parent[v].push_back(u);
            } else if (distance[u] + w == distance[v]) {
                parent[v].push_back(u);
            }
        }
    }

    cout << "Node " << s << ":" << endl;
    for (int i = 0; i < G.V; ++i) {
        if (i == s) {
            cout << "Distance from " << s << " to " << i << " = 0" << endl;
            continue;
        }
        cout << "Distance from " << s << " to " << i << " = ";
        if (distance[i] == INF) {
            cout << "infinity" << endl;
            continue;
        }
        cout << distance[i] << endl;
        cout << "Path: " << s;
        if (!parent[i].empty()) {
            for (int j : parent[i]) {
                if (j != s) cout << " -> " << j;
            }
        }
        cout << " -> " << i << endl;
    }
    if (s != G.V - 1) {
        cout << endl;
    }
}

int main() {
    int V;
    cin >> V;

    Graph G;
    G.V = V;
    G.adj.resize(V);

    int u, v, w;
    while (cin >> u >> v >> w) {
        if (u == -1 || v == -1 || w == -1) break;
        G.adj[u].push_back(Edge(v, w));
    }

    for (int i = 0; i < V; ++i) {
        dijkstra(G, i);
    }

    return 0;
}
