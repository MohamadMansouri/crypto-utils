#include <bitset>

#include "opprf.hpp"
#include "utilities.hpp"

namespace opprf
{


OPPRFserver::OPPRFserver(msg_t theta, dme::crs_ddh_t crs) : ots(crs)
{
    this->theta = theta;
    this->curve = ots.getCurve();
    this->gk = this->curve->getRandomPoint();
    Si0.resize(MSG_BITS);
    Si1.resize(MSG_BITS);
    aes::AES::init();
}

// inline Gk_t OPPRFserver::genKey(symkey_t k1, symkey_t k2)
// {
//     return gk * (k2 - k1);
// }

void OPPRFserver::setSecret(G_t& ga)
{
    ga.curve = curve;
    assert(ga.isValid());
    this->ga = ga;
}


void OPPRFserver::prepareKeysAndInputs()
{
    kopprf = curve->getRandomPoint();
    r = curve->getRandomPoint();
    for (size_t j = 0; j < MSG_BITS; j++)
    {
        k_lt.push_back(utils::getRandom(128));
        k_eq.push_back(utils::getRandom(128));
        k_gt.push_back(utils::getRandom(128));
        ok.push_back(curve->getRandomScalar());
    }

    bool bit = theta & (1 << (MSG_BITS-1));


    if (bit == 0)
    {
        Sl0.k = k_eq[MSG_BITS-1];
        Sl0.prf = r * ok[MSG_BITS-1];
        Sl1.k = k_gt[MSG_BITS-1];
        Sl1.prf = ga * (1 << (MSG_BITS-1)) + r * ok[MSG_BITS-1];
    }
    else
    {
        Sl0.k = k_lt[MSG_BITS-1];
        Sl0.prf = r * ok[MSG_BITS-1];
        Sl1.k = k_eq[MSG_BITS-1];
        Sl1.prf = ga * (1 << (MSG_BITS-1)) + r * ok[MSG_BITS-1];
    }

    for (int i = MSG_BITS-1; i > 0; i--)
    {
        bit = theta & (1 << (i-1));
        if (bit == 0)
        {
            Si0[i].k_lt = aes.encryptCRC(k_lt[i], k_lt[i - 1]);
            Si0[i].k_eq = aes.encryptCRC(k_eq[i], k_eq[i - 1]);
            Si0[i].k_gt = aes.encryptCRC(k_gt[i], k_gt[i - 1]);
            Si0[i].prf = r * ok[i-1];

            Si1[i].k_lt = aes.encryptCRC(k_lt[i], k_lt[i - 1]);
            Si1[i].k_eq = aes.encryptCRC(k_eq[i], k_gt[i - 1]);
            Si1[i].k_gt = aes.encryptCRC(k_gt[i], k_gt[i - 1]);
            Si1[i].prf = ga * (1 << (i-1)) + r * ok[i-1];
        }
        else
        {
            Si0[i].k_lt = aes.encryptCRC(k_lt[i], k_lt[i - 1]);
            Si0[i].k_eq = aes.encryptCRC(k_eq[i], k_lt[i - 1]);
            Si0[i].k_gt = aes.encryptCRC(k_gt[i], k_gt[i - 1]);
            Si0[i].prf = r * ok[i-1];


            Si1[i].k_lt = aes.encryptCRC(k_lt[i], k_lt[i - 1]);
            Si1[i].k_eq = aes.encryptCRC(k_eq[i], k_eq[i - 1]);
            Si1[i].k_gt = aes.encryptCRC(k_gt[i], k_gt[i - 1]);
            Si1[i].prf = ga * (1 << (i-1)) + r * ok[i-1];
        }

    }
}


ot_ctxts_t OPPRFserver::runOTRound(short round, dme::pkey_t pk)
{
    ot_ctxts_t c;
    if (round == MSG_BITS)
    {
        c.ctxt[0] = ots.encMsgs(pk, Sl0.k, Sl1.k);
        c.cprf = ots.encMsgs(pk, Sl0.prf, Sl1.prf);
    }
    else
    {
        c.ctxt[0] = ots.encMsgs(pk, Si0[round].k_lt, Si1[round].k_lt);
        c.ctxt[1] = ots.encMsgs(pk, Si0[round].k_eq, Si1[round].k_eq);
        c.ctxt[2] = ots.encMsgs(pk, Si0[round].k_gt, Si1[round].k_gt);
        std::random_shuffle(c.ctxt.begin(), c.ctxt.end());

        c.cprf = ots.encMsgs(pk, Si0[round].prf, Si1[round].prf);
    }
    return c;
}

symctxt_t OPPRFserver::sendEncryptedMasks()
{
    ok_t ok_sum = ok[0];

    for (int i=1; i < MSG_BITS; i++)
    {
        ok_sum += ok[i];
    }
    G_t mask = kopprf + r * (-ok_sum);
    symctxt_t c;
    // c[0] = gk * k_lt[0] + mask;
    // c[1] = gk * k_eq[0] + mask;
    // c[2] = gk * k_gt[0] + curve->getRandomPoint();
    c[0] = aes.encryptCRC(k_lt[0], mask.getEncodedX());
    c[1] = aes.encryptCRC(k_eq[0], mask.getEncodedX());
    c[2] = aes.encryptCRC(k_gt[0], curve->getRandomPoint().getEncodedX());
    std::random_shuffle(c.begin(), c.end());
 
    return c;
}

void OPPRFserver::clean()
{
    kopprf = G_t();
    r = G_t();

    gk = this->curve->getRandomPoint();
    Si0.clear();
    Si0.resize(MSG_BITS);
    Si1.clear();
    Si1.resize(MSG_BITS);

    k_lt.clear(); 
    k_eq.clear(); 
    k_gt.clear(); 
    ok.clear(); 
}

bool OPPRFclient::correctDecryption(Gk_t)
{
    static int even = 0;
    return !((even++)%4);
}


OPPRFclient::OPPRFclient(dme::crs_ddh_t crs) : otr(crs)
{
    this->curve = otr.getCurve();
}

dme::pkey_t OPPRFclient::runOTRound_start(short round)
{
    bool bit = x & (1 << (round-1));
    return otr.selectMsg((dme::branch_t)bit);
}

void OPPRFclient::runOTRound_end(short round, ot_ctxts_t c)
{
    if (round == MSG_BITS)
    {
        key = otr.decryptMsgDecode(c.ctxt[0]);
    }
    else
    {
        bool decrypted = false;
        for (size_t i = 0; i < 3; i++)
        {
            mpz_class tmp = otr.decryptMsgDecode(c.ctxt[i]);
        
            tmp = aes.decryptCRC(key, tmp);
            if (tmp != mpz_class(0))
            {
                key = tmp;
                decrypted = true;
                break;
            }
        }
        

        assert(decrypted);
        if(!decrypted)
            throw std::invalid_argument("no decryption was possible<");

    }
    result += otr.decryptMsg(c.cprf);

}

void OPPRFclient::unmaskResult(symctxt_t masks)
{
    bool decrypted = false;
    mpz_class x;

    for (size_t i = 0; i < 3; i++)
    {
        mpz_class tmp = aes.decryptCRC(key, masks[i]);
        if (tmp != mpz_class(0))
        {
            x = tmp;
            decrypted = true;
            break;
        }
    }
    assert(decrypted);
    if(!decrypted)
        throw std::invalid_argument("no decryption was possible<");

    G_t mask = curve->getRandomPoint();
    mask.setEncodedX(x);
    
    result += mask;
}


void OPPRFclient::clean()
{
    result = G_t();
    key = mpz_class(0);

}
    
} // namespace opprf

