#include <iostream>

using namespace std;

typedef struct clueBTNode
{
    char data;
    struct clueBTNode *lc;
    int LTag; // 0:lc,1:preNode
    struct clueBTNode *rc;
    int RTag; // 0:rc,1:postNode

} N, *PN;
void initClueBTree(PN &root);              // create binary tree priorly.
void ThreadBinaryTree(PN &head, PN &root); // create a head node and thread the binary tree
void InThreading(PN p, PN &pre);           // Inorder thread the binary tree.
void InorderTraverse(PN head);
int main()
{
    PN root = NULL, head = NULL;
    initClueBTree(root); // ABC##D##E##
    ThreadBinaryTree(head, root);
    InorderTraverse(head);
    return 0;
}

void initClueBTree(PN &root)
{
    char ch;
    cin >> ch;
    if ('#' != ch)
    {
        root = (PN)malloc(sizeof(N));
        if (!root)
            exit(-1);
        else
        {
            root->data = ch;
            root->LTag = root->RTag = 0;
            root->lc = root->rc = NULL;
        }
        initClueBTree(root->lc);
        initClueBTree(root->rc);
    }
    else
        root = NULL;
}
void ThreadBinaryTree(PN &head, PN &root)
{
    if (!(head = (PN)malloc(sizeof(N))))
        exit(-1);
    head->LTag = 0;
    head->RTag = 1;
    head->rc = head;
    if (!root)
    {
        head->lc = head;
        return;
    }
    else
        head->lc = root;
    // create head node and initialize head node

    PN pre = head;
    InThreading(root, pre);
    pre->rc = head;
    pre->RTag = 1;
    head->rc = pre;
    // thread binary tree.
}
/**
 *                   head
 *                  /
 *                root
 *               /    \
 *           lcTree  rcTree
 * InorderTraverse: head lcTree root rcTree.
 * the function is used to inorder thread the binary tree.
 */
void InThreading(PN p, PN &pre)
{
    if (!p)
        return;
    InThreading(p->lc, pre);
    // thread lc;

    if (!p->lc)(p->LTag = 1, p->lc = pre);
    if (!pre->rc)(pre->RTag = 1, pre->rc = p);
    // thread root;

    pre = p;
    InThreading(p->rc, pre);
    // thread rc;
}
void InorderTraverse(PN head)
{
    PN p = head->lc;
    while (p != head)
    {
        while (p->LTag == 0)p = p->lc; // find the beginning of the inorder traverse.
        cout << p->data;
        while (p->RTag == 1 && p->rc != head){p = p->rc;cout << p->data;} 
        // if p->RTag is 1,it means the node don't have right child.in this case,we can find its post node directly.
        // else ,it has right child,we visit its right child tree.
        p = p->rc;
    }
}