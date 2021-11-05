// project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;


typedef struct {
	int length;
	string *data;
	int capacity;
} Vector_city;

typedef struct {
	int length;
	float *data;
	int capacity;
} Vector_sum;


// FUNCTIONS VECTOR_CITY

void init_c(Vector_city *v) {
	v->length = 0;
	v->capacity = 1;
	v->data = new string[v->capacity];
}

void push_c(Vector_city *v, string word) {
	if (v->length >= v->capacity) {
		v->capacity *= 2;
		string *new_data = new string[v->capacity];
		for (int i = 0; i < v->length; i++)
		{
			new_data[i] = v->data[i];
		}
		delete[] v->data;
		v->data = new_data;
	}
	v->data[v->length] = word;
	v->length++;
}

void v_clear_c(Vector_city *v) {
	delete[] v->data;
	init_c(v);
}

// FUNCTIONS VECTOR_SUM

void init_s(Vector_sum *v) {
	v->length = 0;
	v->capacity = 1;
	v->data = new float[v->capacity];
}

void push_s(Vector_sum *v, float ile) {
	if (v->length >= v->capacity) {
		v->capacity *= 2;
		float *new_data = new float[v->capacity];
		for (int i = 0; i < v->length; i++)
		{
			new_data[i] = v->data[i];
		}
		delete[] v->data;
		v->data = new_data;
	}
	v->data[v->length] = ile;
	v->length++;
}

void v_clear_s(Vector_sum *v) {
	delete[] v->data;
	init_s(v);
}


//  OTHER FUNCTIONS

bool check(Vector_city *v, string word)
{
	for (int i = 0; i < v->length; i++)
	{
		if (v->data[i] == word) return false;

	}
	return true;
}

int position(Vector_city *v, string word)
{
	for (int i = 0; i < v->length; i++)
	{
		if (v->data[i] == word) return i;
	}
	return NAN;
}






int main()
{
	Vector_city v;
	Vector_sum suma;
	string client_id;
	string client_name;
	string client_city;
	string towar_id;
	float towar_cena;
	string towar_name;
	int amount;
	string id_c_tmp;

	fstream client;
	fstream merchandise;
	fstream transactions;


	float sum = 0;

	init_c(&v);
	init_s(&suma);
	client.open("klienci.txt", ios::in);
	merchandise.open("towary.txt", ios::in);
	transactions.open("transakcje.txt", ios::in);

	if (client.good() && merchandise.good() && transactions.good())
	{
		while (!merchandise.eof())
		{
			string id_tmp;
			merchandise >> towar_id >> towar_name >> towar_cena;
			id_tmp = towar_id;
			transactions.seekg(0);
			while (!transactions.eof())
			{
				sum = 0;
				transactions >> client_id >> towar_id >> amount;

				if (towar_id == id_tmp)
				{
					id_c_tmp = client_id;

					sum = towar_cena * amount;

					client.seekg(0);
					while (!client.eof())
					{

						client >> client_id >> client_name >> client_city;

						int it = 0;

						if (id_c_tmp == client_id)
						{

							if (check(&v, client_name))
							{
								push_c(&v, client_name);
								push_s(&suma, sum);
							}
							else
							{
								it = position(&v, client_name);
								suma.data[it] += sum;

							}
						}
					}

				}

			}
			cout << endl;
			cout << towar_name << endl;

			for (int i = 0; i < v.length; i++)
			{
				cout << v.data[i] << " " << suma.data[i] << endl;
			}
			v_clear_c(&v);
			v_clear_s(&suma);
		}

	}

}
