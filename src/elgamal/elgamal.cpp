
#include "elgamal.hpp"



namespace elgamal
{
static const unsigned int l = 20;
  
ctxt_t ElGamal::encrypt(const pkey_t pkey, const POINT msg) const
{
    ctxt_t c;
    FIELD_n r = curve.getRandomScalar();
    c.u = curve.getDefaultGen() * r; 
    c.mv = pkey * r + msg;
    return c;
}

mpz_class ElGamal::decrypt(const skey_t skey, const ctxt_t c) const
{
    POINT res = c.mv - c.u * skey;
    return decode(res);
}


mpz_class ElGamal::decode(const POINT P) const
{
    mpz_class res;
    mpz_class x = P.getX().getRawValue();
    mpz_div_2exp(res.get_mpz_t(), x.get_mpz_t(), l);
    return res;

} 

POINT ElGamal::encode(const mpz_class msg)
{
    mpz_class res;
    mpz_mul_2exp(res.get_mpz_t(), msg.get_mpz_t(), l);
    POINT m;
    while(m.isInf())
    {
        m = curve.evaluateP(FIELD_p(res));
        res+=1;
    }
    return m;
}    
}
