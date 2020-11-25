#include <iostream>
#include <vector>

using namespace std;

constexpr auto CASES = 64;

const bool evaluate(vector<bool>& values, int i) {
    /*
				a0  a1  d0  d1  d2  d3
		i = 0:  0   0   0   0   0   0
		i = 1:  0   0   0   0   0   1
		i = 2:  0   0   0   0   1   0
		i = 3:  0   0   0   0   1   1
		i = 4:  0   0   0   1   0   0
		i = 5:  0   0   0   1   0   1
		i = 6:  0   0   0   1   1   0
		i = 7:  0   0   0   1   1   1
		i = 8:  0   0   1   0   0   0
		i = 9:  0   0   1   0   0   1
		...
	*/

    return true;
}

const bool actualOutput(vector<bool>& values) {
	/*
		a0  a1  d0  d1  d2  d3
		0   0   1   0   0   0
		0   1   0   1   0   0
		1   0   0   0   1   0
		1   1   0   0   0   1
	*/

    if (values[0] && values[1]) {
        return values[5];
    }
    if (values[0]) {
        return values[4];
    }
    if (values[1]) {
        return values[3];
    }
    return values[2];
}

const int fitness(vector<bool>& values) {
    auto fitness = 0;
    for (int i = 0; i < CASES; i++) {
        auto currentOutput = evaluate(values, i);
        if (currentOutput == actualOutput(values)) {
            fitness++;
        }
    }
    return fitness;
}

int main() {
    cout << "Genetic Programming" << endl;

    return 0;
}
