#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

void bfs(Node *node)
{
    vector<vector<int>> ans;

    if (!node) ans;
    queue<Node *> q;
    q.push(node);

    while (!q.empty())
    {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++)
        {
            Node *child = q.front();
            q.pop();
            if (child->left)
                q.push(child->left);
            if (child->right)
                q.push(child->right);
            level.push_back(child->data);
        }
        ans.push_back(level);
    }
    int c = 0;
    for (auto i : ans)
    {
        c++;
        cout << "L" << c << " = [ ";
        for (auto j : i)
        {
            cout << j << ' ';
        }
        cout << "] ";
    }
}

Node* searchNode(Node* node, int data){
    while(node && node->data != data){
        node = data < node -> data ? node -> left : node -> right;
    }
    return node;
}

int ceil(Node* node, int key){      //  node -> data >= key
    int ceil = -1;
    while(node){
        if(node->data == key) return key;

        if(node->data > key) { 
            ceil = node->data; 
            node = node->left;
        }
        else node = node->right;
    }
    return ceil;
}

int floor(Node* node, int key){     //      node -> data <= key
    int floor = -1;

    while(node){
        if(node-> data == key) return node->data;
        if(node -> data > key) node = node->left;
        else{
            floor = node->data;
            node = node->right;
        }
    }
    return floor;
}

Node* insert(Node* node, int data){
    Node* root = node;
    while(true){
        if(data < node ->data){ 
            if(node->left)
                node = node->left;
            else{
                node->left = new Node(data);
                break;
            }
        }
        else {
            if(node->right)
                node = node->right;
            else{
                node->right = new Node(data);
                break;
            }
        }
    }
    return root;
}

Node* findLastRight(Node* node){
    if(!node->right) return node;
    return findLastRight(node->right);
}

Node* helper(Node* node){
    if(!node->left) return node->right;
    if(!node->right) return node->left;

    Node* rightChild = node->right;
    Node* lastRight = findLastRight(node->right);
    rightChild -> right = lastRight;
    return node->left;
}

Node* deletion(Node* node, int data){
    if(node -> data == data) return helper(node);
    Node* dummy = node;
    while(node){
        if(node->data > data){
            if(node->left && node->left->data == data){
                node->left = helper(node->left);
            }
            else    node = node->left;
        }
        else{
            if(node->right && node->right->data == data)
                node->right = helper(node->right);
            else
                node = node->right;    
        }
    }
    return dummy;
}

Node* kthSmallest(Node* node, int &k){
    if(!node) return NULL;

    Node* left = kthSmallest(node->left, k);
    if(left) return left;

    k--;

    if(!k) return node;

    return kthSmallest(node->right, k);
}

Node* kthLargest(Node* node, int &k){
    if(!node) return NULL;
    
    Node* right = kthLargest(node->right, k);
    if(right) return right;

    k--;

    if(!k) return node;

    return kthLargest(node->left, k);
}

bool isBstHelper(Node* node, long minVal, long maxVal){
    if(!node) return true;

    if(node->data >= maxVal || node->data <= minVal) return false;
    return (isBstHelper(node->left, minVal, node->data) && isBstHelper(node->right, node->data, maxVal));
}

bool isBst(Node* node){
    return(isBstHelper(node, INT_MIN, INT_MAX));
}

Node* lca(Node* node, Node* p, Node* q){
    if(!node) return NULL;
    int cur = node->data;
    if(cur < p->data && cur < q->data)
        return lca(node->right, p, q);
    if(cur > p->data && cur > q->data)
        return lca(node->left, p, q);
    return node;
}

Node* bstFromPreOrder(vector<int> &preorder, int &i, int bound){
    if(i==preorder.size() || preorder[i] > bound) return NULL;
    Node* node = new Node(preorder[i++]);
    node->left = bstFromPreOrder(preorder, i, node->data);
    node->right = bstFromPreOrder(preorder, i, bound);

    return node;
}

Node* buildBstFromPreorder(vector<int> &preorder){
    int i=0;
    return bstFromPreOrder(preorder, i, INT_MAX);
}

Node* inorderSuccessor(Node* node, Node* p){
    Node* successor = NULL;
    while(node){
        if(p->data >= node->data)
            node = node->right;
        else{
            successor = node;
            node = node->left;
        }
    }
    return successor;
}

class BSTIterator{      //  practice this code for interview
    private:
            stack<Node* > s;
            bool reverse = true;
            void pushAll(Node* node){
                while(node){
                    s.push(node);
                    if(!reverse)   node = node->left;
                    else    node = node->right;
                }
            }

    public:
            BSTIterator(Node* node, bool isReverse){
                reverse = isReverse;
                pushAll(node);
            }

            bool hasNext(){
                return !s.empty();
            }

            int next(){
                Node* tmp = s.top();
                s.pop();
                if(!reverse)    pushAll(tmp->right);
                else    pushAll(tmp->left);
                return tmp->data;
            }
};

bool twoSumBST(Node* node, int k){
    if(!node) return false;
    BSTIterator l(node, false); //  using same objects for two pointer
    BSTIterator r(node, true);  //  l for ascending and r for descending order pointers to get two sum
    int i = l.next();
    int j = r.next();

    while(i<j){
        if(i+j == k) return true;
        if(i+j < k) i = l.next();
        else j = r.next();
    }
    return false;
}

int main(){
/*
                   8
                 /   \
                5    12
               / \   / \
              4   7 10  14
                 /      /
                6      13  
*/
    Node* bstRoot = new Node(8);
    bstRoot -> left = new Node(5);
    bstRoot -> right = new Node(12);
    bstRoot -> left -> left = new Node(4);
    bstRoot -> left -> right = new Node(7);
    bstRoot -> left -> right -> left = new Node(6);
    bstRoot -> right -> left = new Node(10);
    bstRoot -> right -> right = new Node(14);
    bstRoot -> right -> right -> left = new Node(13);

    cout << "BST BFS: "; bfs(bstRoot);

    cout << endl << endl;

    Node* foundNode = searchNode(bstRoot, 7);
    if(foundNode)
    cout << "Node found at: " << foundNode->data << endl;

    cout << endl;

    cout << "Ceil of root with data 11:" << ceil(bstRoot, 11) << endl;

    cout << endl;

    cout << "Floor of root with data 11:" << floor(bstRoot, 11) << endl;

    cout << endl;

    Node* inserted = insert(bstRoot, 15);
    cout << "BFS after insertion: "; bfs(bstRoot);

    cout << endl;

    Node* deleted = deletion(bstRoot, 15);
    cout << "BFS after deletion: "; bfs(bstRoot);

    cout << endl;
    cout << endl;

    int k=4;
    Node* smallestK = kthSmallest(bstRoot, k);

    k=4;
    Node* largestK = kthLargest(bstRoot, k);

    cout << "kth smallest element in the tree: " << smallestK->data << endl;
    cout << "kth largest element in the tree: " << largestK->data << endl;

    cout << "Is BST: " << isBst(bstRoot) << endl;
    
    cout << "LCA of " << 4 << ',' << 7  << ": " << lca(bstRoot, bstRoot->left->left, bstRoot->left->right) -> data << endl;

    vector<int> preorder = {8,5,4,7,6,12,10,14,13};
    Node* preOrderRoot = buildBstFromPreorder(preorder);

    cout << "BFS of preoder insertion: "; bfs(preOrderRoot); cout << endl;

    cout << "Inorder Successor of 10: " << inorderSuccessor(bstRoot, bstRoot->right) -> data << endl;

    cout << "Two nodes with Sum 17 exist: " << twoSumBST(bstRoot, 17) << endl;

    cout << endl;
    cout << endl;
    cout << endl;
    return 0;
}