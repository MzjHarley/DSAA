#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MAX_VERTEX_NUM 100
#define MAX_INT 32767
typedef char VertexType;
typedef int ArcType;
typedef struct AMGraph
{
    int vertexNum;
    int arcNum;
    VertexType vexs[MAX_VERTEX_NUM];
    ArcType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} AMGraph;

void CreateDN(AMGraph &G);
int LocateVex(AMGraph G, VertexType u);
void DFS_Traverse(AMGraph G);
void DFS_AMGraph(AMGraph G, int v, int *visit);
void BFS_traverse(AMGraph G);
void BFS_AMGraph(AMGraph G, int v, int *visit, queue<int> &q);
void ShortestPath_Dijkstra(AMGraph G, int v);
void path(AMGraph G, int v, int *pre);
/*
test data:
5 7
A B C D E
A B 10
A D 30
A E 100
B C 50
C E 10
D C 20
D E 60
 */
int main()
{
    AMGraph G;
    CreateDN(G);
    DFS_Traverse(G);
    BFS_traverse(G);
    ShortestPath_Dijkstra(G, 0);
    return 0;
}
void CreateDN(AMGraph &G) // create directed network in which all edges are with weight.
{
    cin >> G.vertexNum >> G.arcNum;
    for (int i = 0; i < G.vertexNum; i++)
        cin >> G.vexs[i];
    for (int i = 0; i < G.vertexNum; i++)
        for (int j = 0; j < G.vertexNum; j++)
            G.arcs[i][j] = MAX_INT;
    VertexType v1, v2;
    ArcType w;
    for (int i = 0; i < G.arcNum; i++)
    {
        cin >> v1 >> v2 >> w;
        G.arcs[LocateVex(G, v1)][LocateVex(G, v2)] = w;
    }
}
int LocateVex(AMGraph G, VertexType u)
{
    for (int i = 0; i < G.vertexNum; i++)
        if (u == G.vexs[i])
            return i;
    return -1;
}
/**
 * DFS_Traverse: Depth-First Search Traverse.
 * we start from some point like v, visit this point,then starting from unvisited adjacent(邻接的) points of v,
 * the graph is depth-first traversed until all vertics in the graph communicate with v are visited.
 * if tex ishere are still unvisited vertics in the graph,then another unvisited vert selected as the starting point,
 * and repeat the above process until all the vertics in the graph are visited.
 *                                             v1
 *                                           /    \
 *                                          \/    \/
 *                                          v2     v3
 *                                         /  \   /  \
 *                                        \/  \/ \/  \/
 *                                        v4  v5 v6->v7
 *                                         \  /
 *                                         \/\/
 *                                          v8
 * DFS_Traverse(from v1): v1->v2->v4->v8->v5->v3->v6->v7
 */
void DFS_Traverse(AMGraph G)
{
    int visit[G.vertexNum]; // it's just a tag array which records the point visited.  0:not visited     1:has been visited.
    memset(visit, 0, sizeof(int) * G.vertexNum);
    for (int i = 0; i < G.vertexNum; i++)
        if (!visit[i])
            DFS_AMGraph(G, i, visit);
    cout << endl;
}
/** Adjacent Martrix of UDN
 *     *******************
 *     *    v1 v2 v3  ...*
 *     * v1 10  1 100 ...*
 *     * v2 11  0 101 ...*
 *     * v3 12  3 132 ...*
 *     *  .  .  .  .  ...*
 *     *  .  .  .  .  ...*
 *     *  .  .  .  .  ...*
 *     *******************
 */
void DFS_AMGraph(AMGraph G, int v, int *visit)
{
    cout << G.vexs[v] << " ";
    visit[v] = 1;
    for (int i = 0; i < G.vertexNum; i++)
        if (G.arcs[v][i] != MAX_INT && !visit[i])
            DFS_AMGraph(G, i, visit);
}
/**
 * BFS_Traverse: Breadth-First Search Traverse.
 * we start from some point like v, visit v,then visit all unvisited adjacent points of v in turn.
 * then start from the adjacent points of v, visit the unvisited adjacent points of them.
 * when we visit the vertex,we need to make the adjacent points of the first visited vertex visited  before the adjacent points of the later vertex.
 * until all vertics in the graph that have a path to vertex v are visited.
 *                                             v1
 *                                           /    \
 *                                          \/    \/
 *                                          v2     v3
 *                                         /  \   /  \
 *                                        \/  \/ \/  \/
 *                                        v4  v5 v6->v7
 *                                         \  /
 *                                         \/\/
 *                                          v8
 * BFS_Traverse(from v1): v1->v2->v3->v4->v5->v6->v7->v8
 */
void BFS_traverse(AMGraph G)
{
    int visit[G.vertexNum];
    queue<int> q;
    memset(visit, 0, sizeof(int) * G.vertexNum);
    for (int i = 0; i < G.vertexNum; i++)
        if (!visit[i])
            q.push(i), BFS_AMGraph(G, i, visit, q);
    cout << endl;
}
void BFS_AMGraph(AMGraph G, int v, int *visit, queue<int> &q)
{
    while (!q.empty())
    {
        if (!visit[v])
        {
            cout << G.vexs[v] << " ";
            visit[v] = 1;
            for (int i = 0; i < G.vertexNum; i++)
                if (G.arcs[v][i] != MAX_INT && !visit[i])
                    q.push(i);
            q.pop();
            BFS_AMGraph(G, q.front(), visit, q);
        }
        else
        {
            q.pop();
        }
    }
}
void ShortestPath_Dijkstra(AMGraph G, int v)
{
    int visit[G.vertexNum], D[G.vertexNum], pre[G.vertexNum];
    // visit is a tag array to record visited point.
    // D is a array to record the shortest distance between v and other points.
    // pre is a array to record the pre points of v's adjacent points.
    for (int i = 0; i < G.vertexNum; i++)
    {
        visit[i] = 0, D[i] = G.arcs[v][i];
        pre[i] = D[i] != MAX_INT ? v : -1;
    }
    visit[v] = 1, D[v] = 0, pre[v] = -1;
    for (int i = 0; i < G.vertexNum; i++)
    {
        int min = MAX_INT; // store min distance.
        int temp;          // when get min distance,store the index of v's adjacent points.
        // get min distance  and the index of v's adjacent points when it's min distance.
        for (int j = 0; j < G.vertexNum; j++)
            if (!visit[j] && min > D[j])
                temp = j, min = D[j];
        visit[temp] = 1;
        // update D[G.vertexNum]
        for (int k = 0; k < G.vertexNum; k++)
            if (G.arcs[temp][k] != MAX_INT && !visit[k] && D[k] > D[temp] + G.arcs[temp][k])
                D[k] = D[temp] + G.arcs[temp][k], pre[k] = temp;
    }
    cout << "visit_Point   "<< "shortest_path   "<< "   shortest_distance\n";
    for (int m = 0; m < G.vertexNum; m++)
    {
        if(m!=v){
        cout << "     " << G.vexs[m] << "              ";
        path(G, m, pre);
        cout << "           \t" << D[m]<< endl;
        }
    }
}
void path(AMGraph G, int v, int *pre)
{
    if (-1 == v)
        return;
    path(G, pre[v], pre);
    cout << G.vexs[v];
}