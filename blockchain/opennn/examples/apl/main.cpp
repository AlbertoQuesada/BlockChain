/****************************************************************************************************************/
/*                                                                                                              */ 
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A P L   A P P L I C A T I O N                                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */  
/****************************************************************************************************************/

// This is a function regression problem. 

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>

// OpenNN includes

#include "../../opennn/opennn.h"

using namespace OpenNN;

int main(void)
{

   try            
  {
      std::cout << "OpenNN. APL Application." << std::endl;

      srand((unsigned)time(NULL));

      //
      // DESING MODE
      //
/*
      // Data set
  
      DataSet data_set;
	  
      data_set.load_data("../data/apl.dat");

      const Vector< Statistics<double> > inputs_statistics = data_set.scale_inputs_minimum_maximum();

      // Neural network

      const unsigned inputs_number = data_set.get_variables().count_inputs_number();
      const unsigned hidden_neurons_number = 30;
      const unsigned outputs_number = data_set.get_variables().count_targets_number();

      NeuralNetwork neural_network(inputs_number, hidden_neurons_number, outputs_number);

      MultilayerPerceptron* multilayer_perceptron = neural_network.get_multilayer_perceptron_pointer();

      multilayer_perceptron->set_layer_activation_function(0, Perceptron::Logistic);
      multilayer_perceptron->set_layer_activation_function(1, Perceptron::Logistic);

      neural_network.construct_scaling_layer();

      ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

      scaling_layer_pointer->set_statistics(inputs_statistics);

      scaling_layer_pointer->set_scaling_method(ScalingLayer::NoScaling);

      neural_network.construct_unscaling_layer();

	  // Performance functional

      PerformanceFunctional performance_functional(&neural_network, &data_set);

	  // Training strategy 

	  TrainingStrategy training_strategy(&performance_functional);

      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

      // Save results

      scaling_layer_pointer->set_scaling_method(ScalingLayer::MinimumMaximum);

      data_set.save("../data/data_set.xml");

      neural_network.save("../data/neural_network.xml");
      neural_network.save_expression("../data/expression.txt");

      training_strategy.save("../data/training_strategy.xml");
      training_strategy_results.save("../data/training_strategy_results.dat");
*/
      //
      // PRODUCTION MODE
      //

      NeuralNetwork neural_network;

      neural_network.load("../data/neural_network.xml");

      Vector<double> inputs(201);

      inputs.randomize_normal();

      Vector<double> outputs = neural_network.calculate_outputs(inputs);

      std::cout << "Output: " << outputs[0] << std::endl;


      return(0);
   }
   catch(std::exception& e)
   {
      std::cerr << e.what() << std::endl;

      return(1);
   }
}  


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2014 Roberto Lopez
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
