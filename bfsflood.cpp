#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
PROBLEM STATEMENT:
Simulate the spread of a flood in a grid starting from a source cell.
We want to know the order in which cells are flooded.

WHY BFS:
Breadth-First Search (BFS) is ideal because it explores cells level by
level, ensuring that cells closer to the source are flooded first.
This naturally models the flood spreading step by step.
*/

const int ROWS = 5;
const int COLS = 5;

// Initialize flood map and visited map
void initializeFlood(int flood[ROWS][COLS], int visited[ROWS][COLS], int srcR, int srcC) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++) {
            flood[i][j] = 0;
            visited[i][j] = 0;
        }
    flood[srcR][srcC] = 1;
    visited[srcR][srcC] = 1;
}

// Display the flood map
void displayFloodMap(int flood[ROWS][COLS]) {
    cout << "\nFlood map:\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            cout << flood[i][j] << " ";
        cout << "\n";
    }
}

// BFS flood spread simulation (4-directional)
void floodBFS(int flood[ROWS][COLS], int visited[ROWS][COLS], int srcR, int srcC) {
    queue<pair<int,int>> q;
    q.push({srcR, srcC});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int step = 0;
    cout << "\nFlood spread simulation (BFS):\n";

    while (!q.empty()) {
        int size = q.size();  // cells at current step
        step++;
        cout << "\nStep " << step << ":\n";

        for (int s = 0; s < size; s++) {
            pair<int,int> cell = q.front(); q.pop();
            int r = cell.first, c = cell.second;

            cout << "Flood reached cell (" << r << "," << c << ")\n";

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && !visited[nr][nc]) {
                    visited[nr][nc] = 1;
                    flood[nr][nc] = 1;
                    q.push({nr,nc});
                }
            }
        }
    }
}

// Optional: 8-directional flood
void floodBFS8Dir(int flood[ROWS][COLS], int visited[ROWS][COLS], int srcR, int srcC) {
    queue<pair<int,int>> q;
    q.push({srcR, srcC});

    int dr[] = {-1,1,0,0,-1,-1,1,1};
    int dc[] = {0,0,-1,1,-1,1,-1,1};

    int step = 0;
    cout << "\nFlood spread (8 directions):\n";

    while (!q.empty()) {
        int size = q.size();
        step++;
        cout << "\nStep " << step << ":\n";

        for (int s = 0; s < size; s++) {
            pair<int,int> cell = q.front(); q.pop();
            int r = cell.first, c = cell.second;
            cout << "Flood reached cell (" << r << "," << c << ")\n";

            for (int i = 0; i < 8; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && !visited[nr][nc]) {
                    visited[nr][nc] = 1;
                    flood[nr][nc] = 1;
                    q.push({nr,nc});
                }
            }
        }
    }
}

// Controller function
void runFloodSimulation() {
    int flood[ROWS][COLS];
    int visited[ROWS][COLS];
    int srcR, srcC;

    cout << "Enter source cell row (0-" << ROWS-1 << "): ";
    cin >> srcR;
    cout << "Enter source cell column (0-" << COLS-1 << "): ";
    cin >> srcC;

    initializeFlood(flood, visited, srcR, srcC);

    floodBFS(flood, visited, srcR, srcC);

    displayFloodMap(flood);

    cout << "\nDo 8-directional flood simulation? (1 = Yes, 0 = No): ";
    int choice; cin >> choice;
    if(choice == 1) {
        initializeFlood(flood, visited, srcR, srcC);
        floodBFS8Dir(flood, visited, srcR, srcC);
        displayFloodMap(flood);
    }
}

int main() {
    runFloodSimulation();
    return 0;
}
