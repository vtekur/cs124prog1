#include <iostream>
#include <climits>
#include <cmath>
#include <time.h>
using namespace std;
 

/*struct heap_element
{
	int source; 
	float dist; 
};*/
/*void add_edges_to_matrix_from_coodrinates(float** edges, float** vertex_locations, int numpoints, int dimension)
{
	for(int i = 0; i < numpoints - 1; i++)
	{
		edges[i][i] = 0; 
		for(int j = i + 1; j < numpoints; j++)
		{
			edges[i][j] = edges[j][i] = calculate_distance(vertex_locations[i], vertex_locations[j], dimension); 
		}
	}
}
void add_edges_to_matrix_random_len(float** edges, int numpoints)
{
	//cout << "Edges" << endl; 
	for(int i = 0; i < numpoints - 1; i++)
	{
		edges[i][i] = 0; 
		for(int j = i + 1; j < numpoints; j++)
		{
			edges[i][j] = edges[j][i] = ((float)(rand()))/((float)(RAND_MAX));
			//cout << edges[i][j] << endl;
		}
	}
}
float prims_shortest_path(float** edges, float* heap, bool* visited, int source, int numpoints)
{
	int vertex_count = 0;
	float shortest_path_length = 0; 
	int current_vertex = source; 
	visited[source] = true;
	float* min_arr; 
	//Condition of heap being empty is the same as number of vertices added
	//to MST being == numpoints 
	
	//cout << "Starting Prim's" << endl; 
	while(vertex_count <  numpoints)
	{
		if(vertex_count != 0)
		{
			min_arr = deletemin(heap, numpoints); 
			current_vertex = (int)min_arr[1]; 
			shortest_path_length += min_arr[0]; 
			//cout << min_arr[0] << endl; 
			visited[current_vertex] = true; 
			free(min_arr); 
		}
		vertex_count++; 
		for(int i = 0; i < numpoints; i++)
		{
			//Something to think about - do we need to iterate through all possible edges each time? 
			//Or can we store/check edges in a way that allows us to remove
			//edges that have already been searched? - This would 
			//perhaps require an adjacency list instead of a matrix
			if(i != current_vertex && !visited[i] && heap[i] > edges[current_vertex][i])
			{
				heap[i] = edges[current_vertex][i]; 
			}
		}
	}
	return shortest_path_length; 
}*/
float* deletemin(float* heap, int size)
{
	float min_len = (float)INT_MAX; 
	int min_index = -1; 
	for(int i = 0; i < size; i++)
	{
		if(heap[i] != -1 && heap[i] < min_len)
		{
			min_len = heap[i]; 
			min_index = i; 
		}
	}
	heap[min_index] = -1; 
	float* ret_val = (float*)malloc(2 * sizeof(float)); 
	ret_val[0] = min_len; 
	ret_val[1] = min_index;
	return ret_val;
}
void generate_vertex_locations(float** vertex_locations, int numpoints, int dimension)
{
	for(int i = 0; i < numpoints; i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			vertex_locations[i][j] = ((float)(rand()))/((float)(RAND_MAX)); 
		}
	}
}
float calculate_distance(float* point1, float* point2, int dimension)
{
	float dist = 0; 
	for(int i = 0; i < dimension; i++)
	{
		dist += (point1[i] - point2[i]) * (point1[i] - point2[i]); 
	}
	return (float)sqrt(dist); 
}

float prims_shortest_path(float** vertex_locations, float* heap, bool* visited, int source, int numpoints, int dimension)
{
	int vertex_count = 0;
	float shortest_path_length = 0; 
	int current_vertex = source; 
	visited[source] = true;
	float* min_arr; 
	float current_edge; 
	//Condition of heap being empty is the same as number of vertices added
	//to MST being == numpoints 
	while(vertex_count <  numpoints)
	{
		if(vertex_count != 0)
		{
			min_arr = deletemin(heap, numpoints); 
			current_vertex = (int)min_arr[1]; 
			shortest_path_length += min_arr[0]; 
			visited[current_vertex] = true; 
			free(min_arr); 
		}
		vertex_count++; 
		for(int i = 0; i < numpoints; i++)
		{
			if(i != current_vertex && !visited[i])
			{
				if(dimension == 0)
				{
					current_edge = ((float)(rand()))/((float)(RAND_MAX));
				}
				else
				{
					current_edge = calculate_distance(vertex_locations[current_vertex], vertex_locations[i], dimension);
				}
				if(heap[i] > current_edge)
				{
					heap[i] = current_edge;
				}
			}
		}
	}
	return shortest_path_length; 
}
int main(int argc, char **argv) 
{
 
   if(argc != 5)
   {
   	cout << "Invalid Argument Number" << endl; 
   }
   else
   {

   	 srand(time(NULL));
   	 const clock_t begin_time = clock();


   	 //read from command line
     int version = atoi(argv[1]); 
     int numpoints = atoi(argv[2]); 
     int numtrials = atoi(argv[3]); 
     int dimension = atoi(argv[4]);

     //reserve memory
     float** edges = (float**)(malloc(sizeof(float**) * numpoints)); 
     float* heap = (float*)malloc(sizeof(float) * numpoints); 
     bool* visited = (bool*)malloc(sizeof(bool) * numpoints); 
   	 //reserve memory for vertex coordinate locations
   	 float** vertex_locations; 
   	 if(dimension != 0)
     {
    	vertex_locations = (float**)malloc(numpoints * sizeof(float**)); 
 	 }
     for(int i = 0; i < numpoints; i++)
     {
     	if(dimension != 0)
     	{
     		vertex_locations[i] = (float*)malloc(dimension * sizeof(int)); 
     	}
     	edges[i] = (float*)(malloc(sizeof(float*) * numpoints));
     }

     //run shortest path Prim's numtrials times and average results
     float avg_mst_length = 0; 
     for(int i = 0; i < numtrials; i++)
     {
     	for(int i = 0; i < numpoints; i++)
     	{
     		//initialize heap distance to infinity
     		heap[i]= (float)INT_MAX; 
     		//visited array passed into prim's mst method 
     		visited[i] = false; 
     	}

     	if(dimension != 0)
     	{
     		//generate vertex coordinates
     		generate_vertex_locations(vertex_locations, numpoints, dimension); 
     		//calculate edge lengths and store in matrix
     		//add_edges_to_matrix_from_coodrinates(edges, vertex_locations, numpoints, dimension); 
     	}
     	avg_mst_length += prims_shortest_path(vertex_locations, heap, visited, 0, numpoints, dimension);
     }
     avg_mst_length = avg_mst_length/(float)(numtrials);
     cout << "Average MST Length: " << avg_mst_length << endl;
     cout << "Time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
     
   }
   return 0;
}