/**
 * @file   network.hpp
 * @author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  class that build a network of neurons
 */

#include "neuron.hpp"
#include <fstream>
#include <string>

#ifndef NETWORK_H
#define NETWORK_H

class Network
{
	public :
	
		/** Constructor
		 * 
		 * @param title	the title of the file in which we want to 
		 * 					print the data of the update
		 * 
		 * @note opens the flow to write the data
		 */
		Network(std::string title);
		
		/** Destructor
		 * 
		 * @note close the flow used to write the data
		 */
		~Network();
		
		/** update
		 * 
		 * @param simStep 	the step of the simulation at which we want
		 * 					to update de network of neurons
		 * 
		 * @note prints all the neurons id that spikes at a certain time
		 * 		 like this :
		 * 		 time in ms 	neuron n°1	neuron n°2	...
		 */
		void update(double simStep);
		
		/** writeSpikes
		 * 
		 * @param out 	the file in which we want to print the spikes
		 * @note gives the spike's times for each neuron like this :
		 * 		neuron id 	 spike time n°1 	spike time n°2	...
		 * 
		 */
		void writeSpikes(std::ofstream& out);
		
	private :
	
		std::vector<Neuron> neurons; //!< List of the neurons of the network
		std::vector<std::vector<int>> network; //!< Behold the informations about the connections between the neurons of the network
		
		std::ofstream spikes; //!< Flow that connect to the data file
		
		/** initialiseExcitatory
		 * 
		 * @note initialise the right number of excitatory neurons in
		 * 		 the network according to the constants.hpp file
		 */
		void initialiseExcitatory();
		
		/** initialiseInhibitory
		 * 
		 * @note initialise the right number of inhibitory neurons in
		 * 		 the network according to the constants.hpp file
		 */
		void initialiseInhibitory();
		
		/** initialiseConnexions
		 * 
		 * @note initialise the network
		 */
		void initialiseConnexions();
		
		/** createConnexions
		 * 
		 * @note create randomly according to the poisson's law the
		 * 		 connections between the neurons of the network
		 */
		void createConnections();
		
};


#endif
