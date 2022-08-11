#ifndef __TOPPRF__
#define __TOPPRF__

#include "opprf.hpp"

namespace opprf
{


class TOPPRFproxy
{

};

class TOPPRFserver
{
private:
    ot::OTsndr ots;
    dme::CURVE* curve;
    aes::AES aes; 


    msg_t theta;

    G_t ga;
    G_t kopprf;
    G_t r;

    Gk_t gk;

    symkey_v_t k_lt; 
    symkey_v_t k_eq; 
    symkey_v_t k_gt; 

    ok_v_t ok; 

    srv_inputl_t Sl0;
    srv_inputl_t Sl1;
    srv_inputi_v_t Si0;
    srv_inputi_v_t Si1;

    aes::ctxt_t Enc(symkey_t key, symkey_t k);

public:
    TOPPRFserver(msg_t theta, dme::crs_ddh_t crs);
    ~TOPPRFserver() {}

    void setSecret(G_t& ga);
    void prepareKeysAndInputs();
    G_t getKOPPRF() {return kopprf;}
    void clean();

    ot_ctxts_t runOTRound(short round, dme::pkey_t pk);
    symctxt_t sendEncryptedMasks();
};

enum keysymbol_t {lt, eq, gt};

class TOPPRFclient
{
private:
    dme::CURVE* curve;

    ot::OTrecv otr;
    msg_t x;
    G_t result;
    symkey_t key;


    Gk_t getKeyi(Gk_t ki, Gk_t k);
    bool correctDecryption(Gk_t);
    aes::AES aes;

public:
    OPPRFclient(dme::crs_ddh_t crs);
    ~OPPRFclient() {}

    void setMessage(msg_t msg) {x = msg;}
    G_t getResult() {return result;}
    void clean();

    dme::pkey_t runOTRound_start(short round);
    void runOTRound_end(short round, ot_ctxts_t c);
    void unmaskResult(symctxt_t masks);
};



}


#endif