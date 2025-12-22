#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
PROBLEM:
To perform a structural scan of a building floor-by-floor to detect weak elements.
Each structural element is a node in a graph, and load paths between them are edges.

WHY BFS:
Breadth-First Search is suitable because it explores nodes level by level,
simulating a floor-by-floor inspection and detecting weak points in a logical order.
*/

/* ----------------------------
   Input Graph Function
   ---------------------------- */
vector<vector<int>> inputGraph(int n) {
    vector<vector<int>> graph(n);
    cout << "Enter adjacency list for each node (0-based indices).\n";
    for(int i=0;i<n;i++){
        int k;
        cout << "Number of connections for node " << i << ": ";
        cin >> k;
        graph[i].resize(k);
        cout << "Enter connected nodes: ";
        for(int j=0;j<k;j++)
            cin >> graph[i][j];
    }
    return graph;
}


vector<int> inputWeakNodes(int n) {
    vector<int> weak(n);
    cout << "Enter 1 if node is weak, 0 if strong:\n";
    for(int i=0;i<n;i++){
        cout << "Node " << i << ": ";
        cin >> weak[i];
    }
    return weak;
}

/* ----------------------------
   Display Graph
   ---------------------------- */
void displayGraph(const vector<vector<int>>& graph) {
    cout << "\nGraph Structure (Adjacency List):\n";
    for(size_t i=0;i<graph.size();i++){
        cout << "Node " << i << ": ";
        for(int j : graph[i])
            cout << j << " ";
        cout << "\n";
    }
}


void bfsCheck(int start, vector<vector<int>>& graph, vector<int>& weak) {
    queue<int> q;
    vector<int> visited(graph.size(), 0);
    q.push(start);
    visited[start] = 1;

    cout << "\nBFS Structural Scan (Floor-by-Floor):\n";

    int level = 0; // floor level
    while(!q.empty()){
        int sz = q.size();
        cout << "Scanning floor level " << level << ":\n";

        for(int i=0;i<sz;i++){
            int node = q.front(); q.pop();

            cout << "Checking element " << node;
            if(weak[node] == 1)
                cout << "  --> WEAK POINT FOUND!";
            cout << "\n";

            for(int next : graph[node]){
                if(!visited[next]){
                    visited[next] = 1;
                    q.push(next);
                }
            }
        }
        level++;
        cout << "\n";
    }
}


void runStructuralScan(){
    int n;
    cout << "Enter number of structural nodes: ";
    cin >> n;

    vector<vector<int>> graph = inputGraph(n);
    displayGraph(graph);

    vector<int> weak = inputWeakNodes(n);

    bfsCheck(0, graph, weak);
}


int main(){
    cout << "=== Building Structural BFS Scan ===\n\n";
    runStructuralScan();
    return 0;
}
