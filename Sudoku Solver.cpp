#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool solve(vector<vector<int>>& input);
bool possible(vector<vector<int>> input, int y, int x, int num);
void printMatrix(vector<vector<int>> input);
void checkForUnique(vector<vector<int>>row, vector<int>& rosa);
int count = 0;
vector<vector<vector<int>>> possibilityGrid = {

    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}},
    {{},{},{},{},{},{},{},{},{}}
};

int main()
{
    
    vector<vector<int>> input = {
        {0,4,0,0,5,0,8,0,0},
        {0,0,0,3,0,0,0,2,6},
        {0,0,6,0,0,0,0,0,0},
        {0,0,0,0,8,0,2,5,0},
        {0,3,2,0,0,0,6,0,0},
        {0,0,0,4,0,7,0,0,3},
        {3,0,0,0,9,8,1,0,0},
        {8,0,0,0,0,0,0,7,0},
        {1,0,0,0,6,0,0,3,8}
    };
   
    cout << "Starting Grid" << endl;
    printMatrix(input);
    while(solve(input));

}

void printMatrix(vector<vector<int>> input) {
    for (vector<int> vec : input) {
        cout << " -------------------------------------" << endl;
        for (int in : vec) {
            cout << " | " << in;
        }
        cout << " |" << endl;
    }
    cout << " -------------------------------------" << endl;
}

bool solve(vector<vector<int>>& input) {
    int x = 0;
    int y = 0;
    ::count++;
    
    //for each 0 place
    cout << endl << "Possibilities Grid" << endl;
    for (vector<int> vec : input) {
        cout << "[";
        for (int in : vec) {
            vector<int> possibilities;
            if (in == 0) {
                

                //check if the number fits
                for (int num = 1; num < 10; num++) {
                    if (possible(input, y, x, num)) {
                        possibilities.emplace_back(num);
                        cout << "{" << num << "}";
                    }
                }
                if (possibilities.size() == 1) {
                    input[y][x] = possibilities[0];
                    ::count = 0;
                }
            }
            else {
                possibilities.emplace_back(0);
            }

            possibilityGrid[y][x] = possibilities;
            
            //keep track of position
            x += 1;
            cout << "] - [";
        }
        cout << "]" << endl;
        x = 0;
        y += 1;

    }
    

    int w = 0;
    for (vector < vector<int>> row : possibilityGrid) {

        vector<int> rosa = {};
        checkForUnique(row, rosa);
        for (int check : rosa) {
            for (int q = 0; q < row.size(); q++) {
                for (int a = 0; a < possibilityGrid[w][q].size(); a++) {
                    if (check == possibilityGrid[w][q][a]) {
                        input[w][q] = check;
                        ::count = 0;
                    }
                }
            }
        }
        w++;
    }

    w = 0;
    for (int j = 0; j < 9; j++) {
        vector<vector<int>> checkit;
        vector<int> rosa = {};
        for (int i = 0; i < 9; i++) {

            checkit.emplace_back(possibilityGrid[i][j]);

        }
        checkForUnique(checkit, rosa);
        for (int check : rosa) {
            for (int q = 0; q < checkit.size(); q++) {
                for (int a = 0; a < possibilityGrid[q][w].size(); a++) {
                    if (check == possibilityGrid[q][w][a]) {
                        input[q][w] = check;
                        ::count = 0;
                    }
                }
            }
        }


        w++;
    }

    if (::count > 0) {
        return false;
    }

    cout << endl << endl << "Current Grid" << endl;

    printMatrix(input);

    solve(input);
}

bool checkRow(vector<vector<int>> input, int y, int x, int num) {

    for (int i = 0; i < 9; i++) {
        if (input[i][x] == num) {
            return false;
        }
    }
    return true;
}

bool checkColumn(vector<vector<int>> input, int y, int x, int num) {

    for (int j = 0; j < 9; j++) {
        if (input[y][j] == num) {
            return false;
        }
    }
    return true;
}

void checkForUnique(vector<vector<int>> row, vector<int>& rosa) {
    int num = 0;

    
        vector<int> checklist;

        for (vector<int> square : row) {
            for (int val : square) {
                if (val != 0) {
                    checklist.emplace_back(val);
                }
            }
        }

        sort(checklist.begin(), checklist.end());
        
        for (int i = 1; i < checklist.size(); i++) {
            int removed = 0;
            if (checklist.size() > 1) {
                if(checklist[i] == checklist[i - 1] && checklist.size() > i) {
                    while (checklist.size() > i && checklist[i] == checklist[i - 1]) {
                        checklist.erase(checklist.begin() + i);
                        removed++;
                    }
                    checklist.erase(checklist.begin() + i - 1);
                    i--;
                }
            }
        }
        
        for (int j = 0; j < checklist.size(); j++) {
            rosa.emplace_back(checklist[j]);
        }
}


bool possible(vector<vector<int>> input, int y, int x, int num) {
    
    //check column;
    if (!checkColumn(input, y, x, num) || !checkRow(input, y, x, num)) {
        return false;
    }

    int k = y % 3;
    int l = x % 3;

    for (int t = 0; t < 3; t++) {
        for (int s = 0; s < 3; s++) {
            if (input[y - k + t][x - l + s] == num) {
                return false;
            }

        }
    }

    return true;
}
