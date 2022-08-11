#ifndef __OT__
#define __OT__
#include <vector>

#include "dme.hpp"


namespace ot
{
typedef std::vector<dme::ctxt_t> ctxt_v_t;
typedef std::vector<dme::ctxt_t>::iterator ctxt_v_it ;

class OTrecv
{
private:
    dme::DME_DDH dme;
    dme::skey_t sk; 
    dme::branch_t b;

public:

    OTrecv(dme::mode_t mu) : dme(mu) {};
    OTrecv(dme::crs_ddh_t crs) : dme(crs) {};
    ~OTrecv() {};

    dme::CURVE* getCurve(void) {return dme.getCurve();}
    dme::branch_t getBranch() {return b;}

    dme::pkey_t selectMsg(dme::branch_t b) ;
    dme::msg_t decryptMsg(ctxt_v_t c) const;
    mpz_class decryptMsgDecode(ctxt_v_t c) const;
};


class OTsndr
{
private:
    dme::DME_DDH dme;
    ctxt_v_t c;

public:
    OTsndr(dme::mode_t mu) : dme(mu) {};
    OTsndr(dme::crs_ddh_t crs) : dme(crs) {};
    ~OTsndr() {};

    dme::CURVE* getCurve(void) {return dme.getCurve();}

    dme::msg_t getRandomMsg() {return dme.getCurve()->getRandomPoint();}
    ctxt_v_t encMsgs(dme::pkey_t pk, dme::msg_t m0, dme::msg_t m1); 
    ctxt_v_t encMsgs(dme::pkey_t pk, mpz_class m0, mpz_class m1); 

};

}



#endif