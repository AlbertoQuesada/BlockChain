/****************************************************************************************************************/
/*                                                                                                              */
/*   B L O C K   C H A I N   P R O J E C T                                                                      */
/*                                                                                                              */
/*   T R A N S C T I O N D A T A   C L A S S   H E A D E R                                                      */
/*                                                                                                              */
/*   Alberto Quesada    albertoquesada@artelnics.com                                                            */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef TransactionData_h
#define TransactionData_h

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <istream>
#include <map>
#include <numeric>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
#include <climits>
#include <ctime>

#include "../../opennn/opennn/opennn.h"

using namespace std;
using namespace OpenNN;

struct TransactionData
{
    size_t amount;
    size_t time;
    string sender;
    time_t transaction_time;
    
    TransactionData(){}
    
    TransactionData(size_t new_amount, size_t new_time, string new_sender, time_t new_transaction_time)
    {
        amount = new_amount;
        time = new_time;
        sender = new_sender;
        transaction_time = new_transaction_time;
    }
};

#endif
