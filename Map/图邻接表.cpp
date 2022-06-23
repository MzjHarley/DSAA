#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
#define MAX_VERTEX_NUM 100
#define MAX_INT 32767
typedef char VertexType;
typedef int ArcType;
/**
 *           ***************************************************************************
 *           *    VNode                 arcNode              arcNode                   *
 *           *  -----------         ---------------       ---------------              *
 *           *  |data|next|    ->   |adjvex|w|next|   ->  |adjvex|w|next|  ->   ...... *
 *           *  -----------         ---------------       ---------------              *
 *           *    VNode                 arcNode              arcNode                   *
 *           *  -----------         ---------------       ---------------              *
 *           *  |data|next|    ->   |adjvex|w|next|   ->  |adjvex|w|next|  ->   ...... *
 *           *  -----------         ---------------       ---------------              *
 *           *       .                   .                    .                 ...... *
 *           *       .                   .                    .                 ...... *
 *           *       .                   .                    .                 ...... *
 *           ***************************************************************************
 *                                             ALGraph
 */
typedef struct arcNode
{
    int adjvex;
    ArcType weight;
    struct arcNode *next;
} arcNode;
typedef struct VNode
{
    ArcType data;
    arcNode *next;
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct ALGraph
{
    int vertexNum;
    int arcNum;
    AdjList vertics;
} ALGraph;
void CreateUDN(ALGraph &G);
int LocateVex(ALGraph G, VertexType u);
void DFS_Traverse(ALGraph G);
void DFS_ALG(ALGraph G, int v, int *visit);
void BFS_traverse(ALGraph G);
void BFS_ALGraph(ALGraph G, int v, int *visit, queue<int> &q);
int main()
{
    return 0;
}
void CreateUDN(ALGraph &G)
{
    cin >> G.vertexNum >> G.arcNum;
    for (int i = 0; i < G.vertexNum; i++)
    {
        cin >> G.vertics[i].data;
        G.vertics[i].next = NULL;
    }
    VertexType v1, v2;
    ArcType w;
    for (int i = 0; i < G.arcNum; i++)
    {
        cin >> v1 >> v2 >> w;
        arcNode *arcNode1 = new arcNode;
        arcNode1->adjvex = LocateVex(G, v1), arcNode1->next = NULL, arcNode1->weight = w;
        arcNode *arcNode2 = new arcNode;
        arcNode2->adjvex = LocateVex(G, v2), arcNode2->next = NULL, arcNode2->weight = w;
        arcNode1->next = G.vertics[LocateVex(G, v2)].next, G.vertics[LocateVex(G, v2)].next = arcNode1;
        arcNode2->next = G.vertics[LocateVex(G, v1)].next, G.vertics[LocateVex(G, v1)].next = arcNode2;
    }
}
int LocateVex(ALGraph G, VertexType u)
{
    for (int i = 0; i < G.vertexNum; i++)
        if (u == G.vertics[i].data)
            return i;
    return -1;
}
/**
 * DFS_Traverse: Depth-First Search Traverse.
 * we start from some point like v, visit this point,then starting from unvisited adjacent(邻接的) points of v,
 * the graph is depth-first traversed until all vertics in the graph communicate with v are visited.
 * if there are still unvisited vertics in the graph,then another unvisited vertex is selected as the starting point,
 * and repeat the above process until all the vertics in the graph are visited.
 *                                             v1
 *                                           /    \
 *                                          v2     v3
 *                                         /  \   /  \
 *                                        v4  v5 v6-v7
 *                                         \  /
 *                                          v8
 * DFS_Traverse(from v1): v1->v2->v4->v8->v5->v3->v6->v7
 */
void DFS_Traverse(ALGraph G)
{
    int visit[G.vertexNum];
    memset(visit, 0, sizeof(int) * G.vertexNum);
    for (int i = 0; i < G.vertexNum; i++)
        if (!visit[i])
            DFS_ALG(G, i, visit);
}
void DFS_ALG(ALGraph G, int v, int *visit)
{
    cout << G.vertics[v].data << " ";
    visit[v] = 1; // it's just a tag array which records the visited points.
    arcNode *p = G.vertics[v].next;
    while (p)
    {
        if (!visit[p->adjvex])
            DFS_ALG(G, p->adjvex, visit);
        p = p->next;
    }
}
/**
 * BFS_Traverse: Breadth-First Search Traverse.
 * we start from some point like v, visit v,then visit all unvisited adjacent points of v in turn.
 * then start from the adjacent points of v, visit the unvisited adjacent points of them.
 * when we visit the vertex,we need to make the adjacent points of the first visited vertex visited  before the adjacent points of the later vertex.
 * until all vertics in the graph that communicate with v are visited.
 *                                             v1
 *                                           /    \
 *                                          v2    v3
 *                                         /  \   /  \
 *                                        v4  v5 v6->v7
 *                                         \  /
 *                                          v8
 * BFS_Traverse(from v1): v1->v2->v3->v4->v5->v6->v7->v8
 */
void BFS_traverse(ALGraph G)
{
    queue<int> q;
    int visit[G.vertexNum];
    memset(visit, 0, sizeof(int) * G.vertexNum);
    for (int i = 0; i < G.vertexNum; i++)
        if (!visit[i])
            q.push(i), BFS_ALGraph(G, i, visit, q);
}
void BFS_ALGraph(ALGraph G, int v, int *visit, queue<int> &q)
{
    while (!q.empty())
    {
        if (!visit[v])
        {
            cout << G.vertics[v].data << " ";
            visit[v] = 1;
            for (arcNode *p = G.vertics[v].next; p != NULL && !visit[p->adjvex]; p = p->next)
                q.push(p->adjvex);
            q.pop();
            BFS_ALGraph(G, q.front(), visit, q);
        }
        else
        {
            q.pop();
        }
    }
}