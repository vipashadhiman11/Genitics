#include<iostream>
#include <list>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include <conio.h>
#include<vector>
#include<unordered_map>
#include<ctime>


#define W 0
#define G 1
#define B 2
using namespace std;
int start_s=clock();
vector<vector<int> > myPath;
vector<int> pathCost;
int n,cost_index=0,edges = 0;
int *cost,*dist,**edge_weight;
int count_path=0;

class Graph
{
    list<int> *adj; // Pointer to an array containing adjacency lists

    // A recursive function used by printAllPaths()
    void printAllPathsUtil(int , int , bool [], int [], int &);

public:
    Graph();   // Constructor
    void addEdge(int u, int v);
    void printAllPaths(int s, int d);
};

Graph::Graph()
{
    adj = new list<int>[n];
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v); // Add v to u’s list.
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[n];

    // Create an array to store paths
    int *path = new int[n];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_index);
}

int distance_calc(int s,int d)
{
	int weight;
	if(d == s)
	{
	   	return 0;
    }


	for(int k = 0; k < edges;k++)
   				{

   					if((edge_weight[k][0] == s) && (edge_weight[k][1] == d))
   					{
   						 weight = edge_weight[k][2];
   						 break;
					}
				}

     return weight;
 }

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index)
{
    // Mark the current node and store it in path[]
	visited[u] = true;
    path[path_index] = u;
    path_index++;
	 int cost_var=0;
	 int s = path[0],i;
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
    	vector<int> newRow;
    	count_path++;
        for ( i = 0; i<path_index-1; i++)
        {
			cout << path[i]+1 << " -> ";
			cost_var += distance_calc(s,path[i]);
			s = path[i];
			newRow.push_back(path[i]+1);
	    }
        cout<<path[path_index-1]+1;
        newRow.push_back(path[path_index-1]+1);
        myPath.push_back(newRow);
		cost_var += distance_calc(s,path[i]);


        cost[cost_index++]=cost_var;
        pathCost.push_back(cost_var);
        cout<<"\t Cost: "<<cost_var<<endl<<endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}

// Function To print only the unique (non-repeated) stored paths and all the costs
void printUtil() {

    int i,j;
	for(i=0; i<myPath.size(); i++) {
		cout<<endl<<endl;
		for(j=0; j<myPath[i].size()-1; j++) {
			cout<<myPath[i][j]<<" -> ";
		}
		cout<<myPath[i][j];
		cout<<"\t Cost: "<<pathCost[i];
	}
}


// Function to remove the repeated paths and their costs
void delRepeat() {
	int flag=0;
	for(int i=0; i<myPath.size(); i++) {
		unordered_map<int, int> map;
		for(int j=0; j<myPath[i].size(); j++) {
			int key=myPath[i][j];
			if(map.count(key)!=0) {
				map[key]++;
			}
			else {
				map[key]=1;
			}
		}
		for(int k=0; k<myPath.size(); k++) {
			if(k==i) {
				continue;
			}
			flag=0;
			if(myPath[i].size() >= myPath[k].size()) {
				for(int j=0; j<myPath[k].size(); j++) {
					int key=myPath[k][j];
					if(map.count(key)==0) {
						flag = 1;
						break;
					}
					else {
                        map[key]--;
					}
				}
				if(flag==0) {
					cost[k]=0;
				}
			}
		}
	}
    int r=0;
    for(int i=0; i<myPath.size(); i++, r++) {
        if(cost[r]==0) {
            myPath.erase(myPath.begin() + i);
            pathCost.erase(pathCost.begin() + i);
            i--;
        }
    }

    printUtil();
}

class node
{
	public:


          int *adj;

          node()
          {

            adj=new int[n];

            for(int i=0;i<n;i++)
            	adj[i]=-1;
           }

};

// Function to print the maximum path cost value
void maxim() {
    int max = pathCost[0];
    for(int i=1; i<pathCost.size(); i++) {
        if(pathCost[i] > max) {
            max=pathCost[i];
        }
    }
    cout<<endl<<endl<<endl;
    cout<<"optimized path cost value using HGTO algorithm is: "<<max<<endl;
}

int main()
{

	cout << "Enter the number of nodes:  ";
	cin >> n;
	int** in_out = new int*[n];

	for(int i = 0; i < n; ++i)
    {
		in_out[i] = new int[2];
	}

	cost=new int[n];
	for(int i = 0; i < n ;i++)
	{
		for(int j = 0; j < 2; j++)
		{
			in_out[i][j] = 0;
		}
	}
	node *nodes = new node[n];

	int a,x;
	Graph g;
	for(int i = 0; i < n ;i++)
    {

    	cout <<"Enter the number of nodes adjacent to "<<i+1<<" node: ";
    	cin >>a;
		in_out[i][1] = a;
		edges += in_out[i][1];
    	for(int j = 0; j < a; j++)
    	{
    		cout << "\tNode "<<j+1<<")  ";
    		cin >> x;
    		nodes[i].adj[j] = x-1;
    		in_out[x-1][0]++;
    		g.addEdge(i,x-1);

		}
    }

	edge_weight = new int*[edges];
	for(int i = 0; i < edges; ++i)
    {
		edge_weight[i] = new int[3];
	}
	int i = 0;

	for(int k = 0; k < n ;k++)
	{
		for(int j = 0; j < in_out[k][1]; j++)
		{
			edge_weight[i][0] = k;
			edge_weight[i][1] = nodes[k].adj[j];
			edge_weight[i][2] = in_out[edge_weight[i][0]][0] +in_out[edge_weight[i][1]][1];

			i++;

		}
	}

	int v,u,weight,source,destination;
	cout<<"\nEnter the source node: ";
	cin>>source;
	cout<<"\nEnter the destination node: ";
	cin>>destination;
	cout<<"\n ITERATION NUMBER: 1"<<endl;
    cout<<"\nFollowing are all different paths from source node "<<source<<" to destination node "<<destination<<endl;
    g.printAllPaths(source-1, destination-1);  // To print all paths
    cout<<"\n ITERATION NUMBER: 2"<<endl;
    getch();
    cout<<"\nFollowing are the clustered paths using HGTO algorithm from source node "<<source<<" to destination node "<<destination<<endl;
    delRepeat(); // To remove repeated paths and then, print unique paths only
    maxim(); // To print max path cost value
int stop_s=clock();
cout << "time in ms: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;

}


