#include <iostream>
#include<string>

using namespace std;

const int x_diff = 3;
const int y_diff = 6;

struct coordinates{
	int x;
	int y;
};

//INICJALIZACJA TABLICY
void inicjaliztion(char tab[31][61])
{

	for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j < 61; ++j)
		{

			if (i == 0 || j == 0 || i == 30 || j == 60 || i % 3 == 0 || j % 6 == 0)
			{
				if (i == 0 && j == 0 || i == 30 && j == 60 || i % 3 == 0 && j % 6 == 0)
					tab[i][j] = '+';
				else if (i % 3 == 0 || i == 30)
					tab[i][j] = '-';
				else if (j % 6 == 0 || j == 60)
					tab[i][j] = '|';
				else
					tab[i][j] = '0';
			


			}
			else tab[i][j] =' ';
		}
		
	}

}
 

//WYPELNIENIE STRZAL
void fill_shoot(int x,int y,char action,char tab[31][61]) {  
	
	for (int i=x; i<x+2; i++)
	{
		for(int j=y-2;j<y+3;j++)
		{
			tab[i][j] = action;
		}
	}

}

//WYPELNIENIE PIONEK
void fill_normal(int x, int y, char action,char tab[31][61]) {

	for (int i = x; i < x + 2; i++)
	{
		for (int j = y - 1; j < y + 2; j++)
		{
			tab[i][j] = action;
		}
	}

}

//POZYCJA STARTOWA
void start_position(char tab[31][61])
{
	//A4 A7 D1 D10 G1 G10 J4 J7
	fill_normal(10, 3, '#',tab);
	fill_normal(19, 3, 'O',tab);
	fill_normal(1, 21, '#',tab);
	fill_normal(28, 21, 'O',tab);
	fill_normal(1, 39, '#',tab);
	fill_normal(28, 39, 'O',tab);
	fill_normal(10, 57, '#',tab);
	fill_normal(19, 57, 'O',tab);
}

//PISZ TABLICE
void print(char tab[31][61]) {
	char letter = 'A';
	int number=1;
	for (int x=0; x < 10; x++)
	{
		cout << "   " << letter << "  ";
		letter++;
	}
	cout << endl;
	for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j < 61; ++j)
		{
			cout << tab[i][j];
			
		}if ((i+1)% 3 == 0) { cout << " " << number; number++; }
		cout << endl;
	}
}

//STRZELAJ
void shoot(char tab[31][61],coordinates corr)
{
	int x1 = corr.x;
	int y1 = corr.y;
	
	
	if (tab[x1][y1] ==' ')
	{ 
		fill_shoot(x1, y1, '.',tab);
	}

		
}

//ZMIANA WPROWADZENIE NA WSPOLRZEDNE POLA
void swap_string_to_int(string line,coordinates *xy)
{
	
	int tmp = line.length();
	if (tmp == 2) {
		
		switch (line[0]) {
		case'A':xy->y = 3; break;
		case'B':xy->y = 9; break;
		case'C':xy->y = 15; break;
		case'D':xy->y = 21; break;
		case'E':xy->y = 27; break;
		case'F':xy->y = 33; break;
		case'G':xy->y = 39; break;
		case'H':xy->y = 45; break;
		case'I':xy->y = 51; break;
		case'J':xy->y = 57; break;
		}

		switch (line[1]) {
		case'1':xy->x = 1; break;
		case'2':xy->x = 4; break;
		case'3':xy->x = 7; break;
		case'4':xy->x = 10; break;
		case'5':xy->x = 13; break;
		case'6':xy->x = 16; break;
		case'7':xy->x = 19; break;
		case'8':xy->x = 22; break;
		case'9':xy->x = 25; break;
			//	case'10':xy.from[i] = 28; break;
		}
	

	}

	if (tmp == 3)
	{
		switch (line[0]) {
		case'A':xy->y = 3; break;
		case'B':xy->y = 9; break;
		case'C':xy->y = 15; break;
		case'D':xy->y = 21; break;
		case'E':xy->y = 27; break;
		case'F':xy->y = 33; break;
		case'G':xy->y = 39; break;
		case'H':xy->y = 45; break;
		case'I':xy->y = 51; break;
		case'J':xy->y = 57; break;
		}
		xy->x = 28;
	}



}
//SPRAWDZA KOLEJKE
bool check_turn(char tab[31][61], int x, int y, char turn )
{
	if (tab[x][y] == turn)return true;
	else return false;
}
//ZMINA POLA
void change_position(char &turn,char tab[31][61],coordinates f,coordinates t)
{
	int x1 = f.x;
	int y1 = f.y;
	int x2 = t.x;
	int y2 = t.y;

	fill_normal(x1, y1, ' ',tab);
	fill_normal(x2, y2, turn,tab);
	if (turn == 'O') { turn = '#';}
	else if (turn = '#') { turn = 'O';}

}

//CZY RUCH/STRZAL MOZLIWY
bool is_possible(coordinates f, coordinates t, char tab[31][61])
{
	int a=abs(f.x - t.x)/x_diff;
	int b=abs(f.y - t.y)/y_diff;
	
	if (a==b)
	{
		int i = f.x;
		int j = f.y;
		
		if (f.x > t.x)
		{
			cout << f.x << " " << f.y << endl; cout << t.x << " " << t.y << endl;
			if (f.y > t.y) 
			{
				while (i != t.x&&j != t.y)
				{
					i -= x_diff;
					j -= y_diff;
		
					if (tab[i][j] != ' ')return false;
				}
				return true;
			}
			else if (f.y < t.y)
			{
		
				while (i != t.x&&j != t.y)
				{
					i -= x_diff;
					j += y_diff;
		
					if (tab[i][j] != ' ')return false;
				}
				return true;
			}
		}

		else if (f.x < t.x)
		{
			if (f.y > t.y)
			{
				while (i != t.x&&j != t.y)
				{
					i += x_diff;
					j -= y_diff;
			
					if (tab[i][j] != ' ')return false;
				}
				return true;
			}
			else if (f.y < t.y)
			{
				while (i != t.x&&j != t.y)
				{
					i += x_diff;
					j += y_diff;
				
					if (tab[i][j] != ' ')return false;
				}
				return true;
			}
		}
	}
	if (f.x == t.x)
	{		
		if (f.y > t.y)
		{		
			
			for (int i = f.y-y_diff; i >= t.y; i -= y_diff)
			{
				
				if (tab[f.x][i] != ' ')
				{
					return false;
				}
				
			}
			return true;
		}
		if (f.y < t.y)
		{
			
			for (int i = f.y+y_diff; i<= t.y; i +=y_diff)
			{
			
				if (tab[f.x][i] !=' ')
				{
					return false;
				}
				
			}
			return true;
		}
		return false;
	}
	if (f.y == t.y)
	{		
		if (f.x > t.x)
		{
			for (int i = f.x - x_diff; i >= t.x; i -= x_diff)
			{

			
				if (tab[i][f.y] != ' ')
				{
					return false;
				}

			}
			return true;
		}
		if (f.x < t.x)
		{
			
			for (int i = f.x +x_diff; i <= t.x; i += x_diff)
			{
				
				if (tab[i][f.y] != ' ')
				{
					return false;
				}

			}
			return true;
		}
		return false;
	}
	else return false;

}

bool win(char tab[31][61], char turn)
{
	int counter = 0;
	for (int i = 1; i < 31; i+=x_diff)
	{
		for (int j = 3; j < 61; j+=y_diff)
		{
			if (tab[i][j] == turn)
			{
				
				if (i == 1 && j == 3)  //left top corener
				{
					if (tab[i + x_diff][j] != ' '&&tab[i][j + y_diff] != ' '&&tab[i + x_diff][j + y_diff] != ' ') { counter++;}
				}
				if (i == 1 && j == 57) //right top corner
				{
					if (tab[i + x_diff][j] != ' '&&tab[i][j - y_diff] != ' '&&tab[i + x_diff][j - y_diff] != ' ') { counter++;}
				}
				if (i == 28 && j == 3)  //left down corner
				{
					if (tab[i - x_diff][j] != ' '&&tab[i][j + y_diff] != ' '&&tab[i - x_diff][j + y_diff] != ' ') { counter++; }
				}
				if (i == 28 && j == 57)  //right down corner
				{
					if (tab[i - x_diff][j] != ' '&&tab[i][j - y_diff] != ' '&&tab[i - x_diff][j - y_diff] != ' ') { counter++;}
				}
				else if (i == 1&& j!=3&&j!=57) //1 row
				{
					if (tab[i - x_diff][j] != ' '&&tab[i - x_diff][j+y_diff] != ' '&&tab[i + x_diff][j] != ' '&&tab[i][j + y_diff] != ' '&&tab[i + x_diff][j + y_diff] != ' ') { counter++; }
				}
				else if (j == 3&&i!=1&&i!=28)//A column
				{
					if (tab[i + x_diff][j] != ' '&&tab[i][j - y_diff] != ' '&&tab[i + x_diff][j - y_diff] != ' '&&tab[i - x_diff][j + y_diff] != ' '&&tab[i][j + y_diff] != ' ') { counter++;}
				}
				else if (i == 28&&j != 57&&j!=3) //10 row
				{
					if (tab[i - x_diff][j] != ' '&&tab[i][j + y_diff] != ' '&&tab[i - x_diff][j + y_diff] != ' '&&tab[i][j - y_diff] != ' '&&tab[i - x_diff][j - y_diff] != ' ') { counter++;  }
				}
				else if (j == 57 && i!=28&&i!=1) //J column
				{
					if (tab[i - x_diff][j] != ' '&&tab[i][j - y_diff] != ' '&&tab[i - x_diff][j - y_diff] != ' '&&tab[i - x_diff][j+ y_diff] != ' '&&tab[i][j + y_diff] != ' ') { counter++;  }
				}
				else if(j>3&&i>1&&j<57&&i<28)
				{
					if (tab[i - x_diff][j - y_diff] != ' '&&tab[i - x_diff][j] != ' '&&tab[i - x_diff][j + y_diff] != ' '&&tab[i][j - y_diff] != ' '&&tab[i][j + y_diff] != ' '&&tab[i + x_diff][j - y_diff] != ' '&&tab[i + x_diff][j] != ' '&&tab[i + x_diff][j + y_diff]) {
						counter++; 
					}
				}


			}
		}
	}
	
	if (counter == 4)return true;
	else return false;
}
int main()
{
	//inicjalizacja zmiennych
	string move_from;
	string move_to;
	string shoot_;
	char turn = 'O';
	char arr[31][61];
	coordinates from = { 0 };
	coordinates to = { 0 };
	coordinates gun = { 0 };


	inicjaliztion(arr);
	start_position(arr);

	print(arr);

	while (!win(arr,turn)) {
		cout << "CHOOSE PAWN '" <<turn<<"'"<< endl;
		cin >> move_from;
		swap_string_to_int(move_from, &from);
		if (check_turn(arr,from.x,from.y,turn)) {
			cout << "WHERE TO GO" << endl;
			cin >> move_to;
			swap_string_to_int(move_to, &to);

			cout << endl;
		
			if (is_possible(from, to, arr))
			{
				change_position(turn, arr, from, to);
				print(arr);
				
					cout << "WHERE YOU WANT SHOOT:"<< endl;
					cin >> shoot_;
					swap_string_to_int(shoot_, &gun);
					while (!is_possible(to, gun, arr))
					{
						cout << "Wrong field, try another" << endl;
						cin >> shoot_;
						swap_string_to_int(shoot_, &gun);
					}

					shoot(arr, gun);
					print(arr);
				
			}
			else cout << "MOVE BLOCKED" << endl;
		}
		else cout << "BAD PAWN" << endl;
	}

	if (turn == 'O') { turn = '#'; }
	else if (turn = '#') { turn = 'O'; }

	cout << "WINNER IS: " << turn;

}
