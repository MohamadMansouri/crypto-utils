#include <iomanip>
#include <iostream>

#include "ot.hpp"
#include "dot.hpp"
#include "dmhe.hpp"


using namespace std;

int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;
    

    cout << "Testing OT protocol" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    


    dme::DME_DDH dme(dme::mode_t::messy);
    
    ot::OTrecv otr(dme.crs);
    ot::OTsndr ots(dme.crs);

    
    // sender selects the branch and generates a public key
    dme::branch_t selection = dme::branch_t::b0;
    dme::pkey_t pk = otr.selectMsg(selection);


    // receiver encrypts the two messages on each branch 
    dme::msg_t m0 = ots.getRandomMsg();
    dme::msg_t m1 = ots.getRandomMsg();
    ot::ctxt_v_t ctxts = ots.encMsgs(pk, m0, m1);

    //sender decrypts the selected branch message
    dme::msg_t m = otr.decryptMsg(ctxts);
    ctxts.clear();


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(m == m0) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    selection = dme::branch_t::b1;
    pk = otr.selectMsg(selection);

    m0 = ots.getRandomMsg();
    m1 = ots.getRandomMsg();
    ctxts = ots.encMsgs(pk, m0, m1);

    m = otr.decryptMsg(ctxts);
    ctxts.clear();


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(m == m1) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    selection = dme::branch_t::b0;
    pk = otr.selectMsg(selection);

    mpz_class mpz0 = mpz_class(19123);
    mpz_class mpz1 = mpz_class(73812);
    ctxts = ots.encMsgs(pk, mpz0, mpz1);

    mpz_class mpz = otr.decryptMsgDecode(ctxts);
    ctxts.clear();


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(mpz0 == mpz) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }



    ot::DOTrecv dotr(dme.crs);
    ot::DOTsndr dotsa(dme.crs);
    ot::DOTsndr dotsb(dme.crs);
    ot::DOTsndr dotsc(dme.crs);
    ot::DOTprxy dotp(dme.crs);

    selection = dme::branch_t::b0;
    pk = dotr.selectMsg(selection);

    vector<ot::ctxt_v_t> c_v;
    dme::msg_t m0a = dotsa.getRandomMsg();
    dme::msg_t m1a = dotsa.getRandomMsg();
    ctxts = dotsa.encMsgs(pk, m0a, m1a);
    c_v.push_back(ctxts);
    ctxts.clear();

    dme::msg_t m0b = dotsb.getRandomMsg();
    dme::msg_t m1b = dotsb.getRandomMsg();
    ctxts = dotsb.encMsgs(pk, m0b, m1b);
    c_v.push_back(ctxts);
    ctxts.clear();

    dme::msg_t m0c = dotsc.getRandomMsg();
    dme::msg_t m1c = dotsc.getRandomMsg();
    ctxts = dotsc.encMsgs(pk, m0c, m1c);
    c_v.push_back(ctxts);
    ctxts.clear();

    ctxts = dotp.aggregate(c_v);

    m = dotr.decryptMsg(ctxts);


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(m == m0a+m0b+m0c) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    return success;
}
