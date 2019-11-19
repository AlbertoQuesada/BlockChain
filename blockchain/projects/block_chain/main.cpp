/****************************************************************************************************************/
/*                                                                                                              */
/*   B L O C K   C H A I N   P R O J E C T                                                                      */
/*                                                                                                              */
/*   M A I N                                                                                                    */
/*                                                                                                              */
/*   Alberto Quesada    albertoquesada@artelnics.com                                                            */
/*                                                                                                              */
/****************************************************************************************************************/

#include <iostream>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <QApplication>

#include "TransactionData.h"
#include "Block.h"
#include "Blockchain.h"

#include "../../opennn/opennn/opennn.h"

using namespace std;
using namespace OpenNN;

int main(int argc, char* argv[])
{
    try
    {
        QApplication app(argc, argv);

        cout << "                                               BLOCKCHAIN PROJECT" << endl;

        Blockchain iber_coin;

        time_t time_1;
        TransactionData transaction_1(1000, 7200, "Joe", time(&time_1));

        iber_coin.add_block(transaction_1);

        time_t time_2;
        TransactionData transaction_2(300, 3600, "Martha", time(&time_2));

        iber_coin.add_block(transaction_2);

        iber_coin.print_chain();

        cout << "Is chain still valid? " << iber_coin.is_chain_valid() << "\n\n" << endl;

        Block* last_block = iber_coin.get_latest_block();
        last_block->transaction_data.amount = 100000;
        last_block->transaction_data.sender = "Jon";

        iber_coin.print_chain();

        cout << "Is chain still valid? " << iber_coin.is_chain_valid() << "\n\n" << endl;

        return 0;
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;

        return(1);
    }
}
