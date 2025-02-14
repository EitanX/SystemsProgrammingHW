#include "BlockChain.h"
#include "Transaction.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

// --------------------------- CONSTRUCTORS --------------------------------------
// -------------------------------------------------------------------------------
Node::Node(const Transaction &transaction) {
    this->currentTransaction.value = transaction.value;
    this->currentTransaction.receiver = transaction.receiver;
    this->currentTransaction.sender = transaction.sender;
}

Node::Node(unsigned int value, const string &sender, const string &receiver) {
    this->currentTransaction.value = value;
    this->currentTransaction.sender = sender;
    this->currentTransaction.receiver = receiver;
    this->previousNodeAddress = nullptr;
}
// -------------------------------------------------------------------------------
// --------------------------- CONSTRUCTORS --------------------------------------

int BlockChainGetSize(const BlockChain &blockChain) {
    // Check block not empty
    if (blockChain.topNode == nullptr) {
        return 0;
    }
    // Block not empty - start counting and moving on the BlockChain
    Node *currentNode = blockChain.topNode;
    int counter = 1;
    while (currentNode->previousNodeAddress != nullptr) {
        counter++;
        currentNode = currentNode->previousNodeAddress;
    }
    return counter;
}

int BlockChainPersonalBalance(const BlockChain &blockChain, const string &name) {
    // Check block not empty
    if (blockChain.topNode == nullptr) {
        return 0;
    }
    // Block not empty - start counting BALANCE of `name` on the BlockChain
    // BlockTransactionValue --- Returns a +- value of money `name` received/sent
    Node *currentNode = blockChain.topNode;
    long int balance = BlockTransactionValue(*currentNode, name);
    while (currentNode->previousNodeAddress != nullptr) {
        currentNode = currentNode->previousNodeAddress;
        balance += BlockTransactionValue(*currentNode, name);
    }
    return balance;
}

void BlockChainAppendTransaction(
        BlockChain &blockChain,
        unsigned int value,
        const string &sender,
        const string &receiver,
        const string &timestamp
) {
    BlockChainAppendTransaction(blockChain, Transaction {
            value, sender, receiver
    }, timestamp);
}

void BlockChainAppendTransaction(
        BlockChain &blockChain,
        const Transaction &transaction,
        const string &timestamp
) {
    //Initializing The Node
    Node *newNode = new Node(transaction);
    newNode->timestamp = timestamp;
    newNode->previousNodeAddress = blockChain.topNode;

    //Blockchain points to new topNode
    blockChain.topNode = newNode;
}

BlockChain BlockChainLoad(ifstream &file) {
    // Flags if we are only in the begging of the Initialization
    BlockChain newBlockChain;
    Node *tempPreviousNode = nullptr;
    bool isTopNodeFlag = true;

    unsigned int value;
    string sender, receiver, timestamp;
    while (file >> sender >> receiver >> value >> timestamp) {
        // Init Node - points to nullptr
        Node *newNode = new Node(value, sender, receiver);
        newNode->timestamp = timestamp;

        // IF BlockChain doesn't exist - Init BlockChain pointer to FIRST NODE
        if (isTopNodeFlag) {
            newBlockChain.topNode = newNode;
            isTopNodeFlag = false;
        }

        // IF we already have a PrevNode - we must point the LastNode to NewNode
        if (tempPreviousNode != nullptr) {
            tempPreviousNode->previousNodeAddress = newNode;
        }

        // Point the flag of PrevNode to this Node
        tempPreviousNode = newNode;

    }
    return newBlockChain;
}

void BlockChainDump(const BlockChain &blockChain, ofstream &file) {
    file << "BlockChain Info:" << std::endl;

    // Check if blockchain is empty.
    if (blockChain.topNode == nullptr) {
        return;
    }

    // Prints the first NODE only
    Node *currentNode = blockChain.topNode;
    int counter = 1;
    PrintDump(currentNode, file, counter);

    // Prints all the next NODES
    while (currentNode->previousNodeAddress != nullptr) {
        counter++;
        currentNode = currentNode->previousNodeAddress;
        PrintDump(currentNode, file, counter);
    }
}

void BlockChainDumpHashed(const BlockChain &blockChain, ofstream &file) {
    // if the blockchain is empty return;
    if (blockChain.topNode == nullptr) {
        return;
    }
    Node *currentNode = blockChain.topNode;
    while (currentNode != nullptr) {
        // prints the n-1 line with endl
        if (currentNode->previousNodeAddress != nullptr) {
            file << TransactionHashedMessage(currentNode->currentTransaction)
                 << std::endl;
            currentNode = currentNode->previousNodeAddress;
            continue;
        }
        // Prints the last line without endl
        file << TransactionHashedMessage(currentNode->currentTransaction);
        currentNode = currentNode->previousNodeAddress;
    }
}

bool BlockChainVerifyFile(const BlockChain &blockChain, std::ifstream &file) {
    Node *currentNode = blockChain.topNode;
    string line;
    // Condition (LINE EXISTS) && (NODE EXISTS)
    // Using one of prev func to verify.
    // If one of the HASH wrong ----- RETURN FALSE
    while (currentNode != nullptr && std::getline(file, line)) {
        if (!TransactionVerifyHashedMessage(currentNode->currentTransaction, line)) {
            return false;
        }
        currentNode = currentNode->previousNodeAddress;
    }
    if (currentNode != nullptr || std::getline(file, line)) {
        return false;
    }
    return true;
}

void BlockChainCompress(BlockChain &blockChain) {
    // Check block not empty
    if (blockChain.topNode == nullptr) {
        return;
    }

    // Block not empty - start checking COMPRESS CONDITION on the BlockChain
    Node *currentNode = blockChain.topNode;
    unsigned int sum = 0;
    while (currentNode != nullptr) {
        sum = currentNode->currentTransaction.value;
        Node *tempNode = currentNode->previousNodeAddress;
        while (tempNode != nullptr &&
               currentNode->currentTransaction.sender == tempNode->currentTransaction.sender &&
               currentNode->currentTransaction.receiver == tempNode->currentTransaction.receiver) {
            sum += tempNode->currentTransaction.value;
            tempNode = tempNode->previousNodeAddress;
            DeleteRecursivelyNode(currentNode->previousNodeAddress);
            currentNode->previousNodeAddress = tempNode;
        }
        currentNode->currentTransaction.value = sum;
        sum = 0;
        currentNode = tempNode;
    }
}

void BlockChainTransform(BlockChain &blockChain, updateFunction function) {
    // Usual if to check BlockChain not empty
    if (blockChain.topNode == nullptr) {
        return;
    }
    Node *currentNode = blockChain.topNode;

    // Apply the function on the value of each transaction and replace.
    while (currentNode != nullptr) {
        currentNode->currentTransaction.value = function(currentNode->currentTransaction.value);
        currentNode = currentNode->previousNodeAddress;
    }
}

/**
 *
 * OUR FUNCTIONS
 *
*/
long int BlockTransactionValue(const Node &node, const string &name) {
    if (node.currentTransaction.receiver == name && node.currentTransaction.sender == name) {
        return 0;
    }
    if (node.currentTransaction.receiver == name) {
        return node.currentTransaction.value;
    }
    if (node.currentTransaction.sender == name) {
        return -node.currentTransaction.value;
    }
    return 0;
}

void PrintDump(Node *currentNode, ofstream &file, int number) {
    file << number << "." << std::endl;
    file << "Sender Name: " << currentNode->currentTransaction.sender << std::endl;
    file << "Receiver Name: " << currentNode->currentTransaction.receiver << std::endl;
    file << "Transaction Value: " << currentNode->currentTransaction.value << std::endl;
    file << "Transaction timestamp: " << currentNode->timestamp << std::endl;
}

void DeleteRecursivelyNode(Node *node) {
    if (node == nullptr) {
        return;
    }
    delete node;
}

void DeleteRecursivelyBlockChain(BlockChain *blockChain) {
    if (blockChain->topNode == nullptr) {
        return;
    }
    Node *currentNode = blockChain->topNode;
    Node *tempNodeDelete = nullptr;
    while (currentNode->previousNodeAddress != nullptr) {
        tempNodeDelete = currentNode;
        currentNode = currentNode->previousNodeAddress;
        DeleteRecursivelyNode(tempNodeDelete);
    }
    DeleteRecursivelyNode(currentNode);
}