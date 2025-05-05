// A Dictionary stores keywords & its meanings. Provide facility for
// adding new keywords, deleting keywords, updating values of any
// entry. Provide facility to display whole data sorted in ascending/
// Descending order. Also find how many maximum comparisons may
// require for finding any keyword. Use Height balance tree and find the
// complexity for finding a keyword.

#include <iostream>
using namespace std;

struct AvlNode
{
    int key;
    AvlNode *leftChild, *rightChild;
    int bf;

    AvlNode(int k)
    {
        key = k;
        leftChild = NULL;
        rightChild = NULL;
        bf = 0;
    }
};

class AVL
{
private:
    AvlNode *root;

public:
    AVL()
    {
        root = NULL;
    }

    void Insert(int k)
    {
        if (!root)
        {
            root = new AvlNode(k);
            return;
        }

        // Phase 1: Locate insertion point
        AvlNode *a = root; // a: last node with bf != 0
        AvlNode *pa = NULL;
        AvlNode *p = root;
        AvlNode *pp = NULL;

        while (p)   // set a, pp, pa
        {
            if (p->bf != 0)
            {
                a = p;
                pa = pp;
            }
            if (k < p->key)
            {
                pp = p;
                p = p->leftChild;
            }
            else if (k > p->key)
            {
                pp = p;
                p = p->rightChild;
            }
            else
            {
                return; // key already exists
            }
        }

        // Insert new node
        AvlNode *y = new AvlNode(k);
        if (k < pp->key)
        {
            pp->leftChild = y;
        }
        else
        {
            pp->rightChild = y;
        }

        // Phase 2: Adjust balance factors
        int d;
        AvlNode *b, *c;
        if (k < a->key)
        {
            b = a->leftChild;
            p = a->leftChild;
            d = 1;
        }
        else
        {
            b = a->rightChild;
            p = a->rightChild;
            d = -1;
        }

        while (p != y)
        {
            if (k < p->key)
            {
                p->bf = 1;
                p = p->leftChild;
            }
            else
            {
                p->bf = -1;
                p = p->rightChild;
            }
        }

        // Check if tree is still balanced
        a->bf += d;
        if(abs(a->bf) == 1 || a->bf == 0)
        {
            return;
        }

        // Tree is unbalanced: do rotations
        AvlNode *newSubRoot;
        if (d == 1)
        { // Left imbalance
            if (b->bf == 1)
            { // LL
                a->leftChild = b->rightChild;
                b->rightChild = a;
                a->bf = b->bf = 0;
                newSubRoot = b;
            }
            else
            { // LR
                c = b->rightChild;
                b->rightChild = c->leftChild;
                a->leftChild = c->rightChild;
                c->leftChild = b;
                c->rightChild = a;

                switch (c->bf)
                {
                case 1:
                    a->bf = -1;
                    b->bf = 0;
                    break;
                case -1:
                    b->bf = 1;
                    a->bf = 0;
                    break;
                case 0:
                    a->bf = b->bf = 0;
                    break;
                }
                c->bf = 0;
                newSubRoot = c;
            }
        }
        else
        { // Right imbalance
            if (b->bf == -1)
            { // RR
                a->rightChild = b->leftChild;
                b->leftChild = a;
                a->bf = b->bf = 0;
                newSubRoot = b;
            }
            else
            { // RL
                c = b->leftChild;
                b->leftChild = c->rightChild;
                a->rightChild = c->leftChild;
                c->rightChild = b;
                c->leftChild = a;

                switch (c->bf)
                {
                case 1:
                    a->bf = 0;
                    b->bf = -1;
                    break;
                case -1:
                    a->bf = 1;
                    b->bf = 0;
                    break;
                case 0:
                    a->bf = b->bf = 0;
                    break;
                }
                c->bf = 0;
                newSubRoot = c;
            }
        }

        // Attach the new root of the rotated subtree
        if (!pa)
            root = newSubRoot;
        else if (a == pa->leftChild)
            pa->leftChild = newSubRoot;
        else
            pa->rightChild = newSubRoot;
    }

    // In-order traversal
    void InOrder(AvlNode *node)
    {
        if (!node)
            return;
        InOrder(node->leftChild);
        cout << node->key << " ";
        InOrder(node->rightChild);
    }

    void DisplayInOrder()
    {
        InOrder(root);
        cout << endl;
    }
};

int main()
{
    AVL tree;
    tree.Insert(30);
    tree.Insert(20);
    tree.Insert(10); // LL
    tree.Insert(25); // LR
    tree.Insert(40);
    tree.Insert(50); // RR
    tree.Insert(45); // RL

    tree.DisplayInOrder(); // Should print sorted keys

    return 0;
}
