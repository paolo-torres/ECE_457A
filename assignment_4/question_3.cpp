#include <iostream>
#include <vector>

using namespace std;

const vector<vector<const bool> > v {
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

const bool evaluate(int i) {
	auto a0 = v[i][0];
	auto a1 = v[i][1];
	auto d0 = v[i][2];
	auto d1 = v[i][3];
	auto d2 = v[i][4];
	auto d3 = v[i][5];

	auto program = a0 ? (((a0 ? a0 : a1) ? a1 : !d1) ? d3 : d2) 
		: (a1 ? (a0 ? d3 : d1) : d0);

    return program;
}

const bool actualOutput(int i) {
	auto a0 = v[i][0];
	auto a1 = v[i][1];
	auto d0 = v[i][2];
	auto d1 = v[i][3];
	auto d2 = v[i][4];
	auto d3 = v[i][5];

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
    for (int i = 0; i < v.size(); ++i) {
        auto currentOutput = evaluate(i);
        if (currentOutput == actualOutput(i)) {
            ++fitness;
        }
		cout << "Current: " << currentOutput 
			 << " Actual: " << actualOutput(i) 
			 << " Fitness: " << fitness << endl;
    }
    return fitness;
}

int main() {
    auto result = fitness();
	cout << "Fitness: " << result << endl;

    return 0;
}
