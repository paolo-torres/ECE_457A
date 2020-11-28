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

const bool evaluateOutput(int i, bool a0, bool a1, bool d0, bool d1, bool d2, bool d3) {
	auto program = a0 ? (((a0 ? a0 : a1) ? a1 : !d1) ? d3 : d2) 
		: (a1 ? (a0 ? d3 : d1) : d0);
	
	/*
		if (a0) {
			auto x = 0;
			if (a0) {
				x = a0;
			} else {
				x = a1;
			}
			auto y = 0;
			if (x) {
				y = a1;
			} else {
				y = !d1;
			}
			if (y) {
				return d3;
			} else {
				return d2;
			}
		} else {
			if (a1) {
				if (a0) {
					return d3;
				} else {
					return d1;
				}
			} else {
				return d0;
			}
		}
	*/

    return program;
}

const bool correctOutput(int i, bool a0, bool a1, bool d0, bool d1, bool d2, bool d3) {
    if (a0 && a1) {
        return d3;
    }
    if (a0) {
        return d2;
    }
    if (a1) {
        return d1;
    }
    return d0;
}

const int fitness() {
    auto fitness = 0;
    for (int i = 0; i < cases.size(); ++i) {
		auto a0 = cases[i][0];
		auto a1 = cases[i][1];
		auto d0 = cases[i][2];
		auto d1 = cases[i][3];
		auto d2 = cases[i][4];
		auto d3 = cases[i][5];
        auto currentOutput = evaluateOutput(i, a0, a1, d0, d1, d2, d3);
		auto actualOutput = correctOutput(i, a0, a1, d0, d1, d2, d3);
        if (currentOutput == actualOutput) {
            ++fitness;
        }
    }
    return fitness;
}

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

const void storeTrees(TreeNode* head, vector<vector<string>>& initTrees, int i) {
	if (head == NULL) {
		return;
	}
	storeTrees(head->left, initTrees, i);
	initTrees[i].push_back(head->val);
	storeTrees(head->right, initTrees, i);
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
		storeTrees(head, initTrees, i);
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

int main() {
    auto bestFitness = fitness();
	cout << "Best Fitness: " << bestFitness << endl << endl;

	vector<string> functions = {"AND", "OR", "NOT", "IF"};
	vector<string> terminals = {"a0", "a1", "d0", "d1", "d2", "d3"};

	const auto populationSize = 10;

	vector<vector<string>> initTrees;
	generateTrees(initTrees, functions, terminals, populationSize);
	showTrees(initTrees);

    return 0;
}
