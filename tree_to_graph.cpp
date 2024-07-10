class Solution {
    const int N = 1e5 + 10;
    vector<vector<int>> adjList;
    vector<int> depth; // Depth of each node

    // Function to get the total number of nodes in the tree
    int getNodeCount(TreeNode* root) {
        if (!root) return 0; // If the node is null, return 0
        return 1 + getNodeCount(root->left) + getNodeCount(root->right); // Recursively count nodes
    }

    // Function to map each node to a unique index
    void buildMap(TreeNode* root, map<TreeNode*, int>& nodeToIndex, int& index) {
        if (!root) return; // If the node is null, return
        nodeToIndex[root] = index++; // Assign the current index to the node and increment the index
        buildMap(root->left, nodeToIndex, index); // Recursively process the left subtree
        buildMap(root->right, nodeToIndex, index); // Recursively process the right subtree
    }

    // Function to fill the adjacency list based on the node indices
    void fillAdjList(TreeNode* root, map<TreeNode*, int>& nodeToIndex) {
        if (!root) return; // If the node is null, return
        int u = nodeToIndex[root]; // Get the index of the current node
        if (root->left) {
            int v = nodeToIndex[root->left]; // Get the index of the left child
            adjList[u].push_back(v); // Add the left child to the adjacency list of the current node
            adjList[v].push_back(u); // Add the current node to the adjacency list of the left child (since it's undirected)
        }
        if (root->right) {
            int v = nodeToIndex[root->right]; // Get the index of the right child
            adjList[u].push_back(v); // Add the right child to the adjacency list of the current node
            adjList[v].push_back(u); // Add the current node to the adjacency list of the right child (since it's undirected)
        }
        fillAdjList(root->left, nodeToIndex); // Recursively process the left subtree
        fillAdjList(root->right, nodeToIndex); // Recursively process the right subtree
    }

    // DFS function to compute the depth of each node
    void dfs(int vertex, int par = -1) {
        for (int child : adjList[vertex]) {
            if (child == par) continue; // Skip the parent node
            depth[child] = depth[vertex] + 1; // Update depth
            dfs(child, vertex); // Recursively process the child
        }
    }

public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0; // If the tree is empty, the maximum depth is 0
        
        int n = getNodeCount(root); // Get the total number of nodes in the tree
        adjList.resize(n); // Resize the adjacency list to accommodate all nodes
        depth.resize(n, 0); // Initialize depth array with 0
        
        map<TreeNode*, int> nodeToIndex; // Map to store the index of each node
        int index = 0; // Start index from 0
        buildMap(root, nodeToIndex, index); // Populate the node-to-index map
        fillAdjList(root, nodeToIndex); // Fill the adjacency list based on tree structure
        
        dfs(nodeToIndex[root]); // Start DFS from the root node index
        
        int maxi = -1;
        for (int i = 0; i < n; i++) {
            maxi = max(maxi, depth[i]); // Find the maximum depth
        }
        return maxi+1;
    }
};
