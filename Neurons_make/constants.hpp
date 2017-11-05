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

constexpr long tau = 20;  //!< ms
constexpr double tau_ref = 2; //!< ms
constexpr double refractorySteps = 20; //!< refractory time given in steps of h
const double teta = 20; //!<
const double eta = 2; //!<
constexpr double v_th = 20; //!< //mV
constexpr double v_res = 0; //!<
		
constexpr int N(12500); //!< // Total number of neurons
constexpr int N_e(0.8*N); //!<// Number of excitatory neurons
constexpr int N_i(0.2*N); //!<// Number of inhibitory neurons
constexpr int C_e(N_e*0.1);//!< // Number of connections with excitatory neurons
constexpr int C_i(N_i*0.1); //!<// Number of conncections with inhibitory neurons
constexpr double J_e = 0.1; //!<
constexpr double J_i = -0.5; //!<

constexpr double c = 1; //!<
constexpr double R = 20e6; //!<// 20.0 G ohm résistance de la membrane
constexpr int bufferDelay = 15; //!<
constexpr double r(tau/c); //!<
const double c1 = exp(-h/tau); //!<
const double c2 = r*(1-exp(-h/tau)); //!<
const double nu_th(teta/(0.1*0.8*N*J_e*tau)); //!<
const double nu_ext(eta*0.1*0.8*N*nu_th); //!<






#endif
