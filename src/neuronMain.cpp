/**
 * @file   neuronMain.cpp
 * @author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  Main programm to simulate a network of neurons
 */


#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <random>
#include "neuron.hpp"
#include "network.hpp"


using namespace std;

/** progressPrinting
 * 
 * @note print a progress indicator on the terminal
 */
void progressPrinting(double step); 

int main()
{
/// Initialisation -----------------------------------------------------
	
	cout << "** INITIALIZATION **" << endl;
	
	double simStep(0); //!< the step at wich the simulation is
	int progress(0); //!< indicate the progress of the simulation
	int percent(0); //!< the progress at every step is recalculated and save in this variable
	Network network("Neurons_Spikes.txt");
	
	
/// Lancement de la simulation -----------------------------------------
	
	while(simStep <= total_steps) {
		
		network.update(simStep);
		
		percent = simStep/total_steps*100;
		
		if(percent != progress){
			progressPrinting(percent);
			
			progress = percent;
		}
		
		simStep += 1;
		
	}
	
	cout << endl;
	cout << "** SIMULATION DONE **" << endl;
	
	return 0;
}




/** progressPrinting
 * 
 * @note print a progress indicator on the terminal
 */
 
void progressPrinting(double percent)
{
		
	int barWidth = 70;
	std::cout << "[";
	int pos = barWidth * percent/100;
	
	for (int i = 0; i < barWidth; ++i) {
		
			if (i < pos) std::cout << "=";
			else if (i == pos)std::cout << ">";
			else std::cout << " ";
	}
		std::cout << "] " << int(percent) << " % \r";
		std::cout.flush();
	

}
