#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#include <iostream>
#include <hash.h>

/* ------------------------------------ */

using namespace std;

template <typename TV, typename TE>
class Blockchain {
    private:
        int prev_hash;
        TV *transactions;
        int block_hash;

    public:
        Blockchain();
        Blockchain(int prev_hash, TV *transactions);
        ~Blockchain();

        int getPrevHash();
        TV getTrnsactions();

};


template <typename TV, typename TE>
Blockchain<TV, TE>::Blockchain() {
    this->prev_hash = 0;
    this->transactions = NULL;
}

template <typename TV, typename TE>
Blockchain<TV, TE>::Blockchain(int prev_hash, TV *transactions) {
    this->prev_hash = prev_hash;
    this->transactions = transactions;

    this->block_hash = hash. prev_hash + transactions->getHash();
}

template <typename TV, typename TE>
Blockchain<TV, TE>::~Blockchain() {
    delete this->transactions;
}

template <typename TV, typename TE>
int Blockchain<TV, TE>::getPrevHash() {
    return this->prev_hash;
}

template <typename TV, typename TE>
TV Blockchain<TV, TE>::getTrnsactions() {
    return this->transactions;
}

#endif /* BLOCKCHAIN_H_ */