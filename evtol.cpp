#include <iostream>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sim_globals.h"
#include "simulator.h"
#include "evtol.h"


std::map<std::string, double> totals_map {{"time_in_flight", 0}, {"time_charging", 0}, {"wait_time_for_charger", 0}, {"number_of_faults", 0}, {"battery_range", 0}, {"miles_per_minute", 0}, {"battery_range_time", 0}, {"distance_traveled", 0}, {"passenger_miles", 0}};

void eVTOL::getNumberOfFaults() {
    
    // I made the assumption that there will be at most one fault per hour.
    int faults = 0, count = 0, result = 0;
    srand(time(NULL));

    while (count < 3) {    // 3 minutes
        result = rand() % 100 + 1;    //generate a random number from 1 to 100
        if (result <= (probability_of_fault_ * 100))   // percent chance of getting a fault
            faults++;
        count++;
    }
    totals_map["number_of_faults"] = faults;
}

void eVTOL::getPassengerMiles() {
    totals_map["passenger_miles"] = totals_map["distance_traveled"] * passenger_count_;
}

void eVTOL::fly() {

    while (sim_globals::simulation_running==true) {
        
        int flying_time = 0;

        while ((flying_time < totals_map["battery_range_time"]) && (sim_globals::simulation_running==true)) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            flying_time++;
            totals_map["time_in_flight"]++;
            totals_map["distance_traveled"] += totals_map["miles_per_minute"];
        }
        flying_time = 0;

        chargeVehicle();
    }

    end();

}

void eVTOL::chargeVehicle() {

    while (sim_globals::simulation_running==true) {

        int charging_time = 0;

        if (sim_globals::charger1_ready.exchange(false)) {
            std::cout << company_name_ << " vehicle is charging on charger 1.\n";
            while ((charging_time < time_to_charge_) && (sim_globals::simulation_running==true)) {
                charging_time++;
                totals_map["time_charging"]++;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            sim_globals::charger1_ready = true;
            return;
        }
        else if (sim_globals::charger2_ready.exchange(false)) {
            std::cout << company_name_ << " vehicle is charging on charger 2.\n";
            while ((charging_time < time_to_charge_) && (sim_globals::simulation_running==true)) {
                charging_time++;
                totals_map["time_charging"]++;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            sim_globals::charger2_ready = true;
            return;
        }
        else if (sim_globals::charger3_ready.exchange(false)) {
            std::cout << company_name_ << " vehicle is charging on charger 3.\n";
            while ((charging_time < time_to_charge_) && (sim_globals::simulation_running==true)) {
                charging_time++;
                totals_map["time_charging"]++;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            sim_globals::charger3_ready = true;
            return;
        }
        else {
            totals_map["wait_time_for_charger"]++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }

}

eVTOL::eVTOL(const std::string company_name, const double cruise_speed, const double battery_capacity, const int time_to_charge, const double energy_use_at_cruise, const int passenger_count, double probability_of_fault)
    : company_name_(company_name), cruise_speed_(cruise_speed), battery_capacity_(battery_capacity), time_to_charge_(time_to_charge), energy_use_at_cruise_(energy_use_at_cruise), passenger_count_(passenger_count), probability_of_fault_(probability_of_fault) {

    start();

}

void eVTOL::start() {

    // Calculate the battery range, battery range time, and miles per minute
    totals_map["miles_per_minute"] = (double)(cruise_speed_ / 60);
    totals_map["battery_range_time"] = (int)((battery_capacity_ / energy_use_at_cruise_) / totals_map["miles_per_minute"]);

    // Wait for simulation to start.
    while (sim_globals::simulation_running==false) {}

    fly();

}

void eVTOL::end() {
    /* Adds the values of time_in_flight, time_charging, wait_time_for_charger, number_of_faults, 
    distance_traveled to stl maps (alpha_maps, beta_maps, charlie_maps, etc.) in sim_globals.h.
    */
    getNumberOfFaults();
    getPassengerMiles();

    if (company_name_=="alpha") {
        sim_globals::updateAlphaData(totals_map["time_in_flight"], totals_map["time_charging"], totals_map["wait_time_for_charger"], totals_map["number_of_faults"], totals_map["passenger_miles"]);
    }
    else if (company_name_=="beta") {
        sim_globals::updateBetaData(totals_map["time_in_flight"], totals_map["time_charging"], totals_map["wait_time_for_charger"], totals_map["number_of_faults"], totals_map["passenger_miles"]);
    }
    else if (company_name_=="charlie") {
        sim_globals::updateCharlieData(totals_map["time_in_flight"], totals_map["time_charging"], totals_map["wait_time_for_charger"], totals_map["number_of_faults"], totals_map["passenger_miles"]);
    }
    else if (company_name_=="delta") {
        sim_globals::updateDeltaData(totals_map["time_in_flight"], totals_map["time_charging"], totals_map["wait_time_for_charger"], totals_map["number_of_faults"], totals_map["passenger_miles"]);
    }
    else if (company_name_=="echo") {  
        sim_globals::updateEchoData(totals_map["time_in_flight"], totals_map["time_charging"], totals_map["wait_time_for_charger"], totals_map["number_of_faults"], totals_map["passenger_miles"]);
    }

}

/* If I had more time I would instantiate an eVTOL class object in this function and test out 
the fly() function, findCharger(), and chargeBattery() functions one at a time. I would 
also create another friend function to test the Simulator class.
*/
void eVTOLUnitTest(const std::string company_name, const int cruise_speed, const int battery_capacity, const int time_to_charge, const double energy_use_at_cruise, const int passenger_count, double probability_of_fault) {} 

void SimulatorUnitTest() {}