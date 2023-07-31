### Flight Simulator

**About**  
This is a simple flight simulator for twenty eVTOL aircraft. A random 
number of vehicles from five different companies are selected to participate 
in the simulation. Each manufacturer's vehicle has different characteristics. 
For example, Delta eVTOL vehicles have a cruise speed of 90 mph and a battery 
capacity of 120 kWh. More details about each eVTOL vehicle are included in 
the presentation slides. The goal is to run a 3 minute simulation, where each 
simulated second is equivalent to 1 minute of simulated time. So, a 3-minute 
simulation represents 3 hours of simulated data. Some of the constraints 
include: 

* There are only 3 battery chargers that must be shared among all vehicles.  
* A charger can only be used by 1 vehicle at a time.

At the end of the simulation the program will display for each company:  
* Average time in flight  
* Average time charging  
* Average time waiting in line to charge  
* Maximum number of faults  
* Total distance traveled by passengers

This simulation assumes the following: All vehicles start with a fully charged 
battery. The vehicle is airborne for the full use of the battery. The vehicle 
instanteously reaches cruise speed and instanteously gets in line for the charger 
when it runs out of battery.


**Files**  
evtol.h  
evtol.cpp  
sim_global.h  
sim_global.cpp  
simulator.h  
simulator.cpp  
main.cpp  
makefile  

**Requirements**  
Please copy all files into the working directory. This program uses C++11 and later.
  
**Instructions**  
To run from the command line enter the following:  
_g++ -std=c++11 -c *.cpp_  
_g++ -std=c++11 *.o -o evtol.out_  
_./evtol.out_  

A Cmake makefile is available. If cmake is installed, type _make_ at the command line to run the program. Results are output to the console.
  
  
**Notes**
- Some companies have vehicles that have battery charging times with a fractional value 
of a second (for example, Delta company vehicles take 37.2 seconds to charge). It took 
too long to implement milliseconds for a precise time, so I just took the integer 
value of the battery charging time (for Delta it's 37 seconds). If I were building an 
actual simulator, I would convert values like battery charging time to milliseconds 
and then convert them back to seconds.

- Please let me know if you have any questions.
