/**
 * @file   neuron.hpp
 * @author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  class that describe a neuron
 */
 
#include <iostream>
#include <vector>
#include <cmath>
#include "constants.hpp"
 
#ifndef NEURON_H
#define NEURON_H

/// State of the neuron : Active or Refractory
enum State {ACTIVE, REFRACTORY, stateSize};
/// Type of the neuron : Excitatory or Inhibitory
enum Type {INHIBITORY, EXCITATORY, typeSize};

class Neuron
{
	
	public :

		/** Constructor
		 *  needs a type (INHIBITORY or EXCITATORY) to set the specific J (the amplitude of the EPSP)
		 *  @note the neuron is REFRACTORY by default
		 *  @param type	the type of the neuron
		 */
		Neuron(Type type);
		
		/** update
		 *  @param simStep 	the time expressed in steps at which the neuron update
		 *  @retval TRUE	the neuron spikes
		 *  @retval FALSE	the neuron doesn't spike
		 */
		bool update(double simStep);
		
		/** updateTest
		 * 
		 *  @note	 only used for unittest to check if the update is well implemented
		 *  @param iExt	 the current given to the neuron
		 *  @param simStep 	the time expressed in steps at which the neuron update
		 *  @retval TRUE	the neuron spikes
		 *  @retval FALSE	the neuron doesn't spike
		 */
		bool updateTest(double iExt, double simStep);
		
		/** getSpikesTime
		 * @return spikes	the step when a spike occured
		 */
		std::vector<long> getSpikesTime();
		
		/** getV
		 * @return v 	the membrane potential of the neuron
		 */
		double getV();
		
		/** getJ
		 * @return J 	the amplitude of the EPSP (excitatory post synaptic potential)
		 */
		double getJ();
		
		/** receive
		 * @param step 	the step at which the neuron receive an EPSP from an other one
		 * @param J 	the amplitude of the EPSP that is received
		 * @brief put the ESPS received in the ringBuffer that manage the delay of the actual effect of the ESPS
		 */
		void receive(long step, double J);

	private :
	
		State state; //!< State of the neuron : Active or Refractory
		Type type; //!< Type of the neuron : Excitatory or Inhibitory
		double v; //!< Membrane potential
		double J; //!< Amplitude of the EPSP (excitatory post synaptic potential)
		std::vector<long> spikes; //!< List of the steps at which the neuron spikes
		long localStep; //!< Local clock expressed in steps
		std::vector<double> ringBuffer; //!< Buffer in which we stock the EPSP that the neuron received for a certain delay
		
		/** updateState
		 * 
		 * @param simStep 	the time given in steps
		 * @brief manage the switch between the ACTIVE and REFRACTORY state
		 *   	  if the neurons spikes, it will be REFRACTORY for a certain time
		 *   	  given by refractoryTime
		 */
		void updateState(double simStep);
};



#endif
