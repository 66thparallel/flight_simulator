#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <thread>
#include <vector>
#include "sim_globals.h"
#include "evtol.h"


class Simulator {
    private:
        static Simulator * instance;

        Simulator();    // private constructor

        // A vector container of lambda threads that calls the eVTOL constructor.
        std::vector<std::thread> evtol_threads_;

    public:
        static Simulator * getInstance();

        void start();

};


#endif // SIMULATOR_H