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
    
    dmeDDH_EC dme(dme_mode_t::messy);
    
    OTrecv otr(dme.crs);
    OTsndr ots(dme.crs);

    
    // sender selects the branch and generates a public key
    dme_branch_t selection = dme_branch_t::b0;
    pkey_t pk = otr.selectMsg(selection);


    // receiver encrypts the two messages on each branch 
    Point m0 = ots.getRandomMsg();
    Point m1 = ots.getRandomMsg();
    ctxt_p_t ctxts = ots.encMsgs(pk, m0, m1);

    //sender decrypts the selected branch message
    msg_t m = otr.decryptMsg(ctxts[selection]);
    ctxts.clear();


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(m == m0) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    selection = dme_branch_t::b1;
    pk = otr.selectMsg(selection);

    m0 = ots.getRandomMsg();
    m1 = ots.getRandomMsg();
    ctxts = ots.encMsgs(pk, m0, m1);

    m = otr.decryptMsg(ctxts[selection]);
    ctxts.clear();


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(m == m1) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    DOTrecv dotr(dme.crs);
    DOTsndr dotsa(dme.crs);
    DOTsndr dotsb(dme.crs);
    DOTsndr dotsc(dme.crs);
    DOTprxy dotp(dme.crs);

    selection = dme_branch_t::b0;
    pk = dotr.selectMsg(selection);

    vector<ctxt_p_t> c_v;
    msg_t m0a = dotsa.getRandomMsg();
    msg_t m1a = dotsa.getRandomMsg();
    ctxts = dotsa.encMsgs(pk, m0a, m1a);
    c_v.push_back(ctxts);
    ctxts.clear();

    msg_t m0b = dotsb.getRandomMsg();
    msg_t m1b = dotsb.getRandomMsg();
    ctxts = dotsb.encMsgs(pk, m0b, m1b);
    c_v.push_back(ctxts);
    ctxts.clear();

    msg_t m0c = dotsc.getRandomMsg();
    msg_t m1c = dotsc.getRandomMsg();
    ctxts = dotsc.encMsgs(pk, m0c, m1c);
    c_v.push_back(ctxts);
    ctxts.clear();

    ctxts = dotp.aggregate(c_v);

    m = dotr.decryptMsg(ctxts[selection]);


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
