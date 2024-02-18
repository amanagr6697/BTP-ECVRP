#include "Variables.h"

std::vector<std::pair<double, double>> locations = {
    {23,27}, //depo location
    {20, 15},
    {10, 25},
    {15, 10},
    {30, 20},
    {25, 5},
    {15, 30},
    {8, 18},
    {22, 28},
    {21, 12},
    {16, 13}};

std::vector<double> demand_weights = {0,20, 12, 28, 18, 15, 25, 13, 17, 30, 10};

std::vector<double> mx_battery_levels = {0,950, 540, 220, 340};

std::vector<double> mx_cost_allowed = {0,4500, 2000, 400, 1200};

std::vector<double> mx_weight_allowed = {0,80, 50, 70, 60};

double fast_ch_time_per_unit_of_charge = 0.5;

double medium_ch_time_per_unit_of_charge = 0.8;

double slow_ch_time_per_unit_of_charge = 1.3;

double battery_swapping_cost = 50;

double battery_swapping_time = 0.2;

int mx_vehicles = 4;

int mx_customers = 10;

std::vector<std::pair<double, double>> battery_ch_stations = {
    {23,27},
    {13, 12},
    {19, 12},
    {13, 8},
    {15,19},
    {8,19},{18,12},{14,18},{19,12},{8,9},{3,9},{2,11}};

std::vector<std::pair<double, double>> battery_swap_stations = {
    {23,27},
    {15, 11},
    {18, 7},
    {29, 13}};

double discharging_const = 10;

double temperature = 300;

double sclaing_factor = 0.03;

double parameter = 0.5;

int fast_time_chargers = 2;

int medium_time_chargers = 2;

int slow_time_chargers = 4;

double cost_per_unit_charge_of_fast = 5;
double cost_per_unit_charge_of_medium = 3;
double cost_per_unit_charge_of_slow = 1;

std::vector<double> speed_of_vehicles = {0, 12, 9, 13, 17};

std::vector<double> weight_factor_for_speed = {0, 0.13, 0.17, 0.09, 0.03};

std::vector<double> weight_factor_for_distance = {0, 0.13, 0.17, 0.09, 0.03};

double charge_per_unit_of_distance = 7;

int mx_battery_charging_stations =11;