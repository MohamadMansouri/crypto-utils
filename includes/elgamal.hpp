#ifndef __ELGAMAL__
#define __ELGAMAL__
#include <string>

#include "ecc_secp256r1.hpp"

using std::string;


namespace elgamal
{
typedef field::Field_secp256r1_p FIELD_p;
typedef field::Field_secp256r1_n FIELD_n;
typedef ecc::Point_secp256r1 POINT;
typedef ecc::Curve_secp256r1 CURVE;
    
typedef struct CTXT
{
    POINT u;
    POINT mv;
} ctxt_t;
typedef POINT pkey_t;
typedef FIELD_n skey_t;

typedef struct KeyPair
{
    skey_t sk;
    pkey_t pk;
} keypair_t;


class ElGamal
{
private:
    CURVE curve;

    POINT encode(const mpz_class msg);
    mpz_class decode(const POINT P) const;

public:
    ElGamal(){}
    ~ElGamal(){}

    keypair_t keyGen() const {curve.generateKeyPair();}
    
    ctxt_t encrypt(const pkey_t pkey, const POINT msg) const;
    ctxt_t encrypt(const pkey_t pkey, const mpz_class msg) {return encrypt(pkey, encode(msg));}

    mpz_class decrypt(const skey_t skey, const ctxt_t c) const;
};

}


#endif