#include<iostream>
#include<vector>
#include<stack>
#include<omp.h>

using namespace std;

class Graph {
private:
    int numvertices;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : numvertices(vertices), adj(vertices) {}

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    void viewgraph() {
        cout << "Graph:" << endl;
        for (int i = 0; i < numvertices; i++) {
            cout << "Vertex " << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void parallel_dfs(int startvertex) {
        double start_time = omp_get_wtime();
        vector<bool> visited(numvertices, false);
        stack<int> s;
        vector<int> dfsorder;

        visited[startvertex] = true;
        s.push(startvertex);

        while (!s.empty()) {
            int currentvertex = s.top();
            s.pop();
            dfsorder.push_back(currentvertex);

            #pragma omp parallel for
            for (int i = 0; i < adj[currentvertex].size(); i++) {
                int neighbor = adj[currentvertex][i];
                printf("Thread %d is processing neighbor %d of vertex %d\n", omp_get_thread_num(), neighbor, currentvertex);

                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        s.push(neighbor);
                    }
                }
            }
        }

        double end_time = omp_get_wtime();

        cout << "DFS order (Parallel): ";
        for (int v : dfsorder) {
            cout << v << " ";
        }
        cout << "\nParallel DFS completed in " << (end_time - start_time) * 1000 << " milliseconds\n";
    }

    void sequential_dfs(int startvertex) {
        double start_time = omp_get_wtime();
        vector<bool> visited(numvertices, false);
        stack<int> s;
        vector<int> dfsorder;

        visited[startvertex] = true;
        s.push(startvertex);

        while (!s.empty()) {
            int currentvertex = s.top();
            s.pop();
            dfsorder.push_back(currentvertex);

            for (int neighbor : adj[currentvertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }

        double end_time = omp_get_wtime();
        cout << "DFS order (Sequential): ";
        for (int v : dfsorder) {
            cout << v << " ";
        }
        cout << "\nSequential DFS completed in " << (end_time - start_time) * 1000 << " milliseconds\n";
    }
};

int main() {
    int numvertices;
    cout << "Enter the number of vertices: ";
    cin >> numvertices;

    Graph graph(numvertices);
    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (src dest):" << endl;
    for (int i = 0; i < edges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    graph.viewgraph();

    int startvertex;
    cout << "Enter the starting vertex: ";
    cin >> startvertex;

    cout << "\nParallel DFS:\n";
    graph.parallel_dfs(startvertex);

    cout << "\n\nSequential DFS:\n";
    graph.sequential_dfs(startvertex);

    return 0;
}
