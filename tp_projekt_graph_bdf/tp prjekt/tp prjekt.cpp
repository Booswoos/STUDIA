#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;


//generate road
bool conn_gen()
{
	int number = rand() % 100;
	if (number <75)return 1;
	else return 0;
	
}

//generate adj matrix 
void adj_gen(bool **matrix, int p, int n)
{
	char iterator = -1;

	for (int i = 0; i < p; i++)
	{
		iterator++;
		//cout << char('A' + iterator) << endl;
		//cout << "A B C D E F G H I J K L " << endl;




		if (i + 1 < p && (i + 1) % n != 0)
		{

			matrix[i][i + 1] = conn_gen();


			matrix[i + 1][i] = matrix[i][i + 1];

		}
		if (i + n < p)
		{
			matrix[i][i + n] = conn_gen();


			matrix[i + n][i] = matrix[i][i + n];
		}

		for (int j = 0; j < p; j++)
		{
		//	cout <<matrix[i][j] << " ";
		}

		//cout << endl;
	}
}
// Queue struct
struct queue
{
	queue * next;
	int data;
};

//Print city map
void print_city(bool **road,char **city,int m,int n)
{
	for (int i = 0; i < m; i++)
	{

		for (int j = 0; j < n; j++)
		{

			cout << city[i][j];
			 if (road[i*n + j][i*n + j + 1] == 1) { cout << "-"; }
			 else cout << " ";
		}
		cout << endl;
		for (int j = 0; j < n; j++)
		{
			
			if (road[i*n + j][i*n + j + n] == 1) { cout << "| "; }
			else cout << "  ";
			
		}
		cout << endl;
	}
}
// Final map print
void print_finnal_map(bool **watermatrix,bool **adjmatrix,char **city,int n,int m,int p)
{
	for (int i = 0; i < m; i++)
	{
		for (int j  = 0; j < n; j++)
		{
			cout<< city[i][j]<<"";
			if (watermatrix[i*n+j][i*n+j+1] == 1) { cout << " = "; }
			else if (adjmatrix[i*n+j][i*n+j+1] == 1) { cout << " - "; }
			else cout << "   ";
		}
		cout << endl;
		for (int j = 0; j < n; j++)
		{
			if (watermatrix[i*n+j][i*n+j+n] == 1) { cout << "||";  }
			else if (adjmatrix[i*n+j][i*n+j+n] == 1) { cout << "| "; }
			else cout << "  ";
			cout << "  ";
		}
		cout << endl;
	}

}
 // Water adj matrix print
void print_water(bool **water, int p)
{

	for (int i = 0; i < p; i++)
	{

		for (int j = 0; j < p; j++)
		{

			cout << water[i][j] << " ";
		}
		cout << endl;
	}
}
 
// BFS algorithm, waterpipe creation, connectivity check
void BFS(int v,bool **matrix,bool vertex[],int p,bool **water)
{
queue *q, *start, *last; 

	q = new queue;       
	q->next = NULL;
	q->data = v;
	start = last = q;
	
	vertex[v] = true; 
	
	while (start)
	{
		v = start->data;       

		q = start;           
		start = start->next;
		if (!start) last = NULL;
		delete q;

		for (int i = 0; i < p; i++)
			if ((matrix[v][i] == 1) && !vertex[i])
			{		
				q = new queue; 
				q->next = NULL;
				q->data = i;
				if (!last) start = q;
				else last->next = q;
				last = q;
				vertex[i] = true;
				water[v][i] = 1;
				water[i][v] = 1;
				//cout << i << " " << vertex[i] << endl;
			}
	}
	delete start;
	delete last;
	
}
//connectivity check
bool Connectivity(bool vertex[],int p)
{
	for (int i = 0; i < p; i++)
	{
		if (vertex[i] == 0)
			return 0;
	}
	return 1;

}
//City array init
void init_city(char **map,int m,int n)
{
	char it = -1;
	for (int i = 0; i < m; i++)
	{

		for (int j = 0; j < n; j++)
		{

			it++;
			map[i][j] = 'A' + it;
		}
	}
}
// Connectivity array init
void init_vertex(bool vertex[], int p)
{
	for (int i = 0; i < p; i++)
	{
		vertex[i] = 0;

	}

}
// Adj matrix's init
void init_adj(bool **road, bool **water, int p)
{
	for (int i = 0; i < p; i++)
	{

		for (int j = 0; j < p; j++)
		{

			road[i][j] = 0;
			water[i][j] = 0;
		}

	}
}
//Init everything
void init_all(bool **road, bool **water,char **map, bool vertex[], int m, int n, int p)
{
	init_city(map, m, n);
	init_adj(road, water, p);
	init_vertex(vertex, p);
}

int main()
{

	srand(time(NULL));

	int m, n; //size
	cout << "podaj wymiary" << endl;
	cin >> m >> n;


	int p = m * n;

	//init arrays
	char **city_map = new char*[m];
	bool **adj_matrix = new bool*[p];
	bool *vertex=new bool[p];
	bool **water = new bool*[p];


	for (int i = 0; i < m; i++)
	{
		city_map[i] = new char[n];
	}

	for (int i = 0; i < p; i++)
	{
		adj_matrix[i] = new bool[p];
		water[i] = new bool[p];
	}

	// init all
	init_all(adj_matrix, water, city_map, vertex, m, n, p);



	
	//create adjacency matrix
	adj_gen(adj_matrix, p, n);
	//print city with road
	print_city(adj_matrix,city_map, m, n);
	
	//BFS algorithm + waterpipe creation
	BFS(0,adj_matrix,vertex,p,water);

	//Graph Connectivity
	if (Connectivity(vertex, p))cout << "CONNECTED" << endl;
	else cout << "DISCONNECTED" << endl;

	//Print final map
	print_finnal_map(water,adj_matrix ,city_map, n, m, p);
	

	return 0;
}
