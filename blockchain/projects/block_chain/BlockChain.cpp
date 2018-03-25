/****************************************************************************************************************/
/*                                                                                                              */
/*   B L O C K   C H A I N   P R O J E C T                                                                      */
/*                                                                                                              */
/*   B L O C K C H A I N   C L A S S                                                                            */
/*                                                                                                              */
/*   Alberto Quesada    albertoquesada@artelnics.com                                                            */
/*                                                                                                              */
/****************************************************************************************************************/

#include "Block.h"
#include "Blockchain.h"

Blockchain::Blockchain()
{
    Block genesis = create_genesis_block();

    chain.push_back(genesis);
}


Vector<Block> Blockchain::get_chain()
{
    return (chain);
}


Block Blockchain::create_genesis_block()
{
    time_t current;
    
    TransactionData d(0, 0, "Genesis", time(&current));
    
    Block genesis(0, d, 0);

    return (genesis);
}


Block* Blockchain::get_latest_block()
{
    return (&chain.back());
}


void Blockchain::add_block(TransactionData transaction_data)
{
    int index = (int)chain.size();

    size_t previous_hash = (int)chain.size() > 0 ? get_latest_block()->get_hash() : 0;

    Block new_block(index, transaction_data, previous_hash);

    chain.push_back(new_block);
}


bool Blockchain::is_chain_valid()
{
    for (size_t i = 0; i < chain.size(); i++)
    {
        Block current_block = chain[i];

        if (!current_block.is_hash_valid())
        {
            return(false);
        }

        if(i != 0)
        {
            Block previous_block = chain[i-1];

            if (current_block.get_previous_hash() != previous_block.get_hash())
            {
                return false;
            }
        }

    }

    return true;
}


void Blockchain::print_chain()
{
    for (size_t i = 0; i < chain.size(); i++)
    {
        Block current_block = chain[i];

        time_t current_block_transaction_data_time = current_block.transaction_data.transaction_time;

        struct tm* transaction_data_time = localtime(&current_block_transaction_data_time);

        cout << "Block" << endl;
        cout << "Index: " << to_string(current_block.get_index()) << endl;
        cout << "Sender: " << current_block.transaction_data.sender << endl;
        cout << "Transaction date: " << asctime(transaction_data_time) << endl;
        cout << "Amount: " << to_string(current_block.transaction_data.amount) << " \$" << endl;
        cout << "Time: " << to_string(current_block.transaction_data.time) << " seconds" << endl;
        cout << "Current hash: " << to_string(current_block.get_hash()) << endl;
        cout << "Previous hash: " << to_string(current_block.get_previous_hash()) << endl;
        cout << "Is block valid? " << to_string(current_block.is_hash_valid()) <<  "\n\n" << endl;
    }
}
