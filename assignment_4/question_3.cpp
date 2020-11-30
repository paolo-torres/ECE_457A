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

const void storeFunctions(TreeNode* head, vector<vector<string>>& initFunctions,
	int i) {
	if (head == NULL) {
		return;
	}
	storeFunctions(head->left, initFunctions, i);
	initFunctions[i].push_back(head->val);
	storeFunctions(head->right, initFunctions, i);
}

const void storeTerminals(vector<string>& initTerminals, mt19937& rng,
	const int maxDepth) {
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

const double evaluate(vector<string>& solution, vector<string>& correctProgram) {
    double fitness = 0;
    for (int i = 0; i < solution.size(); ++i) {
        if (solution[i] == correctProgram[i]) {
            ++fitness;
        }
    }
    return fitness / solution.size();
}

const void performCrossover(vector<vector<string>>& solutions, int i,
	mt19937& rng, vector<string>& correctProgram) {
	uniform_int_distribution<int> uniCrossover(i + 1, solutions.size() - 1);
	auto crossoverIndex = uniCrossover(rng);

	auto firstFitness = evaluate(solutions[i], correctProgram);
	auto secondFitness = evaluate(solutions[crossoverIndex], correctProgram);

	auto firstElement = rand() * solutions[i].size() / RAND_MAX;
	auto secondElement = rand() * (solutions[crossoverIndex].size() - 1) / RAND_MAX;
	if (secondElement >= firstElement) {
		++secondElement;
	}

	swap(solutions[i][firstElement], solutions[crossoverIndex][secondElement]);
	auto newFirstFitness = evaluate(solutions[i], correctProgram);
	auto newSecondFitness = evaluate(solutions[crossoverIndex], correctProgram);

	if (firstFitness + secondFitness > newFirstFitness + newSecondFitness) {
		swap(solutions[i][firstElement], solutions[crossoverIndex][secondElement]);
	}
}

const void performMutation(vector<vector<string>>& solutions, int i,
	mt19937& rng, vector<string>& correctProgram) {
	auto fitness = evaluate(solutions[i], correctProgram);

	auto element = rand() * solutions[i].size() / RAND_MAX;
	if (find(functions.begin(), functions.end(),
		solutions[i][element]) != functions.end()) {
		uniform_int_distribution<int> uniFunctions(0, functions.size() - 1);
		auto functionsIndex = uniFunctions(rng);

		solutions[i][element] = functions[functionsIndex];
	} else {
		uniform_int_distribution<int> uniTerminals(0, terminals.size() - 1);
		auto terminalsIndex = uniTerminals(rng);

		solutions[i][element] = terminals[terminalsIndex];
	}
	auto temp = solutions[i][element];
	auto newFitness = evaluate(solutions[i], correctProgram);
	if (fitness > newFitness) {
		solutions[i][element] = temp;
	}
}

const void evolve(vector<vector<string>>& solutions, const int numGenerations,
	const double crossoverProbability, const double mutationProbability, 
	mt19937& rng, vector<string>& correctProgram, double& correctFitness, 
	vector<string>& bestProgram, double& bestFitness) {

	int generation = 1;
	while (generation <= numGenerations) {
		uniform_real_distribution<> uniOperator(0, 1);
		auto probability = uniOperator(rng);

		for (int i = 0; i < solutions.size(); ++i) {
			auto currentFitness = evaluate(solutions[i], correctProgram);
			if (currentFitness > bestFitness) {
				bestProgram = solutions[i];
				bestFitness = currentFitness;
			}
		}

		for (int i = 0; i < solutions.size() - 1; ++i) {
			uniform_int_distribution<int> uniBinary(0, 1);
			auto variationOperator = uniBinary(rng);

			if (variationOperator == 0) {
				if (probability < crossoverProbability) {
					performCrossover(solutions, i, rng, correctProgram);
				}
			} else {
				if (probability < mutationProbability) {
					performMutation(solutions, i, rng, correctProgram);
				}
			}
		}

		cout << generation << ": ";
		for (int i = 0; i < bestProgram.size(); ++i) {
			cout << bestProgram[i] << " ";
		}
		cout << "Fitness: " << bestFitness << endl;

		++generation;
	}
	cout << endl;
}

int main() {
	random_device rd;
	mt19937 rng(rd());

	const auto populationSize = 100;
	const auto numGenerations = 1000;
	const auto crossoverProbability = 0.9;
	const auto mutationProbability = 0.6;
	const auto maxDepth = 7;

	vector<vector<string>> initFunctions(populationSize, vector<string>());
	auto initTerminals = initFunctions;
	auto solutions = initFunctions;

	generateTrees(initFunctions, initTerminals, populationSize, maxDepth, rng);
	combineTrees(initFunctions, initTerminals, solutions, populationSize);

	vector<string> correctProgram = {"IF", "AND", "IF", "AND", "NOT", "IF",
		"AND", "NOT", "a0", "a1", "d3", "a0", "a1", "d2", "a0", "a1", "d1", "d0"};
	double correctFitness = 1;

	vector<string> bestProgram = {};
	double bestFitness = 0;

	evolve(solutions, numGenerations, crossoverProbability, mutationProbability,
		rng, correctProgram, correctFitness, bestProgram, bestFitness);

	cout << "Correct Program: ";
	for (int i = 0; i < correctProgram.size(); ++i) {
		cout << correctProgram[i] << " ";
	}
	cout << endl;
	cout << "Correct Fitness: " << correctFitness << endl << endl;

	cout << "Best Program: ";
	for (int i = 0; i < bestProgram.size(); ++i) {
		cout << bestProgram[i] << " ";
	}
	cout << endl;
	cout << "Best Fitness: " << bestFitness << endl;

    return 0;
}
