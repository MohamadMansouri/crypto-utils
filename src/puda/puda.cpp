#include <limits.h>

#include "puda.hpp"

namespace puda
{

Puda::Puda()
{
    pp.curve1 = new CURVE1;
    pp.curve2 = new CURVE2;
}

Puda::~Puda()
{
    delete pp.curve1;
    delete pp.curve2;
}

msg_t Puda::compute_dlog(POINT1 c)
{
    for(uint16_t i=0; i!=USHRT_MAX; i++)
    {
        if (pp.g1 * mpz_class(i) == c)
            return i;
    }
    return 0;
}

std::tuple<ek_v_t, sk_v_t, ak_t, vk_t>
Puda::Setup(size_t n)
{
    pp.g1 = pp.curve1->getDefaultGen();
    pp.g2 = pp.curve2->getDefaultGen();
    pp.hash = pp.curve1->getRandomPoint();

    ek_v_t ekv;
    sk_v_t skv;
    ak_t ak(0);
    tk_t tks;

    mpz_class a =  pp.curve1->getRandomScalar().getRawValue();


    for(size_t i=0; i < n; i++)
    {
        ek_t ek = pp.curve1->getRandomScalar();
        ekv.push_back(ek);

        ek_t tk = pp.curve1->getRandomScalar();
        skv.push_back(sk_t(a, tk));

        ak -= ek;
        tks += tk;
    }

    vk_t vk;
    vk.vk_1 = pp.g2 * tks;
    vk.vk_2 = pp.g2 * a;

    return std::make_tuple(ekv, skv, ak, vk);
}


ctxt_t Puda::Enc(ek_t ek, msg_t m, int t) 
{
    return (pp.hash*t)*ek + pp.g1 * m;
}


tag_t Puda::Tag(sk_t sk, msg_t m, int t)
{
    return (pp.hash*t)*sk.tk + (pp.g1*sk.a) * m;
}

std::pair<msg_t,tag_t> Puda::Agg(ak_t ak, ctxt_v_t ctxts, tag_v_t tags, int t)
{
    ctxt_t c;
    tag_t tag;
    for(auto it = ctxts.begin(); it != ctxts.end(); ++it)
    {
        c += *it;
    }
    for(auto it = tags.begin(); it != tags.end(); ++it)
    {
        tag += *it;
    }
    c += (pp.hash*t)*ak;
    msg_t m = compute_dlog(c);
    return std::make_pair(m,tag);
}


bool Puda::Verify(vk_t vk, msg_t sum, tag_t tag, int t)
{
    //return e(tag, g2) == e(pp.hash*t, vk.vk_1) + e(pp.g1.sum, vk.vk_2)
    return true;
}

}

