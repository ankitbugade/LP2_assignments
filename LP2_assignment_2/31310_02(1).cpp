//8 Puzzle Problem

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Node {
public:
    vector<vector<char>> data; // Puzzle data (2D matrix)
    int level; // Level of the node (i.e., the number of moves to reach this state)
    int fval; // f-value (h + g)

    Node(vector<vector<char>> puzzle, int lvl) {
        data = puzzle;
        level = lvl;
        fval = 0;
    }

    // Find position of the blank space ('_')
    pair<int, int> findBlank() {
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                if (data[i][j] == '_') {
                    return {i, j};
                }
            }
        }
        return {-1, -1}; // Just a fallback, should never happen
    }

    // Generate child nodes by moving the blank space
    vector<Node> generateChildren() {
        pair<int, int> blankPos = findBlank();
        int x = blankPos.first, y = blankPos.second;
        vector<pair<int, int>> directions = {{x, y - 1}, {x, y + 1}, {x - 1, y}, {x + 1, y}};
        vector<Node> children;

        for (auto& dir : directions) {
            int newX = dir.first, newY = dir.second;
            if (isValidMove(newX, newY)) {
                vector<vector<char>> newPuzzle = shuffle(x, y, newX, newY);
                Node child(newPuzzle, level + 1);
                children.push_back(child);
            }
        }
        return children;
    }

    // Check if the new position is within bounds
    bool isValidMove(int x, int y) {
        return x >= 0 && x < data.size() && y >= 0 && y < data.size();
    }

    // Shuffle the puzzle by swapping the blank space
    vector<vector<char>> shuffle(int x1, int y1, int x2, int y2) {
        vector<vector<char>> newPuzzle = data;
        swap(newPuzzle[x1][y1], newPuzzle[x2][y2]);
        return newPuzzle;
    }
};

class Puzzle {
public:
    int n; // Size of the puzzle (e.g., 3 for a 3x3 puzzle)
    vector<Node> open; // Open list (nodes to explore)
    vector<Node> closed; // Closed list (nodes that have been explored)

    Puzzle(int size) : n(size) {}

    // Accept the puzzle configuration from the user
    vector<vector<char>> accept() {
        vector<vector<char>> puzzle(n, vector<char>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> puzzle[i][j];
            }
        }
        return puzzle;
    }

    // Calculate the f-value (f = g + h)
    int f(Node& node, vector<vector<char>>& goal) {
        return h(node.data, goal) + node.level;
    }

    // Heuristic function (misplaced tiles)
    int h(const vector<vector<char>>& node, const vector<vector<char>>& goal) {
        int misplaced = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (node[i][j] != goal[i][j] && node[i][j] != '_') {
                    misplaced++;
                }
            }
        }
        return misplaced;
    }

    // Process to solve the puzzle
    void process() {
        vector<vector<char>> start, goal;

        cout << "Enter the start state matrix (3x3):\n";
        start = accept();

        cout << "Enter the goal state matrix (3x3):\n";
        goal = accept();

        Node startNode(start, 0);
        startNode.fval = f(startNode, goal);
        open.push_back(startNode);

        while (!open.empty()) {
            Node current = open[0];
            cout << "Current state:\n";
            printPuzzle(current.data);

            // If current puzzle is the goal state, terminate
            if (h(current.data, goal) == 0) {
                cout << "Goal reached!\n";
                break;
            }

            // Generate children and add them to the open list
            vector<Node> children = current.generateChildren();
            for (Node& child : children) {
                child.fval = f(child, goal);
                open.push_back(child);
            }

            // Move current node to the closed list
            closed.push_back(current);
            open.erase(open.begin());

            // Sort the open list by f-value (ascending order)
            sort(open.begin(), open.end(), [](Node& a, Node& b) {
                return a.fval < b.fval;
            });
        }
    }

    // Function to print the puzzle matrix
    void printPuzzle(const vector<vector<char>>& puzzle) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << puzzle[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Puzzle puzzle(3); // Initialize a 3x3 puzzle
    puzzle.process();
    return 0;
}
