#include <iostream>
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

int main() {
    auto result = fitness();
	cout << "Fitness: " << result << endl;

    return 0;
}
