Author : Jonathan Haab 
Date : 4 november 2017

Informations about the use of the « Neurons » project

NEURONS——————————————————————————————————————————————————————————————————————————————

Follow the next instructions to run the simulation:

1	go into the « build » folder through the terminal
2	write « make » to compile using cmake
3	write « ./Neurons » to run the simulation
4	if one or several neurons spike at a certain time t, you’ll find the time t 	followed by every neuron’s identification number in the « Neuron_Spikes.txt » 	file present in the « build » folder

Note : you can tune the parameters (for instance the duration of the simulation or 		the number of neurons) in the « constants.cpp » file

Follow the next instructions to generate a graph similar to the one already present 	in folder named « Spike_Plot.png » using Jupyter:

1	load « https://try.jupyter.org/ » in your internet browser
2	select « New » on the right of the window
3	select « Python 3 »
4	paste the following lines and make sure you indicated the emplacement of the 	« Neuron_Spikes.txt » file

import numpy as np
import pylab as pl

data = np.genfromtxt(‘THE LOCATION OF THE « Neuron_Spikes.txt » FILE’)


select = np.array([d for d in data if d[1] < 30])
data1 = select.transpose()
pl.scatter(0.1*data1[0], data1[1], alpha=0.8, edgecolors = 'none');
pl.show();


UNITTEST—————————————————————————————————————————————————————————————————————————————

Follow the next instructions to run the unittest :

1	go into the « build » folder through the terminal
2	write « ./Neurons_unittest » to run the tests using googletest

DOXYGEN——————————————————————————————————————————————————————————————————————————————

Follow the next instructions to generate Doxygen’s documentation :

1	go into the « build » folder through the terminal
2	write « make doc » to generate documentation of the code using Doxygen
3	you’ll find the documentation in the « html » or « latex » folders of the 	« Neurons_make » folder

