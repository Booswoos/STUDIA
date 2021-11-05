#include <iostream>
#include <vector>
#include <queue>
#include<time.h>
#include <string>
#include <stack>

using namespace std;

//ZMIENNE GLOBALNE
int w = 10;
string blocks[4] = { "####","#++#","#--#","++++" };


//INICJALIZACJA WEKTORA KOLEJEK
void init_vec(vector<queue <string> > &v, int w, int k, int b)
{
	for (int i = 0; i < k; i++)
	{
		v.push_back(queue<string>());


		for (int j = 0; j < b; j++)
		{
			v[i].push("####");
		}
	}
}

//WARUNEK GRY
bool game_condition(vector<queue<string>> v, int w, int k)
{
	for (int i = 0; i < k; i++)
	{
		if (v[i].size() >= w - 1)
			return 0;
	}
	return 1;
}

//WYPISYWANIE PLANSZY
void print(vector<queue<string>> v, int w, int k, int b)
{
	for (int i = 0; i < w - 1; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (v[j].size() >= 1 && !v[j].empty())
			{
				cout << v[j].front();

				cout << "   ";
				v[j].pop();
			
			}
			else if (v[j].empty())
				cout << "       ";
		}

		//cout << i;
		cout << endl;
	}

	for (int i = 1; i < k * 6; i++)
	{
		cout << "-";
		if ((i) == (k * 3))
			cout << "- [*] -";
	}
	cout << endl;
	int ctr=0;
	for (int i = 0; i < k; i++)
	{
		if(i==0)
		cout << "  " << ctr << "   ";
		else
		cout <<"   "<<ctr<<"   ";
		ctr++;
	}

	cout << endl;
}
//GENEROWANIE LOSOWE
int rng(int n)
{
	int round = rand() % n;
	return round;
}
//DODANIE BLOKU
void add_blocks(vector<queue <string> > &v, int k)
{
	int ctr = 0;

	for (int i = 0; i < k; i++)
	{
		if (ctr % 5 == 3)
			v[i].push(blocks[2]);
		else if (ctr % 5 == 2)
			v[i].push(blocks[1]);
		else if (ctr % 6 == 5)
			v[i].push(blocks[3]);
		else
			v[i].push(blocks[0]);
		ctr++;
	}
}
//SPRAWDZENIE MOZLIWOSCI STRZALU
bool check_shoot(vector<queue <string> > v, int col, int k)
{

	if (col < 0 || col >= k)return 0;
	if (v[col].empty())return 0;
	return 1;
}
//REVERSE 
void rev_first(vector<queue<string>> &v,int col,stack<string>&st)
{
	while (!v[col].empty())
	{
		st.push(v[col].front());
		v[col].pop();
	}
	while (!st.empty())
	{
		v[col].push(st.top());
		st.pop();
	}
}

//STRZAL I PUNKTY
int shoot_point(int column, vector<queue<string>> &v)
{	
	int bonus=0;
	
	string block = v[column].back();
	if (block == blocks[0])bonus = 1;
	else if (block == blocks[1])bonus = 3;
	else if (block == blocks[2])bonus = -3;
	else if (block == blocks[3])bonus = 5;
	
	stack<string> st;
	
	rev_first(v, column, st);
	v[column].pop();
	rev_first(v, column, st);


	return bonus;
}

int main()
{
	srand(time(NULL));
	int  k,b,n,r;
	vector <queue<string>> v;
	int changer;

	// WPROWADZENIE DANYCH
	
	do {
		cout << "Podaj K i B" << endl;
		cin >> k >> b;
	} while (b<0||b>=w);

	do {
		cout << "Podaj R i N" << endl;
		cin >> r >> n;
	} while (r > n);

	//INICJALIZACJA ZMIENNYCH
	init_vec(v, w, k, b);
	changer = rng(n)+r;
	int counter=0,points=0;


	cout << "Dodawanie co " << changer << " rund" << endl;
	while (game_condition(v,w,k))
	{
		cout << "LICZBA PUNKTOW:" << points;
		cout << endl;
	int column;
		if (counter == changer)
		{
			counter = 0;
			add_blocks(v, k);

		}
		print(v, w, k, b);
		counter++;

		do {
			cout << "Podaj kolumne do strzalu (0,1,...)" << endl;
			cin >> column;
			
		} while (!check_shoot(v, column,k));
		points+=shoot_point(column, v);
	}
	cout << "PRZEGRALES ZDOBLES "<<points<<" PUNKTOW";
	
   
}
