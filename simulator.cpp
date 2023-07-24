#include <algorithm>
#include <atomic>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include <utility>
#include "sim_globals.h"
#include "evtol.h"
#include "simulator.h"


Simulator::Simulator() {}

Simulator * Simulator::getInstance() {
    if (!instance) 
        instance = new Simulator;
    return instance;
}

Simulator * Simulator::instance = 0;

void Simulator::start() {

    int random_number = 0;
    srand(time(NULL));

    // Spawn a thread for each vehicle
    for (int i = 0; i < 20; i++) {

        // Generates a random number from 1 to 5, where 1 indicates alpha, 2 indicates beta, etc. This number determines which company's eVTOL object will be created.
        random_number = rand() % 5 + 1;

        // Create threads for the eVTOL objects
        switch(random_number) {
            case 1: {
                evtol_threads_.push_back(std::thread([]() {
                    eVTOL vehicle {"alpha", 120, 320, (int)(0.6 * 60), 1.6, 4, 0.25};
                }));
                sim_globals::vehicles_per_company["alpha"]++;
                break;
            } 
            case 2: {
                evtol_threads_.push_back(std::thread([]() {
                    eVTOL vehicle {"beta", 100, 100, (int)(0.2 * 60), 1.5, 5, 0.10};
                }));
                sim_globals::vehicles_per_company["beta"]++;
                break;
            }
            case 3: {
                evtol_threads_.push_back(std::thread([]() {
                    eVTOL vehicle {"charlie", 160, 220, (int)(0.8 * 60), 2.2, 3, 0.05};
                }));
                sim_globals::vehicles_per_company["charlie"]++;
                break;
            }
            case 4: {
                evtol_threads_.push_back(std::thread([]() {
                    eVTOL vehicle {"delta", 90, 120, (int)(0.62 * 60), 0.8, 2, 0.22};
                }));
                sim_globals::vehicles_per_company["delta"]++;
                break;
            }
            case 5: {
                evtol_threads_.push_back(std::thread([]() {
                    eVTOL vehicle {"echo", 30, 150, (int)(0.3 * 60), 5.8, 2, 0.61};
                }));
                sim_globals::vehicles_per_company["echo"]++;
            }
        }
    }

    // Displays the number of vehicles generated for each company
    std::cout << "\n=== Number of vehicles per company ===\n";
    for (auto & vehicle : sim_globals::vehicles_per_company) {
        std::cout << vehicle.first << " company has " << vehicle.second << " vehicles.\n";
    }

    std::thread t_timer(sim_globals::simTimer);
    t_timer.join();

    std::for_each(evtol_threads_.begin(), evtol_threads_.end(), [](std::thread &t) {
        t.join();
    });

    sim_globals::presentData();  // display calculated averages and other data to the console

}