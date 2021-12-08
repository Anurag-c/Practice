// even length cycle => isBipartite && isCycle
// not Bipartite => odd length cycle
// Bipartite => may or may not have a cycle
// in bfs, cycle and bipartite can be checked at a time

bool helper(vector<vector<int>>& graph, vector<int>& parent, vector<int>& color, int vertex)
{
    queue<int>q;
    q.push(vertex);
    parent[vertex] = vertex;
    color[vertex] = 0;
    int currColor = 1;
    //bool isCycle = false 
    
    while(!q.empty())
    {
        int size = q.size();
        while(size--)
        {
            int u = q.front();
            q.pop();
            for(int v : graph[u])
            {
                if(v == parent[u]) continue;
                
                else if(parent[v] == -1)
                {
                    parent[v] = u;
                    color[v] = currColor;
                    q.push(v);
                }
                
                else
                {
                    if(color[v] != currColor)
                        return false;
                    //isCycle = true;
                }
            }
        }
        currColor ^= 1;
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) 
{
    int vertices = graph.size();
    vector<int>parent(vertices, -1);
    vector<int>color(vertices, -1);
    
    for(int i = 0; i < vertices; i++)
    {
        if(parent[i] == -1)
        {
            bool res = helper(graph, parent, color, i);
            if(!res) return false;
        }
    }
    
    return true;
}

// here in dfs parent is not required because they have different colors already, 
// if not that is not bipartite
bool helper(vector<vector<int>>& graph, vector<int>& color, int vertex, int currColor)
{
    color[vertex] = currColor;
    for(int v : graph[vertex])
    {
        if(color[v] == -1)
        {
            bool res = helper(graph, color, v, currColor ^ 1);
            if(!res) return false;
        }
        else if(color[v] != currColor ^ 1)
            return false;
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) 
{
    int vertices = graph.size();
    vector<int>color(vertices, -1);
    
    for(int i = 0; i < vertices; i++)
    {
        if(color[i] == -1)
        {
            bool res = helper(graph, color, i, 0);
            if(!res) return false;
        }
    }
    return true;
}