/**
 * @file   constants.hpp
 * @Author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  library of every constants neede for the simulation of the neurons' network
 */

#include <cmath>

#ifndef CONSTANTS_H
#define CONSTANTS_H


constexpr double h = 0.1; //!< time in ms of a step
constexpr double startTime = 0; //!< time at which we begin the simulation
constexpr double stopTime = 200; //!< time at which we end the simulation
const double total_steps = std::abs(stopTime-startTime)/h; //!< total number of step of the simulation

constexpr long tau = 20;  //!< a variable (in ms) of the differential equation for the update fonction
constexpr double refractorySteps = 20; //!< refractory time given in steps of h

constexpr double v_th = 20; //!< the potential (in mV) at which the neuron spike 
constexpr double v_res = 0; //!< the potential given to the neuron after it spikes

constexpr int N(12500); //!< total number of neurons
constexpr int N_e(0.8*N); //!< number of excitatory neurons
constexpr int N_i(0.2*N); //!< number of inhibitory neurons
constexpr int C_e(N_e*0.1);//!< number of connections with excitatory neurons
constexpr int C_i(N_i*0.1); //!< number of conncections with inhibitory neurons
constexpr double J_e = 0.1; //!< the EPSP of an excitatory neuron
constexpr double J_i = -0.5; //!< the EPSP of an inhibitory neuron

constexpr double c = 1; //!< the capacity of the neuron's membrane 
constexpr double R = 20e6; //!<// 20.0 (Giga Ohm) neuron's membrane resistance
constexpr int bufferDelay = 15; //!< the delay (in steps) after which a neuron receive an EPSP

const double c1 = exp(-h/tau); //!< first parameter of the differential equation for the update fonction
const double c2 = tau/c*(1-exp(-h/tau)); //!< second parameter of the differential equation for the update fonction







#endif
