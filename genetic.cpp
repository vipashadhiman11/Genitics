#include<iostream>
#include <list>
#include<iomanip>
#include<cmath>
#include<cstdlib>


#define W 0
#define G 1
#define B 2
using namespace std;
int start_s=clock();
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
    	count_path++;
        for ( i = 0; i<path_index-1; i++)
        {		
			cout << path[i]+1 << " -> ";
			cost_var += distance_calc(s,path[i]);
			s = path[i];
			
	    }
        cout<<path[path_index-1]+1;
        cost_var += distance_calc(s,path[i]);
        
     
        cost[cost_index++]=cost_var;
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



int no_digit(int x)
{
	int count = 0;
	while(x!=0)
	{
		x=x/10;
		count++;
	}
	return count;
}

void create_bins(long double *x[],int n)
{
	x[0][5] = 0;
    x[n-1][6] = 1;
  	for(int i=0;i<n-1;i++)							
	{
		double a= trunc(10 * x[i][4]) / 10;
		x[i+1][5] = a+0.1;
		x[i][6] = a+0.1;
		
	}
	
}

int dec_bin(int dec)
{
	    int rem,i=1;
		long sum=0;

    do
    {
        rem=dec%2;
        sum=sum + (i*rem);
        dec=dec/2;
        i=i*10;
    }while(dec>0);
   
    return sum;

}

int bin_dec(int bin)
{
	int base=1,rem=0,dec=0;
	while(bin>0)
	{
		rem=bin%10;
		dec=dec+rem*base;
		base=base*2;
		bin=bin/10;
	}
	return dec;
}


void crossover(long double *y[],int n)
{
	for(int i = 0;i < n; i=i+2)				
	{
		if(i+1 < n)
		{
			int s1 = y[i][2];
			int s2 = y[i+1][2];
			int t1,t2;
		
			int n1 = no_digit(y[i][2]);
		    int n2 = no_digit(y[i+1][2]);
	    	n1=n1-2;
	    	n2=n2-2;
	    	int n1n = n1, n2n = n2;
	    	
	    	while(n1)
	    	{
			  t1= s1 % 10;
			   s1 /= 10;
			   n1--;
			}
			while(n2)
	    	{
			  t2= s2 % 10;
			   s2 /= 10;
			   n2--;
			}
			
			if(t1!=t2)
			{
				y[i][3]=y[i][2];
				y[i+1][3]=y[i+1][2];
				if(t1==0)
				{
						
						y[i][3]+=pow(10,n1n-1);
						y[i+1][3]-=pow(10,n2n-1);
				}
				else
				{
						y[i][3]-=pow(10,n1n-1);
						y[i+1][3]+=pow(10,n2n-1);
				}	
			}
			else
			{
				y[i][3]=y[i][2];
				y[i+1][3]=y[i+1][2];
			}
	   }
	   else
	   {
			y[n-1][3]=y[n-1][2];
		}
	}
}

void mutation(long double *y[],int n)
{
		for(int i = 0;i < n; i++)
	{
			int t1;
			if(y[i][0]<0.2)
			{
				int s1 = y[i][3];
				for(int j = 0; j<3; j++)
				{
					t1= s1 % 10;
			        s1 /= 10;
				}
				if(t1==0)
				{
						y[i][4]=y[i][3]+pow(10,2);
				}	
				else
				{
						y[i][4]=y[i][3]-pow(10,2);
				}	
			}
			else
			{
				y[i][4]=y[i][3];
			}
  }		
	
}

void tab(long double *x[],int n,int sum)
{
	double cumu=0;
	for(int i=0;i<n;i++)							           //Probability
	{
		x[i][3]=x[i][2]/sum;
		cumu+=x[i][3];
		x[i][4]=cumu;
	}
	
	create_bins(x,n);
                                                              //display 
	cout<<"Path "<<setw(10)<<" Chromosome "<<setw(6)<<"x "<<setw(8)<<"f(x)=x"<<setw(15)<<"Probability"<<setw(15)<<" Cumm prob"<<setw(6)
	<<" bin min "<<setw(6)<<" bin max "<<endl;
	cout<<endl;
	for(int i=0;i<n;i++)
	{ 
		cout<<i+1<<" "<<setw(10)<<x[i][0] <<setw(10)<<x[i][1]<<setw(8)<<x[i][2]<<setw(15)<<x[i][3]<<setw(15)<<x[i][4]<<setw(6)<<x[i][5]<<setw(6)<<x[i][6
		]<<endl;
	
	}
	
	cout<<endl<<endl;
}


void tab1(long double *x[],int n)
{
	/*----------------------------- table-1-----------------------------
	col 0 - chromosome
	col 1- x
	col 2- f(x)=x
	col 3- probability
	col 4- cumm prob
	col 5- min bin
	col 6- max bin
*/
int sum =0;

	for(int i=0;i<n;i++)									//binary,x^2
	{
	    
		x[i][1]=cost[i];
		x[i][0]=dec_bin(x[i][1]);
		x[i][2]=x[i][1];
		sum+=x[i][2];	
	}
	tab(x,n,sum);
}


void tab3(long double *x[],long double *y[],int n)
{
	/*----------------------------- table-1-----------------------------
	col 0 - chromosome (mutation from tab1)
	col 1- x (bin to dec)
	col 2- f(x)=x
	col 3- probability
	col 4- cumm prob
	col 5- min bin
	col 6- max bin
*/
cout<<"\n***************FITNESS OF NEW GENERATION**************\n";
int sum =0;

	for(int i=0;i<n;i++)									//binary,x^2
	{
	    
		x[i][0]=y[i][4];
		x[i][1]=bin_dec(x[i][0]);
		x[i][2]=x[i][1];
		sum+=x[i][2];	
	}
	tab(x,n,sum);
	cout<<endl<<endl<<endl;
}


void tab2(long double *x[], long double *y[],int n)
{
	//-----------------------------table 2------------------------------
	/*
	col 0 random no.
	col 1 respective path no. 
	col 2 binary of respective path (selection)
	col 3 crossover
	col 4 mutation
	*/
	cout<<"\n***************SELECTION OF NEW GENERATION**************\n";
		for(int i = 0; i < n; i++)
	   {
		int b = rand() % 1000;
		y[i][0] = b/1000.0;
		for(int j = 0; j < n; j++ )
		{		
	     	if(x[j][5] <= y[i][0] && x[j][6] > y[i][0])          //checked for bin
		   {
		    	y[i][1] = j+1;                                   //bin no.
		    	y[i][2] = x[j][0];
				break;							                //selection
		   }
	   }
	}
	crossover(y,n);
    mutation(y,n);
        															// display	
   cout<<"Random "<<setw(6)<<" Bin no. "<<setw(6)<<" Selection "<<setw(10)<<" Crossover "<<setw(10)<<" Mutation "<<endl;
	for(int i = 0; i < n; i++)
	{
	   cout<<y[i][0]<<setw(10)<<y[i][1]<<setw(12)<<y[i][2]<<setw(10)<<y[i][3]<<setw(10)<<y[i][4]<<endl;
    }	
    cout<<endl<<endl<<endl;
}


int max(long double *x[], int n)
{
	int m = x[0][2];
	for(int i = 1; i < n; i++)
	{
		if(m < x[i][2])
		   m= x[i][2];
	}
	return m;
}

int major(long double *x[], int n , int maximum_x)
{
	int count = 0;
	for(int i = 0; i < n; i++)
	{
		if(x[i][2] == maximum_x)
		{
			count++;
		}
	}
	
	if(count >= n-1)
	  return 1;
	else 
	return 0;  
}

void input()
{
	int sum=0,k=1;
	double cumu=0;
	
	int n=count_path;
    long double** x = new long double*[n]; //Table 1
	for(int i = 0; i<n; ++i)
    	x[i] = new long double[7];
    	 
   	 long double** y =  new long double*[n]; //Table 2
	for(int i = 0; i<n; ++i)
    	y[i] = new long double[7];
	
	cout<<endl<<endl;
    tab1(x,n);
    int maximum_x = max(x,n);
    cout <<"maximun_x "<<maximum_x<<endl;
    
    while(k<=50)
    {
	cout<<"\n ITERATION NUMBER: "<<k<<endl;
	tab2(x,y,n);
   	tab3(x,y,n);
  	int major_x = major(x,n,maximum_x);
   	if(major_x == 1)
   	  break;
   	
   	k++;
	}
    
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
		//cout<<endl;
	}

	int v,u,weight,source,destination;
	cout <<"\nEnter the source node: ";
	cin >> source;
	cout <<"\nEnter the destination node: ";
	cin >> destination;
   cout <<"\nFollowing are all different paths from source node " << source<< " to destination node " << destination << endl;
    g.printAllPaths(source-1, destination-1);
    input();
    int stop_s=clock();
cout << "time in ms: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
	
}

