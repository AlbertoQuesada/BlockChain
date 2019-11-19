/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   B A N K   M A R K E T I N G   A P P L I C A T I O N                                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - Making intelligent use of data                                                                 */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// This is a classical pattern recognition problem.

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>

// OpenNN includes

#include "../../tinyxml2/tinyxml2.h"
#include "../../opennn/opennn.h"

using namespace OpenNN;

int main(void)
{
    try
    {
        int rank = 0;

#ifdef __OPENNN_MPI__

        int size = 1;

        MPI_Init(NULL,NULL);

        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

#endif

        if(rank == 0)
        {
            std::cout << "OpenNN. Bank Marketing Application." << std::endl;
        }

        srand((unsigned)time(NULL));

        // Global variables

        DataSet data_set;

        NeuralNetwork neural_network;

        LossIndex loss_index;

        TrainingStrategy training_strategy;

        ModelSelection model_selection;

        // Local variables

        DataSet local_data_set;

        NeuralNetwork local_neural_network;

        LossIndex local_loss_index;

        TrainingStrategy local_training_strategy;

        ModelSelection local_model_selection;

        if(rank == 0)
        {
            // Data set

            data_set.set_data_file_name("../data/bankmarketing.dat");

            data_set.set_header_line(true);

            data_set.set_separator("Comma");

//            data_set.set_missing_values_label("?");

            data_set.load_data();

            Variables* variables = data_set.get_variables_pointer();

            Instances* instances = data_set.get_instances_pointer();

            instances->split_random_indices(0.60,0.20,0.20);

            const size_t inputs_number = variables->count_inputs_number();

            const Matrix<std::string> inputs_information = variables->arrange_inputs_information();
            const Matrix<std::string> targets_information = variables->arrange_targets_information();

            MissingValues* missing_values_pointer = data_set.get_missing_values_pointer();

            missing_values_pointer->set_scrubbing_method(MissingValues::Median);

            data_set.scrub_missing_values();

            const Vector< Statistics<double> > inputs_statistics = data_set.scale_inputs_minimum_maximum();

            // Neural network

            neural_network.set(inputs_number, 3, 1);

            Inputs* inputs_pointer = neural_network.get_inputs_pointer();

            inputs_pointer->set_information(inputs_information);

            neural_network.construct_scaling_layer();

            ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

            scaling_layer_pointer->set_statistics(inputs_statistics);

            scaling_layer_pointer->set_scaling_methods(ScalingLayer::NoScaling);

            MultilayerPerceptron* multilayer_perceptron_pointer = neural_network.get_multilayer_perceptron_pointer();

            multilayer_perceptron_pointer->set_layer_activation_function(1, Perceptron::Logistic);

            Outputs* outputs_pointer = neural_network.get_outputs_pointer();

            outputs_pointer->set_information(targets_information);

            neural_network.construct_probabilistic_layer();

            ProbabilisticLayer* probability_layer_pointer = neural_network.get_probabilistic_layer_pointer();

            probability_layer_pointer->set_probabilistic_method(ProbabilisticLayer::Probability);

            // Loss index

            loss_index.set_data_set_pointer(&data_set);
            loss_index.set_neural_network_pointer(&neural_network);

            loss_index.set_error_type(LossIndex::WEIGHTED_SQUARED_ERROR);
            loss_index.set_regularization_type(LossIndex::NEURAL_PARAMETERS_NORM);

            loss_index.get_weighted_squared_error_pointer()->set_weights();
            loss_index.get_neural_parameters_norm_pointer()->set_neural_parameters_norm_weight(0.01);

            // Training strategy

            training_strategy.set(&loss_index);

            training_strategy.set_main_type("QUASI_NEWTON_METHOD");

            QuasiNewtonMethod* quasi_Newton_method_pointer = training_strategy.get_quasi_Newton_method_pointer();

            quasi_Newton_method_pointer->set_minimum_loss_increase(1.0e-4);

            training_strategy.set_display(false);

            // Model selection

            model_selection.set_training_strategy_pointer(&training_strategy);

            model_selection.set_order_selection_type(ModelSelection::INCREMENTAL_ORDER);

            model_selection.set_threshold_selection_type(ModelSelection::YOUDEN_INDEX);

            YoudenIndexOptimizationThreshold* youden_index_optimization_pointer = model_selection.get_youden_index_optimization_threshold();

            youden_index_optimization_pointer->set_minimum_threshold(0.4);

            youden_index_optimization_pointer->set_maximum_threshold(0.6);

            youden_index_optimization_pointer->set_step(0.001);
        }

#ifdef __OPENNN_MPI__
        MPI_Barrier(MPI_COMM_WORLD);

        local_data_set.set_MPI(&data_set);

        local_neural_network.set_MPI(&neural_network);

        local_loss_index.set_MPI(&local_data_set,&local_neural_network,&loss_index);

        local_training_strategy.set_MPI(&local_loss_index,&training_strategy);

        local_model_selection.set_MPI(&local_training_strategy, &model_selection);

        MPI_Barrier(MPI_COMM_WORLD);

        local_training_strategy.set_display(false);

        ModelSelection::ModelSelectionResults model_selection_results = local_model_selection.perform_order_selection();
#else
        ModelSelection::ModelSelectionResults model_selection_results = model_selection.perform_order_selection();
#endif

        if(rank == 0)
        {
#ifdef __OPENNN_MPI__
            neural_network.set_multilayer_perceptron_pointer(local_neural_network.get_multilayer_perceptron_pointer());
#endif
            // Testing analysis

            TestingAnalysis testing_analysis(&neural_network, &data_set);

            Matrix<size_t> confusion = testing_analysis.calculate_confusion();

            Vector<double> binary_classification_tests = testing_analysis.calculate_binary_classification_tests();

            // Save results

            ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

            scaling_layer_pointer->set_scaling_methods(ScalingLayer::MinimumMaximum);

            data_set.save("../data/data_set.xml");

            neural_network.save("../data/neural_network.xml");
            neural_network.save_expression("../data/expression.txt");

            training_strategy.save("../data/training_strategy.xml");

            model_selection.save("../data/model_selection.xml");
            //        model_selection_results.save("../data/model_selection_results.dat");

            confusion.save("../data/confusion.dat");
            binary_classification_tests.save("../data/binary_classification_tests.dat");
        }

#ifdef __OPENNN_MPI__

        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Finalize();
#endif
        return(0);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;

        return(1);
    }
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2016 Roberto Lopez.
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
