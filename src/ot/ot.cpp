#include <tuple>

#include "ot.hpp"



pkey_t OTrecv::selectMsg(dme_branch_t b)
{
    keypair_t keyp = dme.KeyGen(b);
    sk = keyp.sk;
    return keyp.pk;
}


msg_t OTrecv::decryptMsg(ctxt_t c) const
{
    return dme.Dec(sk, c);
}

ctxt_p_t OTsndr::encMsgs(pkey_t pk, msg_t s0, msg_t s1)
{
    c.clear();
    c.push_back(dme.Enc(pk, dme_branch_t::b0, s0));
    c.push_back(dme.Enc(pk, dme_branch_t::b1, s1));
    return c;
} 
