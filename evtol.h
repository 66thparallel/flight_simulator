#ifndef EVTOL_H
#define EVTOL_H

#include <string>
#include <thread>
#include <algorithm>
#include <atomic>
#include "sim_globals.h"


class eVTOL {

    private:
        const std::string company_name_;
        const double cruise_speed_;
        const double battery_capacity_;
        const int time_to_charge_;
        const double energy_use_at_cruise_;
        const int passenger_count_;
        const double probability_of_fault_;

        // Store data for calculating averages after simulation ends
        std::map<std::string, double> totals_map;

        // Randomly determine if the vehicle develops faults in this simulation
        void getNumberOfFaults();

        // Gets the number of passenger miles for this vehicle
        void getPassengerMiles();

        // Look for an available charger when battery power runs out
        void chargeVehicle();

        // Begin flight
        void fly();

    public:
        // Constructor initializes vehicle
        eVTOL(const std::string company_name, const double cruise_speed, const double battery_capacity, const int time_to_charge, const double energy_use_at_cruise, const int passenger_count, double probability_of_fault);

        void start();

        void end();

        // Unit test for eVTOL class
        friend void eVTOLUnitTest(const std::string company_name, const int cruise_speed, const int battery_capacity, const int time_to_charge, const double energy_use_at_cruise, const int passenger_count, double probability_of_fault);

        // Unit test for Simulator class
        friend void SimulatorUnitTest();

};


#endif // EVTOL_H