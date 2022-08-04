#ifndef __DMHE__
#define __DMHE__


#include "dme.hpp"


class dmheDDH_EC : public dmeDDH_EC
{
public:
    dmheDDH_EC(dme_mode_t mu) : dmeDDH_EC(mu) {};
    dmheDDH_EC(crs_ddh_ec_t crs) : dmeDDH_EC(crs) {};

    ctxt_t Eval(const ctxt_t& ca, const ctxt_t& cb) const;

};



#endif