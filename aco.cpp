#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<math.h>
int cc=0;
int alpha=1,beta=1;

// A structure to represent an adjacency list node
void algo(struct Graph* graph);
struct AdjListNode
{
	float heuristic;
	float pheromone;
	float probability;
	int dest;
	int visited;

    struct AdjListNode* next;
};


// A structure to represent an adjacency list
struct AdjList
{
	int data;
    int visited;
	struct AdjListNode *head;  // pointer to head node of list
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{   int key;
    struct AdjListNode* endNode;
    struct AdjListNode* startNode;
    int V;
    struct AdjList* array;
};


// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
	    (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices

struct Graph* createGraph(int V)
{
    int i;
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

     // Initialize each adjacency list as empty by making head as NULL

    for (i=0;i<V;++i){
    graph->array[i].head = NULL;
	graph->array[i].visited = 0;
	graph->array[i].data =i+1 ;
}
    return graph;
}


// Adds an edge to an directed graph
 void addEdge(struct Graph* graph, int src, int dest)
     {
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    newNode->heuristic=2;
	newNode->pheromone=1;
	newNode->visited=0;
	newNode->probability=0;
	graph->array[src].data=src+1;

	graph->array[src].head = newNode;
 }

struct pathNode
  {
       int dest;
       struct pathNode* next;
    };
struct pathList
{
    int priority;
    float strength;
    struct pathNode *head;  // pointer to head node of list
};

struct Path
  {
	int cc;
	struct pathList* array;
  };
struct pathNode* newPathNode(int dest)
   {
	struct pathNode* newNode = (struct pathNode*) malloc(sizeof(struct pathNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
     }
struct Path* createPath(int cc)
   {
	     int i;
	     struct Path* path = (struct Path*) malloc(sizeof(struct Path));
       path->cc = cc;

       path->array = (struct pathList*) malloc(cc * sizeof(struct pathList));

       for (i = 0; i < cc; ++i){
		path->array[i].head = NULL;
		path->array[i].priority=0;
		path->array[i].strength=0.0;
	 }
	 return path;
      }

void addPathEdge(struct Path* path, int src, int dest)
   {
       struct pathNode* newNode = newPathNode(dest);
       newNode->next = path->array[src].head;
       path->array[src].head =newNode;
      }

// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
	struct AdjListNode* traverse = graph->array[v].head;
	printf("\n Adjacency list of vertex %d\n ", graph->array[v].data);
	printf("%d",traverse->dest);
	while (traverse->next != NULL)
	{
	    traverse= traverse->next;
	    printf("->%d", traverse->dest);

		}
	printf("\n");
      }
 }
void printPath(struct Path* graph)
{
    int v;
    for (v = 0; v < graph->cc; ++v)
    {
	struct pathNode* traverse = graph->array[v].head;

printf("\n Path %d Strenght %f\n ", v+1,graph->array[v].strength);
	  printf("%d",traverse->dest);
	while (traverse->next != NULL)
	{
	    traverse = traverse->next;
	    printf("->%d ", traverse->dest);
		}
	printf("\n");

    }
    getch();
}


void insertion(){
    int num,node,i,j,V,edge=0,predicate=0,s,e;
    char ch;
    struct Graph* graph;
    printf("\nEnter number of nodes in the graph : ");
    scanf("%d",&V);

     graph = createGraph(V);
    for(i=0;i<V;i++){
    printf("\n Enter number of nodes connect with %d node : ",i+1);
    scanf("%d",&num);
    if(num>=2){
    predicate++;
    }
    if(num>0){

     for(j=0;j<num;j++){
      printf("\nEnter node: ") ;
      scanf("%d",&node);
      if( (node<=V) && (node>0) ){
      addEdge(graph, i, node);
      edge++;
      }
      else{
      printf("\n This node doesn't exist Try again");
      j--;
      continue;
	 }
       }
     }
   }
	printf("\nEnter the start node of the graph: ");
	scanf("%d",&s);
	printf("\nEnter the end node of the graph :");
	scanf("%d",&e);
	graph->key=e;
	graph->startNode=graph->array[s-1].head;
	graph->endNode=graph->array[e-1].head;

    printGraph(graph);
    cc=predicate+1;
  /*  printf("\nedges are: %d",edge);
    printf("\npredicate are: %d",predicate);
    printf("\nvertices are: %d",V);        */
    printf("\n start node %d and endnode %d",s,e);
    printf("\ncomplexity is : %d",cc);
    getch();
    algo(graph);

}
void algo(struct Graph* graph)
{
    int v=0,temp1;
    int maxprob;
    int count=cc;
    int start,visit=0,p=0;
    float sum=0;
	float denominator;
	struct AdjListNode* traverse;
		struct AdjListNode* ptr,*feasible,*temp;

   struct Path* path= createPath(cc);
    while(count>0)
       {
	//	printf("check1");
	  //	getch();
		start=v;sum=0;
		visit=0;
		if(graph->array[v].visited==0){
		graph->array[v].visited+=1;
		visit++;
		}
		ptr=NULL;
		traverse = graph->array[v].head;

			addPathEdge(path,p,v+1);


		do
		{
	    //	    printf("check2");
	      //	    getch();
		   if((traverse->visited==0)){
		traverse->visited+=1;
		visit++;
		}
	       feasible=traverse;
		denominator=0.0;
		temp=traverse;

			while(temp)
			  {  //     printf("check3");
		//	  getch();
				denominator=denominator+(pow(temp->pheromone,alpha)*pow(temp->heuristic,(beta*-1)));
				temp=temp->next;
			  }
			  temp=traverse;
			while (traverse)
			    {
			   //	printf("check4");
			   //	getch();
				float numer=(pow(traverse->pheromone,alpha)*pow(traverse->heuristic,(beta*-1)));
				traverse->probability=numer/denominator;
				traverse=traverse->next;
			     }

		       ptr=feasible;
		       while(feasible->next){
			    //	  printf("check4");
			     //	  getch();
				 if(ptr->probability>feasible->next->probability)
					   ;
				else if(ptr->probability==feasible->next->probability)
				      {
					    if(ptr->dest==graph->key)
						    ;
					    else if(feasible->next->dest==graph->key){
					       ptr=feasible->next;

							}
						else{
							if(feasible->next->visited==0)
								ptr=feasible->next;
							}
				      }
				else
					  ptr=feasible->next;

			    feasible=feasible->next;

		 }

       ptr->visited+=1;
       ptr->pheromone=pow(ptr->pheromone,alpha)+pow(ptr->heuristic,(beta*-1));
       ptr->heuristic*=2.0;
       sum+=ptr->pheromone;
//    printf("\nsum value: %f  %f",ptr->pheromone,ptr->heuristic);
  //  getch();
       path->array[p].strength=sum;

       start=ptr->dest;
    //  printf("\nchoose path %f",start);


	       addPathEdge(path,p,ptr->dest);
       if(start!=graph->key) {
	traverse=ptr;

	}
       else{
	    if(visit==0)
	      {
	//	printf("\nvisit come");
      //		getch();
	     path->array[p].head=NULL;
	      p--;
	      // start=graph->key;
	      count++;
	      }
	    else {
	    }
       }
       temp1=ptr->dest;
    traverse = graph->array[temp1-1].head;

    }while(start!=graph->key);
    p++;
    count--;

    }


printPath(path);
	}

int main()
{
    clrscr();
    insertion();
    getch();
    return 0;
}


