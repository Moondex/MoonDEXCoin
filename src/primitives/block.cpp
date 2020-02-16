// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2018 The MoonDEX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"

#include "hash.h"
#include "chainparams.h"
#include "tinyformat.h"
#include "main.h"
#include "utilstrencodings.h"
#include "crypto/common.h"
#include "crypto/neoscrypt.h"
#include "crypto/Lyra2.h"

uint256 CBlockHeader::GetHash(int nHeight, bool fForceLyra) const
{
        uint256 thash;
        if (nHeight >= retargetLwmaHeight + 10 || (fForceLyra && nHeight >= 1)) {
            LYRA2(BEGIN(thash), 32, BEGIN(nVersion), 80, BEGIN(nVersion), 80, 2, 330, 256);
            return thash;
        }

        if(nTime <= 1522584000)
            neoscrypt((unsigned char *) &nVersion, (unsigned char *) &thash, 0x0);
        else
            thash = HashX16R(BEGIN(nVersion), END(nNonce), hashPrevBlock);

	return thash;
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (unsigned int i = 0; i < vtx.size(); i++)
    {
        s << "  " << vtx[i].ToString() << "\n";
    }
    return s.str();
}
