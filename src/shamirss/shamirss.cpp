#include "shamirss.hpp"


namespace sss
{
ShamirSS::ShamirSS()
{

}

ShamirSS::~ShamirSS()
{

}
FIELD ShamirSS::evalPoly(FIELD x, field_v_t& poly)
{
    FIELD y;
    FIELD temp = FIELD(1);
 
    for (auto coeff : poly) {
        y = (y + (coeff * temp));
        temp = (temp * x);
    }
    return y;
}
share_v_t ShamirSS::getShares(size_t t, size_t n, FIELD secret)
{
    field_v_t coefs = {secret};
    share_v_t shares;
    for (size_t i = 0; i < t-1; i++)
    {
        coefs.push_back(FIELD((rand()+1) %100));
    }

    for (size_t i = 1; i <= n; i++)
    {
        share_t share;
        share.idx = FIELD(i);
        share.val = evalPoly(share.idx, coefs);
        shares.push_back(share);
    }       
    return shares;
    
}

FIELD ShamirSS::reconSecret(share_v_t shares)
{
    FIELD res;

    for (size_t i = 0; i < shares.size(); i++)
    {
        FIELD numerator = FIELD(1);
        FIELD denominator = FIELD(1);

        for (size_t j = 0; j < shares.size(); j++)
        {
            if(i!=j)
            {
                numerator *= shares[j].idx;
                denominator *= shares[j].idx - shares[i].idx;
            }
        }
        res += shares[i].val * numerator / denominator;
    }
    
    return res;
    
    
}
}
