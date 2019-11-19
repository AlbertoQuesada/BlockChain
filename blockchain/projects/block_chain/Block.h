/****************************************************************************************************************/
/*                                                                                                              */
/*   B L O C K   C H A I N   P R O J E C T                                                                      */
/*                                                                                                              */
/*   B L O C K   C L A S S   H E A D E R                                                                        */
/*                                                                                                              */
/*   Alberto Quesada    albertoquesada@artelnics.com                                                            */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef Block_h
#define Block_h

#include "TransactionData.h"

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

// Block Class

class Block
{
private:

    int index;

    size_t block_hash;

    size_t previous_hash;

    size_t generate_hash();
    
public:

    Block(int new_index, TransactionData new_transaction_data, size_t new_previous_hash);
    
    int get_index();
    
    size_t get_hash();
    
    size_t get_previous_hash();
        
    bool is_hash_valid();

    TransactionData transaction_data;
};

#endif
