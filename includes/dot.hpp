#ifndef __DOT__
#define __DOT__

#include <vector>

#include "dmhe.hpp"
#include "ot.hpp"

namespace ot
{
typedef std::vector<ctxt_v_t>::iterator ctxt_it;

class DOTrecv : public OTrecv
{
public:
    DOTrecv(dme::crs_ddh_t crs) : OTrecv(crs) {};
};


class DOTsndr : public OTsndr
{
public:
    DOTsndr(dme::crs_ddh_t crs) : OTsndr(crs) {};
};


class DOTprxy
{
private:
    ctxt_v_t c;
    dme::DMHE_DDH dmhe;

public:
    DOTprxy(dme::crs_ddh_t crs) : dmhe(crs) {};

    ctxt_v_t aggregate(std::vector<ctxt_v_t> c);
};

}


#endif