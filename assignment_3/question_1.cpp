#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const int layoutSize = 20;
const int layoutRows = 4;
const int layoutCols = 5;

vector<vector<int>> getData(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Could not open flow file");
    }

    string line = "";
    vector<vector<int>> data;
    int row = 0;
    int val = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        data.push_back(vector<int>());

        while (ss >> val) {
            data[row].push_back(val);

            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        row++;
    }
    file.close();

    return data;
}

vector<vector<int>> getLayout() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    auto engine = default_random_engine(seed);

    int index = 0;
    vector<int> v(layoutSize);
    iota(begin(v), end(v), 1);
    shuffle(v.begin(), v.end(), engine);

    vector<vector<int>> layout(layoutRows, vector<int>(layoutCols, 0));
    for (int i = 0; i < layoutRows; i++) {
        for (int j = 0; j < layoutCols; j++) {
            layout[i][j] = v[index];
            index++;
        }
    }

    return layout;
}

int getCost(vector<vector<int>>& layout, int primary, int primary_i, int primary_j,
    const vector<vector<int>>& flows, const vector<vector<int>>& distances) {
    int cost = 0;
    
    for (int secondary_i = 0; secondary_i < layoutRows; secondary_i++) {
        for (int secondary_j = 0; secondary_j < layoutCols; secondary_j++) {
            int secondary = layout[secondary_i][secondary_j];

            int primary_pos = primary_i * layoutCols + primary_j;
            int secondary_pos = secondary_i * layoutCols + secondary_j;

            cost += flows[primary - 1][secondary - 1] 
                * distances[primary_pos][secondary_pos];
        }
    }

    return cost;
}

int main() {
    const vector<vector<int>> flows = getData("Flow.csv");
    const vector<vector<int>> distances = getData("Distance.csv");

    vector<vector<int>> currLayout(layoutRows, vector<int>(layoutCols, 0));
    vector<vector<int>> bestLayout = currLayout;

    int currCost = 0;
    int bestCost = INT_MAX;

    int iterations = 0;
    while (iterations < 1000000) {
        currLayout = getLayout();

        for (int i = 0; i < layoutRows; i++) {
            for (int j = 0; j < layoutCols; j++) {
                currCost += getCost(currLayout, currLayout[i][j], 
                    i, j, flows, distances);
            }
        }
        if (currCost < bestCost) {
            bestLayout = currLayout;
            bestCost = currCost;
        }
        currCost = 0;
        iterations++;
    }
    for (int i = 0; i < layoutRows; i++) {
        for (int j = 0; j < layoutCols; j++) {
            cout << bestLayout[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
    cout << "Cost: " << bestCost << endl;

    return 0;
}
