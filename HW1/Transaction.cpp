#include "Transaction.h"
#include "Utilities.h"
#include <iostream>


void TransactionDumpInfo(const Transaction &transaction, ofstream &file) {
    if (file.is_open()) {
        file << "Sender Name: " << transaction.sender << std::endl;
        file << "Receiver Name: " << transaction.receiver << std::endl;
        file << "Transaction Value: " << transaction.value << std::endl;
    }
}

string TransactionHashedMessage(const Transaction &transaction) {
    return hash(transaction.value, transaction.sender, transaction.receiver);
}

bool TransactionVerifyHashedMessage(const Transaction &transaction,
                                    string hashedMessage
) {
    if (hashedMessage == TransactionHashedMessage(transaction)) return true;
    else return false;
}