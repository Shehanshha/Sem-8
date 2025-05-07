#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>

using namespace std;

class Graph{
	
	private:
	int numvertices;
	vector<vector<int>>adj;
	
	public:
	Graph(int vertices):numvertices(vertices),adj(vertices){}
	
	void addEdge(int src, int dest)
	{
		adj[src].push_back(dest);
		adj[dest].push_back(src);
	}
	
	void viewgraph()
	{
		cout<<"Graph"<<endl;
		for(int i=0;i<numvertices;i++)
		{
			cout<<" Vertex "<<i<<" -> ";
			for(int neighbor: adj[i])
			{
				cout<<neighbor<< " ";
			}
		    cout<<endl;
		}
	}
	
	void bfs_parallel(int startvertex)
	{
		double start_time = omp_get_wtime();
		
		vector<bool> visited(numvertices,false);
		queue<int>q;
		vector<int>bfsorder;
		
		visited[startvertex] = true;
		q.push(startvertex);
		
		while(!q.empty())
		{
			int currentvertex = q.front();
			q.pop();
			bfsorder.push_back(currentvertex);
			
			#pragma omp parallel for
			for(int i=0;i<adj[currentvertex].size();i++)
			{
				int neighbor = adj[currentvertex][i];
				printf("Thread %d is processing neighbor %d of vertex %d\n",omp_get_thread_num(),neighbor,currentvertex);
				
				#pragma omp critical
				{
					if(!visited[neighbor])
					{
						visited[neighbor] = true;
						q.push(neighbor);
					}
				}
			}
		}
		double end_time = omp_get_wtime();
		
		cout<<"Bfs order"<<endl;
		for(int v : bfsorder)
		{
			cout<< v <<" ";
		}
		cout<<"Parallel DFS completed in"<<(end_time - start_time) * 1000<<"Millisecond"<<endl;
	}
	void sequential_bfs(int startvertex)
	{
		double start_time = omp_get_wtime();
		
		vector<bool>visited(numvertices,false);
		queue<int>q;
		vector<int>bfsorder;
		
		visited[startvertex] = true;
		q.push(startvertex);
		
		while(!q.empty())
		{
			int currentvertex = q.front();
			q.pop();
			bfsorder.push_back(currentvertex);
			
			for(int neighbor : adj[currentvertex])
			{
				if(!visited[neighbor])
				{
					visited[neighbor] = true;
				    q.push(neighbor);
				}
			}
		}
		double end_time = omp_get_wtime();
		cout<<"Sequential bfs order:"<<endl;
		for(int v : bfsorder)
		{
			cout<< v <<" ";
		}
		cout<<"Sequential BFS completed in "<<(end_time - start_time) *1000<<" Millisecond";
	}	
};
int main()
{
	int numvertices;
	cout<<"Enter the no.of vertices:"<<endl;
	cin>>numvertices;
	
	Graph graph(numvertices);
	
	int numedges;
	cout<<"Enter the no,of edges:"<<endl;
	cin>>numedges;
	cout<<"Enter the edges:"<<endl;
	for(int i = 0;i<numedges;i++)
	{
		int src,dest;
		cin>>src>>dest;
		
		graph.addEdge(src,dest);
	}
	graph.viewgraph();
	int startvertex;
	cout<<"Enter the startvertex:"<<endl;
	cin>>startvertex;
	
	cout<<" Parallel Breadth first search:"<<endl;
	graph.bfs_parallel(startvertex);
	cout<<endl;
	
	cout<<"Sequential Breadth first search"<<endl;
	graph.sequential_bfs(startvertex);
	cout<<endl;
	return 0;
}	