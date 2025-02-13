#include <bits/stdc++.h>
using namespace std;

//Create Tree Node
struct Node {
    int value;
    Node* left;
    Node* right;

    Node() {
        left = right = NULL;
    }

    Node(int v) {
        this->value = v;
        left = right = NULL;
    }
};

//recursive DFS
bool DFS(Node* root, int key) {
    if (root == NULL) return false;
    cout<<root->value<<" ";
    if (root->value == key) return true;
    return DFS(root->left, key) || DFS(root->right, key);
}

//recursive BFS
bool BFS(vector<Node*> level, int key) {
    if (level.empty()) return false;

    vector<Node*> next_level;//store next level

    for (Node* node : level) {
        cout<<node->value<<" ";
        if (node->value == key) {
            return true;
        }

        if (node->left != NULL) next_level.push_back(node->left);
        if (node->right != NULL) next_level.push_back(node->right);
    }

    return BFS(next_level, key);
}

//levelorder traversal 
void levelOrder(Node* root) {
    if (root == NULL) return ;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->value << " ";
        if (curr->left != NULL) q.push(curr->left);
        if (curr->right != NULL) q.push(curr->right);
    }
    return ;
}

//Build Tree
Node* buildTree() {
    cout << "Enter root value: ";
    int val;
    cin >> val;
    Node* root = new Node(val);

    cout << "Continue adding nodes? (0/1): ";
    int cont;
    cin >> cont;

    queue<Node*> q;
    q.push(root);
    
    while (cont) {
        Node* current = q.front();
        q.pop();

        cout << "Enter left value for node " << current->value << " (-1 for no left child): ";
        cin >> val;
        if (val != -1) {
            current->left = new Node(val);
            q.push(current->left);
        }

        cout << "Enter right value for node " << current->value << " (-1 for no right child): ";
        cin >> val;
        if (val != -1) {
            current->right = new Node(val);
            q.push(current->right);
        }

        cout << "Continue adding nodes? (0/1): ";
        cin >> cont;
    }

    return root;
}
 
int main() {
    Node* root = buildTree();

    cout<<"Level Order: ";
    levelOrder(root);
    cout<<endl;
    int c;
    do
    {
        cout << "Enter key to search: ";
        int key;
        cin >> key;
        cout<<"DFS Search: ";
        if (DFS(root, key)) {
            cout << "\nDFS: Key found in the tree!" << endl;
        } else {
            cout << "\nDFS: Key not found in the tree." << endl;
        }
        cout<<"BFS Search: ";
        if (BFS({root}, key)) {
            cout << "\nBFS: Key found in the tree!" << endl;
        } else {
            cout << "\nBFS: Key not found in the tree." << endl;
        }
        cout<<"Continue(0/1): ";cin>>c;cout<<endl;
    } while (c==1);

    cout<<"DFS: Time Complexity : O(N)   Space Complexity : O(N)"<<endl;
    cout<<"BFS: Time Complexity : O(N)   Space Complexity : O(N)"<<endl;
 
    return 0;
}