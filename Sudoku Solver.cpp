#include <iostream>
#include <vector>
using namespace std;

void solve(vector<vector<int>> input);
bool possible(vector<vector<int>> input, int y, int x, int num);
void printMatrix(vector<vector<int>> input);

int main()
{
    vector<vector<int>> input = {
        {0,3,4,5,0,6,9,0,0},
        {0,0,5,4,0,0,0,0,0},
        {0,0,0,0,8,0,0,1,0},
        {0,0,0,8,2,3,0,0,7},
        {1,0,8,7,0,0,3,0,0},
        {0,0,0,0,0,9,0,0,0},
        {0,8,7,0,0,0,0,0,0},
        {0,0,0,0,0,8,0,7,2},
        {4,0,9,0,0,0,0,0,0}
    };

    solve(input);
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

void solve(vector<vector<int>> input) {
    int x = 0;
    int y = 0;
    printMatrix(input);

    //for each 0 place
    for (vector<int> vec : input) {
        for (int in : vec) {
            if (in == 0) {
                vector<int> possibilities;

                //check if the number fits
                for (int num = 1; num < 10; num++) {
                    if (possible(input, y, x, num)) {
                        possibilities.emplace_back(num);
                        cout << num;
                    }
                }
                if (possibilities.size() == 1) {
                    input[y][x] = possibilities[0];
                }
                possibilities.empty();
            }
            cout << " ";
            //keep track of pos
            x += 1;
        }
        x = 0;
        y += 1;
    }
    cout << endl << endl;

    solve(input);
}

bool possible(vector<vector<int>> input, int y, int x, int num) {
    
    //check column;
    for (int i = 0; i < 9; i++) {
        if (input[i][x] == num) {
            return false;
        }
    }

    for (int j = 0; j < 9; j++) {
        if (input[y][j] == num) {
            return false;
        }
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



