void Propag(int node, int st, int dr)
{
    trp[node] += lazy[node], tri[node] += lazy[node], mini[node] += lazy[node], maxp[node] += lazy[node];
    if (st != dr)
        lazy[(node << 1) + 1] += lazy[node], lazy[(node << 1) + 2] += lazy[node];
    if (lazy[node] % 2)
        swap(trp[node], mini[node]), swap(tri[node], maxp[node]);
    lazy[node] = 0;
}
void Update(int st, int dr, int node, int x, int y, int val)
{
    if (st >= x && y >= dr)
    {
        if (lazy[node])
            Propag(node, st, dr);
        trp[node] += val, tri[node] += val, mini[node] += val, maxp[node] += val;
        if (st != dr)
            lazy[(node << 1) + 1] += val, lazy[(node << 1) + 2] += val;
        if (val % 2)
            swap(trp[node], mini[node]), swap(tri[node], maxp[node]);
        return;
    }
    if (lazy[node])
        Propag(node, st, dr);
    int mid = (st + dr) >> 1;
    if (x <= mid)
        Update(st, mid, (node << 1) + 1, x, y, val);
    else
    {
        if (lazy[(node << 1) + 1])
            Propag((node << 1) + 1, st, mid);
    }
    if (mid < y)
        Update(mid + 1, dr, (node << 1) + 2, x, y, val);
    else
    {
        if (lazy[(node << 1) + 2])
            Propag((node << 1) + 2, mid + 1, dr);
    }
    int nx = (node << 1) + 1, nx2 = nx + 1;
    tri[node] = max(tri[(node << 1) + 1], tri[(node << 1) + 2]);
    trp[node] = min(trp[(node << 1) + 1], trp[(node << 1) + 2]);
    mini[node] = min(mini[nx], mini[nx2]);
    maxp[node] = max(maxp[nx], maxp[nx2]);
}