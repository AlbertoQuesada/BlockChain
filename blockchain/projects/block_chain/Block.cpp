/****************************************************************************************************************/
/*                                                                                                              */
/*   B L O C K   C H A I N   P R O J E C T                                                                      */
/*                                                                                                              */
/*   B L O C K   C L A S S                                                                                      */
/*                                                                                                              */
/*   Alberto Quesada    albertoquesada@artelnics.com                                                            */
/*                                                                                                              */
/****************************************************************************************************************/

#include "TransactionData.h"
#include "Block.h"

using namespace std;

Block::Block(int new_index, TransactionData new_transaction_data, size_t new_previous_hash)
{
    index = new_index;
    transaction_data = new_transaction_data;
    previous_hash = new_previous_hash;
    block_hash = generate_hash();
}


int Block::get_index()
{
    return (index);
}


size_t Block::generate_hash()
{
    string transaction_data_string = to_string(transaction_data.amount) +
                                     to_string(transaction_data.time) +
                                     transaction_data.sender +
                                     to_string(transaction_data.transaction_time);
    
    hash<string> transaction_data_hash;

    size_t transaction_data_hash_number = transaction_data_hash(transaction_data_string);

    hash<string> previous_data_hash;

    size_t previous_data_hash_number = previous_data_hash(to_string(previous_hash));
    
    return (transaction_data_hash_number ^ (previous_data_hash_number << 1));
}


size_t Block::get_hash()
{
    return (block_hash);
}


size_t Block::get_previous_hash()
{
    return (previous_hash);
}


bool Block::is_hash_valid()
{
    bool boolean = generate_hash() == get_hash();

    return (boolean);
}
