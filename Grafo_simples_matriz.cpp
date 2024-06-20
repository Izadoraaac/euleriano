#include <bits/stdc++.h>
using namespace std;

void leituraGrafo(vector<vector<int>> &, int);
bool isEulerianCycle(vector<vector<int>> &);
list<int> findEulerianCycle(vector<vector<int>> &);

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> Grafo(n, vector<int>(n, 0));
    leituraGrafo(Grafo, m);

    if (isEulerianCycle(Grafo)) {
        list<int> eulerianCycle = findEulerianCycle(Grafo);
        cout << "Ciclo Euleriano encontrado: ";
        for (int vertex : eulerianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "Não existe um ciclo Euleriano no grafo." << endl;
    }

    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;
    return 0;
}

void leituraGrafo(vector<vector<int>> &G, int m) {
    int a, b;
    while (m--) {
        cin >> a >> b;
        G[a][b]++;
        G[b][a]++;
    }
}

bool isEulerianCycle(vector<vector<int>> &G) {
    int n = G.size();
    vector<int> degree(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (G[u][v] > 0) {
                degree[u] += G[u][v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            return false;
        }
    }
    
    vector<bool> visited(n, false);
    stack<int> s;
    int start = 0;

    for (int i = 0; i < n; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }

    s.push(start);
    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (!visited[v]) {
            visited[v] = true;
            for (int u = 0; u < n; u++) {
                if (G[v][u] > 0 && !visited[u]) {
                    s.push(u);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i]) {
            return false;
        }
    }

    return true;
}

list<int> findEulerianCycle(vector<vector<int>> &G) {
    int n = G.size();
    unordered_map<int, list<int>> adj;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            for (int k = 0; k < G[u][v]; k++) {
                adj[u].push_back(v);
            }
        }
    }

    stack<int> currPath;
    list<int> circuit;

    int start = 0;
    for (int i = 0; i < n; i++) {
        if (!adj[i].empty()) {
            start = i;
            break;
        }
    }

    currPath.push(start);
    int currV = start;

    while (!currPath.empty()) {
        if (!adj[currV].empty()) {
            currPath.push(currV);
            int nextV = adj[currV].front();
            adj[currV].pop_front();
            adj[nextV].remove(currV);
            currV = nextV;
        } else {
            circuit.push_front(currV);
            currV = currPath.top();
            currPath.pop();
        }
    }

    return circuit;
}
