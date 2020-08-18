#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
#include <limits>
#include <list>

#define ROW 10
#define COL 10
int INT_INF = 1e9;
int DBL_INF = 1e9;

struct cell {
    int parent_i, parent_j;
    double f, g, h;
};

bool isValid (int row, int col) {
    return (row >= 0) && (col >= 0) && (row < ROW) && (col < COL);
}
bool isUnblocked (int grid [][COL], int row, int col) {
    if (grid [row][col] == 1) {
        return true;
    }
    return false;
}
bool isDestination (int row, int col, std::pair<int, int> dest) {
    if (row == dest.first && col == dest.second) {
        return true;
    }
    return false;
}
double heurestic (int row, int col, std::pair<int, int> dest) {
    //Manhattan Distance (For 4 way)
    //return std::max(abs(row - dest.first), abs(col - dest.second));
    //Diagonal Distance (For 8 way)
    //return (abs(row - dest.first) + abs(col - dest.second));
    //Euclidean Distance (For anyway)
    return ((double) sqrt ((row - dest.first)*(row - dest.first) + (col - dest.second)*(col - dest.second)));
}
void backTrack (cell cellDetailed[][COL], std::pair<int, int> dest) {

    int row = dest.first;
    int col = dest.second;
    double pathCost = cellDetailed[row][col].f;
    std::cout << "The path cost is: " << pathCost << std::endl;
    std::stack <std::pair<int, int> > path;
		//std::cout << cellDetailed[row][col].parent_i << cellDetailed[row][col].parent_j << std::endl;
    while (!(cellDetailed[row][col].parent_i == row && cellDetailed[row][col].parent_j == col)) {
      	//std::cout << cellDetailed[row][col].parent_i << cellDetailed[row][col].parent_j << std::endl;
        path.push(std::make_pair(row, col));
        int temp_row = cellDetailed[row][col].parent_i;
        int temp_col = cellDetailed[row][col].parent_j;
      	row = temp_row;
      	col = temp_col;
    }

    path.push(std::make_pair(row, col));

    while(!path.empty()) {
        std::pair<int, int> cellToPath = path.top();
        path.pop();
        printf ("-> (%d, %d)", cellToPath.first, cellToPath.second);
    }
}
void AStar (int grid[][COL], std::pair <int, int> start, std::pair <int, int> dest) {

    //Best cases
    if (isValid(start.first, start.second) == false) {
        throw "This start point is not valid";
    }
    if (isValid(dest.first, dest.second) == false) {
        throw "This destination point is not valid";
    }
    if (isUnblocked(grid, start.first, start.second) == false || isUnblocked(grid, start.first, start.second) == false) {
        throw "One or both start and destination point is/are blocked by obstacle(s)";
    }
    if (isDestination(start.first, start.second, dest) == true) {
        throw "We are already here";
    }

    //Initializations
    bool closedList [ROW][COL];
    memset(closedList, false, sizeof(closedList));
    
    cell cellDetailed [ROW][COL];

    int r, c;
    for (r = 0; r < ROW; r++) {
        for (c = 0; c < COL; c++) {
            cellDetailed [r][c].f = DBL_INF;
            cellDetailed [r][c].h = DBL_INF;
            cellDetailed [r][c].g = DBL_INF;
            cellDetailed [r][c].parent_i = -1;
            cellDetailed [r][c].parent_j = -1;
        }
    }

    r = start.first;
    c = start.second;
    cellDetailed [r][c].f = 0.0;
    cellDetailed [r][c].h = 0.0;
    cellDetailed [r][c].g = 0.0;
    cellDetailed [r][c].parent_i = r;
    cellDetailed [r][c].parent_j = c;

    std::set <std::pair<double, std::pair<int, int> > > openedList;

    openedList.insert(std::make_pair(0.0, std::make_pair(r, c)));

    bool DestFound = false;

    while (!openedList.empty()) {
        std::pair<double, std::pair<int, int> > current = *openedList.begin();
        openedList.erase(openedList.begin());

        int r = current.second.first;
        int c = current.second.second;
        closedList [r][c] = true;

        double FNew, HNew, GNew;

        if (isValid (r - 1, c) == true) {
            if (isDestination(r - 1, c, dest) == true) {
                cellDetailed [r - 1][c].parent_i = r;
                cellDetailed [r - 1][c].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r - 1][c].g = cellDetailed[r][c].g + 1.0;
              	cellDetailed[r - 1][c].h = heurestic (r - 1, c, dest);
              	cellDetailed[r - 1][c].f = cellDetailed[r - 1][c].g + cellDetailed[r - 1][c].h;
                  
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r - 1][c] == false && isUnblocked(grid, r - 1, c) == true) {
                GNew = cellDetailed[r][c].g + 1.0;
                HNew = heurestic (r - 1, c, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r - 1][c].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r - 1, c)));

                    cellDetailed[r - 1][c].f = FNew;
                    cellDetailed[r - 1][c].g = GNew;
                    cellDetailed[r - 1][c].h = HNew;
                    cellDetailed[r - 1][c].parent_i = r;
                    cellDetailed[r - 1][c].parent_j = c;
                }
            }
        }
        if (isValid (r + 1, c) == true) {
            if (isDestination(r + 1, c, dest) == true) {
                cellDetailed[r + 1][c].parent_i = r;
                cellDetailed[r + 1][c].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r + 1][c].g = cellDetailed[r][c].g + 1.0;
              	cellDetailed[r + 1][c].h = heurestic (r + 1, c, dest);
              	cellDetailed[r + 1][c].f = cellDetailed[r + 1][c].g + cellDetailed[r + 1][c].h;
                
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r + 1][c] == false && isUnblocked(grid, r + 1, c) == true) {
                GNew = cellDetailed[r][c].g + 1.0;
                HNew = heurestic (r + 1, c, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r + 1][c].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r + 1, c)));

                    cellDetailed[r + 1][c].f = FNew;
                    cellDetailed[r + 1][c].g = GNew;
                    cellDetailed[r + 1][c].h = HNew;
                    cellDetailed[r + 1][c].parent_i = r;
                    cellDetailed[r + 1][c].parent_j = c;
                }
            }
        }
        if (isValid (r, c - 1) == true) {
            if (isDestination (r, c - 1, dest) == true) {
                cellDetailed[r][c - 1].parent_i = r;
                cellDetailed[r][c - 1].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r][c - 1].g = cellDetailed[r][c].g + 1.0;
              	cellDetailed[r][c - 1].h = heurestic (r, c - 1, dest);
              	cellDetailed[r][c - 1].f = cellDetailed[r][c - 1].g + cellDetailed[r][c - 1].h;
                
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r][c - 1] == false && isUnblocked(grid, r, c - 1) == true) {
                GNew = cellDetailed[r][c].g + 1.0;
                HNew = heurestic (r, c - 1, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r][c - 1].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r, c - 1)));

                    cellDetailed[r][c - 1].f = FNew;
                    cellDetailed[r][c - 1].g = GNew;
                    cellDetailed[r][c - 1].h = HNew;
                    cellDetailed[r][c - 1].parent_i = r;
                    cellDetailed[r][c - 1].parent_j = c;
                }
            }
        }
        if (isValid (r, c + 1) == true) {
            if (isDestination (r, c + 1, dest) == true) {
                cellDetailed[r][c + 1].parent_i = r;
                cellDetailed[r][c + 1].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r][c + 1].g = cellDetailed[r][c].g + 1.0;
              	cellDetailed[r][c + 1].h = heurestic (r, c + 1, dest);
              	cellDetailed[r][c + 1].f = cellDetailed[r][c + 1].g + cellDetailed[r][c + 1].h;
              
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r][c + 1] == false && isUnblocked(grid, r, c + 1) == true) {
                GNew = cellDetailed[r][c].g + 1.0;
                HNew = heurestic (r, c + 1, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r][c + 1].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r, c + 1)));

                    cellDetailed[r][c + 1].f = FNew;
                    cellDetailed[r][c + 1].g = GNew;
                    cellDetailed[r][c + 1].h = HNew;
                    cellDetailed[r][c + 1].parent_i = r;
                    cellDetailed[r][c + 1].parent_j = c;
                }
            }
        }
        if (isValid (r - 1, c - 1) == true) {
            if (isDestination (r - 1, c - 1, dest) == true) {
                cellDetailed[r - 1][c - 1].parent_i = r;
                cellDetailed[r - 1][c - 1].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r - 1][c - 1].g = cellDetailed[r][c].g + 1.4;
              	cellDetailed[r - 1][c - 1].h = heurestic (r - 1, c - 1, dest);
              	cellDetailed[r - 1][c - 1].f = cellDetailed[r - 1][c - 1].g + cellDetailed[r - 1][c - 1].h;
                  
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r - 1][c - 1] == false && isUnblocked(grid, r - 1, c - 1) == true) {
                GNew = cellDetailed[r][c].g + 1.4;
                HNew = heurestic (r - 1, c - 1, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r - 1][c - 1].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r - 1, c - 1)));

                    cellDetailed[r - 1][c - 1].f = FNew;
                    cellDetailed[r - 1][c - 1].g = GNew;
                    cellDetailed[r - 1][c - 1].h = HNew;
                    cellDetailed[r - 1][c - 1].parent_i = r;
                    cellDetailed[r - 1][c - 1].parent_j = c;
                }
            }
        }
        if (isValid (r - 1, c + 1) == true) {
            if (isDestination (r - 1, c + 1, dest) == true) {
                cellDetailed[r - 1][c + 1].parent_i = r;
                cellDetailed[r - 1][c + 1].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r - 1][c + 1].g = cellDetailed[r][c].g + 1.4;
              	cellDetailed[r - 1][c + 1].h = heurestic (r - 1, c + 1, dest);
              	cellDetailed[r - 1][c + 1].f = cellDetailed[r - 1][c + 1].g + cellDetailed[r - 1][c + 1].h;
                
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r - 1][c + 1] == false && isUnblocked(grid, r - 1, c + 1) == true) {
                GNew = cellDetailed[r][c].g + 1.4;
                HNew = heurestic (r - 1, c + 1, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r - 1][c + 1].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r - 1, c + 1)));

                    cellDetailed[r - 1][c + 1].f = FNew;
                    cellDetailed[r - 1][c + 1].g = GNew;
                    cellDetailed[r - 1][c + 1].h = HNew;
                    cellDetailed[r - 1][c + 1].parent_i = r;
                    cellDetailed[r - 1][c + 1].parent_j = c;
                }
            }
        }
        if (isValid (r + 1, c - 1) == true) {
            if (isDestination (r + 1, c - 1, dest) == true) {
                cellDetailed[r + 1][c - 1].parent_i = r;
                cellDetailed[r + 1][c - 1].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r + 1][c - 1].g = cellDetailed[r][c].g + 1.4;
              	cellDetailed[r + 1][c - 1].h = heurestic (r + 1, c - 1, dest);
              	cellDetailed[r + 1][c - 1].f = cellDetailed[r + 1][c - 1].g + cellDetailed[r + 1][c - 1].h;
                
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r + 1][c - 1] == false && isUnblocked(grid, r + 1, c - 1) == true) {
                GNew = cellDetailed[r][c].g + 1.4;
                HNew = heurestic (r + 1, c - 1, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r + 1][c - 1].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r + 1, c - 1)));

                    cellDetailed[r + 1][c - 1].f = FNew;
                    cellDetailed[r + 1][c - 1].g = GNew;
                    cellDetailed[r + 1][c - 1].h = HNew;
                    cellDetailed[r + 1][c - 1].parent_i = r;
                    cellDetailed[r + 1][c - 1].parent_j = c;
                }
            }
        }
        if (isValid (r + 1, c + 1) == true) {
            if (isDestination (r + 1, c + 1, dest) == true) {
                cellDetailed[r + 1][c + 1].parent_i = r;
                cellDetailed[r + 1][c + 1].parent_j = c;
                std::cout << "We found the destination" << std::endl;
              	cellDetailed[r + 1][c + 1].g = cellDetailed[r][c].g + 1.4;
              	cellDetailed[r + 1][c + 1].h = heurestic (r + 1, c + 1, dest);
              	cellDetailed[r + 1][c + 1].f = cellDetailed[r + 1][c + 1].g + cellDetailed[r + 1][c + 1].h;
                
                DestFound = true;
                backTrack(cellDetailed, dest);
                return;
            }
            else if (closedList[r + 1][c + 1] == false && isUnblocked(grid, r + 1, c + 1) == true) {
                GNew = cellDetailed[r][c].g + 1.4;
                HNew = heurestic (r + 1, c + 1, dest);
                FNew = GNew + HNew;

                if (FNew < cellDetailed[r + 1][c + 1].f) {

                    openedList.insert(std::make_pair(FNew, std::make_pair(r + 1, c + 1)));

                    cellDetailed[r + 1][c + 1].f = FNew;
                    cellDetailed[r + 1][c + 1].g = GNew;
                    cellDetailed[r + 1][c + 1].h = HNew;
                    cellDetailed[r + 1][c + 1].parent_i = r;
                    cellDetailed[r + 1][c + 1].parent_j = c;
                }
            }
        }
    }
}

int main () {
    int grid [ROW][COL] =
        {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
         {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
         {1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
         {1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
         {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
         {1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
         {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
         {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
         {1, 1, 1, 0, 0, 1, 1, 0, 1, 1},
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        std::pair <int, int> start = std::make_pair(0, 0);
        std::pair <int, int> destination = std::make_pair(9, 9);

        AStar(grid, start, destination);

        return 0;
}