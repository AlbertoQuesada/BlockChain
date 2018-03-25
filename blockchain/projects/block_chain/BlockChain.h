/****************************************************************************************************************/
/*                                                                                                              */
/*   B L O C K   C H A I N   P R O J E C T                                                                      */
/*                                                                                                              */
/*   B L O C K C H A I N   C L A S S   H E A D E R                                                              */
/*                                                                                                              */
/*   Alberto Quesada    albertoquesada@artelnics.com                                                            */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef Blockchain_h
#define Blockchain_h

#include <Block.h>

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

class Blockchain
{
private:

    Block create_genesis_block();

    Vector<Block> chain;

public:

    Blockchain();
        
    Vector<Block> get_chain();

    Block* get_latest_block();

    bool is_chain_valid();

    void add_block(TransactionData transaction_data);

    void print_chain();
};

#endif
