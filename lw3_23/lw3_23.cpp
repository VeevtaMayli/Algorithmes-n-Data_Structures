/*
23. Имеется  сеть  автомобильных  дорог.  Для каждой  дороги
известна ее длина. Один из городов является столицей. Требуется
вывести список длин вторых по минимальности путей из столицы  в
другие города. Допускается  присутствие  циклических  путей.  В
некоторые города вторых путей может не оказаться (12).
Матвеев Илья
ИПС-2017
*/

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> findShortPath(vector<vector<int>> a, const int n, int st)
{
	vector<bool> isVisited(n);
	vector<pair<int, int>> c(n);
	for (int i = 0; i < n; i++)
	{
		c[i].first = INT_MAX;
		isVisited[i] = false;
	}
	c[st].first = 0;
	int index = 0, u = 0;
	for (int i = 0; i < n; i++)
	{
		int min = INT_MAX;

		for (int j = 0; j < n; j++)
		{
			if (!isVisited[j] && c[j].first < min)
			{
				min = c[j].first;
				index = j;
			}
		}
		u = index;
		isVisited[u] = true;

		for (int j = 0; j < n; j++)
		{
			if (!isVisited[j] && a[u][j] && c[u].first != INT_MAX && (c[u].first + a[u][j] < c[j].first))
			{
				c[j].first = c[u].first + a[u][j];
				c[j].second = u;
			}
		}
	}
	return c;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Incorrect arguments count\n"
				  << "Usage: lw3_23.exe <input file>\n";
		return 1;
	}

	std::ifstream input((std::string)argv[1]);

	if (!input.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	if (input.eof())
	{
		std::cout << "Empty input file\n";
		return 1;
	}

	int nTown, nRoad; // количество городов и дорог
	input >> nTown >> nRoad;

	vector<vector<int>> d(nTown);
	vector<vector<pair<int, int>>> d2(nTown);
	vector<int> d3(nTown);
	for (int i = 0; i < nTown; i++)
	{
		d[i].resize(nTown);
		d2[i].resize(nTown);
	}

	int roadCounter = nRoad;

	while (roadCounter > 0)
	{
		int i, j, w; // номера начального и конечного городов, длина дороги
		input >> i >> j >> w;
		d[i - 1][j - 1] = w;
		roadCounter--;
	}

	for (int i = 0; i < nTown; i++)
	{
		for (int j = 0; j < nTown; j++)
		{
			d2[i][j] = findShortPath(d, nTown, i)[j];
		}
	}

	int start = 0;

	for (int i = 0; i < nTown; i++)
	{
		int min = INT_MAX;
		if (i == start)
			continue;

		int parent = d2[start][i].second;
		string parents = " " + to_string(parent);

		while (parent != start)
		{
			parent = d2[start][parent].second;
			parents += " " + to_string(parent);
		}
		parents += " ";

		for (int j = 0; j < nTown; j++)
		{
			if (j == i || j == start) continue;

			if (parents.find(" " + to_string(j) + " ") == string::npos && d2[start][j].first != INT_MAX && d2[j][i].first != INT_MAX)
			{
				int newShortPath = d2[start][j].first + d2[j][i].first;
				if (newShortPath < min)		
				{
					min = newShortPath;
				}
			}
		}

		d3[i] = min;
	}

	for (int i = 1; i < nTown; i++)
	{
		if (d3[i] != INT_MAX)
			cout << d3[i];
		else
			cout << "No";
		cout << endl;
	}
}
