// Create an inordered threaded binary search tree. Perform inorder,
// preorder traversals without recursion and deletion of a node. Analyze
// time and space complexity of the algorithm.

#include <iostream>
using namespace std;

class TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    bool Rthread;

public:
    TreeNode()
    {
        val = 0;
        left = NULL;
        right = NULL;
        Rthread = false;
    }

    void insert(TreeNode *&);
    void delet(TreeNode *&);
    void inorder(TreeNode *&);
    void preorder(TreeNode *&);
};

void TreeNode::insert(TreeNode *&root)
{
    int n;
    cout << "Enter the value of a node to be inserted: ";
    cin >> n;
    TreeNode *newNode = new TreeNode;
    newNode->val = n;

    if (!root)
    {
        root = newNode;
        cout << "Inserted!\n";
        return;
    }

    TreeNode *q = root;

    while (q)
    {
        if (n < q->val)
        {
            if (q->left == NULL)
            {
                q->left = newNode;
                newNode->right = q;
                newNode->Rthread = true;
                cout << "Inserted!\n";
                return;
            }
            else
            {
                q = q->left;
            }
        }
        else if (n > q->val)
        {
            if (q->right == NULL || q->Rthread)
            {
                newNode->right = q->right;
                q->right = newNode;
                q->Rthread = false;
                newNode->Rthread = true;

                cout << "Inserted!\n";
                return;
            }
            else
            {
                q = q->right;
            }
        }
    }
}

void TreeNode::delet(TreeNode *&root)
{
    int key;
    cout << "Enter node to be deleted: ";
    cin >> key;

    TreeNode *parent = NULL;
    TreeNode *curr = root;

    // Search for the node
    while (curr)
    {
        if (key == curr->val)
            break;
        parent = curr;
        if (key < curr->val)
            curr = curr->left;
        else
        {
            if (curr->Rthread)
                break;
            curr = curr->right;
        }
    }

    if (!curr || curr->val != key)
    {
        cout << "Node not found!\n";
        return;
    }

    // Case: Node with two children
    if (curr->left && curr->right && !curr->Rthread)
    {
        TreeNode *succ = curr->right;
        TreeNode *succParent = curr;

        while (succ->left)
        {
            succParent = succ;
            succ = succ->left;
        }

        curr->val = succ->val;
        curr = succ;
        parent = succParent;
        key = succ->val;
    }

    // Now curr has at most one child
    TreeNode *child = NULL;
    if (curr->left)
        child = curr->left;
    else if (!curr->Rthread)
        child = curr->right;

    if (!parent)
    {
        root = child;
    }
    else if (parent->left == curr)
    {
        parent->left = child;
    }
    else
    {
        if (parent->Rthread)
        {
            parent->right = curr->right;
        }
        else
        {
            parent->right = child;
        }
    }

    delete curr;
    cout << "Deleted!\n";
}


void TreeNode::inorder(TreeNode *&root)
{
    TreeNode *curr = root;

    // Go to the leftmost node
    while (curr && curr->left)
        curr = curr->left;

    while (curr)
    {
        cout << curr->val << " ";

        // If Rthread is true, follow the thread
        if (curr->Rthread)
            curr = curr->right;
        else
        {
            // Go to the leftmost node of right subtree
            curr = curr->right;
            while (curr && curr->left)
                curr = curr->left;
        }
    }
}

void TreeNode::preorder(TreeNode *&root)
{
    TreeNode *curr = root;

    while (curr)
    {
        cout << curr->val << " ";

        if (curr->left)
        {
            curr = curr->left;
        }
        else
        {
            while (curr && (curr->Rthread || curr->right == NULL))
            {
                curr = curr->right;
            }

            if (curr)
                curr = curr->right;
        }
    }
}

int main()
{
    TreeNode *root = NULL;
    TreeNode t;
    int n = 10;
    while (n)
    {
        cout << "\n\nEnter 1:Insert 2:Delete 0:Stop :- ";
        cin >> n;
        if (n == 1)
        {
            t.insert(root);
            cout << "Inorder: ";
            t.inorder(root);
            cout << "\nPreorder: ";
            t.preorder(root);
        }
        else if (n == 2)
        {
            t.delet(root);
            cout << "Inorder: ";
            t.inorder(root);
            cout << "\nPreorder: ";
            t.preorder(root);
        }
        else if (n == 0)
        {
            break;
        }
        else
        {
            cout << "Please enter correct option";
        }
    }

    return 0;
}