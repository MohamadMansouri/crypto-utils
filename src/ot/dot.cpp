#include "dot.hpp"


ctxt_p_t DOTprxy::aggregate(std::vector<ctxt_p_t> c_v)
{
    c.clear();
    c.push_back(c_v[0][0]);
    c.push_back(c_v[0][1]);

    for(ctxt_it it = c_v.begin()+1; it != c_v.end(); ++it)
    {
        c[0] = dmhe.Eval(c[0],(*it)[0]);
        c[1] = dmhe.Eval(c[1],(*it)[1]);
    }
    return c;
}
