#include <iostream>
#include <set>

#define ROW 8
#define COL 8
const int DBL_INF = 1e9;

bool isValid (int row, int col) {
    return (row >= 0) && (col >= 0) && (row < ROW) && (col < COL);
}

bool isBlocked (int grid [][COL], int row, int col) {
    return grid [row][col] == 0;
}

bool areNeighboursBlocked(int grid [][COL], int r, int c) {
     return (isBlocked(grid, r - 1, c) && isValid(r - 1, c)) 
     &&     (isBlocked(grid, r + 1, c) && isValid(r + 1, c))
     &&     (isBlocked(grid, r, c - 1) && isValid(r, c - 1))
     &&     (isBlocked(grid, r, c + 1) && isValid(r, c + 1));
}

void result (double gCostMap [][COL]) {
    for (int r = 0; r < ROW; ++r) {
        std::cout << "{";
        for (int c = 0; c < COL; ++c) {
            std::cout << gCostMap[r][c]<< ", ";
        }
        std::cout << "}\n" <<std::endl;
    }
}

void Disparity (int grid[][COL]) {

    //Initializations
    bool visited [ROW][COL];
    std::memset(visited, false, sizeof(visited));
    
    double gCostMap [ROW][COL];

    std::set <std::pair<double, std::pair<int, int> > > openedList;

    int r, c;
    for (r = 0; r < ROW; r++) {
        for (c = 0; c < COL; c++) {
            if (grid[r][c] == 1) {
                gCostMap [r][c]= DBL_INF;
            }
            if (grid[r][c] == 0) {
                gCostMap [r][c]= 0;
                if (! areNeighboursBlocked(grid, r, c)) {
                    openedList.insert(std::make_pair(0.0, std::make_pair(r, c)));
                    //std::cout << "(" << r << "," << c << ")->";
                }
            }
        }
    }

    while (!openedList.empty()) {
        auto current = *openedList.begin();
        openedList.erase(openedList.begin());

        int i = current.second.first;
        int j = current.second.second;
        visited [i][j] = true;

        double GNew;

        if (isValid (i - 1, j) && isBlocked(grid, i - 1, j) == false && visited[i - 1][j] == false) {
            GNew = gCostMap[i][j]+ 1.0;

            if (GNew < gCostMap[i - 1][j]) {
                openedList.insert(std::make_pair(GNew, std::make_pair(i - 1, j)));

                gCostMap[i - 1][j]= GNew;
            }
        }
        if (isValid (i + 1, j)  && isBlocked(grid, i + 1, j) == false && visited[i + 1][j] == false) {
            GNew = gCostMap[i][j]+ 1.0;

            if (GNew < gCostMap[i + 1][j]) {
                openedList.insert(std::make_pair(GNew, std::make_pair(i + 1, j)));

                gCostMap[i + 1][j]= GNew;
            }
        }
        if (isValid (i, j + 1)  && isBlocked(grid, i, j + 1) == false && visited[i][j + 1] == false) {
            GNew = gCostMap[i][j]+ 1.0;

            if (GNew < gCostMap[i][j + 1]) {
                openedList.insert(std::make_pair(GNew, std::make_pair(i, j + 1)));

                gCostMap[i][j + 1]= GNew;
            }
        }
        if (isValid (i, j - 1)  && isBlocked(grid, i, j - 1) == false && visited[i][j - 1] == false) {
            GNew = gCostMap[i][j]+ 1.0;

            if (GNew < gCostMap[i][j - 1]) {
                openedList.insert(std::make_pair(GNew, std::make_pair(i, j - 1)));

                gCostMap[i][j - 1]= GNew;
            }
        }
    }
    result (gCostMap);
}

int main () {
    int grid[ROW][COL] =
        {{1, 1, 1, 1, 1, 0, 0, 1},
         {1, 0, 1, 1, 0, 0, 0, 1},
         {1, 1, 1, 0, 1, 0, 1, 1},
         {1, 1, 1, 0, 1, 1, 1, 1},
         {1, 1, 1, 1, 1, 1, 1, 1},
         {1, 1, 1, 1, 1, 1, 1, 1},
         {1, 1, 0, 1, 1, 0, 1, 1},
         {1, 0, 1, 1, 1, 1, 1, 1},
        };

        Disparity(grid);

        return 0;
}