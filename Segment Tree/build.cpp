void Build(int st, int dr, int node)
{
    if (st == dr)
    {
        Do(v[st], node);
        return;
    }
    int mid = (st + dr) >> 1;
    Build(st, mid, (node << 1) + 1), Build(mid + 1, dr, (node << 1) + 2);
    int nx = (node << 1) + 1, nx2 = nx + 1;
    tri[node] = max(tri[(node << 1) + 1], tri[(node << 1) + 2]);
    trp[node] = min(trp[(node << 1) + 1], trp[(node << 1) + 2]);
    mini[node] = min(mini[nx], mini[nx2]);
    maxp[node] = max(maxp[nx], maxp[nx2]);
}