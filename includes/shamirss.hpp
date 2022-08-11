#ifndef __SHAMIRSS__
#define __SHAMIRSS__

#include <vector>

#include "field_secp256r1.hpp"



namespace sss
{
typedef field::Field_secp256r1_n FIELD;

typedef struct Share
{
    FIELD idx;
    FIELD val;
    Share() {}
    Share(FIELD idx, FIELD val)
    {
        this->idx = idx;
        this->val = val;
    }
} share_t;

typedef std::vector<share_t> share_v_t;
typedef std::vector<FIELD> field_v_t;

class ShamirSS
{
private:
    int i;
    FIELD evalPoly(FIELD x, field_v_t& poly);
public:
    ShamirSS();
    ~ShamirSS();

    share_v_t getShares(size_t t, size_t n, FIELD secret);
    FIELD reconSecret(share_v_t shares);
};
    
} // namespace field

#endif