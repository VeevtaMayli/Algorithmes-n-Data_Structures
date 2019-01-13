/*
19. В  листьях  И-ИЛИ  дерева,  соответствующего некоторому
множеству  конструкций,  заданы   значения   массы.   Известно
максимально допустимое значение массы изделия. Требуется усечь
дерево   так,   чтобы   дерево    включало    все    элементы,
соответствующие  допустимым  значениям массы,  но не содержало
"лишних" вершин.  Конечное дерево выдать на экран в  наглядном
виде (14).
Матвеев Илья
ИПС-2017
*/

#include "pch.h"

enum treeElement
{
	LEAF, AND, OR
};

struct Tree
{
	std::vector<Tree> children;

	treeElement type = LEAF;
	std::string name = "";
	
	int weight = 0;
	int minWeight = 0;
	int maxWeight = 0;

	bool nameFlag = false;

	std::string toString()
	{
		std::string tree = "";
		tree += this->name + ' ';

		switch (this->type)
		{
			case AND:
				tree += 'a';
				break;
			case OR:
				tree += 'o';
				break;
			default:
				tree += std::to_string(this->weight);
		}

		return tree;
	};

	void read(std::istream &in, int startingLevel)
	{
		std::string str = "";
		int currentLevel = 0;
		
		if (in.eof())
		{
			std::cout << "Input tree is empty\n";
			throw 1;
		}

		do
		{
			char symbol = in.get();
						
			if (symbol == '\n' || symbol == EOF)
			{
				if (this->type == LEAF)
				{
					this->weight = std::stoi(str);
					this->minWeight = this->weight;
					this->maxWeight = this->weight;
				}
			}
			else if (symbol == '.')
			{
				currentLevel++;
				if (in.peek() != '.')
				{
					if (startingLevel < currentLevel)
					{
						Tree child;
						child.read(in, currentLevel);
						this->children.push_back(child);
						currentLevel = 0;
					}
					else
					{
						int currentPosition = in.tellg();
						in.seekg(-currentLevel, in.cur);
						break;
					}
				}
			}
			else if (symbol == ' ')
			{
				this->nameFlag = true;
				continue;
			}
			else if (isalpha(symbol))
			{
				if (!this->nameFlag)
				{
					this->name += symbol;
				}
				else
				{
					this->type = symbol == 'a' ? AND : symbol == 'o' ? OR : throw 1;
				}

			}
			else if (isdigit(symbol))
			{
				str += symbol;
			}
			else
			{
				std::cout << "Detected forbidden symbols\n";
				throw 1;
			}
		} while (!in.eof());
	}

	void calculate()
	{
		Tree &first = this->children.front();
		
		int min = 0;
		int max = 0;

		if (first.type != LEAF)
		{
			first.calculate();
		}

		min = first.minWeight;
		max = first.maxWeight;
		
		for (size_t i = 1; i < this->children.size(); i++)
		{
			Tree &child = this->children[i];
			if (child.type != LEAF) child.calculate();

			if (this->type == AND)
			{
				min += child.minWeight;
				max += child.maxWeight;
			}
			else
			{
				min = child.minWeight < min ? child.minWeight : min;
				max = child.maxWeight > max ? child.maxWeight : max;
			}
		}

		this->minWeight = min;
		this->maxWeight = max;
	}

	bool truncate(const int max)
	{
		if (this->minWeight > max) return false;

		if (this->maxWeight < max) return true;

		size_t size = this->children.size();
		for (size_t i = 0; i < size; i++)
		{
			Tree &child = this->children[i];

			int curMax = max;

			if (child.type == LEAF)
			{
				if (child.weight > curMax && this->type == OR && size > 1)
				{
					this->children.erase(this->children.begin() + i);
					i--;
					size--;
				}

				continue;
			}

			if (this->type != OR)
			{
				for (size_t j = 0; j < size; j++)
				{
					if (j == i) continue;
					
					curMax -= this->children[j].minWeight;
				}
			}

			child.truncate(curMax);

			if (this->type == OR && child.minWeight > curMax && size > 1)
			{
				this->children.erase(this->children.begin() + i);
				i--;
				size--;
			}
		}

		this->calculate();
		return this->minWeight <= max;
	}
};

void printTree(Tree treeElement, const std::string &indent)
{
	std::cout << indent << treeElement.toString() << std::endl;

	for (int i = 0; i < treeElement.children.size(); i++)
	{
		printTree(treeElement.children[i], indent + '.');
	}
};

int readMaxWeight(std::istream &in)
{
	std::string str;
	std::getline(in, str);
	return std::stoi(str);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Incorrect arguments count\n"
			<< "Usage: lw2_19.exe <input file>\n";
		return 1;
	}

	std::ifstream input((std::string) argv[1]);

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
	
	try
	{
		int maxWeight = readMaxWeight(input);

		Tree root;
		root.read(input, 0);
		
		root.calculate();

		if (root.truncate(maxWeight))
		{
			printTree(root, "");
		}
		else
		{
			std::cout << "Tree is empty, minimal mass is " << root.minWeight << std::endl;
		}
	}
	catch (int)
	{
		return 1;
	}
	catch (...)
	{
		std::cout << "Invalid maximum weight\n";
	}

	return 0;
}
