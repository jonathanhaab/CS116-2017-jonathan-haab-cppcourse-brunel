/**
 * @file   neuron.cpp
 * @author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  contains all the methods for the neuron
 */
 
#include <iostream>
#include <random>
#include "neuron.hpp"


using namespace std;

/** Constructor
 *  needs a type (INHIBITORY or EXCITATORY) to set the specific J (the amplitude of the EPSP)
 *  @note the neuron is REFRACTORY by default
 *  @param type
 */
 
Neuron::Neuron(Type type)
	: localStep(0), type(type)
{
	state = REFRACTORY;
	v = v_res; //mV
	spikes.clear();
	ringBuffer.resize(bufferDelay + 1);
	
	if(type == INHIBITORY){
		J = J_i;
	} else { // otherwise it's EXCITATORY
		J = J_e;
	}
}

/** update
 * 
 *  @param simStep 	the time expressed in steps at which the neuron update
 *  @retval TRUE	the neuron spikes
 *  @retval FALSE	the neuron doesn't spike
 */

bool Neuron::update(double simStep)
{
	bool isSpiking(false);
	
	while(localStep < simStep){
		
		updateState(localStep);
		
		if(state == ACTIVE) {

			// Distribution de poisson
			//static poisson_distribution<> poisson(nu_ext * h);
			static poisson_distribution<> poisson(v_th*h);
			static random_device rd;
			static mt19937 gen(rd());
			
			//cout << (nu_ext * h) << endl;
			// Potentiel de la membrane
			double r(tau/c);
			int x(localStep);
			
			v = c1*v + ringBuffer[x%(bufferDelay+1)] + J_e*poisson(gen);
			
			// Réinitialisation de la cellule du ringBuffer qui vient d'être utilisée
			ringBuffer[x%(bufferDelay+1)] = 0;
			
			// Spike (20mV)
			if(v > v_th) {
				v = v_res;
				spikes.push_back(localStep);
				isSpiking = true;
			}
			
		} else {
			
			v = v_res; // refractory
			
		}
		
		localStep += 1;
	}
	return isSpiking;
}

/** updateTest
 * 
 *  @note	 only used for unittest to check if the update is well implemented
 *  @param iExt	 the current given to the neuron
 *  @param simStep 	the time expressed in steps at which the neuron update
 *  @retval TRUE	the neuron spikes
 *  @retval FALSE	the neuron doesn't spike
 */
bool Neuron::updateTest(double iExt, double simStep)
{
	bool isSpiking(false);
	
	while(localStep < simStep){
		
		updateState(localStep);
		int x(localStep);
		if(state == ACTIVE) {
				
				
				
				v = c1*v + c2*iExt + ringBuffer[x%(bufferDelay+1)];
				
				// Réinitialisation de la cellule du ringBuffer qui vient d'être utilisée
				//ringBuffer[x%(bufferDelay+1)] = 0;
				
				// Spike (20mV)
				if(v > v_th) {
					v = v_res;
					spikes.push_back(localStep);
					isSpiking = true;
				}
				
			} else {
				
				v = v_res; // refractory
				
				// Réinitialisation de la cellule du ringBuffer qui aurait du être utilisée si on avait pas été refractory
				//ringBuffer[x%(bufferDelay+1)] = 0;
			}
			
			// Réinitialisation de la cellule du ringBuffer correspondant à notre step
			ringBuffer[x%(bufferDelay+1)] = 0;
				
		localStep += 1;
	}
	
	return isSpiking;
}

/** updateState
 * 
 * @param simStep 	the time given in steps
 * @brief manage the switch between the ACTIVE and REFRACTORY state
 *   	  if the neurons spikes, it will be REFRACTORY for a certain 
 * 		  number of steps given by refractorySteps
 */
 
void Neuron::updateState(double simStep)
{
	if(spikes.empty() or abs(spikes.back() - (simStep)) > refractorySteps) {
		state = ACTIVE;
	} else {
		state = REFRACTORY;
	}
	
}

/** getSpikesTime
 * 
 * @return spikes	the step when a spike occured
 */
 
vector<long> Neuron::getSpikesTime()
{
	return spikes;
}

/** getV
 * 
 * @return v 	the membrane potential of the neuron
 */

double Neuron::getV()
{
	return v;
}

/** getJ
 * 
 * @return J 	the amplitude of the EPSP (excitatory post synaptic potential)
 */

double Neuron::getJ()
{
	
	return J;
}


/** receive
 * 
 * @param step 	the step at which the neuron receive an EPSP from an other one
 * @param J 	the amplitude of the EPSP that is received
 * @brief put the ESPS received in the ringBuffer that manage the delay of the actual effect of the ESPS
 */
 
void Neuron::receive(long step, double J) 
{
	int x(step);
	ringBuffer[(x+bufferDelay)%(bufferDelay)] += J;
}
