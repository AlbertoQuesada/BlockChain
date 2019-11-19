/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   O U T P U T S   T R E N D I N G   L A Y E R   C L A S S   H E A D E R                                      */
/*                                                                                                              */
/*   Patricia Garcia                                                                                            */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   patriciagarcia@artelnics.com                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __OUTPUTSTRENDINGLAYER_H__
#define __OUTPUTSTRENDINGLAYER_H__

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


// OpenNN includes

#include "vector.h"
#include "matrix.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents a layer of outputs trending neurons.

class OutputsTrendingLayer
{

public:

   // DEFAULT CONSTRUCTOR

   explicit OutputsTrendingLayer(void);

   // OUTPUTS TRENDING NEURONS NUMBER CONSTRUCTOR

   explicit OutputsTrendingLayer(const size_t&);

   // XML CONSTRUCTOR

   explicit OutputsTrendingLayer(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   OutputsTrendingLayer(const OutputsTrendingLayer&);

   // DESTRUCTOR

   virtual ~OutputsTrendingLayer(void);

   // ASSIGNMENT OPERATOR

   OutputsTrendingLayer& operator = (const OutputsTrendingLayer&);

   // EQUAL TO OPERATOR

   bool operator == (const OutputsTrendingLayer&) const;

   // ENUMERATIONS

   /// Enumeration of available methods for trending the output variables.

   enum OutputsTrendingMethod{NoTrending, Linear};

   // METHODS

   bool is_empty(void) const;

   size_t get_outputs_trending_neurons_number(void) const;

   const OutputsTrendingMethod& get_outputs_trending_method(void) const;

   string write_outputs_trending_method(void) const;

   Vector<double> get_intercepts(void) const;
   double get_intercept(const size_t&) const;

   Vector<double> get_slopes(void) const;
   double get_slope(const size_t&) const;

   Vector<double> get_correlations(void) const;
   double get_correlation(const size_t&) const;

   Vector< LinearRegressionParameters<double> > get_outputs_trends(void) const;

   // Variables

   void set(void);
   void set(const size_t&);
   void set(const tinyxml2::XMLDocument&);
   void set(const OutputsTrendingLayer&);

   void set_outputs_trending_method(const OutputsTrendingMethod&);
   void set_outputs_trending_method(const string&);

   void set_intercepts(const Vector<double>&);
   void set_intercept(const size_t&, const double&);

   void set_slopes(const Vector<double>&);
   void set_slope(const size_t&, const double&);

   void set_correlations(const Vector<double>&);
   void set_correlation(const size_t&, const double&);

   void set_outputs_trends(const Vector< LinearRegressionParameters<double> >&);

   void set_display(const bool&);

   void set_default(void);

   // Pruning and growing

   void prune_output_trending_neuron(const size_t&);

   // Initialization

   void initialize_random(void);

   Vector<double> calculate_outputs(const Vector<double>&, const double& = 0.0) const;
   Vector<double> calculate_derivatives(void) const;
   Vector<double> calculate_second_derivatives(void) const;

   Matrix<double> arrange_Jacobian(const Vector<double>&) const;
   Vector< Matrix<double> > arrange_Hessian_form(const Vector<double>&) const;

   // Expression methods

   string write_expression(const Vector<string>&, const Vector<string>&) const;

   // Serialization methods

   string object_to_string(void) const;

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;
   //void read_XML(  );

protected:

   // MEMBERS

   OutputsTrendingMethod outputs_trending_method;

   Vector< LinearRegressionParameters<double> > outputs_trends;

   bool display;
};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2018 Artificial Intelligence Techniques, SL.
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

