#ifndef __DOT__
#define __DOT__

#include <vector>

#include "dmhe.hpp"
#include "ot.hpp"
#include "constants.hpp"

typedef std::vector<ctxt_p_t>::iterator ctxt_it;

class DOTrecv : public OTrecv
{
public:
    DOTrecv(crs_ddh_ec_t crs) : OTrecv(crs) {};
};


class DOTsndr : public OTsndr
{
public:
    DOTsndr(crs_ddh_ec_t crs) : OTsndr(crs) {};
};


class DOTprxy
{
private:
    ctxt_p_t c;
    dmheDDH_EC dmhe;

public:
    DOTprxy(crs_ddh_ec_t crs) : dmhe(crs) {};

    ctxt_p_t aggregate(std::vector<ctxt_p_t> c);
};


#endif