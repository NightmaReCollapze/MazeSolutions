#include <iostream>  
#include <vector>  
#include <queue>  
#include <algorithm>  
#include <utility>  

using namespace std;

// Define a maze (0 for a passage, 1 for a wall, start at (0,0), end at (mazeSize-1, mazeSize-1))
vector<vector<int>> maze = {
    {0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 0},
    {1, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 1, 1},
    {0, 1, 0, 0, 1, 0, 1},
    {0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0}
};
// the size of the maze
const int mazeSize = 7;

// Define orientation array (right, down, left, up)  
vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

// Check that the given location is within the maze range and is a passage
bool canReach(int x, int y)
{
    return x >= 0 && x < mazeSize && y >= 0 && y < mazeSize && maze[x][y] == 0;
}
 
// dfs
bool depthFirstSearch(int x, int y, vector<vector<bool>>& visited, vector<pair<int, int>>& path)
{
    // Determine whether reached the end
    if (x == mazeSize - 1 && y == mazeSize - 1) 
    {
        path.push_back({ x, y });
        return true;
    }

    // Mark the current location as visited 
    visited[x][y] = true;
    path.push_back({ x, y });

    // Try all the orientations 
    for (const auto& dir : directions) // needed C++11 or above to run this range-based for loop
    {
        int newX = x + dir.first;
        int newY = y + dir.second;

        // If the new location is valid and has not been visited, continue the next search through recursion
        if (canReach(newX, newY) && !visited[newX][newY]) 
        {
            if (depthFirstSearch(newX, newY, visited, path)) 
            {
                return true;
            }
        }
    }

    // Backtracking: If the current path is unsuccessful, 
    //               remove the current location from the path and mark it as not visited
    path.pop_back();
    visited[x][y] = false;

    return false; // didn't find the solution
}

int main() 
{
    vector<vector<bool>> visited(mazeSize, vector<bool>(mazeSize, false));
    vector<pair<int, int>> path;

    // maze can be input here, 
    // but in order to show the algorithm conveniently I initialize it at where it been defined. (Line 14)

    // searching start at 0,0
    cout << "Start to use depth first search to find the solution of the maze..." << endl;
    if (depthFirstSearch(0, 0, visited, path)) 
    {
        cout << "Found a solution!" << endl;
        for (const auto& step : path)  // needed C++11 or above to run this range-based for loop
        {
            cout << "-> (" << step.first << ", " << step.second << ") "; // output the solution
        }
    }
    else 
    {
        cout << "No solution!" << endl;
    }

    return 0;
}