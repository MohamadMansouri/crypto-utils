#include <tuple>

#include "ot.hpp"


namespace ot
{

dme::pkey_t OTrecv::selectMsg(dme::branch_t b)
{
    dme::keypair_t keyp = dme.KeyGen(b);
    this->sk = keyp.sk;
    this->b = b;
    return keyp.pk;
}


dme::msg_t OTrecv::decryptMsg(ctxt_v_t c) const
{
    return dme.Dec(sk, c[b]);
}

mpz_class OTrecv::decryptMsgDecode(ctxt_v_t c) const
{
    return dme.DecDecode(sk, c[b]);
}

ctxt_v_t OTsndr::encMsgs(dme::pkey_t pk, dme::msg_t s0, dme::msg_t s1)
{
    c.clear();
    c.push_back(dme.Enc(pk, dme::branch_t::b0, s0));
    c.push_back(dme.Enc(pk, dme::branch_t::b1, s1));
    return c;
} 

ctxt_v_t OTsndr::encMsgs(dme::pkey_t pk, mpz_class s0, mpz_class s1)
{
    c.clear();
    c.push_back(dme.Enc(pk, dme::branch_t::b0, s0));
    c.push_back(dme.Enc(pk, dme::branch_t::b1, s1));
    return c;
} 

}

