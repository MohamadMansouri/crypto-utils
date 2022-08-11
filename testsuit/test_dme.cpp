#include <iomanip>
#include <iostream>
#include <gmpxx.h>


#include "dmhe.hpp"
#include "utilities.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;


    cout << "Testing Dual-Mode Encryption (DME) scheme" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    

    dme::DMHE_DDH DMHE_messy(dme::mode_t::messy);
    dme::msg_t msg, decrypted;
    dme::ctxt_t c0, c1;
    dme::keypair_t keyp;

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_messy.KeyGen(dme::branch_t::b0);
    msg = DMHE_messy.getCurve()->getRandomPoint();
    c0 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_messy.Dec(keyp.sk, c0);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_messy.KeyGen(dme::branch_t::b0);
    msg = DMHE_messy.getCurve()->getRandomPoint();
    c0 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_messy.Dec(keyp.sk, c1);
    if(!(msg == decrypted))
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_messy.KeyGen(dme::branch_t::b1);
    msg = DMHE_messy.getCurve()->getRandomPoint();
    c0 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_messy.Dec(keyp.sk, c0);
    if(!(msg == decrypted))
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_messy.KeyGen(dme::branch_t::b1);
    msg = DMHE_messy.getCurve()->getRandomPoint();
    c0 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_messy.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_messy.Dec(keyp.sk, c1);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_messy.KeyGen(dme::branch_t::b0);
    if(DMHE_messy.FindMessy(keyp.pk) == dme::branch_t::b1)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_messy.KeyGen(dme::branch_t::b1);
    if(DMHE_messy.FindMessy(keyp.pk) == dme::branch_t::b0)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    dme::DMHE_DDH DMHE_dec(dme::mode_t::dec);


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_dec.KeyGen(dme::branch_t::b0);
    msg = DMHE_dec.getCurve()->getRandomPoint();
    c0 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_dec.Dec(keyp.sk, c0);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_dec.KeyGen(dme::branch_t::b0);
    msg = DMHE_dec.getCurve()->getRandomPoint();
    c0 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_dec.Dec(keyp.sk, c1);
    if(!(msg == decrypted))
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_dec.KeyGen(dme::branch_t::b1);
    msg = DMHE_dec.getCurve()->getRandomPoint();
    c0 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_dec.Dec(keyp.sk, c0);
    if(!(msg == decrypted))
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE_dec.KeyGen(dme::branch_t::b1);
    msg = DMHE_dec.getCurve()->getRandomPoint();
    c0 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE_dec.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE_dec.Dec(keyp.sk, c1);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    tuple<dme::pkey_t, dme::skey_t, dme::skey_t> keys = DMHE_dec.TrapKeyGen();
    dme::pkey_t pk = get<0>(keys);
    dme::skey_t sk0 = get<1>(keys);
    dme::skey_t sk1 = get<2>(keys);

    msg = DMHE_dec.getCurve()->getRandomPoint();
    c0 = DMHE_dec.Enc(pk, dme::branch_t::b0, msg);
    c1 = DMHE_dec.Enc(pk, dme::branch_t::b1, msg);
    decrypted = DMHE_dec.Dec(sk0, c0);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    decrypted = DMHE_dec.Dec(sk1, c1);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    dme::DMHE_DDH DMHE(DMHE_messy.crs);

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE.KeyGen(dme::branch_t::b0);
    msg = DMHE.getCurve()->getRandomPoint();
    c0 = DMHE.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE.Dec(keyp.sk, c0);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE.KeyGen(dme::branch_t::b0);
    msg = DMHE.getCurve()->getRandomPoint();
    c0 = DMHE.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE.Dec(keyp.sk, c1);
    if(!(msg == decrypted))
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE.KeyGen(dme::branch_t::b1);
    msg = DMHE.getCurve()->getRandomPoint();
    c0 = DMHE.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE.Dec(keyp.sk, c0);
    if(!(msg == decrypted))
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE.KeyGen(dme::branch_t::b1);
    msg = DMHE.getCurve()->getRandomPoint();
    c0 = DMHE.Enc(keyp.pk, dme::branch_t::b0, msg);
    c1 = DMHE.Enc(keyp.pk, dme::branch_t::b1, msg);
    decrypted = DMHE.Dec(keyp.sk, c1);
    if(msg == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }
    

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE.KeyGen(dme::branch_t::b0);
    dme::msg_t msga = DMHE.getCurve()->getRandomPoint();
    dme::msg_t msgb = DMHE.getCurve()->getRandomPoint();
    dme::ctxt_t ca = DMHE.Enc(keyp.pk, dme::branch_t::b0, msga);
    dme::ctxt_t cb = DMHE.Enc(keyp.pk, dme::branch_t::b0, msgb);
    dme::ctxt_t cab = DMHE.Eval(ca, cb);
    decrypted = DMHE.Dec(keyp.sk, cab);

    if(msga+msgb == decrypted)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }



    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    keyp = DMHE.KeyGen(dme::branch_t::b1);
    mpz_class number = utils::getRandom(128);
    c0 = DMHE.Enc(keyp.pk, dme::branch_t::b0, number);
    c1 = DMHE.Enc(keyp.pk, dme::branch_t::b1, number);
    mpz_class decr = DMHE.DecDecode(keyp.sk, c1);
    if(number == decr)
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << "--------------END OF TEST-------------------" << endl;


    return success;
}
