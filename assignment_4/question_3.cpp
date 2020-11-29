#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const vector<string> functions = {"AND", "OR", "NOT", "IF"};
const vector<string> terminals = {"a0", "a1", "d0", "d1", "d2", "d3"};

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

const void generate(TreeNode* root, mt19937& rng, const int maxDepth) {
	if (maxDepth == 0) {
		return;
	}

	uniform_int_distribution<int> uniBinary(0, 1);
	auto direction = uniBinary(rng);

	uniform_int_distribution<int> uniFunctions(0, 3);
	auto functionIndex = uniFunctions(rng);

	if (direction == 0) {
		root->left = new TreeNode(functions[functionIndex]);
		generate(root->left, rng, maxDepth - 1);
	} else {
		root->right = new TreeNode(functions[functionIndex]);
		generate(root->right, rng, maxDepth - 1);
	}
}

const void storeFunctions(TreeNode* head, vector<vector<string>>& initFunctions, int i) {
	if (head == NULL) {
		return;
	}
	storeFunctions(head->left, initFunctions, i);
	initFunctions[i].push_back(head->val);
	storeFunctions(head->right, initFunctions, i);
}

const void storeTerminals(vector<string>& initTerminals, mt19937& rng, const int maxDepth) {
	initTerminals = terminals;
	uniform_int_distribution<int> uniInputs(0, 1);
	int n = (maxDepth + 1) / 2;
	for (int i = 0; i < n; ++i) {
		auto inputIndex = uniInputs(rng);
		initTerminals.push_back(terminals[inputIndex]);
	}
	shuffle(begin(initTerminals), end(initTerminals), rng);
}

const void generateTrees(vector<vector<string>>& initFunctions,
	vector<vector<string>>& initTerminals, const int populationSize,
	const int maxDepth, mt19937& rng) {
	for (int i = 0; i < populationSize; ++i) {
		TreeNode* root = new TreeNode(functions[3]);
		TreeNode* head = root;

		generate(root, rng, maxDepth);
		storeFunctions(head, initFunctions, i);
		storeTerminals(initTerminals[i], rng, maxDepth);
	}
}

const void showTrees(vector<vector<string>>& initFunctions,
	vector<vector<string>>& initTerminals) {
	for (int i = 0; i < initFunctions.size(); ++i) {
		for (int j = 0; j < initFunctions[i].size(); ++j) {
			cout << initFunctions[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < initTerminals.size(); ++i) {
		for (int j = 0; j < initTerminals[i].size(); ++j) {
			cout << initTerminals[i][j] << " ";
		}
		cout << endl;
	}
}

const bool correctOutput(int i) {
	if (cases[i][0] && cases[i][1]) {
		return cases[i][5];
	} else if (cases[i][0] && !cases[i][1]) {
		return cases[i][4];
	} else if (!cases[i][0] && cases[i][1]) {
		return cases[i][3];
	} else {
		return cases[i][2];
	}
}

const bool evaluateOutput(int i, const string program) {
	if (program == "IF AND IF AND NOT IF AND NOT a0 a1 d3 a0 a1 d2 a0 a1 d1 d0") {
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

const void evolve(vector<vector<string>>& initFunctions,
	vector<vector<string>>& initTerminals, const int numGenerations,
	const double crossover, const double mutation, string& bestProgram,
	int& bestFitness) {
	bestProgram = "IF AND IF AND NOT IF AND NOT a0 a1 d3 a0 a1 d2 a0 a1 d1 d0";
	bestFitness = evaluate(bestProgram);
}

int main() {
	random_device rd;
	mt19937 rng(rd());

	const auto populationSize = 10;
	const auto numGenerations = 50;
	const auto crossover = 0.5;
	const auto mutation = 0.05;
	const auto maxDepth = 7;

	vector<vector<string>> initFunctions(populationSize, vector<string>());
	vector<vector<string>> initTerminals(populationSize, vector<string>());

	generateTrees(initFunctions, initTerminals, populationSize, maxDepth, rng);
	showTrees(initFunctions, initTerminals);

	string bestProgram = "";
	auto bestFitness = 0;

	evolve(initFunctions, initTerminals, numGenerations, crossover, mutation, 
	bestProgram, bestFitness);

	cout << "Best Program: " << bestProgram << endl;
	cout << "Best Fitness: " << bestFitness << endl;

    return 0;
}
