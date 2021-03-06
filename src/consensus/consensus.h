// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <stdlib.h>
#include <stdint.h>

static const uint64_t UB_FORK1_BLOCK_NUM=498777;
static const uint64_t UB_FORK_BLOCK_NUM=506400;
//extern int COINBASE_MATURITY_FORKV1;
inline unsigned int MaxBlockSize(uint64_t nblock) {
    if (nblock < UB_FORK_BLOCK_NUM)
        return 4000*1000;

    return (32*1000*1000);
}
//static const unsigned int MAX_TRANSACTION_SIZE = 1000*1000;
inline unsigned int MaxBlockSigops(uint64_t nblock) {
    return MaxBlockSize(nblock) / 50;
}
inline unsigned int MaxBlockSerializedSize(uint64_t nblock){
    if (nblock < UB_FORK_BLOCK_NUM)
        return 4000*1000;

    return (32*1000*1000);
}

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
static const unsigned int MAX_BLOCK_SERIALIZED_SIZE = 4000000;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
static const unsigned int MAX_BLOCK_WEIGHT = 4000000;
/** The maximum allowed number of signature check operations in a block (network rule) */
static const int64_t MAX_BLOCK_SIGOPS_COST = 80000;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 100;
static const int COINBASE_MATURITY_FORKV1 = 7200;
static const int COINBASE_MATURITY_INVALID = 999999;

static const int WITNESS_SCALE_FACTOR = 4;

static const size_t MIN_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 60; // 60 is the lower bound for the size of a valid serialized CTransaction
static const size_t MIN_SERIALIZABLE_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 10; // 10 is the lower bound for the size of a serialized CTransaction

/** Flags for nSequence and nLockTime locks */
/** Interpret sequence numbers as relative lock-time constraints. */
static constexpr unsigned int LOCKTIME_VERIFY_SEQUENCE = (1 << 0);
/** Use GetMedianTimePast() instead of nTime for end point timestamp. */
static constexpr unsigned int LOCKTIME_MEDIAN_TIME_PAST = (1 << 1);

inline int getCoinBaseMaturity(int coinBaseHeight) {
    if (coinBaseHeight < 0){
        return COINBASE_MATURITY_INVALID;
    }
    else if (coinBaseHeight < UB_FORK1_BLOCK_NUM){
        return COINBASE_MATURITY;
    }

    return COINBASE_MATURITY_FORKV1;
}



#endif // BITCOIN_CONSENSUS_CONSENSUS_H