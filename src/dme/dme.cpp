#include <gmpxx.h>
#include <tuple>

#include "dme.hpp"
#include "ecc_secp256r1.hpp"


namespace dme
{


CRS_DDH::CRS_DDH(POINT g0, POINT g1, POINT h0, POINT h1)
{
    this->g0 = g0;
    this->g1 = g1;
    this->h0 = h0;
    this->h1 = h1;
}


CRS_DDH& CRS_DDH::operator= (const CRS_DDH& crs)
{
    this->g0 = crs.g0;
    this->g1 = crs.g1;
    this->h0 = crs.h0;
    this->h1 = crs.h1;
    return *this;
}

void CRS_DDH::updateCurve(CURVE* c)
{
    this->g0.curve = c;
    this->g1.curve = c;
    this->h0.curve = c;
    this->h1.curve = c;
}

bool CRS_DDH::operator==(const CRS_DDH& crs) const
{
    return 
    this->g0 == crs.g0 &&
    this->g1 == crs.g1 &&
    this->h0 == crs.h0 &&
    this->h1 == crs.h1;
}

td_messy_DDH::td_messy_DDH(FIELD_n e0, FIELD_n e1)
{
    this->e0 = e0;
    this->e1 = e1;
}

td_messy_DDH& td_messy_DDH::operator=(const td_messy_DDH& td)
{
    this->e0 = td.e0;
    this->e1 = td.e1;
    return *this;
}

bool td_messy_DDH::operator==(const td_messy_DDH& td) const
{
    return this->e0 == td.e0 && this->e1 == td.e1;
}


td_dec_DDH::td_dec_DDH(FIELD_n y)
{
    this->y = y;
}


td_dec_DDH& td_dec_DDH::operator=(const td_dec_DDH& td)
{
    this->y = td.y;
    return *this;
}

bool td_dec_DDH::operator==(const td_dec_DDH& td) const
{
    return this->y == td.y;
}




PKEY::PKEY(POINT g, POINT h)
{
    this->g = g;
    this->h = h;
}
PKEY& PKEY::operator=(const PKEY& pk)
{
    this->g = pk.g;
    this->h = pk.h;
    return *this;
}
bool PKEY::operator==(const PKEY& pk) const
{
    return this->g == pk.g && this->h == pk.h;
}


KeyPair::KeyPair(pkey_t pk, skey_t sk)
{
    this->pk = pk;
    this->sk = sk;
}
KeyPair& KeyPair::operator=(const KeyPair& keys)
{
    this->pk = keys.pk;
    this->sk = keys.sk; 
    return *this;
}
bool KeyPair::operator==(const KeyPair& keys) const
{
    return this->pk == keys.pk && this->sk == keys.sk; 
}

CTXT::CTXT(POINT u, POINT mv)
{
    this->u = u;
    this->mv = mv;
}

CTXT& CTXT::operator=(const CTXT& ctxt)
{
    this->u = ctxt.u;
    this->mv = ctxt.mv;
    return *this;
}

bool CTXT::operator==(const CTXT& ctxt) const
{
    return this->u == u && this->mv == mv;
}



DME_DDH::DME_DDH(mode_t mu)
{  
    mode = mu;
    if(mode == messy)
    {
        FIELD_n e0 = curve->getRandomScalar();
        FIELD_n e1 = curve->getRandomScalar();
        POINT g0 = curve->getRandomPoint();
        POINT g1 = curve->getRandomPoint();
        POINT h0 = g0 * e0;
        POINT h1 = g1 * e1;

        crs = crs_ddh_t(g0,g1,h0,h1);
        td_m = td_messy_ddh_t(e0,e1);

    }
    else
    {
        FIELD_n y = curve->getRandomScalar();
        POINT g0 = curve->getRandomPoint();
        POINT g1 = g0 * y;
        FIELD_n e = curve->getRandomScalar();
        POINT h0 = g0 * e;
        POINT h1 = g1 * e;

        crs = crs_ddh_t(g0,g1,h0,h1);
        td_d = td_dec_ddh_t(y);
    }
}

DME_DDH::DME_DDH()
{
    POINT g0 = curve->getRandomPoint();
    POINT h0 = curve->getRandomPoint();
    POINT g1 = curve->getRandomPoint();
    POINT h1 = curve->getRandomPoint();

    crs = crs_ddh_t(g0,g1,h0,h1);
}


DME_DDH::DME_DDH(crs_ddh_t crs)
{
    this->crs = crs;
    this->crs.updateCurve(curve);
}


DME_DDH::~DME_DDH()
{
    if (curve)
        delete curve;
}




keypair_t DME_DDH::KeyGen(branch_t branch) const
{
    skey_t sk = curve->getRandomScalar();
    pkey_t pk;
    switch (branch)
    {
    case b0:
        pk.g = crs.g0 * sk;
        pk.h = crs.h0 * sk;
        break;
    
    case b1:
        pk.g = crs.g1 * sk;
        pk.h = crs.h1 * sk;
        break;

    default:
        break;
    }

    return keypair_t(pk,sk);
}


msg_t DME_DDH::encode(const mpz_class& m) const
{
    mpz_class res;
    mpz_mul_2exp(res.get_mpz_t(), m.get_mpz_t(), ENCODING_SHIFT);
    POINT msg;
    while(msg.isInf())
    {
        msg = curve->evaluateP(FIELD_p(res));
        res+=1;
    }
    return msg;
}

mpz_class DME_DDH::decode(const msg_t& m) const
{
    mpz_class res;
    mpz_class x = m.getX().getRawValue();
    mpz_div_2exp(res.get_mpz_t(), x.get_mpz_t(), ENCODING_SHIFT);
    return res;

}


ctxt_t DME_DDH::Enc(const pkey_t& pk, branch_t b, const msg_t& m) const
{
    FIELD_n s = curve->getRandomScalar();
    FIELD_n t = curve->getRandomScalar();

    POINT v = pk.g * s + pk.h * t;
    

    ctxt_t c; 
    
    switch (b)
    {
    case b0:
        c = ctxt_t(crs.g0 * s + crs.h0 * t, v + m);
        break;
    
    case b1:
        c = ctxt_t(crs.g1 * s + crs.h1 * t, v + m);
        break;

    default:
        break;
    }

    return c;
}

ctxt_t DME_DDH::Enc(const pkey_t& pk, branch_t b, const mpz_class& m) const
{
    return Enc(pk, b, encode(m));
}


ctxt_t DME_DDH::EncCRC(const pkey_t& pk, branch_t b, const mpz_class& m) const
{
    // std::string s = m;
    // return Enc(pk, b, encode(m));
}



msg_t DME_DDH::Dec(const skey_t& sk, const ctxt_t& c) const
{
    return c.mv - c.u * sk;
}

mpz_class DME_DDH::DecDecode(const skey_t& sk, const ctxt_t& c) const
{
    return decode(Dec(sk, c));
}


branch_t DME_DDH::FindMessy(const pkey_t& pk) const
{
    return branch_t(pk.h == (pk.g * td_m.e0));
}


std::tuple<pkey_t, skey_t, skey_t > DME_DDH::TrapKeyGen() const
{
    skey_t r = curve->getRandomScalar();
    pkey_t pk(crs.g0*r, crs.h0*r);
    return std::make_tuple(pk, r, r/(td_d.y));
}
}
