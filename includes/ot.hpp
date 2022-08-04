#ifndef __OT__
#define __OT__
#include <vector>

#include "dme.hpp"

typedef std::vector<ctxt_t> ctxt_p_t;
typedef std::vector<ctxt_t>::iterator ctxt_p_it ;

class OTrecv
{
private:
    dmeDDH_EC dme;
    skey_t sk; 

public:

    OTrecv(dme_mode_t mu) : dme(mu) {};
    OTrecv(crs_ddh_ec_t crs) : dme(crs) {};
    ~OTrecv() {};

    pkey_t selectMsg(dme_branch_t b) ;
    msg_t decryptMsg(ctxt_t c) const;
};


class OTsndr
{
private:
    dmeDDH_EC dme;
    ctxt_p_t c;

public:
    OTsndr(dme_mode_t mu) : dme(mu) {};
    OTsndr(crs_ddh_ec_t crs) : dme(crs) {};
    ~OTsndr() {};

    msg_t getRandomMsg() {return dme.getCurve()->getRandomPoint();}
    ctxt_p_t encMsgs(pkey_t pk, msg_t m0, msg_t m1); 

};


#endif