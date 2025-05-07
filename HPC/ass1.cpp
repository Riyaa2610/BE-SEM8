// Design and implement Parallel Breadth First Search and Depth First Search based on
// existing algorithms using OpenMP. Use a Tree or an undirected graph for BFS and DFS .
// Measure the performance of sequential and parallel algorithms.
#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int vertices)
    {
        this->vertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (int j = 0; j < adjList[i].size(); j++)
            {
                cout << adjList[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Sequential BFS
    void BFS_Sequential(int start)
    {
        vector<bool> visited(vertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            cout << "Visited " << current << endl;

            for (int neighbor : adjList[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // Parallel BFS
    void BFS_Parallel(int start)
    {
        vector<bool> visited(vertices, false);
        queue<int> queue;
        queue.push(start);
        visited[start] = true;

        while (!queue.empty())
        {
            int current;

#pragma omp parallel shared(queue, visited)
            {

#pragma omp single
                {
                    current = queue.front();
                    queue.pop();
                    cout << "Thread " << omp_get_thread_num() << " visited " << current << endl;
                }

#pragma omp for
                for (int i = 0; i < adjList[current].size(); i++)
                {
                    if (!visited[adjList[current][i]])
                    {
#pragma omp critical
                        {
                            queue.push(adjList[current][i]);
                            visited[adjList[current][i]] = true;
                        }
                    }
                }
            }
        }
    }

    // Sequential DFS
    void DFS_Sequential(int start)
    {
        vector<bool> visited(vertices, false);
        DFSUtil_Sequential(start, visited);
    }

    void DFSUtil_Sequential(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << "Visited " << v << endl;

        for (int u : adjList[v])
        {
            if (!visited[u])
                DFSUtil_Sequential(u, visited);
        }
    }

    // Parallel DFS
    void DFS_Parallel(int start)
    {
        vector<bool> visited(vertices, false);
        DFSUtil(start, visited);
    }

    void DFSUtil(int v, vector<bool> &visited)
    {

#pragma omp critical
        {
            visited[v] = true;
            cout << "Thread " << omp_get_thread_num() << " visited " << v << endl;
        }

#pragma omp parallel for
        for (int i = 0; i < adjList[v].size(); i++)
        {
            int u = adjList[v][i];
            if (!visited[u])
            {
                DFSUtil(u, visited);
            }
        }
    }
};

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 1);
    g.addEdge(2, 4);

    g.printGraph();

    double start, end;

    cout << "\n--- BFS Sequential ---\n";
    start = omp_get_wtime();
    g.BFS_Sequential(0);
    end = omp_get_wtime();
    cout << "BFS Sequential Time: " << (end - start) << " seconds\n";

    cout << "\n--- BFS Parallel ---\n";
    start = omp_get_wtime();
    g.BFS_Parallel(0);
    end = omp_get_wtime();
    cout << "BFS Parallel Time: " << (end - start) << " seconds\n";

    cout << "\n--- DFS Sequential ---\n";
    start = omp_get_wtime();
    g.DFS_Sequential(0);
    end = omp_get_wtime();
    cout << "DFS Sequential Time: " << (end - start) << " seconds\n";

    cout << "\n--- DFS Parallel ---\n";
    start = omp_get_wtime();
    g.DFS_Parallel(0);
    end = omp_get_wtime();
    cout << "DFS Parallel Time: " << (end - start) << " seconds\n";

    return 0;
}

//compile with: g++ -fopenmp -o ass ass_1.cpp
//./ass