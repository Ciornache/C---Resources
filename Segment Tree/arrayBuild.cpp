void Build(int st, int dr, int node)
{
    if (st == dr)
    {
        tree[node].add(v[st].second);
        return;
    }
    int mid = (st + dr) >> 1;
    Build(st, mid, (node << 1) + 1), Build(mid + 1, dr, (node << 1) + 2);
    int nx = (node << 1) + 1, nx2 = nx + 1;
    merge(tree[nx].begin(), tree[nx].end(), tree[nx2].begin(), tree[nx2].end(), back_inserter(tree[node]));
}