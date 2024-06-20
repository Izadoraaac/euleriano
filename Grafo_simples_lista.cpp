#include <bits/stdc++.h>
using namespace std;

void leituraGrafo(vector<vector<int>> &, int);
void escritaGrafo(vector<vector<int>> &);
bool isEulerianCycle(vector<vector<int>> &);
list<int> findEulerianCycle(vector<vector<int>> &);

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> Grafo;
    Grafo.assign(n, vector<int>());
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
        G[a].push_back(b);
        G[b].push_back(a);
    }
}

void escritaGrafo(vector<vector<int>> &G) {
    int n = G.size();
    cout << "Lista de Adjacência:" << endl;
    for (int u = 0; u < n; u++) {
        cout << u << ": ";
        for (auto v : G[u]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

bool isEulerianCycle(vector<vector<int>> &G) {
    int n = G.size();
    vector<int> degree(n, 0);

    for (int u = 0; u < n; u++) {
        if (G[u].size() % 2 != 0)
            return false;
        degree[u] = G[u].size();
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
            for (int u : G[v]) {
                if (!visited[u]) {
                    s.push(u);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i])
            return false;
    }

    return true;
}

list<int> findEulerianCycle(vector<vector<int>> &G) {
    unordered_map<int, list<int>> adj;
    for (int u = 0; u < G.size(); u++) {
        for (int v : G[u]) {
            adj[u].push_back(v);
        }
    }

    stack<int> currPath;
    list<int> circuit;

    currPath.push(0);
    int currV = 0;

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
