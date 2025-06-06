#include<iostream>
#include<queue>
#include<omp.h>
using namespace std;

class node {
public:
    node *left, *right;
    int data;
};

class Breadthfs {
public:
    node* insert(node*, int);  // Correct declaration
    void bfs(node*);
};

node* Breadthfs::insert(node* root, int data) {
    if (!root) {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        } else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

void Breadthfs::bfs(node* head) {
    if (!head) return;

    queue<node*> q;
    q.push(head);

    while (!q.empty()) {
        int qSize = q.size();
        vector<node*> currLevel;

        // Extract all current level nodes first (avoid race condition)
        for (int i = 0; i < qSize; i++) {
            node* currNode = q.front();
            q.pop();
            currLevel.push_back(currNode);
        }

        // Parallel processing for current level nodes
        #pragma omp parallel for
        for (int i = 0; i < currLevel.size(); i++) {
            cout << "\t" << currLevel[i]->data;
        }

        // Push children of all current level nodes sequentially
        for (int i = 0; i < currLevel.size(); i++) {
            if (currLevel[i]->left)
                q.push(currLevel[i]->left);
            if (currLevel[i]->right)
                q.push(currLevel[i]->right);
        }

        cout << endl;
    }
}

int main() {
    node* root = NULL;
    Breadthfs b;
    int data;
    char ans;

    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = b.insert(root, data);

        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    cout << "\nBFS traversal (parallelized):\n";
    b.bfs(root);

    return 0;
}
