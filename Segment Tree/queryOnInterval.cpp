int query(int st, int dr, int node, int x, int y, int tree[])
{
    if (x > y)
        return 0;
    if (st >= x && y >= dr)
        return tree[node];
    int mid = (st + dr) >> 1;
    int val = 0;
    val += (x <= mid ? query(st, mid, (node << 1) + 1, x, y, tree) : 0);
    val += (mid < y ? query(mid + 1, dr, (node << 1) + 2, x, y, tree) : 0);
    return val;
}