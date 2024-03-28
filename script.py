import re

def convert_variable_name(variable_name):
    parts = variable_name.split('_')
    camel_case_name = parts[0] + ''.join(word.capitalize() for word in parts[1:])
    return camel_case_name[0].lower() + camel_case_name[1:]

def convert_cpp_code(input_code):
    # Define a regular expression to match variable names
    variable_pattern = r'\b([a-zA-Z][a-zA-Z0-9_]*)\b'
    # Find all variable names in the input code
    variable_names = re.findall(variable_pattern, input_code)
    # Replace variable names with converted names
    converted_code = input_code
    for name in variable_names:
        converted_name = convert_variable_name(name)
        converted_code = converted_code.replace(name, converted_name)
    return converted_code

# Example C++ code
cpp_code = """
#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <utility>

extern std::vector<std::pair<double, double>> locations;
extern std::vector<double> demand_weights;
extern std::vector<std::pair<double,double>> battery_charging_stations;
extern std::vector<std::pair<double,double>> battery_swap_stations;
extern std::vector<double> mx_battery_levels;
extern std::vector<double> mx_cost_allowed;
extern std::vector<double> mx_weight_allowed;
extern int mx_vehicles;
extern int mx_customers;
extern int mx_battery_charging_stations;
extern int mx_battery_swapping_stations;
extern double fast_charging_time_per_unit_of_charge;
extern double medium_charging_time_per_unit_of_charge;
extern double slow_charging_time_per_unit_of_charge;
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
#endif 
"""

# Convert the C++ code
converted_code = convert_cpp_code(cpp_code)
print(converted_code)
