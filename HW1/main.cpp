#include "BlockChain.h"
#include "Transaction.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    // OP - decides what to do
    // OP can get     format --- hash --- compress --- verify
    if (argc != 4) {
        std::cout << getErrorMessage() << std::endl;
        return 0;
    }
    std::string op = argv[1];
    if (op == "verify") {
        std::ifstream source(argv[2]);
        std::ifstream target(argv[3]);
        BlockChain blockChain = BlockChainLoad(source);
        if (BlockChainVerifyFile(blockChain, target)) {
            std::cout << "Verification passed" << std::endl;
        } else {
            std::cout << "Verification failed" << std::endl;
        }
        source.close();
        target.close();
        DeleteRecursivelyBlockChain(&blockChain);
        return 0;
    }
    std::ifstream file1(argv[2]);
    std::ofstream file2(argv[3]);

    // Init the BlockChain from file 1
    BlockChain blockChain = BlockChainLoad(file1);

    if (op == "format") {
        BlockChainDump(blockChain, file2);
    }
    if (op == "hash") {
        BlockChainDumpHashed(blockChain, file2);
    }
    if (op == "compress") {
        BlockChainCompress(blockChain);
        BlockChainDump(blockChain, file2);
    }
    // Close files. IMPORTANT
    file1.close();
    file2.close();

    // FREE ALLOCATED SPACE
    DeleteRecursivelyBlockChain(&blockChain);

    return 0;
}

