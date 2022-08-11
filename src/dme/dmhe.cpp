#include "dmhe.hpp"


namespace dme
{
ctxt_t DMHE_DDH::Eval(const ctxt_t& ca, const ctxt_t& cb) const
{
    return ctxt_t(ca.u + cb.u, ca.mv + cb.mv);
}

}
