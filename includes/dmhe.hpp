#ifndef __DMHE__
#define __DMHE__


#include "dme.hpp"
namespace dme
{

class DMHE_DDH : public DME_DDH
{
public:
    DMHE_DDH(mode_t mu) : DME_DDH(mu) {};
    DMHE_DDH(crs_ddh_t crs) : DME_DDH(crs) {};

    ctxt_t Eval(const ctxt_t& ca, const ctxt_t& cb) const;

};

}



#endif