#include <gmpxx.h>
#include <tuple>

#include "dme.hpp"
#include "ecc_secp256r1.hpp"




CRS_DDH_EC::CRS_DDH_EC(Point g0, Point g1, Point h0, Point h1)
{
    this->g0 = g0;
    this->g1 = g1;
    this->h0 = h0;
    this->h1 = h1;
}


CRS_DDH_EC& CRS_DDH_EC::operator= (const CRS_DDH_EC& crs)
{
    this->g0 = crs.g0;
    this->g1 = crs.g1;
    this->h0 = crs.h0;
    this->h1 = crs.h1;
    return *this;
}

void CRS_DDH_EC::updateCurve(CURVE* c)
{
    this->g0.curve = c;
    this->g1.curve = c;
    this->h0.curve = c;
    this->h1.curve = c;
}

bool CRS_DDH_EC::operator==(const CRS_DDH_EC& crs) const
{
    return 
    this->g0 == crs.g0 &&
    this->g1 == crs.g1 &&
    this->h0 == crs.h0 &&
    this->h1 == crs.h1;
}

td_messy_DDH_EC::td_messy_DDH_EC(FIELD_n e0, FIELD_n e1)
{
    this->e0 = e0;
    this->e1 = e1;
}

td_messy_DDH_EC& td_messy_DDH_EC::operator=(const td_messy_DDH_EC& td)
{
    this->e0 = td.e0;
    this->e1 = td.e1;
    return *this;
}

bool td_messy_DDH_EC::operator==(const td_messy_DDH_EC& td) const
{
    return this->e0 == td.e0 && this->e1 == td.e1;
}


td_dec_DDH_EC::td_dec_DDH_EC(FIELD_n y)
{
    this->y = y;
}


td_dec_DDH_EC& td_dec_DDH_EC::operator=(const td_dec_DDH_EC& td)
{
    this->y = td.y;
    return *this;
}

bool td_dec_DDH_EC::operator==(const td_dec_DDH_EC& td) const
{
    return this->y == td.y;
}




PKEY::PKEY(Point g, Point h)
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


KeyPair_t::KeyPair_t(pkey_t pk, skey_t sk)
{
    this->pk = pk;
    this->sk = sk;
}
KeyPair_t& KeyPair_t::operator=(const KeyPair_t& keys)
{
    this->pk = keys.pk;
    this->sk = keys.sk; 
    return *this;
}
bool KeyPair_t::operator==(const KeyPair_t& keys) const
{
    return this->pk == keys.pk && this->sk == keys.sk; 
}

CTXT::CTXT(Point u, Point mv)
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



dmeDDH_EC::dmeDDH_EC(dme_mode_t mu)
{  
    mode = mu;
    if(mode == messy)
    {
        FIELD_n e0 = curve->getRandomScalar();
        FIELD_n e1 = curve->getRandomScalar();
        Point g0 = curve->getRandomPoint();
        Point g1 = curve->getRandomPoint();
        Point h0 = g0 * e0;
        Point h1 = g1 * e1;

        crs = crs_ddh_ec_t(g0,g1,h0,h1);
        td_m = td_messy_ddh_ec_t(e0,e1);

    }
    else
    {
        FIELD_n y = curve->getRandomScalar();
        Point g0 = curve->getRandomPoint();
        Point g1 = g0 * y;
        FIELD_n e = curve->getRandomScalar();
        Point h0 = g0 * e;
        Point h1 = g1 * e;

        crs = crs_ddh_ec_t(g0,g1,h0,h1);
        td_d = td_dec_ddh_ec_t(y);
    }
}



dmeDDH_EC::dmeDDH_EC(crs_ddh_ec_t crs)
{
    this->crs = crs;
    this->crs.updateCurve(curve);
}


dmeDDH_EC::~dmeDDH_EC()
{
    if (curve)
        delete curve;
}



void dmeDDH_EC::setMode(dme_mode_t mu)
{
    mode = mu;
}
void dmeDDH_EC::setTdMessy(td_messy_ddh_ec_t td)
{
    td_m = td;
}
void dmeDDH_EC::setTdDec(td_dec_ddh_ec_t td)
{
    td_d = td;
}


keypair_t dmeDDH_EC::KeyGen(dme_branch_t branch) const
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


ctxt_t dmeDDH_EC::Enc(const pkey_t& pk, dme_branch_t b, const msg_t& m) const
{
    FIELD_n s = curve->getRandomScalar();
    FIELD_n t = curve->getRandomScalar();

    Point v = pk.g * s + pk.h * t;
    

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


msg_t dmeDDH_EC::Dec(const skey_t& sk, const ctxt_t& c) const
{
    return c.mv - c.u * sk;
}


dme_branch_t dmeDDH_EC::FindMessy(const pkey_t& pk) const
{
    return dme_branch_t(pk.h == (pk.g * td_m.e0));
}


std::tuple<pkey_t, skey_t, skey_t > dmeDDH_EC::TrapKeyGen() const
{
    skey_t r = curve->getRandomScalar();
    pkey_t pk(crs.g0*r, crs.h0*r);
    return std::make_tuple(pk, r, r/(td_d.y));
}