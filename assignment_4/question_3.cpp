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

const void combineTrees(vector<vector<string>>& initFunctions,
	vector<vector<string>>& initTerminals, vector<vector<string>>& solutions,
	const int populationSize) {
	solutions = initFunctions;
	for (int i = 0; i < populationSize; ++i) {
		solutions[i].insert(solutions[i].end(), initTerminals[i].begin(),
			initTerminals[i].end());
	}
}

const void displayTrees(vector<vector<string>>& solutions) {
	for (int i = 0; i < solutions.size(); ++i) {
		cout << "Program " << i + 1 << ": \t";
		for (int j = 0; j < solutions[i].size(); ++j) {
			cout << solutions[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

const int evaluate(vector<string>& solution, vector<string>& correctProgram) {
    auto fitness = 0;
    for (int i = 0; i < solution.size(); ++i) {
        if (solution[i] == correctProgram[i]) {
            ++fitness;
        }
    }
    return fitness;
}

const void evolve(vector<vector<string>>& solutions, const int numGenerations,
	const double crossoverProbability, const double mutationProbability, 
	mt19937& rng, vector<string>& correctProgram, int& correctFitness, 
	vector<string>& bestProgram, int& bestFitness) {

	int generation = 0;
	while (generation < numGenerations) {
		uniform_int_distribution<int> uniBinary(0, 1);
		auto variationOperator = uniBinary(rng);

		uniform_real_distribution<> uniOperator(0, 1);
		auto probability = uniOperator(rng);

		for (int i = 0; i < solutions.size(); ++i) {
			auto currentFitness = evaluate(solutions[i], correctProgram);
			if (currentFitness > bestFitness) {
				bestProgram = solutions[i];
				bestFitness = currentFitness;
			}
		}

		if (variationOperator == 0) {
			if (probability < crossoverProbability) {
				auto first = rand() * solutions.size() / RAND_MAX;
				auto second = rand() * (solutions.size() - 1) / RAND_MAX;
				if (second >= first) {
					++second;
				}
				
				auto firstParent = solutions[first];
				auto secondParent = solutions[second];

				auto firstFitness = evaluate(firstParent, correctProgram);
				auto secondFitness = evaluate(secondParent, correctProgram);

				auto firstElement = rand() * firstParent.size() / RAND_MAX;
				auto secondElement = rand() * secondParent.size() / RAND_MAX;
				if (secondElement >= firstElement) {
					++secondElement;
				}

				swap(firstParent[firstElement], secondParent[secondElement]);
				auto newFirstFitness = evaluate(firstParent, correctProgram);
				auto newSecondFitness = evaluate(secondParent, correctProgram);

				if (firstFitness + secondFitness > newFirstFitness + newSecondFitness) {
					swap(firstParent[firstElement], secondParent[secondElement]);
				}
			}
		} else {
			if (probability < mutationProbability) {
				// Apply Mutation
			}
		}
		++generation;
	}
}

int main() {
	random_device rd;
	mt19937 rng(rd());

	const auto populationSize = 10;
	const auto numGenerations = 500;
	const auto crossoverProbability = 0.9;
	const auto mutationProbability = 0.05;
	const auto maxDepth = 7;

	vector<vector<string>> initFunctions(populationSize, vector<string>());
	auto initTerminals = initFunctions;
	auto solutions = initFunctions;

	generateTrees(initFunctions, initTerminals, populationSize, maxDepth, rng);
	combineTrees(initFunctions, initTerminals, solutions, populationSize);
	displayTrees(solutions);

	vector<string> correctProgram = {"IF", "AND", "IF", "AND", "NOT", "IF",
		"AND", "NOT", "a0", "a1", "d3", "a0", "a1", "d2", "a0", "a1", "d1", "d0"};
	auto correctFitness = 64;

	vector<string> bestProgram = {};
	auto bestFitness = 0;

	evolve(solutions, numGenerations, crossoverProbability, 
		mutationProbability, rng, correctProgram, correctFitness, bestProgram, 
		bestFitness);

	cout << "Correct:\t";
	for (int i = 0; i < correctProgram.size(); ++i) {
		cout << correctProgram[i] << " ";
	}
	cout << endl << endl;

	cout << "Best Program:\t";
	for (int i = 0; i < bestProgram.size(); ++i) {
		cout << bestProgram[i] << " ";
	}
	cout << endl;
	cout << "Best Fitness:\t" << bestFitness << endl;

    return 0;
}
