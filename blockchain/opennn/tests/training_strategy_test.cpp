/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   T R A I N I N G   S T R A T E G Y   T E S T   C L A S S                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "training_strategy_test.h"

using namespace OpenNN;


// GENERAL CONSTRUCTOR 

TrainingStrategyTest::TrainingStrategyTest(void) : UnitTesting() 
{
}


// DESTRUCTOR

TrainingStrategyTest::~TrainingStrategyTest(void)
{
}


// METHODS

void TrainingStrategyTest::test_constructor(void)
{
   message += "test_constructor\n";

   LossIndex pf;

   // Test

   TrainingStrategy ts1(&pf);

   assert_true(ts1.has_loss_index() == true, LOG);

   // Test

   TrainingStrategy ts2;

   assert_true(ts2.has_loss_index() == false, LOG);
}


void TrainingStrategyTest::test_destructor(void)
{
   message += "test_destructor\n";

   TrainingStrategy* ts = new TrainingStrategy();

   delete ts;
}


void TrainingStrategyTest::test_get_loss_index_pointer(void)
{
   message += "test_get_loss_index_pointer\n";

   LossIndex pf;
   
   TrainingStrategy ts(&pf);

   LossIndex* pfp = ts.get_loss_index_pointer();

   assert_true(pfp != NULL, LOG);
}


void TrainingStrategyTest::test_get_display(void)
{
   message += "test_get_warning_gradient_norm\n";

   TrainingStrategy ts;

   ts.set_display(false);

   assert_true(ts.get_display() == false, LOG);
}


void TrainingStrategyTest::test_set(void)
{
   message += "test_set\n"; 
}


void TrainingStrategyTest::test_set_default(void)
{
   message += "test_set_default\n"; 
}


void TrainingStrategyTest::test_set_loss_index_pointer(void)
{
   message += "test_set_loss_index_pointer\n"; 
}


void TrainingStrategyTest::test_set_display(void)
{
   message += "test_set_display\n"; 
}


void TrainingStrategyTest::test_initialize_layers_autoencoding(void)
{
/*
    message += "test_initialize_layers_autoencoding\n";

    DataSet ds;
    ds.randomize_data_normal();

    Vector<size_t> architecture;
    NeuralNetwork nn;

    LossIndex pf(&nn, &ds);
    TrainingStrategy ts(&pf);

    // Test

    ds.set(2,10,10);

    architecture.set(10,10);

    nn.set(architecture);

    ts.initialize_layers_autoencoding();

    // Test
/*
    ds.set(2,3,1);
    ds.randomize_data_normal();

    nn.set(3,4,1);

    ts.initialize_layers_autoencoding();
*/


//    system("pause");

//    assert_true(loss < old_loss, LOG);
 /*
    // Minimum parameters increment norm

    nn.initialize_parameters(3.1415927);

    double minimum_parameters_increment_norm = 0.1;

    qnm.set_minimum_parameters_increment_norm(minimum_parameters_increment_norm);
    qnm.set_loss_goal(0.0);
    qnm.set_minimum_loss_increase(0.0);
    qnm.set_gradient_norm_goal(0.0);
    qnm.set_maximum_iterations_number(10);
    qnm.set_maximum_time(1000.0);

    qnm.perform_training();

    // Performance goal

    nn.initialize_parameters(3.1415927);

    double loss_goal = 100.0;

    qnm.set_minimum_parameters_increment_norm(0.0);
    qnm.set_loss_goal(loss_goal);
    qnm.set_minimum_loss_increase(0.0);
    qnm.set_gradient_norm_goal(0.0);
    qnm.set_maximum_iterations_number(10);
    qnm.set_maximum_time(1000.0);

    qnm.perform_training();

    loss = pf.calculate_loss();

    assert_true(loss < loss_goal, LOG);

    // Minimum evaluation improvement

    nn.initialize_parameters(3.1415927);

    double minimum_loss_increase = 100.0;

    qnm.set_minimum_parameters_increment_norm(0.0);
    qnm.set_loss_goal(0.0);
    qnm.set_minimum_loss_increase(minimum_loss_increase);
    qnm.set_gradient_norm_goal(0.0);
    qnm.set_maximum_iterations_number(10);
    qnm.set_maximum_time(1000.0);

    qnm.perform_training();

    // Gradient norm goal

    nn.initialize_parameters(3.1415927);

    double gradient_norm_goal = 100.0;

    qnm.set_minimum_parameters_increment_norm(0.0);
    qnm.set_loss_goal(0.0);
    qnm.set_minimum_loss_increase(0.0);
    qnm.set_gradient_norm_goal(gradient_norm_goal);
    qnm.set_maximum_iterations_number(10);
    qnm.set_maximum_time(1000.0);

    qnm.perform_training();

    double gradient_norm = pf.calculate_gradient().calculate_norm();
    assert_true(gradient_norm < gradient_norm_goal, LOG);
*/
}


void TrainingStrategyTest::test_perform_training(void)
{
   message += "test_perform_training\n";

    NeuralNetwork nn;
    DataSet ds;
    LossIndex pf(&nn, &ds);
    TrainingStrategy ts(&pf);

    // Test

    nn.set(1, 1);
    ds.set(1,1,2);

//    ts.perform_training();

}


void TrainingStrategyTest::test_to_XML(void)
{
   message += "test_to_XML\n";

   TrainingStrategy ts;

   // Test

   ts.set_initialization_type(TrainingStrategy::RANDOM_SEARCH);
   ts.set_main_type(TrainingStrategy::GRADIENT_DESCENT);
//   ts.set_refinement_type(TrainingStrategy::NEWTON_METHOD);

   tinyxml2::XMLDocument* document = ts.to_XML();

   assert_true(document != NULL, LOG);

   delete document;

}


void TrainingStrategyTest::test_from_XML(void)
{
   message += "test_from_XML\n";

   TrainingStrategy ts1;
   TrainingStrategy ts2;

   ts1.set_initialization_type(TrainingStrategy::RANDOM_SEARCH);
   ts1.set_main_type(TrainingStrategy::GRADIENT_DESCENT);
//   ts1.set_refinement_type(TrainingStrategy::NEWTON_METHOD);

   tinyxml2::XMLDocument* document = ts1.to_XML();

    ts2.from_XML(*document);

   delete document;

    assert_true(ts2.get_initialization_type() == TrainingStrategy::RANDOM_SEARCH, LOG);
    assert_true(ts2.get_main_type() == TrainingStrategy::GRADIENT_DESCENT, LOG);
    assert_true(ts2.get_refinement_type() == TrainingStrategy::NEWTON_METHOD, LOG);
}


void TrainingStrategyTest::test_print(void)
{
   message += "test_print\n";
}


void TrainingStrategyTest::test_save(void)
{
   message += "test_save\n";

   string file_name = "../data/training_strategy.xml";

   TrainingStrategy ts;

   ts.set_initialization_type(TrainingStrategy::RANDOM_SEARCH);
   ts.set_main_type(TrainingStrategy::GRADIENT_DESCENT);
//   ts.set_refinement_type(TrainingStrategy::NEWTON_METHOD);

   ts.save(file_name);

}


void TrainingStrategyTest::test_load(void)
{
   message += "test_load\n";

   string file_name = "../data/training_strategy.xml";

   TrainingStrategy ts;

   // Test

   ts.initialize_random();

   ts.save(file_name);
   ts.load(file_name);

}


void TrainingStrategyTest::test_results_constructor(void)
{
    message += "test_results_constructor\n";

//    TrainingStrategy::TrainingStrategyResults results;

}


void TrainingStrategyTest::test_results_destructor(void)
{
    message += "test_results_destructor\n";

//    TrainingStrategy::TrainingStrategyResults* results = new TrainingStrategy::TrainingStrategyResults();

//    delete results;
}


void TrainingStrategyTest::run_test_case(void)
{
   message += "Running training strategy test case...\n";

   // Constructor and destructor methods
/*
   test_constructor();
   test_destructor();

   // Get methods

   test_get_loss_index_pointer();

   // Utilities
   
   test_get_display();

   // Set methods

   test_set();
   test_set_default();   

   test_set_loss_index_pointer();

   // Utilities

   test_set_display();

   // Training methods
*/
   test_initialize_layers_autoencoding();
/*
   test_perform_training();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   test_print();
   test_save();
   test_load();

   // Results methods

   test_results_constructor();
   test_results_destructor();
*/
   message += "End of training strategy test case.\n";
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
