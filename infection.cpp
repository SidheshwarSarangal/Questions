/*You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.

Each minute, a node becomes infected if:

The node is currently uninfected.
The node is adjacent to an infected node.
Return the number of minutes needed for the entire tree to be infected.
  Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
Explanation: The following nodes are infected during:
- Minute 0: Node 3
- Minute 1: Nodes 1, 10 and 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2
It takes 4 minutes for the whole tree to be infected so we return 4.*/
class Solution {
private:
    static int height(TreeNode* n)
    {
        if (!n)
            return 0;
        return 1 + max(height(n->right), height(n->left));
    }
    static pair<bool, int> traverse(TreeNode* n, int targetVal, int& targetSubtreeHeight, int& maxIndirect)
    {
        if (!n)
            return {false, 0};
        else if (n->val == targetVal)
        {
            targetSubtreeHeight = max(height(n->left), height(n->right));
            return {true, 0};
        }
        else
        {
            auto l = traverse(n->left, targetVal, targetSubtreeHeight, maxIndirect);
            auto r = traverse(n->right, targetVal, targetSubtreeHeight, maxIndirect);
            if (l.first)
            {
                // target node found in the left subtree
                maxIndirect = max(maxIndirect, 1 + l.second + r.second);
                return {true, 1 + l.second};
            }
            else if (r.first)
            {
                maxIndirect = max(maxIndirect, 1 + l.second + r.second);
                // target node found in the right subtree
                return {true, 1 + r.second};
            }
            else
            {
                // there is no target in the current tree
                return {false, 1 + max(l.second, r.second)};
            }
        }
    }
public:
    int amountOfTime(TreeNode* root, int start) 
    {
        int targetLeafLen = 0, maxIndirect = 0;
        traverse(root, start, targetLeafLen, maxIndirect);
        return max(maxIndirect, targetLeafLen);
    }
};
