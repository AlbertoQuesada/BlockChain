/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.artelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   T E M P E R A T U R E   F O R E C A S T I N G   A P P L I C A T I O N                                      */
/*                                                                                                              */
/*   Patricia Garcia                                                                                            */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   patriciagarcia@artelnics.com                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/


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
        std::cout << "OpenNN. Temperature Forecasting Application." << std::endl;

        srand((unsigned)time(NULL));


        //Data Set

        DataSet ds;

//        ds.set_data_file_name("../data/temperature.csv");
//        ds.set_data_file_name("../data/global_temperature.csv");
        ds.set_data_file_name("../data/temperature_1950.csv");
        ds.set_header_line(true);
        ds.set_separator("Comma");
//        ds.set_missing_values_label("999.9");

        std::cout << "Loading" << std::endl;

        ds.load_data();

        Variables* variables_pointer = ds.get_variables_pointer();

        Vector<std::string> uses(3);
        uses[0] = "Time";
        uses[1] = "Input";
        uses[2] = "Target";

        variables_pointer->set_uses(uses);


//        std::cout << "Data statistics" << std::endl;
//        Vector< Statistics<double> > data_statistics = ds.calculate_data_statistics();
//        data_statistics.save("../data/data_statistics.dat");


//        std::cout << "Data histograms" << std::endl;
//        Vector< Histogram<double> > data_histograms = ds.calculate_data_histograms();
//        data_histograms.save("../data/data_histograms.dat");


        std::cout << "Converting to time series" << std::endl;

        ds.set_lags_number(12);
        ds.set_steps_ahead_number(1);
        ds.convert_time_series();

        variables_pointer->set_use(25, "Unused");

//        std::cout << "Linear correlations" << std::endl;
//        Matrix<double> linear_correlations = ds.calculate_linear_correlations();
//        linear_correlations.save("../data/linear_correlations.dat");

        DataSet ds_copy(ds);
        ds_copy.impute_missing_values_mean();

        std::cout << "Performing inputs trends transformation" << std::endl;

        const Vector< LinearRegressionParameters<double> > inputs_trends = ds.perform_inputs_trends_transformation();
        inputs_trends.save("../data/inputs_trends.dat");

        std::cout << "Performing outputs trends transformation" << std::endl;

        const Vector< LinearRegressionParameters<double> > outputs_trends = ds.perform_outputs_trends_transformation();
        outputs_trends.save("../data/outputs_trends.dat");

        ds.impute_missing_values_mean();

        // Instances

        Instances* instances_pointer = ds.get_instances_pointer();
        instances_pointer->split_sequential_indices();

        const Vector< Statistics<double> > inputs_statistics = ds.scale_inputs_minimum_maximum();
        const Vector< Statistics<double> > targets_statistics = ds.scale_targets_minimum_maximum();

        // Neural network

        std::cout << "Neural network" << std::endl;

        NeuralNetwork neural_network;

        const size_t inputs_number = variables_pointer->count_inputs_number();
        const size_t hidden_perceptrons_number = 6;
        const size_t outputs_number = variables_pointer->count_targets_number();

        neural_network.set(inputs_number, hidden_perceptrons_number, outputs_number);

        neural_network.construct_scaling_layer();
        ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();
        scaling_layer_pointer->set_statistics(inputs_statistics);
        scaling_layer_pointer->set_scaling_methods(ScalingLayer::NoScaling);

        neural_network.construct_unscaling_layer();
        UnscalingLayer* unscaling_layer_pointer = neural_network.get_unscaling_layer_pointer();
        unscaling_layer_pointer->set_statistics(targets_statistics);
        unscaling_layer_pointer->set_unscaling_method(UnscalingLayer::NoUnscaling);

        neural_network.construct_inputs_trending_layer();
        InputsTrendingLayer* inputs_trending_layer_pointer = neural_network.get_inputs_trending_layer_pointer();
        inputs_trending_layer_pointer->set_inputs_trends(inputs_trends);
        inputs_trending_layer_pointer->set_inputs_trending_method(InputsTrendingLayer::NoTrending);

        neural_network.construct_outputs_trending_layer();
        OutputsTrendingLayer* outputs_trending_layer_pointer = neural_network.get_outputs_trending_layer_pointer();
        outputs_trending_layer_pointer->set_outputs_trends(outputs_trends);
        outputs_trending_layer_pointer->set_outputs_trending_method(OutputsTrendingLayer::NoTrending);


        // Loss index

        LossIndex loss_index;
        loss_index.set_data_set_pointer(&ds);
        loss_index.set_neural_network_pointer(&neural_network);
        loss_index.set_regularization_type(LossIndex::NEURAL_PARAMETERS_NORM);
        loss_index.get_normalized_squared_error_pointer()->set_normalization_coefficient();


        // Training strategy object

        TrainingStrategy training_strategy;
        training_strategy.set(&loss_index);
        QuasiNewtonMethod* quasi_Newton_method_pointer = training_strategy.get_quasi_Newton_method_pointer();
        quasi_Newton_method_pointer->set_maximum_iterations_number(10000);
//        quasi_Newton_method_pointer->set_maximum_time(250);
        quasi_Newton_method_pointer->set_display_period(10);
        quasi_Newton_method_pointer->set_minimum_loss_increase(1.0e-999);
        quasi_Newton_method_pointer->set_reserve_loss_history(true);
        quasi_Newton_method_pointer->set_reserve_selection_loss_history(true);

        TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();


        // Testing analysis

        std::cout << "Testing" << std::endl;

        TestingAnalysis testing_analysis(&neural_network, &ds);
        TestingAnalysis::LinearRegressionResults linear_regression_results = testing_analysis.perform_linear_regression_analysis();
        Vector< Vector<double> > error_autocorrelation = testing_analysis.calculate_error_autocorrelation();
        Vector< Vector<double> > error_crosscorrelation = testing_analysis.calculate_input_error_cross_correlation();
        Vector< Matrix<double> > error_data = testing_analysis.calculate_error_data();
        Vector< Vector< Statistics<double> > > error_data_statistics = testing_analysis.calculate_error_data_statistics();


        // Save results

        ds.save("../data/data_set.xml");

        neural_network.save("../data/neural_network.xml");
        neural_network.save_expression("../data/expression.txt");

        loss_index.save("../data/loss_index.xml");

        training_strategy.save("../data/training_strategy.xml");
        training_strategy_results.save("../data/training_strategy_results.dat");

        linear_regression_results.save("../data/linear_regression_analysis_results.dat");
        error_autocorrelation.save("../data/error_autocorrelation.dat");
        error_crosscorrelation.save("../data/error_crosscorrelation.dat");
        error_data.save("../data/error_data.dat");
        error_data_statistics.save("../data/error_data_statistics.dat");


        // Deployment

        scaling_layer_pointer->set_scaling_methods(ScalingLayer::MinimumMaximum);
        unscaling_layer_pointer->set_unscaling_method(UnscalingLayer::MinimumMaximum);

        inputs_trending_layer_pointer->set_inputs_trending_method(InputsTrendingLayer::Linear);
        outputs_trending_layer_pointer->set_outputs_trending_method(OutputsTrendingLayer::Linear);


/*
        scaling_layer_pointer->set_scaling_methods(ScalingLayer::MinimumMaximum);
        unscaling_layer_pointer->set_unscaling_method(UnscalingLayer::MinimumMaximum);

        inputs_trending_layer_pointer->set_inputs_trending_method(InputsTrendingLayer::Linear);
        outputs_trending_layer_pointer->set_outputs_trending_method(OutputsTrendingLayer::Linear);


        // Testing analysis

        std::cout << "Testing" << std::endl;

        TestingAnalysis testing_analysis(&neural_network, &ds_copy);
        TestingAnalysis::LinearRegressionResults linear_regression_results = testing_analysis.perform_forecasting_linear_regression_analysis();
        Vector< Vector<double> > error_autocorrelation = testing_analysis.calculate_forecasting_error_autocorrelation();
        Vector< Vector<double> > error_crosscorrelation = testing_analysis.calculate_forecasting_input_error_cross_correlation();
        Vector< Matrix<double> > error_data = testing_analysis.calculate_forecasting_error_data();
        Vector< Vector< Statistics<double> > > error_data_statistics = testing_analysis.calculate_forecasting_error_data_statistics();


        // Save results

        ds.save("../data/data_set.xml");

        neural_network.save("../data/neural_network.xml");
        neural_network.save_expression("../data/expression.txt");

        loss_index.save("../data/loss_index.xml");

        training_strategy.save("../data/training_strategy.xml");
        training_strategy_results.save("../data/training_strategy_results.dat");

        linear_regression_results.save("../data/linear_forecasting_regression_analysis_results.dat");
        error_autocorrelation.save("../data/error_forecasting_autocorrelation.dat");
        error_crosscorrelation.save("../data/error_forecasting_crosscorrelation.dat");
        error_data.save("../data/forecasting_error_data.dat");
        error_data_statistics.save("../data/forecasting_error_data_statistics.dat");
*/


        return(0);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return(1);
    }
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2017 Roberto Lopez.
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
