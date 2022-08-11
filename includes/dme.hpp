#ifndef __DME__
#define __DME__

#include <gmpxx.h>
#include <tuple>

#include "ecc_secp256r1.hpp"




namespace dme 
{

#define ENCODING_SHIFT 10

typedef field::Field_secp256r1_p FIELD_p;
typedef field::Field_secp256r1_n FIELD_n;
typedef ecc::Point_secp256r1 POINT;
typedef ecc::Curve_secp256r1 CURVE;

typedef struct CRS_DDH
{
    POINT g0, g1, h0, h1;

    CRS_DDH() {};
    CRS_DDH(POINT g0, POINT g1, POINT h0, POINT h1);
    CRS_DDH& operator= (const CRS_DDH& crs);
    bool operator== (const CRS_DDH& crs) const;
    void updateCurve(CURVE* c);

} crs_ddh_t;

typedef struct td_messy_DDH
{
    FIELD_n e0, e1;

    td_messy_DDH() {};
    td_messy_DDH(FIELD_n e0, FIELD_n e1);
    td_messy_DDH& operator=(const td_messy_DDH& td);
    bool operator==(const td_messy_DDH& td) const;
} td_messy_ddh_t;

typedef struct td_dec_DDH
{
    FIELD_n y;

    td_dec_DDH() {};
    td_dec_DDH(FIELD_n y);
    td_dec_DDH& operator=(const td_dec_DDH& td);
    bool operator==(const td_dec_DDH& td) const;
} td_dec_ddh_t;

enum mode_t {messy, dec};  

enum branch_t{b0 = 0, b1 = 1};


typedef struct PKEY
{
    POINT g, h;
 
    PKEY() {};
    PKEY(POINT g, POINT h);
    PKEY& operator=(const PKEY& pk);
    bool operator==(const PKEY& pk) const;
} pkey_t;

typedef FIELD_n skey_t; 

typedef struct KeyPair
{
    pkey_t pk;
    skey_t sk;

    KeyPair() {};
    KeyPair(pkey_t pk, skey_t sk);
    KeyPair& operator=(const KeyPair& keys);
    bool operator==(const KeyPair& keys) const;
} keypair_t;


typedef struct CTXT
{
    POINT u; 
    POINT mv;

    CTXT() {};
    CTXT(POINT u, POINT mv);
    
    CTXT& operator=(const CTXT& ctxt);
    bool operator==(const CTXT& ctxt) const;

} ctxt_t;

typedef POINT msg_t;

class DME_DDH
{
private:
    static const size_t secparam = 256; //bits
    
    CURVE* curve =  new CURVE;

    mode_t mode;  
    td_messy_ddh_t td_m;
    td_dec_ddh_t td_d;


public:
    crs_ddh_t  crs;

    msg_t encode(const mpz_class& m) const;
    mpz_class decode(const msg_t& m) const;

    DME_DDH();
    DME_DDH(mode_t mu);
    DME_DDH(crs_ddh_t crs);
    ~DME_DDH();
    
    CURVE* getCurve(void) {return curve;}

    keypair_t KeyGen(branch_t branch) const;
    ctxt_t Enc(const pkey_t& pk, branch_t b, const msg_t& m) const;
    ctxt_t Enc(const pkey_t& pk, branch_t b, const mpz_class& m) const;
    ctxt_t EncCRC(const pkey_t& pk, branch_t b, const msg_t& m) const;
    ctxt_t EncCRC(const pkey_t& pk, branch_t b, const mpz_class& m) const;
    msg_t Dec(const skey_t& sk, const ctxt_t& c) const;
    mpz_class DecDecode(const skey_t& sk, const ctxt_t& c) const;
    msg_t DecCRC(const skey_t& sk, const ctxt_t& c) const;
    mpz_class DecDecodeCRC(const skey_t& sk, const ctxt_t& c) const;
    branch_t FindMessy(const pkey_t& pk) const;
    std::tuple<pkey_t, skey_t, skey_t > TrapKeyGen() const;

};

}





#endif