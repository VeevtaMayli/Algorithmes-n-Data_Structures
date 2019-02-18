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

using namespace std;

vector<pair<pair<int, int>, pair<int, int>>> findTwoShortPath(vector<vector<int>> a, const int n, int st)
{
	vector<pair<bool, bool>> isVisited(n);
	vector<pair<pair<int, int>, pair<int, int>>> c(n);
	for (int i = 0; i < n; i++)
	{
		c[i].first.first = INT_MAX;
		c[i].second.first = INT_MAX;
		isVisited[i].first = false;
		isVisited[i].second = false;
	}

	c[st].first.first = 0;
	int index = 0, u = 0;
	bool isMarked = true;
	bool isFirst;

	while (isMarked)
	{
		int min = INT_MAX;

		for (int j = 0; j < n; j++)
		{
			if (!isVisited[j].first && (c[j].first.first < min))
			{
				min = c[j].first.first;
				index = j;
				isFirst = true;
			}

			if (!isVisited[j].second && (c[j].second.first < min))
			{
				min = c[j].second.first;
				index = j;
				isFirst = false;
			}
		}

		if (min == INT_MAX)
			break;

		u = index;

		if (isFirst)
			isVisited[u].first = true;
		else
			isVisited[u].second = true;

		isMarked = false;
		for (int j = 0; j < n; j++)
		{
			if (isFirst)
			{
				if ((!isVisited[j].first || !isVisited[j].second) && a[u][j] && c[u].first.first != INT_MAX)
				{
					if (c[u].first.first + a[u][j] < c[j].first.first)
					{
						c[j].second.first = c[j].first.first;
						c[j].first.first = c[u].first.first + a[u][j];
						c[j].first.second = u;
						isMarked |= true;
					}
					else if (c[u].first.first + a[u][j] < c[j].second.first)
					{
						c[j].second.first = c[u].first.first + a[u][j];
						c[j].second.second = u;
						isMarked |= true;
					}
				}
			}
			else
			{
				if (!isVisited[j].second && a[u][j] && c[u].second.first != INT_MAX && (c[u].second.first + a[u][j] < c[j].second.first))
				{
					c[j].second.first = c[u].second.first + a[u][j];
					c[j].second.second = u;
					isMarked |= true;
				}
			}

			isMarked |= !isVisited[j].first | !isVisited[j].second;
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
	vector<pair<pair<int, int>, pair<int, int>>> paths(nTown);

	for (int i = 0; i < nTown; i++)
	{
		d[i].resize(nTown);
	}

	int roadCounter = nRoad;

	while (roadCounter > 0)
	{
		int i, j, w; // номера начального и конечного городов, длина дороги
		input >> i >> j >> w;
		d[i - 1][j - 1] = w;
		roadCounter--;
	}

	paths = findTwoShortPath(d, nTown, 0);

	for (int i = 1; i < nTown; i++)
	{
		cout << (paths[i].second.first != INT_MAX ? to_string(paths[i].second.first) : "No") << endl;
	}
}
