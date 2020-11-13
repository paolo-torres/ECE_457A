#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

constexpr auto layoutRows = 4;
constexpr auto layoutCols = 5;

const vector<vector<int>> getData(const string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    string line = "";
    vector<vector<int>> data;

    auto row = 0;
    auto val = 0;

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

const vector<vector<int>> getLayout() {
    const unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    auto engine = default_random_engine(seed);

    vector<int> v(20);
    iota(begin(v), end(v), 1);
    shuffle(v.begin(), v.end(), engine);
    
    auto index = 0;

    vector<vector<int>> layout(layoutRows, vector<int>(layoutCols, 0));

    for (int i = 0; i < layoutRows; i++) {
        for (int j = 0; j < layoutCols; j++) {
            layout[i][j] = v[index];
            index++;
        }
    }

    return layout;
}

const int getCost(vector<vector<int>>& layout, int primary, int primary_i, int primary_j,
    const vector<vector<int>>& flows, const vector<vector<int>>& distances) {
    auto cost = 0;
    
    for (auto secondary_i = 0; secondary_i < layoutRows; secondary_i++) {
        for (auto secondary_j = 0; secondary_j < layoutCols; secondary_j++) {
            auto secondary = layout[secondary_i][secondary_j];

            auto primary_pos = primary_i * layoutCols + primary_j;
            auto secondary_pos = secondary_i * layoutCols + secondary_j;

            cost += flows[primary - 1][secondary - 1] 
                * distances[primary_pos][secondary_pos];
        }
    }

    return cost;
}

const void updateTabuList(map<vector<vector<int>>, int>& tabuList) {
    for (auto it = tabuList.begin(); it != tabuList.end();) {
        it->second--;
        if (it->second == 0) {
            it = tabuList.erase(it);
        } else {
            it++;
        }
    }
}

const void useTabuList(map<vector<vector<int>>, int>& tabuList,
    priority_queue<pair<int, vector<vector<int>>>, 
        vector<pair<int, vector<vector<int>>>>, 
        greater<pair<int, vector<vector<int>>>> >& candidates) {
    for (auto it = tabuList.begin(); it != tabuList.end(); it++) {
        while (it->first == candidates.top().second) {
            candidates.pop();
        }
    }

    tabuList.insert({candidates.top().second, 5});
}

const void displaySolution(vector<vector<int>>& bestLayout, int bestCost) {
    for (auto i = 0; i < layoutRows; i++) {
        for (auto j = 0; j < layoutCols; j++) {
            cout << bestLayout[i][j] << '\t';
        }
        cout << endl;
    }
    cout << "Cost: " << bestCost << endl;
}

const void tabuSearch() {
    const auto flows = getData("Flow.csv");
    const auto distances = getData("Distance.csv");

    auto iterations = 0;

    priority_queue<pair<int, vector<vector<int>>>, 
        vector<pair<int, vector<vector<int>>>>, 
        greater<pair<int, vector<vector<int>>>> > candidates;
    const auto clearCandidates = candidates;

    map<vector<vector<int>>, int> tabuList;

    vector<vector<int>> layout1(layoutRows, vector<int>(layoutCols, 0));
    auto layout2 = layout1;
    auto layout3 = layout1;
    auto layout4 = layout1;
    auto layout5 = layout1;

    auto bestLayout = layout1;

    auto cost1 = 0;
    auto cost2 = cost1;
    auto cost3 = cost1;
    auto cost4 = cost1;
    auto cost5 = cost1;

    auto bestCost = INT_MAX;

    while (iterations < 100000) {
        layout1 = getLayout();
        layout2 = getLayout();
        layout3 = getLayout();
        layout4 = getLayout();
        layout5 = getLayout();

        for (auto i = 0; i < layoutRows; i++) {
            for (auto j = 0; j < layoutCols; j++) {
                cost1 += getCost(layout1, layout1[i][j], i, j, flows, distances);
                cost2 += getCost(layout2, layout2[i][j], i, j, flows, distances);
                cost3 += getCost(layout3, layout3[i][j], i, j, flows, distances);
                cost4 += getCost(layout4, layout4[i][j], i, j, flows, distances);
                cost5 += getCost(layout5, layout5[i][j], i, j, flows, distances);
            }
        }

        candidates.push({cost1, layout1});
        candidates.push({cost2, layout2});
        candidates.push({cost3, layout3});
        candidates.push({cost4, layout4});
        candidates.push({cost5, layout5});

        updateTabuList(tabuList);
        useTabuList(tabuList, candidates);

        if (candidates.top().first < bestCost) {
            bestLayout = candidates.top().second;
            bestCost = candidates.top().first;
        }

        cost1 = 0;
        cost2 = cost1;
        cost3 = cost1;
        cost4 = cost1;
        cost5 = cost1;
        candidates = clearCandidates;

        iterations++;
    }

    displaySolution(bestLayout, bestCost);
}

/*
17	4	20	7	6	
19	15	8	5	3	
2	11	16	1	13	
14	18	12	10	9	
Cost: 2792
*/

int main() {
    tabuSearch();

    return 0;
}
