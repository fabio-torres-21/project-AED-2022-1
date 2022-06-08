#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>

using namespace std;

template <typename TV, typename TE>
class Block {
    private:
        TV *transactions;

    public:
        Block();
        insertBlock(int prev_hash, TV *transactions);
}





#endif /* BLOCK_H */