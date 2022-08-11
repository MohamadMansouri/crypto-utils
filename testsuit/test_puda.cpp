#include <iomanip>
#include <iostream>
#include <gmpxx.h>

#include "puda.hpp"


using namespace std;


int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;
    puda::msg_t m = 2;
    int timestamp = 99;
    int nusers = 10;

    cout << "Testing PUDA protocol" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    


    puda::Puda PUDA;

    auto setup = PUDA.Setup(nusers);

    puda::ek_v_t ekv = get<0>(setup);
    puda::sk_v_t skv = get<1>(setup);
    puda::ak_t ak = get<2>(setup);
    puda::vk_t vk = get<3>(setup);
    puda::ctxt_t c;
    puda::tag_t tag;
    puda::ctxt_v_t ctxts;
    puda::tag_v_t tags;
    for(int k =0; k < nusers; k++)
    {

        c = PUDA.Enc(ekv[k], m, timestamp);
        tag = PUDA.Tag(skv[k], m, timestamp);
        ctxts.push_back(c);
        tags.push_back(tag);
    }

    auto result = PUDA.Agg(ak, ctxts,tags,timestamp);
    PUDA.Verify(vk, result.first, result.second, timestamp);

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(result.first == m*nusers) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }
    
    cout << "--------------END OF TEST-------------------" << endl;
    return success;
}
