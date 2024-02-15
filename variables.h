#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <utility>

extern std::vector<std::pair<double, double>> locations;
extern std::vector<double> demand_weights;
extern std::pair<double, double> depot_location;
extern std::vector<std::pair<double,double>> battery_ch_stations;
extern std::vector<std::pair<double,double>> battery_swap_stations;
extern std::vector<double> mx_battery_levels;
extern std::vector<double> mx_cost_allowed;
extern std::vector<double> mx_weight_allowed;
extern int mx_vehicles;
extern int mx_customers;
extern int mx_battery_charging_stations;
extern double mx_battery_swapping_stations;
extern double fast_ch_time_per_unit_of_charge;
extern double medium_ch_time_per_unit_of_charge;
extern double slow_ch_time_per_unit_of_charge;
extern double battery_swapping_cost;
extern double battery_swapping_time;
extern double discharging_const;
extern double temperature; //in Kelvin
extern double sclaing_factor;
extern double parameter;
extern int fast_time_chargers;
extern int medium_time_chargers;
extern int slow_time_chargers;
extern double cost_per_unit_charge_of_fast;
extern double cost_per_unit_charge_of_medium;
extern double cost_per_unit_charge_of_slow;
extern std::vector<double> speed_of_vehicles;
extern std::vector<double> weight_factor_for_speed;
extern std::vector<double> weight_factor_for_distance;
extern double charge_per_unit_of_distance;
#endif 
