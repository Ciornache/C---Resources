void update(int st, int dr, int node, int pz, int val, int tree[])
{
    if (st == dr)
    {
        tree[node] += val;
        return;
    }
    int mid = (st + dr) >> 1;
    if (pz <= mid)
        update(st, mid, (node << 1) + 1, pz, val, tree);
    else
        update(mid + 1, dr, (node << 1) + 2, pz, val, tree);
    tree[node] = tree[(node << 1) + 1] + tree[(node << 1) + 2];
}