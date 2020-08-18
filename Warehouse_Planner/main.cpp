//"Let no man who is not a Mathematician read the elements of my work" said Leonardo Da Vinci
#include "Warehouse_planner_robot.hpp"
#include <iostream>

int main () {
    int number_of_waypoints, waypoint;
    std::scanf("%d", &number_of_waypoints);

    OTTO factory;
    factory.initializing(number_of_waypoints);

    while(number_of_waypoints) {
        for(waypoint = 1; waypoint <= number_of_waypoints; ++waypoint) { 
            int x_axis, y_axis, penalty;
            std::scanf("%d %d %d", &x_axis, &y_axis, &penalty);
            factory.map_creation(waypoint, x_axis, y_axis, penalty);
        }

        factory.graph_construction();
        
        double minimum_time = factory.minimum_distance_finder();

        std::printf("\n%.3f", minimum_time);
        std::scanf("%d", &number_of_waypoints);
        factory.initializing(number_of_waypoints);
    }
    return 0;
}