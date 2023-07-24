#ifndef SIM_GLOBALS_H
#define SIM_GLOBALS_H

#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include <ctime>


namespace sim_globals {

    // 3 global chargers
    extern std::atomic<bool> charger1_ready;
    extern std::atomic<bool> charger2_ready;
    extern std::atomic<bool> charger3_ready;

    extern volatile bool simulation_running; // indicates if the simulation is currently running

    extern void simTimer();

    // Number of vehicles randomly generated for each company in this simulation. Used 
    // for calculating averages.
    extern std::map<std::string, int> vehicles_per_company;

    // Company vehicles and their total stats (timeInFlight, timeCharging, taitTimeForCharger,
    // numberOfFaults, distanceTraveled). Used for calculating averages.
    extern std::map<std::string, double> alpha_totals;
    extern std::map<std::string, double> beta_totals;
    extern std::map<std::string, double> charlie_totals;
    extern std::map<std::string, double> delta_totals;
    extern std::map<std::string, double> echo_totals;

    // Allow eVTOL objects to update stl maps in a thread-safe manner. Maps contain 
    // totals of companies' data.
    extern void updateAlphaData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles);
    extern void updateBetaData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles);
    extern void updateCharlieData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles);
    extern void updateDeltaData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles);
    extern void updateEchoData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles);

    // Calculate averages and get other stats
    extern int getAverageTimeInFlight(std::map<std::string, double> totals, std::string company_name);
    extern int getAverageTimeCharging(std::map<std::string, double> totals, std::string company_name);
    extern int getAverageWaitTimeForCharger(std::map<std::string, double> totals, std::string company_name);
    extern int getMaxNumberOfFaults(std::map<std::string, double> totals);
    extern double getTotalDistanceTraveled(std::map<std::string, double> totals, std::string company_name);

    // Present stats for each company
    extern void presentData();

} // namespace sim_globals

#endif // SIM_GLOBALS_H