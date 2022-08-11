#include <iomanip>
#include <iostream>
#include <gmpxx.h>

#include "opprf.hpp"

#define NB_TESTS 3

using namespace std;


int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;
    uint16_t theta = 1000;
    uint16_t x[NB_TESTS];
    opprf::G_t ga = dme::CURVE().getRandomPoint();
    dme::crs_ddh_t crs = dme::DME_DDH().crs;


    cout << "Testing OPPRF protocol" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    

    for(size_t j=0; j<NB_TESTS; j++)
    {
        x[j] = (uint16_t) (rand() % theta);
    }

    opprf::OPPRFserver opprfs = opprf::OPPRFserver(theta, crs);
    opprf::OPPRFclient opprfc = opprf::OPPRFclient(crs);

    for(size_t j=0; j<NB_TESTS; j++)
    {
        cout << left << setw(6) << "Test " << ++i << ":" << setw(0);
        cout <<"  Evaluating OPPRF for x =" << x[j] << " and theta = " << theta << "\t";

        // set secret for the server
        opprfs.setSecret(ga);

        // set input for the client
        opprfc.setMessage(x[j]);

        // prepare server inputs
        opprfs.prepareKeysAndInputs();

        //run l OTs
        for(int round=MSG_BITS; round >0; round--)
        {
            // client send pk for its selection b 
            dme::pkey_t pk = opprfc.runOTRound_start(round);
            // server encrypt both OT inputs
            opprf::ot_ctxts_t c = opprfs.runOTRound(round, pk);
            // client decrypts the ciphertext of its selection b
            opprfc.runOTRound_end(round, c);
        }

        // server encrypts its masks
        opprf::symctxt_t c = opprfs.sendEncryptedMasks();

        // client decrypts mask and unmask the result
        opprfc.unmaskResult(c);

        opprf::G_t res =  opprfc.getResult();
        opprf::G_t treures =  opprfs.getKOPPRF()+ ga*x[j]; 

        if(opprfc.getResult() == opprfs.getKOPPRF() + ga*x[j]) 
            cout << "OK" << endl;
        else 
        {
            cout  << "FAIL" << endl;
            success = -1;
        }
        opprfs.clean();
        opprfc.clean();
    }

 

    cout << "--------------END OF TEST-------------------" << endl;

    return success;
}
