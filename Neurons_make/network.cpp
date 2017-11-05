/**
 * @file   network.cpp
 * @author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  class that build a network of neurons
 */

#include "network.hpp"
#include <random>

using namespace std;

/** Constructor
 * 
 * @param title	the title of the file in which we want to 
 * 					print the data of the update
 * 
 * @note opens the flow to write the data
 */
 
/** Destructor
 * 
 * @note close the flow used to write the data
 */ 
Network::Network(std::string title)
{
	this->initialiseExcitatory();
	this->initialiseInhibitory();
	this->initialiseConnexions();
	this->createConnections();
	
	// Ouverture du stream pour les Data
	spikes.open(title);
}

Network::~Network()
{
	spikes.close();
}


/** update
 * 
 * @param simStep 	the step of the simulation at which we want
 * 					to update de network of neurons
 * 
 * @note prints all the neurons id that spikes at a certain time
 * 		 like this :
 * 		 time in ms 	neuron n°1	neuron n°2	...
 */
void Network::update(double simStep)
{
	for(int i(0); i < N; ++i){
		
		if(neurons[i].update(simStep)){ // Si update return true => neuron[i] spike
					
			
			spikes << "\t" << simStep*h << "\t" << i << "\n";
			
			for(size_t j(0); j < network[i].size(); ++j){ // On va donner un potentiel additionnel aux neurones auxquels neuron[i] est connecté

				neurons[network[i][j]].receive(simStep-1, neurons[i].getJ());
			}
		}
	}
}

/** writeSpikes
 * 
 * @param out 	the file in which we want to print the spikes
 * @note gives the spike's times for each neuron like this :
 * 		neuron id 	 spike time n°1 	spike time n°2	...
 * 
 */
void Network::writeSpikes(ofstream& out)
{
	for(int i(0); i < N; ++i){
		
		out << "\t" << i << "\t";
		vector<long> spikesTime(neurons[i].getSpikesTime());
		
		for(size_t j(0); j < spikesTime.size(); ++j){
			out << spikesTime[j] << "\t";
		}
		out << "\n\n\n";
	}
}

/** initialiseExcitatory
 * 
 * @note initialise the right number of excitatory neurons in
 * 		 the network according to the constants.hpp file
 */
void Network::initialiseExcitatory()
{
	for(size_t i(0); i < N_e; ++i){
		Neuron n(EXCITATORY);
		neurons.push_back(n); 
	}
}

/** initialiseInhibitory
 * 
 * @note initialise the right number of inhibitory neurons in
 * 		 the network according to the constants.hpp file
 */
void Network::initialiseInhibitory()
{
	for(size_t i(N_e); i < N; ++i){
		Neuron n(INHIBITORY);
		neurons.push_back(n);
	}
}

/** initialiseConnexions
 * 
 * @note initialise the network
 */
void Network::initialiseConnexions()
{
	for(size_t i(0); i < N; ++i){
		vector<int> neuronsInitialisation;
		network.push_back(neuronsInitialisation);
	}
}

/** createConnexions
 * 
 * @note create randomly according to the poisson's law the
 * 		 connections between the neurons of the network
 */
void Network::createConnections()
{
	for(int i(0); i < N; ++i){
		
		// ... excitatory
		for(int j(0); j < C_e; ++j){
		
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::uniform_int_distribution<> connexion_from(0, N_e-1);
			
			network[connexion_from(gen)].push_back(i);

		}
			// ... inhibitory
		for(int j(0); j < C_i; ++j){
			
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::uniform_int_distribution<> connexion_from(N_e, N-1); // N-1 - N_e = N_i
		
			network[connexion_from(gen)].push_back(i);
		}

	}
}
