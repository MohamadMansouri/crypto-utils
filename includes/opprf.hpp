#ifndef __OPPRF__
#define __OPPRF__

#include <stdint.h>
#include <array>

#include "ecc_secp256r1.hpp"
#include "ot.hpp"
#include "aes.hpp"

namespace opprf
{
#define MSG_BITS 16

typedef dme::POINT Gk_t;
typedef dme::POINT G_t;
typedef mpz_class symkey_t;
typedef dme::FIELD_n ok_t;
typedef std::vector<symkey_t> symkey_v_t;
typedef std::vector<ok_t> ok_v_t;

typedef uint16_t msg_t;

typedef struct ServerOTInputl
{
    symkey_t k;
    G_t prf;

} srv_inputl_t;


typedef struct ServerOTInputi
{
    aes::ctxt_t k_lt;
    aes::ctxt_t k_eq;
    aes::ctxt_t k_gt;
    G_t prf;

} srv_inputi_t;

typedef std::array<ot::ctxt_v_t, 3> ctxt_arr_t;

typedef struct OTCtxts
{
    ctxt_arr_t ctxt;
    ot::ctxt_v_t cprf;

} ot_ctxts_t;

typedef std::array<aes::ctxt_t, 3> symctxt_t;

// 
typedef std::vector<srv_inputi_t> srv_inputi_v_t;


class OPPRFserver
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
    OPPRFserver(msg_t theta, dme::crs_ddh_t crs);
    ~OPPRFserver() {}

    void setSecret(G_t& ga);
    void prepareKeysAndInputs();
    G_t getKOPPRF() {return kopprf;}
    void clean();

    ot_ctxts_t runOTRound(short round, dme::pkey_t pk);
    symctxt_t sendEncryptedMasks();
};

enum keysymbol_t {lt, eq, gt};

class OPPRFclient
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