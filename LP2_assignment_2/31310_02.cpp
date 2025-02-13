//A* Search Algorithm in grid/matrix

#include <bits/stdc++.h>
using namespace std;

#define ROW 6
#define COL 6

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

struct Cell {
    int parent_i, parent_j;
    double f, g, h;
};

bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col) {
    return grid[row][col] == 1;
}

bool isDestination(int row, int col, Pair dest) {
    return row == dest.first && col == dest.second;
}
//Calculate heuristic 
double calculateHValue(int row, int col, Pair dest) {
    return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
}

void aStarSearch(int grid[ROW][COL], Pair src, Pair dest) {
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) {
        cout << "Invalid source or destination.\n";
        return;
    }

    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)) {
        cout << "Source or destination is blocked.\n";
        return;
    }
    //create closed list for path already searched
    bool closedList[ROW][COL] = {false};
    Cell cellDetails[ROW][COL];
    
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }
    //source node
    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    //create Open List
    set<pPair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
        cout<<"At ("<<i<<","<<j<<")"<<endl;
        //check all 8 adjacent vertices
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int newRow = i + dx, newCol = j + dy;

                if (isValid(newRow, newCol) && !closedList[newRow][newCol] && isUnBlocked(grid, newRow, newCol)) {
                    if (isDestination(newRow, newCol, dest)) {
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                        cout << "Destination found\n";

                        vector<Pair> path;
                        int r = newRow, c = newCol;
                        while (!(cellDetails[r][c].parent_i == r && cellDetails[r][c].parent_j == c)) {
                            path.push_back(make_pair(r, c));
                            int temp_row = cellDetails[r][c].parent_i;
                            int temp_col = cellDetails[r][c].parent_j;
                            r = temp_row;
                            c = temp_col;
                        }
                        path.push_back(make_pair(r, c));
                        cout << "The Path is: ";
                        for (int i = path.size() - 1; i >= 0; i--) {
                            cout << "(" << path[i].first << "," << path[i].second << ") ";
                        }
                        cout<<endl;
                        foundDest = true;
                        return;
                    }

                    gNew = cellDetails[i][j].g + ((dx == 0 || dy == 0) ? 1.0 : 1.414);//Norma
                    hNew = calculateHValue(newRow, newCol, dest);
                    fNew = gNew + hNew;

                    if (cellDetails[newRow][newCol].f == FLT_MAX || cellDetails[newRow][newCol].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(newRow, newCol)));
                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                    }
                    cout <<"Node : ("<< newRow << "," << newCol <<"), H :"<<hNew <<" F :" << fNew <<endl;


                }
            }
        }
    }

    if (!foundDest) {
        cout << "Destination not found\n";
    }
}

int main() {
    int grid[ROW][COL] = {
        {1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1},
        {1, 1, 1, 0, 1, 1},
        {0, 0, 1, 0, 1, 0},
        {1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 1, 1}
    };

    int x1, y1, x2, y2;
    cout << "Enter source (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter destination (x2 y2): ";
    cin >> x2 >> y2;

    Pair src = make_pair(x1, y1);
    Pair dest = make_pair(x2, y2);

    aStarSearch(grid, src, dest);

    return 0;
}
