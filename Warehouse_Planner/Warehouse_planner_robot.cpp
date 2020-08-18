//"Let no man who is not a Mathematician read the elements of my work" said Leonardo Da Vinci
#include "Warehouse_planner_robot.hpp"

void OTTO::initializing (int number_of_waypoints) {
    int the_end_point = number_of_waypoints + 1;
    adj.clear();
    the_map.clear();
    adj.resize(number_of_waypoints + 2);
    the_map.resize(number_of_waypoints + 2);
    the_map[0] = std::make_pair(std::make_pair(0, 0), INT_INF);
    the_map[the_end_point] = std::make_pair(std::make_pair(100, 100), INT_INF);
}

auto OTTO::heurestic (int first_x, int first_y, int second_x, int second_y) {
    return (((double) sqrt ((first_x - second_x)*(first_x - second_x) + (first_y - second_y)*(first_y - second_y))) / 2);
}

void OTTO::map_creation (int element, int x_axis, int y_axis, int penalty) {
    the_map[element] = std::make_pair(std::make_pair(x_axis, y_axis), penalty);
}

void OTTO::graph_construction () {
    for (int element = 0; element < adj.size() - 1; ++element) {
        int penalty = 0;
        for (int second_element = element + 1; second_element < adj.size(); ++second_element) {
            if (second_element - element > 1) {
                penalty += the_map[second_element - 1].second;
            }
            auto the_heurestic = heurestic (the_map[element].first.first, the_map[element].first.second, the_map[second_element].first.first, the_map[second_element].first.second);
            auto weight = the_heurestic + penalty + 10;
            adj[element].push_back(std::make_pair(second_element, weight));

        }
    }
}

double OTTO::minimum_distance_finder () {
    std::vector<bool> visited(adj.size(), false);
    std::vector<double> times(adj.size(), INT_INF);
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double> >, std::greater<std::pair<int, double> > > pq;
    pq.push(std::make_pair(0, 0));
    times[0] = 0;

    while (!pq.empty()) {
        auto u = (pq.top()).second;
        pq.pop();
        visited[u] = true;
        std::list<std::pair<int, double> >::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++) {
            auto v = (*it).first;
            auto w = (*it).second;
            if (visited[v] == false && times[u] + w < times[v]) {
                times[v] = times[u] + w;
                pq.push(std::make_pair(times[v], v));
            }
        }
    }
    return times[adj.size() - 1];
}