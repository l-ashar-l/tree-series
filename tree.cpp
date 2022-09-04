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

void recursivePreOrder(struct Node *node)
{
    if (!node)
        return;

    cout << node->data << ' ';
    recursivePreOrder(node->left);
    recursivePreOrder(node->right);
}

void recursiveInOrder(Node *node)
{
    if (!node)
        return;

    recursiveInOrder(node->left);
    cout << node->data << ' ';
    recursiveInOrder(node->right);
}

void recursivePostOrder(Node *node)
{
    if (!node)
        return;

    recursivePostOrder(node->left);
    recursivePostOrder(node->right);
    cout << node->data << ' ';
}

vector<vector<int>> bfs(Node *node)
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
    return ans;
}

vector<int> preOrder(Node *node)
{
    vector<int> preorder;
    if (!node)
        return preorder;

    stack<Node *> s;
    s.push(node);

    while (!s.empty())
    {
        node = s.top();
        s.pop();
        preorder.push_back(node->data);
        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);
    }

    for (auto i : preorder)
        cout << i << ' ';

    return preorder;
}

vector<int> inOrder(Node *node)
{
    vector<int> inOrder;
    if (!node)
        return inOrder;
    Node *child = node;
    stack<Node *> s;

    while (true)
    {
        if (child)
        {
            s.push(child);
            child = child->left;
        }
        else
        {
            if (s.empty())
                break;
            child = s.top();
            s.pop();
            inOrder.push_back(child->data);
            child = child->right;
        }
    }
    for (auto i : inOrder)
        cout << i << ' ';

    return inOrder;
}

vector<int> postOrderTwoStack(Node *node)
{
    vector<int> postorder;
    if (!node)
        return postorder;
    stack<Node *> s1, s2;

    Node *root = node;
    s1.push(root);

    while (!s1.empty())
    {
        root = s1.top();
        s1.pop();
        s2.push(root);
        if (root->left)
            s1.push(root->left);
        if (root->right)
            s1.push(root->right);
    }

    while (!s2.empty())
    {
        root = s2.top();
        s2.pop();
        postorder.push_back(root->data);
    }

    for (auto i : postorder)
        cout << i << ' ';

    return postorder;
}

vector<int> postOrder(Node *node)
{
    vector<int> postorder;
    if (!node)
        return postorder;

    Node *current = node;
    stack<Node *> s;

    while (current || !s.empty())
    {
        if (current)
        {
            s.push(current);
            current = current->left;
        }
        else
        {
            Node *temp = s.top()->right;
            if (!temp)
            {
                temp = s.top();
                s.pop();
                postorder.push_back(temp->data);

                while (!s.empty() && temp == s.top()->right)
                {
                    temp = s.top();
                    s.pop();
                    postorder.push_back(temp->data);
                }
            }
            else
                current = temp;
        }
    }
    for (auto i : postorder)
        cout << i << ' ';

    return postorder;
}

vector<vector<int>> allInOne(Node *node)
{
    vector<vector<int>> pre_in_post;
    vector<int> pre, post, in;
    if (!node)
        return pre_in_post;

    stack<pair<Node *, int>> s;
    s.push({node, 1});

    while (!s.empty())
    {
        auto it = s.top();
        s.pop();

        // for preorder
        if (it.second == 1)
        {
            pre.push_back(it.first->data);
            it.second++;
            s.push(it);
            if (it.first->left)
                s.push({it.first->left, 1});
        }

        // for inorder
        else if (it.second == 2)
        {
            in.push_back(it.first->data);
            it.second++;
            s.push(it);
            if (it.first->right)
                s.push({it.first->right, 1});
        }

        // for postorder
        else
        {
            post.push_back(it.first->data);
        }
    }

    pre_in_post.push_back(pre);
    pre_in_post.push_back(in);
    pre_in_post.push_back(post);

    cout << endl
         << "Preorder, Inorder and Postorder in one \n";

    cout << "Pre: ";
    for (auto i : pre)
        cout << i << ' ';
    cout << endl;

    cout << "In: ";
    for (auto i : in)
        cout << i << ' ';
    cout << endl;

    cout << "Post: ";
    for (auto i : post)
        cout << i << ' ';

    cout << endl;

    return pre_in_post;
}

int maxDepth(Node *node)
{
    if (!node)
        return 0;
    int lh = maxDepth(node->left);
    int rh = maxDepth(node->right);

    return 1 + max(lh, rh);
}

int dfsHeight(Node* node){
    if(!node) return 0;
    int lh = dfsHeight(node -> left);
    if(lh == -1) return -1;
    int rh = dfsHeight(node -> right);
    if(rh == -1) return -1;

    if(abs(lh-rh > 1)) return -1;
    return 1+max(lh, rh);
}

bool isBalanced(Node* node){
    if(!node) return false;
    return dfsHeight(node) != -1;
}

int height(Node* node, int &dia){
    if(!node) return 0;

    int lh = height(node->left, dia);
    int rh=height(node->right, dia);
    dia = max(dia, lh + rh);
    return 1+max(lh, rh);
}

int diameter(Node* node){
    int dia=0;
    height(node, dia);
    return dia;
}

int maxPath(Node* node, int &maxi){
    if(!node) return 0;
    int leftSum = max(0, maxPath(node->left, maxi));
    int rightSum = max(0, maxPath(node->right, maxi));
    maxi = max(maxi, leftSum + rightSum + node->data);
    return max(leftSum, rightSum) + node->data;
}

int maxPathCalculator(Node* node){
    int maxi = INT_MIN;
    maxPath(node, maxi);
    return maxi;
}

int sameTree(Node* node1, Node* node2){
    if(!node1 || !node2) return node1 == node2;
    return (node1-> data == node2-> data) 
        && sameTree(node1->left, node2->left) 
            && sameTree(node1->right, node2->right);
}

vector<vector<int>> zigzagSearch(Node* node){
    vector<vector<int>> z;
    if(!node) return z;

    queue<Node*> q;
    q.push(node);
    int iterator = 0;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++)
        {
            Node *child = q.front();
            q.pop();
            if(child -> left) q.push(child->left);
            if(child -> right) q.push(child->right);
            level.push_back(child->data);
        }
        iterator = iterator == 0 ? 1 : 0;
        if(iterator == 0) reverse(level.begin(), level.end());
        z.push_back(level);
    }
    cout << endl << "ZigZag: ";
    int c = 0;
    for (auto i : z)
    {
        c++;
        cout << "L" << c << " = [ ";
        for (auto j : i)
        {
            cout << j << ' ';
        }
        cout << "] ";
    }
    cout << endl;    
    return z;
}

bool isLeaf(Node* node){
    return (!node -> left && !node -> right);
}

void leftBoundary(Node * node, vector < int > &res) {
  Node* cur = node -> left;
  while (cur) {
    if (!isLeaf(cur)) res.push_back(cur -> data);
    if (cur -> left) cur = cur -> left;
    else cur = cur -> right;
  }
}

void rightBoundary(Node * node, vector < int > &res) {
  Node* cur = node -> right;
  vector < int > tmp;
  while (cur) {
    if (!isLeaf(cur)) tmp.push_back(cur -> data);
    if (cur -> right) cur = cur -> right;
    else cur = cur -> left;
  }
  for (int i = tmp.size() - 1; i >= 0; --i) {
    res.push_back(tmp[i]);
  }
}

void addLeaf(Node* node, vector < int > &res) {
  if (isLeaf(node)) {
    res.push_back(node -> data);
    return;
  }
  if (node -> left) addLeaf(node -> left, res);
  if (node -> right) addLeaf(node -> right, res);
}

vector<int> boundaryTraversal(Node* node){
    vector<int> res;
    if(!node) return res;
    if(!isLeaf(node)) res.push_back(node->data);
    leftBoundary(node, res);
    addLeaf(node, res);
    rightBoundary(node, res);

    cout << "Boundary Traversal: ";
    for(auto i: res) cout << i << ' ';
    cout << endl;

    return res;
}

vector<vector<int>> verticalTraversal(Node * root) {
  map<int, map<int, multiset<int>>> nodes;
  // vertical,  level,       data
  queue<pair <Node *, pair<int, int>>> todo;
  //            node,      vertical, level
  todo.push({ root, {0,0}}); //initial vertical and level

  while (!todo.empty()) {
    auto p = todo.front();
    todo.pop();
    Node* temp = p.first;

    //x -> vertical , y->level
    int x = p.second.first, y = p.second.second;
    nodes[x][y].insert(temp -> data); //inserting to multiset

    if (temp -> left) {
      todo.push({ temp -> left, { x-1,  y+1}});
    }
    if (temp -> right) {
      todo.push({temp -> right, {x+1, y+1}});
    }
  }
  vector<vector<int>> ans;
  for (auto p: nodes) {
    vector < int > vertical;
    for (auto q: p.second) {
      vertical.insert(vertical.end(), q.second.begin(), q.second.end());
    }
    ans.push_back(vertical);
  }

    int c = 0;
    cout << "Vertical Traversal: ";
    for (auto i : ans)
    {
        c++;
        cout << "Y" << c << " = [ ";
        for (auto j : i)
        {
            cout << j << ' ';
        }
        cout << "] ";
    }
    cout << endl;

  return ans;
}

vector<int> topView(Node* node){
    vector<int> ans;
    if(!node) return ans;

    map<int, int> m;
    //  line, data

    queue<pair<Node*, int>> q;
    //          node, line

    q.push({node, 0});

    while(!q.empty()){
        auto it = q.front();
        q.pop();
        Node* cur = it.first;
        int line = it.second;
        if(m.find(line) == m.end()) // if line doesnt exist in map
            m[line] = cur->data;
        if(cur->left)   q.push({cur->left, line-1});
        if(cur->right)   q.push({cur->right, line+1});
    }

    for(auto i: m)  ans.push_back(i.second);
    cout << "Top view: ";
    for(auto i: ans) cout << i << ' ';
    cout << endl;
    return ans;
}

vector<int> bottomView(Node* node){
    vector<int> ans;
    if(!node) return ans;

    queue<pair<Node*, int>> q;
    //     node, line
    map<int, int> m;
    //  line, data
    q.push({node, 0});

    while(!q.empty()){
        auto it = q.front();
        q.pop();
        Node* cur = it.first;
        int line = it.second;
        m[line] = cur->data;
        if(cur->left) q.push({cur->left, line-1});
        if(cur->right) q.push({cur->right, line+1});
    }
    for(auto i: m) ans.push_back(i.second);
    cout << "Bottom View: ";
    for(auto i: ans) cout << i << ' ';
    cout << endl;
    return ans;
}

vector<int> rightView(Node* node){
    vector<int> ans;
    if(!node) return ans;

    queue<Node* > q;
    q.push(node);
    
    while(!q.empty()){
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++){
            Node *child = q.front();
            q.pop();
            if (child->right) q.push(child->right);
            if (child->left) q.push(child->left);
            level.push_back(child->data);
        }
        ans.push_back(level[0]);
    }
    cout << "Right View: ";
    for(auto i: ans) cout << i << ' ';
    cout << endl;

    return ans;
}

vector<int> leftView(Node* node){
    vector<int> ans;
    if(!node) return ans;

    queue<Node*> q;
    q.push(node);
    while(!q.empty()){
        int size = q.size();
        vector<int> t;
        for(int i=0; i<size; i++){
            Node* cur = q.front();
            q.pop();
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
            t.push_back(cur->data);
        }
        ans.push_back(t[0]);
    }
    cout << "Left View: ";
    for(auto i: ans) cout << i << ' ';
    cout << endl;

    return ans;
}

bool isSymmetricHelp(Node* left, Node* right){
    if(!left || !right) return left == right; // i.e, left and right both are null
    if(left->data != right-> data) return false;
    return isSymmetricHelp(left->left, right->right) && isSymmetricHelp(left->right, right->left);
}

bool isSymmetric(Node* node){
    return (!node) || isSymmetricHelp(node->left, node->right);
}

bool hasPath(Node* node, vector<int> &res, int leaf){
    if(!node) return false;
    res.push_back(node->data);
    if(node->data == leaf) return true;
    if(hasPath(node->left, res, leaf) || hasPath(node->right, res, leaf)) 
        return true;
    res.pop_back();
    return false;
}

vector<int> pathToNode(Node* node, int leaf){
    vector<int> res;
    if(!node) return res;
    if(!node) cout << "No path available" << endl;
    hasPath(node, res, leaf);
    cout << "Path from root to "<< leaf << ':';
    for(auto i: res) cout << " ->" << i;
    cout << endl;
    return res;
}

Node* lowestCommonAncestor(Node* node, Node* l, Node* r){
        if (node == NULL || node == l || node == r) {
            return node;
        }
        Node* left = lowestCommonAncestor(node->left, l, r);
        Node* right = lowestCommonAncestor(node->right, l, r);

        //result
        if(left == NULL) {
            return right;
        }
        else if(right == NULL) {
            return left;
        }
        else { //both left and right are not null, we found our result
            return node;
        }
}

int maxWidth(Node* node){

    if(!node) return 0;

    int width=0;
    queue<pair<Node*, int>> q;
    q.push({node, 0});
    
    int i=0;
    while(!q.empty()){
        int size=q.size();
        int mmin=q.front().second;
        int first, last;
        for(int k=0; k<size; k++){
            auto cur = q.front();
            int index = cur.second-mmin;
            q.pop();
            if(k==0) first = index;
            if(k==size-1) last = index;
            if(cur.first->left) q.push({cur.first->left, 2*index+1});
            if(cur.first->right) q.push({cur.first->right, 2*index+2});
        }
        width = max(width, last-first+1);
    }
    return width;
}

void childrenSum(Node* node){

    if(!node) return;

    int child=0;
    if(node->left) child += node->left->data;
    if(node->right) child += node->right->data;

    if(child < node->data){
        if(node->left) node->left->data = node->data;
        else if(node->right) node->right->data = node->data;
    }
    
    childrenSum(node->left);
    childrenSum(node->right);

    int total = 0;
    if(node->left) total += node->left->data;
    if(node->right) total += node->right->data;
    if(node->left || node->right) node->data = total;

    return;
}

void markParents(Node* node, unordered_map<Node*, Node*> &parent){
    queue<Node*> q;
    q.push(node);
    while(!q.empty()){
        Node* cur = q.front();
        q.pop();
        if(cur->left){
            q.push(cur->left);
            parent[cur->left] = cur;
        }
        if(cur->right){
            q.push(cur->right);
            parent[cur->right] = cur;
        }
    }
}

vector<int> distanceK(Node* node, Node* target, int k){
    unordered_map<Node*, Node*> parent;
            //    node, parent

    markParents(node, parent);
    unordered_map<Node*, bool> visited;
    queue<Node*> q;
    q.push(target);
    visited[target] = true;

    int cur_distance=0;

    while(!q.empty()){
        int size = q.size();
        if(cur_distance++ == k) break;

        for(int i=0; i<size; i++){
            Node* cur = q.front();
            q.pop();

            if(cur->left && !visited[cur->left]){
                visited[cur->left] = true;
                q.push(cur->left);
            }
            if(cur->right && !visited[cur->right]){
                visited[cur->right] = true;
                q.push(cur->right);
            }
            if(parent[cur] && !visited[parent[cur]]){
                visited[parent[cur]] = true;
                q.push(parent[cur]);
            }
        }
    }
    vector<int> nodes;
    while(!q.empty()){ 
        Node* current = q.front();
        nodes.push_back(current->data); 
        q.pop(); 
    }
    cout << "Nodes from " <<  target->data << " at distance "<< k << ": ";
    for(auto i: nodes) cout << i << ' ';
    cout << endl;
    return nodes;
}

int timeToBurn(Node* node, Node* target){
    if(!node || !target) return 0;

    unordered_map<Node*, Node*> parent;
    markParents(node, parent);

    queue<Node*> q;
    q.push(target);
    map<Node*, bool> visited;
    visited[target] = true;   // initial node to start from;
    int time=0;
    while(!q.empty()){
        int size = q.size();
        int flag = 0;
        for(int i=0; i<size; i++){
            Node* cur = q.front();
            q.pop();

            if(cur->left && !visited[cur->left]){
                flag = 1;
                visited[cur] = true;
                q.push(cur->left);
            }
            if(cur->right && !visited[cur->right]){
                flag = 1;
                visited[cur] = true;
                q.push(cur->right);
            }
            if(parent[cur] && !visited[parent[cur]]){
                flag = 1;
                visited[parent[cur]] = true;
                q.push(parent[cur]);
            }
        }
            if(flag) time++;
    }
    return time;
}

int findLeftHeight(Node* node){
    int h = 0;
    while(node){
        node = node -> left;
        h++;
    }
    return h;
}

int findRightHeight(Node* node){
    int h = 0;
    while(node){
        node = node -> right;
        h++;
    }
    return h;
}

int countNodesWithOptimization(Node* node){     //  O(log(n^2))
    if(!node) return 0;

    int lh = findLeftHeight(node);  // calculate left height
    int rh = findRightHeight(node); // calculate right height

    if(lh == rh) return pow(2, lh) - 1; //  if equal, ans = 2^height - 1

//  else continue to child nodes
    return 1 + countNodesWithOptimization(node->left) + countNodesWithOptimization(node->right);
}

Node* preorderAndinorderBuilder(vector<int> &preOrder, int preStart, int preEnd, vector<int> &inOrder, int inStart, int inEnd, map<int, int> &m){
    if(preStart > preEnd || inStart > inEnd)  return NULL;
    Node* root = new Node(preOrder[preStart]);
    int inRoot = m[root-> data];
    int numsLeft = inRoot - inStart;

    root->left = preorderAndinorderBuilder(preOrder, preStart+1, preStart+numsLeft, inOrder, inStart, inRoot-1, m );
    root->right = preorderAndinorderBuilder(preOrder, preStart+numsLeft+1, preEnd, inOrder, inRoot+1, inEnd, m);

    return root;
}

Node* postorderAndinorderBuilder(vector<int> &inOrder, int inStart, int inEnd, vector<int> &postOrder, int postStart, int postEnd, map<int, int> &m){
    if(postStart > postEnd || inStart > inEnd) return NULL;

    Node* root = new Node(postOrder[postEnd]);

    int inRoot = m[postOrder[postEnd]];

    Node* leftChild = postorderAndinorderBuilder(inOrder, inStart, inRoot-1, postOrder, postStart, postStart+inRoot-inStart-1, m);
    Node* rightChild = postorderAndinorderBuilder(inOrder, inRoot+1, inEnd, postOrder, postStart+inRoot-inStart, postEnd-1, m);
    root->left = leftChild;
    root->right = rightChild;
    return root;
}

Node* treeBuilder(vector<int> &preOrder, vector<int> &inOrder, vector<int> postOrder){
    int preStart = 0, preEnd = preOrder.size()-1;
    int inStart = 0, inEnd = inOrder.size()-1;
    int postStart = 0, postEnd = postOrder.size()-1;

    map<int, int> m;
// node->val, index

    for(int i=inStart; i<=inEnd; i++){
        m[inOrder[i]] = i;
    }
    if(postOrder.size() == 0)
        return preorderAndinorderBuilder(preOrder, preStart, preEnd, inOrder, inStart, inEnd, m);
    if(preOrder.size() == 0)
        return postorderAndinorderBuilder(preOrder, preStart, preEnd, inOrder, inStart, inEnd, m);

    return NULL;
}

string serializer(Node* node){
    string s = "";
    if(!node) return s;

    queue<Node*> q;
    q.push(node);
    while(!q.empty()){
        Node* t = q.front();
        q.pop();
        if(!t) s.append("#,");
        else s.append(to_string(t->data)+',');
        if(t){
            q.push(t->left);
            q.push(t->right);
        }
    }
    return s;
}

Node* deserializer(string s){
    if(s.size() == 0) return NULL;
    
    stringstream ss(s);
    string str;
    getline(ss, str, ',');
    Node* root = new Node(stoi(str));

    queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        Node* node = q.front();
        q.pop();

        getline(ss, str, ',');
        if(str == "#") node->left = NULL;
        else{
            Node* leftChild = new Node(stoi(str));
            node->left = leftChild;
            q.push(leftChild);
        }

        getline(ss, str, ',');
        if(str == "#") node->right = NULL;
        else{
            Node* rightChild = new Node(stoi(str));
            node->right = rightChild;
            q.push(rightChild);
        }
    }
    return root;
}

vector<int> morrisInorder(Node* node){ // use threads
    vector<int> inorder;
    Node* cur = node;

    while(cur){
        if(!cur->left) {
            inorder.push_back(cur->data);
            cur = cur->left;
        }

        else{
            Node* prev = cur->left;
            while(prev->right && prev->right != cur){
                prev = prev->right;
            }
            if(!prev->right){
                prev->right = cur;
                cur = cur->left;
            }
            else{
                prev->right = NULL;
                inorder.push_back(cur->data);
                cur = cur->right;
            }
        }
    }
    return inorder;
}

vector<int> morrisPreorder(Node* node){ // maintain threads but remove after used
    vector<int> preorder;
    Node* cur = node;

    while(cur){
        if(!cur->left) {
            preorder.push_back(cur->data);
            cur = cur->left;
        }
        else{
            Node* prev = cur->left;
            while(prev->right && prev->right != cur){
                prev = prev->right;
            }
            if(!prev->right){
                prev->right = cur;
                preorder.push_back(cur->data);
                cur = cur->left;
            }
            else{
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
    return preorder;
}

Node* flattenBtreeStack(Node* node){
    Node* temp = node;
    stack<Node*> s;
    s.push(temp);
    while(!s.empty()){
        Node* cur = s.top(); s.pop();
        if(cur->right) s.push(cur->right);
        if(cur->left) s.push(cur->left);
        if(!s.empty())  cur->right = s.top();
        cur->left = NULL;
    }
    return temp;
}

int main(){
/*
                    1           
                 /      \           
                2        3
               / \      / \
              4   5    6    7
             / \  / \ / \  / \   
            8   9 0 0 0 0 10  11
*/
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left = new Node(8);
    root->left->left->right = new Node(9);
    root->right->right->left = new Node(10);
    root->right->right->right = new Node(11);

    cout << "recursivePreOrder traversal: ";
    recursivePreOrder(root);

    cout << endl;

    cout << "recursiveInOrder traversal: ";
    recursiveInOrder(root);

    cout << endl;

    cout << "recursivePostOrder traversal: ";
    recursivePostOrder(root);

    cout << endl;
    cout << endl;

    cout << "BFS traversal: ";
    vector<vector<int>> bs = bfs(root);

    cout << endl;

    cout << "Preorder traversal with stack: ";
    vector<int> preorder = preOrder(root);

    cout << endl;

    cout << "Inorder traversal with stack: ";
    vector<int> inorder = inOrder(root);

    cout << endl;

    cout << "Postorder traversal with 2 stack: ";
    vector<int> postorder2 = postOrderTwoStack(root);

    cout << endl;

    cout << "Postorder traversal with single stack: ";
    vector<int> postorder = postOrder(root);

    vector<vector<int>> multiTasker = allInOne(root);

    cout << "Height: " << maxDepth(root) << endl;

    cout << "Balanced: " << isBalanced(root) << endl;

    cout << "Diameter: " << diameter(root) << endl;

    cout << "Maximum Path Sum: " << maxPathCalculator(root) << endl;

    cout << "Trees are same: " << sameTree(root, root) << endl; 

    zigzagSearch(root);

    cout << endl;

    boundaryTraversal(root);
    
    verticalTraversal(root);

    topView(root);
    bottomView(root);
    rightView(root);
    leftView(root);

    cout << "Symmetric: " << isSymmetric(root) << endl;
    cout << endl;

    pathToNode(root, 9);

    Node* lca = lowestCommonAncestor(root, root->right->left, root->right->right->right);


    cout << "Lowest Common Ancestor: " << lca -> data << endl;
    cout << "Max width: "<< maxWidth(root) << endl;

    childrenSum(root);

    bfs(root);

    cout << endl;

/*
                  49        
                  / \           
                22   27
               / \   / \
              17  5 6  21
             / \       / \   
            8   9    10  11
*/

    distanceK(root, root->left, 2);

    cout << "Minimum time to burn the tree: " << timeToBurn(root, root->right) << endl;


    //  complete B tree:-
    Node* root2 = new Node(1);
    root2 -> left = new Node(2);
    root2 -> right =  new Node(3);
    root2 -> left -> left = new Node(4);
    root2 -> left -> right = new Node(5);
    root2 -> right -> left =  new Node(6);
    root2 -> right -> right =  new Node(7);
    root2 -> left -> left -> left = new Node(8);
    root2 -> left -> left -> right = new Node(9);
    root2 -> left -> right -> left = new Node(10);
    root2 -> left -> right -> right = new Node(11);



    cout << "Nodes with O(log(n)) time: " << countNodesWithOptimization(root2) << endl;

    string s = serializer(root);
    cout << "Serialized Tree: " << serializer(root) << endl;

    Node* t = deserializer(s);
    cout << "Deserialized string: ";
    bfs(t);

    cout << endl;

    Node* flat = flattenBtreeStack(root2);
    cout << "Flattened Btree: ";

    bfs(flat);

    cout << endl;
    cout << endl;
    cout << endl;

    return 0;
}