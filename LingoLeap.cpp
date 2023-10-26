#include <bits/stdc++.h>

using namespace std;

/**
 * You are given an m x n matrix with positive integers.
 * You can start with any element of the first column and traverse the grid in the following way:-
 * From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell.
 * Return the maximum number of moves that you can perform.
 * Test Case 1: 4 x 4 , 2 4 3 5 5 4 9 3 3 4 2 11 10 9 13 15
 * Constraints:

    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^6
 */

map<string, int> cache;

int findMaxPath(vector<vector<int>> grid, int rowNo, int colNo)
{
    string currPosition = to_string(rowNo) + to_string(colNo);
    if (cache.find(currPosition) != cache.end())
    {
        return cache[currPosition];
    }
    else
    {
        int URight = 0, right = 0, LRight = 0;
        bool flag = false;
        // checking diagonally up is possible
        if ((rowNo > 0 && colNo < grid[0].size() - 1) && grid[rowNo][colNo] < grid[rowNo - 1][colNo + 1])
        {
            flag = true;
            URight = findMaxPath(grid, rowNo - 1, colNo + 1);
        }
        // checking right is possible
        if (colNo < grid[0].size() - 1 && grid[rowNo][colNo] < grid[rowNo][colNo + 1])
        {
            flag = true;
            right = findMaxPath(grid, rowNo, colNo + 1);
        }
        // checking diagonally down is possible
        if ((rowNo < grid.size() - 1 && colNo < grid[0].size() - 1) && grid[rowNo][colNo] < grid[rowNo + 1][colNo + 1])
        {
            flag = true;
            LRight = findMaxPath(grid, rowNo + 1, colNo + 1);
        }
        if (flag == false)
        {
            cache[currPosition] = 0;
            return 0;
        }
        cache[currPosition] = max(URight, max(right, LRight)) + 1;
        return cache[currPosition];
    }
}

// In C++ you cant determine size of array in a function and it needs to be passed as a param
// Made it a vector of vectors for more flexibility
int findMaxMovesPossible(vector<vector<int>> grid)
{
    int totRows = grid.size();
    int totCols = grid[0].size();

    int maxMovesinGrid = 0;

    for (int i = 0; i < totRows; i++)
    {
        int pathLength = findMaxPath(grid, i, 0);
        maxMovesinGrid = max(maxMovesinGrid, pathLength);
    }

    return maxMovesinGrid;
}

int main()
{
    cout << endl
         << "LingoLeap Assignment:-" << endl;
    int totRows, totCols;

    cout << "Enter number of rows in the grid:";
    cin >> totRows;
    cout << "Enter number of cols in the gird:";
    cin >> totCols;

    vector<vector<int>> grid(totRows);
    cout << "Enter Elements of the grid:";
    for (int i = 0; i < totRows; i++)
    {
        for (int j = 0; j < totCols; j++)
        {
            int el;
            cin >> el;

            grid[i].push_back(el);
        }
    }

    cout << endl
         << "Finding Solution for the following grid:" << endl;
    for (int i = 0; i < totRows; i++)
    {
        for (int j = 0; j < totCols; j++)
        {
            cout << grid[i][j] << " ";
        }

        cout << endl;
    }

    int ans = findMaxMovesPossible(grid);
    cout << endl
         << "Answer:" << ans << endl;
    return 0;
}