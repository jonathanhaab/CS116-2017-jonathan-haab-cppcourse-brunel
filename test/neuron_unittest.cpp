/**
 * @file   neuron_unittest.cpp
 * @author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  Contains all the googletests to control the Neurons project
 */


#include "neuron.hpp"
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/** ExcitatoryImput1
 *  @test ExcitatoryImput1
 *  @note test the behaviour of an excitatory neuron getting an imput current of 1.0
 *  @brief the neuron should tend to a potential of 20 mV without ever reaching it
 *  @throw error if the neuron spikes or if its potential doesn't tend to 20 mV after several updates
 */
TEST (Neurontest, ExcitatoryImput1) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(1.0);
	
	//Test after one update
	neuron.updateTest(imputCurrent, 1);
	EXPECT_EQ(c2*imputCurrent, neuron.getV());
	
	//Test after several update
	neuron.updateTest(imputCurrent, 10000);
	EXPECT_GT(1e-3, std::fabs(19.9999 - neuron.getV()));
	
}

/** ExcitatoryImput0
 *  @test ExcitatoryImput0
 *  @note test the behaviour of an excitatory neuron getting an imput current of 0
 *  @brief the neuron should never get any potential
 *  @throw error if the neuron's potential isn't 0 after several updates
 */
TEST (Neurontest, ExcitatoryImput0) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(0.0);
	
	neuron.updateTest(imputCurrent, 2000);

	EXPECT_EQ(0, neuron.getV());
	
}

/** ExcitatoryImput1_01
 *  @test ExcitatoryImput1_01
 *  @note test the behaviour of an excitatory neuron getting an imput current of 1.01
 *  @brief the neuron should spike at the moment it reaches a potential of 20 mV and then see its potential falling to 0 
 *  @throw error if the neuron's potential isn't close to 20 at known time and if its potential doesn't fall to 0 at the next step
 */
TEST (Neurontest, ExcitatoryImput1_01) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(1.01);
	
	//known spike times
	neuron.updateTest(imputCurrent, 923);
	EXPECT_NEAR(20, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 924);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 1867);
	EXPECT_NEAR(20, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 1868);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 2811);
	EXPECT_NEAR(20, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 2812);
	EXPECT_EQ(0, neuron.getV());
}

/** InhibitoryImput1
 *  @test InhibitoryImput1
 *  @note test the behaviour of an inhibitory neuron getting an imput current of 1.0
 *  @brief the neuron should tend to a potential of 20 mV without ever reaching it
 *  @throw error if the neuron spikes or if its potential doesn't tend to 20 mV after several updates
 */
TEST (Neurontest, InhibitoryImput1) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(1.0);
	
	//Test after one update
	neuron.updateTest(imputCurrent, 1);
	EXPECT_EQ(c2*imputCurrent, neuron.getV());
	
	//Test after several update
	neuron.updateTest(imputCurrent, 10000);
	EXPECT_GT(1e-3, std::fabs(19.9999 - neuron.getV()));
	
}

/** InhibitoryImput0
 *  @test InhibitoryImput0
 *  @note test the behaviour of an inhibitory neuron getting an imput current of 0
 *  @brief the neuron should never get any potential
 *  @throw error if the neuron's potential isn't 0 after several updates
 */
TEST (Neurontest, InhibitoryImput0) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(0.0);
	
	neuron.updateTest(imputCurrent, 2000);

	EXPECT_NEAR(0, neuron.getV(), 1e-3);
	
}

/** InhibitoryImput1_01
 *  @test InhibitoryImput1_01
 *  @note test the behaviour of an inhibitory neuron getting an imput current of 1.01
 *  @brief the neuron should spike at the moment it reaches a potential of 20 mV and then see its potential falling to 0 
 *  @throw error if the neuron's potential isn't close to 20 at known time and if its potential doesn't fall to 0 at the next step
 */
TEST (Neurontest, InhibitoryImput1_01) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(1.01);
	
	//known spike times
	neuron.updateTest(imputCurrent, 923);
	EXPECT_NEAR(20, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 924);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 1867);
	EXPECT_NEAR(20, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 1868);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 2811);
	EXPECT_NEAR(20, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 2812);
	EXPECT_EQ(0, neuron.getV());
}

/** ExcitatoryRefractoryTime
 *  @test ExcitatoryRefractoryTime
 *  @note test the behaviour of an excitatory neuron after it spikes
 *  @brief the neuron should be refractory for a certain time determined by the variable refractoryTime from the constants.cpp file
 *  @throw error if the neuron's potential isn't 0 for a certain time after it spike
 */
TEST (Neurontest, ExcitatoryRefractoryTime) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(1.01);
	
	for(int i(924); i < 924+refractorySteps; ++i){
		neuron.updateTest(imputCurrent, i);
		EXPECT_EQ(0, neuron.getV());
	}
}

/** InhibitoryRefractoryTime
 *  @test InhibitoryRefractoryTime
 *  @note test the behaviour of an inhibitory neuron after it spikes
 *  @brief the neuron should be refractory for a certain time determined by the variable refractoryTime from the constants.cpp file
 *  @throw error if the neuron's potential isn't 0 for a certain time after it spike
 */
TEST (Neurontest, InhibitoryRefractoryTime) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(1.01);
		
	//known spike times
	for(int i(924); i < 924+refractorySteps; ++i){
		neuron.updateTest(imputCurrent, i);
		EXPECT_EQ(0, neuron.getV());
	}
}

/** ExcitatoryExcitatoryConnexion1_01
 *  @test ExcitatoryExcitatoryConnexion1_01
 *  @note test the connection of two excitatory neurons, one getting an imput current of 1.01 and the second the EPSP of the first one
 *  @brief the second neuron should receive a potential of J_e from the first one after a certain time defined by the bufferTime variable 
 *  @throw error if the second neuron's potential isn't equal to the EPSP value of the first and if it doesn't receive it at the right time
 */
TEST (Neurontest, ExcitatoryExcitatoryConnexion1_01) {
	
	Neuron neuron1(EXCITATORY);
	Neuron neuron2(EXCITATORY);
	
	double imputCurrent(1.01);
	
	int spikeOnStep(924);
	
	neuron2.updateTest(0, spikeOnStep);
	
	if(neuron1.updateTest(imputCurrent, spikeOnStep)){
		neuron2.receive(spikeOnStep, neuron1.getJ());
	}
	
	
	
	for(int i(0); i < (spikeOnStep + bufferDelay); ++i){
		neuron2.updateTest(0, i);
	
	}
	
	EXPECT_EQ(neuron2.getV(), J_e);
	
}

/** InhibitoryExcitatoryConnexion1_01
 *  @test InhibitoryExcitatoryConnexion1_01
 *  @note test the connection of an inhibitory to an excitatory neurons, the inhibitory getting an imput current of 1.01 and the excitatory the EPSP of the first one
 *  @brief the excitatory neuron should receive a potential of J_i from the inhibitory after a certain time defined by the bufferTime variable 
 *  @throw error if the second neuron's potential isn't equal to the EPSP value of the first and if it doesn't receive it at the right time
 */
TEST (Neurontest, InhibitoryExcitatoryConnexion1_01) {
	
	Neuron neuron1(INHIBITORY);
	Neuron neuron2(EXCITATORY);
	
	double imputCurrent(1.01);
	
	int spikeOnStep(924);
	
	neuron2.updateTest(0, spikeOnStep);
	
	if(neuron1.updateTest(imputCurrent, spikeOnStep)){
		neuron2.receive(spikeOnStep, neuron1.getJ());
	}
	
	
	
	for(int i(0); i < (spikeOnStep + bufferDelay); ++i){
		neuron2.updateTest(0, i);
	
	}
	
	EXPECT_EQ(neuron2.getV(), J_i);
	
}

/** ExcitatoryInhibitoryConnexion1_01
 *  @test ExcitatoryInhibitoryConnexion1_01
 *  @note test the connection of an excitatory to an inhibitory neurons, the excitatory getting an imput current of 1.01 and the inhibitory the EPSP of the first one
 *  @brief the inhibitory neuron should receive a potential of J_e from the excitatory one after a certain time defined by the bufferTime variable 
 *  @throw error if the second neuron's potential isn't equal to the EPSP value of the first and if it doesn't receive it at the right time
 */
TEST (Neurontest, ExcitatoryInhibitoryConnexion1_01) {
	
	Neuron neuron1(EXCITATORY);
	Neuron neuron2(INHIBITORY);
	
	double imputCurrent(1.01);
	
	int spikeOnStep(924);
	
	neuron2.updateTest(0, spikeOnStep);
	
	if(neuron1.updateTest(imputCurrent, spikeOnStep)){
		neuron2.receive(spikeOnStep, neuron1.getJ());
	}
	
	
	
	for(int i(0); i < (spikeOnStep + bufferDelay); ++i){
		neuron2.updateTest(0, i);
	
	}
	
	EXPECT_EQ(neuron2.getV(), J_e);
	
}

/** InhibitoryInhibitoryConnexion1_01
 *  @test InhibitoryInhibitoryConnexion1_01
 *  @note test the connection of two inhibitory neurons, one getting an imput current of 1.01 and the second the EPSP of the first one
 *  @brief the second neuron should receive a potential of J_i from the first one after a certain time defined by the bufferTime variable 
 *  @throw error if the second neuron's potential isn't equal to the EPSP value of the first and if it doesn't receive it at the right time
 */
TEST (Neurontest, InhibitoryInhibitoryConnexion1_01) {
	
	Neuron neuron1(INHIBITORY);
	Neuron neuron2(INHIBITORY);
	
	double imputCurrent(1.01);
	
	int spikeOnStep(924);
	
	neuron2.updateTest(0, spikeOnStep);
	
	if(neuron1.updateTest(imputCurrent, spikeOnStep)){
		neuron2.receive(spikeOnStep, neuron1.getJ());
	}
	
	
	
	for(int i(0); i < (spikeOnStep + bufferDelay); ++i){
		neuron2.updateTest(0, i);
	
	}
	
	EXPECT_EQ(neuron2.getV(), J_i);
	
}

/** ExcitatoryExcitatoryInducedSpike
 *  @test ExcitatoryExcitatoryInducedSpike
 *  @note test the behaviour of an excitatory neuron that receive an EPSP from an other as it tends to 20mV
 *  @brief the second neuron should receive just enough potential to spike
 *  @throw error if the second neuron doesn't spike
 */
TEST (Neurontest, ExcitatoryExcitatoryInducedSpike) {
	
	Neuron neuron1(EXCITATORY);
	Neuron neuron2(EXCITATORY);
	
	double imputCurrent1(1.01);
	double imputCurrent2(1.00);
	
	//The second neurons needs two EPSP from the first one to spike
	double secondSpikeOfNeuron1OnStep(1867);
	
	for(int i(0); i < secondSpikeOfNeuron1OnStep + bufferDelay-1; ++i){
		
		if(neuron1.updateTest(imputCurrent1, i)){
			neuron2.receive(i, neuron1.getJ());
		}
		
		neuron2.updateTest(imputCurrent2, i);
	}
	
	EXPECT_TRUE(neuron2.updateTest(imputCurrent2, secondSpikeOfNeuron1OnStep + bufferDelay));
	
}


/** InhibitoryExcitatoryInducedSpike
 *  @test InhibitoryExcitatoryInducedSpike
 *  @note test the behaviour of an excitatory neuron that receive an EPSP from an inhibitory one as it tends to 20mV
 *  @brief the excitatory should never spike
 *  @throw error if the excitatory neuron spikes
 */
TEST (Neurontest, InhibitoryExcitatoryInducedSpike) {
	
	Neuron neuron1(INHIBITORY);
	Neuron neuron2(EXCITATORY);
	
	double imputCurrent1(1.01);
	double imputCurrent2(1.00);
	
	for(int i(0); i < 10000; ++i){
		
		if(neuron1.updateTest(imputCurrent1, i)){
			neuron2.receive(i, neuron1.getJ());
		}
		
		//neuron2 should never spike
		EXPECT_FALSE(neuron2.updateTest(imputCurrent2, i));
	}
}

/** ExcitatoryInhibitoryInducedSpike
 *  @test ExcitatoryInhibitoryInducedSpike
 *  @note test the behaviour of an inhibitory neuron that receive an EPSP from an excitatory one as it tends to 20mV
 *  @brief the inhibitory neuron should receive just enough potential to spike
 *  @throw error if the inhibitory neuron doesn't spike
 */
TEST (Neurontest, ExcitatoryInhibitoryInducedSpike) {
	
	Neuron neuron1(EXCITATORY);
	Neuron neuron2(INHIBITORY);
	
	double imputCurrent1(1.01);
	double imputCurrent2(1.00);
	
	//The second neurons needs two EPSP from the first one to spike
	double secondSpikeOfNeuron1OnStep(1867);
	
	for(int i(0); i < secondSpikeOfNeuron1OnStep + bufferDelay-1; ++i){
		
		if(neuron1.updateTest(imputCurrent1, i)){
			neuron2.receive(i, neuron1.getJ());
		}
		
		neuron2.updateTest(imputCurrent2, i);
	}
	
	EXPECT_TRUE(neuron2.updateTest(imputCurrent2, secondSpikeOfNeuron1OnStep + bufferDelay));
	
}

/** InhibitoryInhibitoryInducedSpike
 *  @test InhibitoryInhibitoryInducedSpike
 *  @note test the behaviour of an inhibitory neuron that receive an EPSP from an other one as it tends to 20mV
 *  @brief the second one should never spike
 *  @throw error if the second neuron spikes
 */
TEST (Neurontest, InhibitoryInhibitoryInducedSpike) {
	
	Neuron neuron1(INHIBITORY);
	Neuron neuron2(INHIBITORY);
	
	double imputCurrent1(1.01);
	double imputCurrent2(1.00);
	
	for(int i(0); i < 10000; ++i){
		
		if(neuron1.updateTest(imputCurrent1, i)){
			neuron2.receive(i, neuron1.getJ());
		}
		
		//neuron2 should never spike
		EXPECT_FALSE(neuron2.updateTest(imputCurrent2, i));
	}
}
