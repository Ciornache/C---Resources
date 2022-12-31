#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b)
{
    int ans = uniform_int_distribution<int>(a, b)(rng);
    return ans;
}

struct treapNode
{
    treapNode *left = NULL;
    treapNode *right = NULL;
    long long value = 0, priority = 0, sum = 0, value2 = 0;
};

const int pri[4] = {8514, 9554, 7902, 7367};

vector<pair<long long, int>> answers;

class Treap
{
public:
    treapNode *root = NULL;
    Treap()
    {
        root = new treapNode;
        root = NULL;
    }
    treapNode *rotateRight(treapNode *node)
    {
        treapNode *firstTree = node->left;
        treapNode *secondTree = firstTree->right;
        firstTree->right = node;
        node->left = secondTree;
        return firstTree;
    }
    treapNode *rotateLeft(treapNode *node)
    {
        treapNode *firstTree = node->right;
        treapNode *secondTree = firstTree->left;
        firstTree->left = node;
        node->right = secondTree;
        return firstTree;
    }
    void updateSum(treapNode *&r)
    {
        r->sum = (r->left != NULL ? r->left->sum : 0) + (r->right != NULL ? r->right->sum : 0) + r->value2;
    }
    treapNode *insert(int a, treapNode *&r)
    {
        if (r == NULL)
        {
            treapNode *item = new treapNode;
            item->value = item->value2 = item->sum = 0;
            item->right = item->left = NULL;
            return item;
        }
        if (r->value <= a)
        {
            r->right = insert(a, r->right);
            if (r->right->priority > r->priority)
                r = rotateLeft(r);
        }
        else
        {

            r->left = insert(a, r->left);
            if (r->left->priority > r->priority)
                r = rotateRight(r);
        }
        if (r->left != NULL)
            updateSum(r->left);
        if (r->right != NULL)
            updateSum(r->right);
        updateSum(r);
        return r;
    }
    void findSum(int value, treapNode *root, int &ans)
    {
        if (root == NULL)
            return;
        //        cout << root->value << ' ' << ans << ' ' << value << '\n';
        if (root->value <= value)
            ans += root->value2 + (root->left != NULL ? root->left->sum : 0);
        else
            findSum(value, root->left, ans);
        findSum(value, root->right, ans);
    }
    treapNode *deleteNode(treapNode *root, int value)
    {
        if (root->value > value)
            root->left = deleteNode(root->left, value);
        else if (value > root->value)
            root->right = deleteNode(root->right, value);
        else if (value == root->value)
        {
            if (root->left == NULL)
            {
                treapNode *cp = root->right;
                delete root;
                root = cp;
            }
            else if (root->right == NULL)
            {
                treapNode *cp = root->left;
                delete root;
                root = cp;
            }
            else
            {
                if (root->left->priority < root->right->priority)
                {
                    root = rotateLeft(root);
                    root->left = deleteNode(root->left, value);
                }
                else
                {
                    root = rotateRight(root);
                    root->right = deleteNode(root->right, value);
                }
            }
        }
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    Treap treap;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int a;
        cin >> a;
        treap.insert(a, treap.root);
    }
    int ans = 0;
    treap.findSum(3, treap.root, ans);
    std::cout << ans;
}
