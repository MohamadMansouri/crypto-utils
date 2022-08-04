#include "dmhe.hpp"


ctxt_t dmheDDH_EC::Eval(const ctxt_t& ca, const ctxt_t& cb) const
{
    return ctxt_t(ca.u + cb.u, ca.mv + cb.mv);
}
