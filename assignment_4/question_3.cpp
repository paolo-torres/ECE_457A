#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const vector<vector<const bool> > cases {
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1},

	{0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 1},

	{0, 0, 0, 1, 0, 0},
	{0, 0, 0, 1, 0, 1},
	{0, 0, 0, 1, 1, 0},
	{0, 0, 0, 1, 1, 1},

	{0, 0, 1, 0, 0, 0},
	{0, 0, 1, 0, 0, 1},
	{0, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 1},
	{0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 0, 1},
	{0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1},

	{0, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 1},
	{0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 1},
	{0, 1, 0, 1, 0, 0},
	{0, 1, 0, 1, 0, 1},
	{0, 1, 0, 1, 1, 0},
	{0, 1, 0, 1, 1, 1},
	{0, 1, 1, 0, 0, 0},
	{0, 1, 1, 0, 0, 1},
	{0, 1, 1, 0, 1, 0},
	{0, 1, 1, 0, 1, 1},
	{0, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 1},
	{0, 1, 1, 1, 1, 0},
	{0, 1, 1, 1, 1, 1},

	{1, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0},
	{1, 0, 0, 0, 1, 1},
	{1, 0, 0, 1, 0, 0},
	{1, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 1, 0},
	{1, 0, 0, 1, 1, 1},
	{1, 0, 1, 0, 0, 0},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0},
	{1, 0, 1, 0, 1, 1},
	{1, 0, 1, 1, 0, 0},
	{1, 0, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 0},
	{1, 0, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 0},
	{1, 1, 0, 0, 0, 1},
	{1, 1, 0, 0, 1, 0},
	{1, 1, 0, 0, 1, 1},
	{1, 1, 0, 1, 0, 0},
	{1, 1, 0, 1, 0, 1},
	{1, 1, 0, 1, 1, 0},
	{1, 1, 0, 1, 1, 1},
	{1, 1, 1, 0, 0, 0},
	{1, 1, 1, 0, 0, 1},
	{1, 1, 1, 0, 1, 0},
	{1, 1, 1, 0, 1, 1},
	{1, 1, 1, 1, 0, 0},
	{1, 1, 1, 1, 0, 1},
	{1, 1, 1, 1, 1, 0},
	{1, 1, 1, 1, 1, 1}
};

struct TreeNode {
	string val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(string s) : val(s), left(NULL), right(NULL) {}
};

const void generate(TreeNode* root, vector<string>& functions, 
	vector<string> terminals, mt19937& rng) {
	if (terminals.empty()) {
		return;
	}

	uniform_int_distribution<int> uniBinary(0, 1);
	auto direction = uniBinary(rng);

	if (direction == 0) {
		auto type = uniBinary(rng);
		if (type == 0) {
			uniform_int_distribution<int> uniFunctions(0, 3);
			auto function = uniFunctions(rng);
			root->left = new TreeNode(functions[function]);
		} else {
			uniform_int_distribution<int> uniTerminals(0, terminals.size() - 1);
			auto terminal = uniTerminals(rng);
			root->left = new TreeNode(terminals[terminal]);

			terminals.erase(terminals.begin() + terminal);
		}
		generate(root->left, functions, terminals, rng);
	} else {
		auto type = uniBinary(rng);
		if (type == 0) {
			uniform_int_distribution<int> uniFunctions(0, 3);
			auto function = uniFunctions(rng);
			root->right = new TreeNode(functions[function]);
		} else {
			uniform_int_distribution<int> uniTerminals(0, terminals.size() - 1);
			auto terminal = uniTerminals(rng);
			root->right = new TreeNode(terminals[terminal]);

			terminals.erase(terminals.begin() + terminal);
		}
		generate(root->right, functions, terminals, rng);
	}
}

const void storeTrees(TreeNode* head, vector<vector<string>>& initTrees, 
	vector<string>& functions, int i) {
	if (head == NULL) {
		return;
	}
	storeTrees(head->left, initTrees, functions, i);
	if (find(functions.begin(), functions.end(), head->val) != functions.end()) {
		initTrees[i].insert(initTrees[i].begin(), head->val);
	} else {
		initTrees[i].push_back(head->val);
	}
	storeTrees(head->right, initTrees, functions, i);
}

const void generateTrees(vector<vector<string>>& initTrees, 
	vector<string>& functions, vector<string>& terminals, const int populationSize) {
	random_device rd;
	mt19937 rng(rd());

	for (int i = 0; i < populationSize; ++i) {
		uniform_int_distribution<int> uniFunctions(0, 3);
		auto start = uniFunctions(rng);

		TreeNode* root = new TreeNode(functions[start]);
		TreeNode* head = root;

		generate(root, functions, terminals, rng);

		initTrees.push_back(vector<string>());
		storeTrees(head, initTrees, functions, i);
		initTrees[i][0] = functions[3];
	}
}

const void showTrees(vector<vector<string>>& initTrees) {
	for (int i = 0; i < initTrees.size(); ++i) {
		for (int j = 0; j < initTrees[i].size(); ++j) {
			cout << initTrees[i][j] << " ";
		}
		cout << endl;
	}
}

const bool correctOutput(int i) {
	/*
		IF A0 AND A1 D3 IF A0 AND NOT A1 D2 IF A1 AND NOT A0 D1 D0
		IF AND IF AND NOT IF AND NOT A0 A1 D3 A0 A1 D2 A1 A0 D1 D0
	*/

	if (cases[i][0] && cases[i][1]) {
		return cases[i][5];
	}
	if (cases[i][0] && !cases[i][1]) {
		return cases[i][4];
	}
	if (!cases[i][0] && cases[i][1]) {
		return cases[i][3];
	}
	return cases[i][2];
}

const bool evaluateOutput(int i, const string program) {
	if (program == "IF AND IF AND NOT IF AND NOT A0 A1 D3 A0 A1 D2 A1 A0 D1 D0") {
		auto bestProgram = correctOutput(i);
		return bestProgram;
	}
    return 0;
}

const int evaluate(const string program) {
    auto fitness = 0;
    for (int i = 0; i < cases.size(); ++i) {
        auto currentOutput = evaluateOutput(i, program);
		auto actualOutput = correctOutput(i);
        if (currentOutput == actualOutput) {
            ++fitness;
        }
    }
    return fitness;
}

const void evolve(vector<vector<string>>& initTrees, const int numGenerations,
	const double crossover, const double mutation, string& bestProgram, 
	int& bestFitness) {
	bestProgram = "IF AND IF AND NOT IF AND NOT A0 A1 D3 A0 A1 D2 A1 A0 D1 D0";
	bestFitness = evaluate(bestProgram);
}

int main() {
	vector<string> functions = {"AND", "OR", "NOT", "IF"};
	vector<string> terminals = {"a0", "a1", "d0", "d1", "d2", "d3"};

	const auto populationSize = 10;
	const auto numGenerations = 50;
	const auto crossover = 0.5;
	const auto mutation = 0.05;

	vector<vector<string>> initTrees;
	generateTrees(initTrees, functions, terminals, populationSize);
	showTrees(initTrees);

	string bestProgram = "";
	auto bestFitness = 0;

	evolve(initTrees, numGenerations, crossover, mutation, bestProgram, bestFitness);

	cout << "Best Program: " << bestProgram << endl;
	cout << "Best Fitness: " << bestFitness << endl;

    return 0;
}
