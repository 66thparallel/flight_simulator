#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sim_globals.h"
#include "evtol.h"


namespace sim_globals {

    std::atomic<bool> charger1_ready (true);
    std::atomic<bool> charger2_ready (true);
    std::atomic<bool> charger3_ready (true);

    volatile bool simulation_running = false;

    void simTimer() {
        std::cout << "\n=== Simulation start ===\n";
        simulation_running = true;
        std::this_thread::sleep_for (std::chrono::minutes(3));
        simulation_running = false;
        std::cout << "\n=== Simulation end ===\n(Data will be displayed shortly)\n" << std::endl;
    }
    
    std::map<std::string, int> vehicles_per_company {{"alpha", 0}, {"beta", 0}, {"charlie", 0}, {"delta", 0}, {"echo", 0}};

    std::map<std::string, double> alpha_totals {{"total_time_in_flight", 0}, {"total_time_charging", 0}, {"total_wait_time_for_charger", 0}, {"max_number_of_faults", 0}, {"total_passenger_miles", 0}};
    std::map<std::string, double> beta_totals {{"total_time_in_flight", 0}, {"total_time_charging", 0}, {"total_wait_time_for_charger", 0}, {"max_number_of_faults", 0}, {"total_passenger_miles", 0}};
    std::map<std::string, double> charlie_totals {{"total_time_in_flight", 0}, {"total_time_charging", 0}, {"total_wait_time_for_charger", 0}, {"max_number_of_faults", 0}, {"total_passenger_miles", 0}};
    std::map<std::string, double> delta_totals {{"total_time_in_flight", 0}, {"total_time_charging", 0}, {"total_wait_time_for_charger", 0}, {"max_number_of_faults", 0}, {"total_passenger_miles", 0}};
    std::map<std::string, double> echo_totals {{"total_time_in_flight", 0}, {"total_time_charging", 0}, {"total_wait_time_for_charger", 0}, {"max_number_of_faults", 0}, {"total_passenger_miles", 0}};

    // Locks for stl maps containing total data for all eVTOL objects
    static std::mutex alpha_mtx;
    static std::mutex beta_mtx;
    static std::mutex charlie_mtx;
    static std::mutex delta_mtx;
    static std::mutex echo_mtx;

    // Allows eVTOL objects to update the stl maps above in a thread-safe manner
    void updateAlphaData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles) {
        std::lock_guard<std::mutex> guard(alpha_mtx);
        alpha_totals["total_time_in_flight"] += time_in_flight;
        alpha_totals["total_time_charging"] += time_charging;
        alpha_totals["total_wait_time_for_charger"] += wait_time_for_charger;
        if (alpha_totals["max_number_of_faults"] < number_of_faults) { alpha_totals["max_number_of_faults"] = number_of_faults; }
        alpha_totals["total_passenger_miles"] += passenger_miles;
    }

    void updateBetaData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles) {
        std::lock_guard<std::mutex> guard(beta_mtx);
        beta_totals["total_time_in_flight"] += time_in_flight;
        beta_totals["total_time_charging"] += time_charging;
        beta_totals["total_wait_time_for_charger"] += wait_time_for_charger;
        if(beta_totals["max_number_of_faults"] < number_of_faults) { beta_totals["max_number_of_faults"] = number_of_faults; }
        beta_totals["total_passenger_miles"] += passenger_miles;
    }

    void updateCharlieData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles) {
        std::lock_guard<std::mutex> guard(charlie_mtx);
        charlie_totals["total_time_in_flight"] += time_in_flight;
        charlie_totals["total_time_charging"] += time_charging;
        charlie_totals["total_wait_time_for_charger"] += wait_time_for_charger;
        if(charlie_totals["max_number_of_faults"] < number_of_faults) { charlie_totals["max_number_of_faults"] = number_of_faults; }
        charlie_totals["total_passenger_miles"] += passenger_miles;

    }
    void updateDeltaData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles) {
        std::lock_guard<std::mutex> guard(delta_mtx);
        delta_totals["total_time_in_flight"] += time_in_flight;
        delta_totals["total_time_charging"] += time_charging;
        delta_totals["total_wait_time_for_charger"] += wait_time_for_charger;
        if(delta_totals["max_number_of_faults"] < number_of_faults) { delta_totals["max_number_of_faults"] = number_of_faults; }
        delta_totals["total_passenger_miles"] += passenger_miles;
    }
    void updateEchoData(int time_in_flight, int time_charging, int wait_time_for_charger, int number_of_faults, int passenger_miles) {
        std::lock_guard<std::mutex> guard(echo_mtx);
        echo_totals["total_time_in_flight"] += time_in_flight;
        echo_totals["total_time_charging"] += time_charging;
        echo_totals["total_wait_time_for_charger"] += wait_time_for_charger;
        if(echo_totals["max_number_of_faults"] < number_of_faults) { echo_totals["max_number_of_faults"] = number_of_faults; }
        echo_totals["total_passenger_miles"] += passenger_miles;
    }

    int getAverageTimeInFlight(std::map<std::string, double> totals, std::string company_name) {
        return (int)(totals["total_time_in_flight"] / vehicles_per_company[company_name]);
    }
    int getAverageTimeCharging(std::map<std::string, double> totals, std::string company_name) {
        return (int)(totals["total_time_charging"] / vehicles_per_company[company_name]);
    }
    int getAverageWaitTimeForCharger(std::map<std::string, double> totals, std::string company_name) {
        return (int)(totals["total_wait_time_for_charger"] / vehicles_per_company[company_name]);
    }
    int getMaxNumberOfFaults(std::map<std::string, double> totals) {
        return (int)(totals["max_number_of_faults"]);
    }
    double getTotalDistanceTraveled(std::map<std::string, double> totals, std::string company_name) {
        return totals["total_passenger_miles"];
    }

    void presentData() {

        // Output data
        std::cout << "\n*** Results for all companies ***" << "\n";
        std::cout << "Company name: alpha" << "\n";
        std::cout << "Number of vehicles: " << vehicles_per_company["alpha"] << "\n";
        std::cout << "Average time in flight: " << getAverageTimeInFlight(alpha_totals, "alpha") << " minutes\n";
        std::cout << "Average time charging: " << getAverageTimeCharging(alpha_totals, "alpha") << " minutes\n";
        std::cout << "Average time waiting for charger: " << getAverageWaitTimeForCharger(alpha_totals, "alpha") << " minutes\n";
        std::cout << "Maximum number of faults in a vehicle: " << getMaxNumberOfFaults(alpha_totals) << "\n";
        std::cout << "Total passenger miles of all vehicles: " << getTotalDistanceTraveled(alpha_totals, "alpha") << " miles\n\n";

        std::cout << "Company name: beta" << "\n";
        std::cout << "Number of vehicles: " << vehicles_per_company["beta"] << "\n";
        std::cout << "Average time in flight: " << getAverageTimeInFlight(beta_totals, "beta") << " minutes\n";
        std::cout << "Average time charging: " << getAverageTimeCharging(beta_totals, "beta") << " minutes\n";
        std::cout << "Average time waiting for charger: " << getAverageWaitTimeForCharger(beta_totals, "beta") << " minutes\n";
        std::cout << "Maximum number of faults in a vehicle: " << getMaxNumberOfFaults(beta_totals) << "\n";
        std::cout << "Total passenger miles of all vehicles: " << getTotalDistanceTraveled(beta_totals, "beta") << " miles\n\n";

        std::cout << "Company name: charlie" << "\n";
        std::cout << "Number of vehicles: " << vehicles_per_company["charlie"] << "\n";
        std::cout << "Average time in flight: " << getAverageTimeInFlight(charlie_totals, "charlie") << " minutes\n";
        std::cout << "Average time charging: " << getAverageTimeCharging(charlie_totals, "charlie") << " minutes\n";
        std::cout << "Average time waiting for charger: " << getAverageWaitTimeForCharger(charlie_totals, "charlie") << " minutes\n";
        std::cout << "Maximum number of faults in a vehicle: " << getMaxNumberOfFaults(charlie_totals) << "\n";
        std::cout << "Total passenger miles of all vehicles: " << getTotalDistanceTraveled(charlie_totals, "charlie") << " miles\n\n";

        std::cout << "Company name: delta" << "\n";
        std::cout << "Number of vehicles: " << vehicles_per_company["delta"] << "\n";
        std::cout << "Average time in flight: " << getAverageTimeInFlight(delta_totals, "delta") << " minutes\n";
        std::cout << "Average time charging: " << getAverageTimeCharging(delta_totals, "delta") << " minutes\n";
        std::cout << "Average time waiting for charger: " << getAverageWaitTimeForCharger(delta_totals, "delta") << " minutes\n";
        std::cout << "Maximum number of faults in a vehicle: " << getMaxNumberOfFaults(delta_totals) << "\n";
        std::cout << "Total passenger miles of all vehicles: " << getTotalDistanceTraveled(delta_totals, "delta") << " miles\n\n";

        std::cout << "Company name: echo" << "\n";
        std::cout << "Number of vehicles: " << vehicles_per_company["echo"] << "\n";
        std::cout << "Average time in flight: " << getAverageTimeInFlight(echo_totals, "echo") << " minutes\n";
        std::cout << "Average time charging: " << getAverageTimeCharging(echo_totals, "echo") << " minutes\n";
        std::cout << "Average time waiting for charger: " << getAverageWaitTimeForCharger(echo_totals, "echo") << " minutes\n";
        std::cout << "Maximum number of faults in a vehicle: " << getMaxNumberOfFaults(echo_totals) << "\n";
        std::cout << "Total passenger miles of all vehicles: " << getTotalDistanceTraveled(echo_totals, "echo") << " miles\n\n";

        std::cout << std::endl;   
    }

} // namespace sim_globals