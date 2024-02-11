#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <utility>

extern std::vector<std::pair<double, double>> locations;
extern std::vector<double> demand_weights;
extern std::pair<double, double> depot_location;
extern std::vector<double> mx_battery_levels;
extern std::vector<double> mx_cost_allowed;
extern std::vector<double> mx_weight_allowed;
extern double fast_ch_time;
extern int mx_vehicles;
extern int mx_customers;
extern double medium_ch_time;
extern double slow_ch_time;
extern double battery_swapping_cost;
extern double battery_swapping_time;
extern std::vector<std::pair<double,double>> battery_ch_stations;
extern std::vector<std::pair<double,double>> battery_swap_stations;
extern double discharging_const;
extern double temperature; //in Kelvin
extern double sclaing_factor;
extern double parameter;
#endif 
