//"Let no man who is not a Mathematician read the elements of my work" said Leonardo Da Vinci
#ifndef Warehousing_robot
#define Warehousing_robot

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cmath>

class OTTO {
    public:
        void initializing (int number_of_waypoints);
        auto heurestic (int first_x, int first_y, int second_x, int second_y);
        void map_creation (int element, int x_axis, int y_axis, int penalty);
        void graph_construction ();
        double minimum_distance_finder ();
    private:
        std::vector<std::list<std::pair<int, double > > > adj;
        std::vector<std::pair<std::pair<int, int>, int> > the_map;
        const int INT_INF = 1e9; //INT_MAX
};

#endif //Warehouse_robot