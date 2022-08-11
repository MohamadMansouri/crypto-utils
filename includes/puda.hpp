#ifndef __PUDA__
#define __PUDA__

#include <tuple>
#include <vector>

#include "field_secp256r1.hpp"
#include "ecc_secp256r1.hpp"

namespace puda
{

typedef field::Field_secp256r1_n FIELD1_n;
typedef field::Field_secp256r1_n FIELD1_n;
typedef field::Field_secp256r1_p FIELD1_p;
typedef field::Field_secp256r1_p FIELD2_p;
typedef ecc::Point_secp256r1 POINT1;
typedef ecc::Point_secp256r1 POINT2;
typedef ecc::Curve_secp256r1 CURVE1;
typedef ecc::Curve_secp256r1 CURVE2;

typedef struct PudaPublicParam
{
    CURVE1* curve1;
    CURVE2* curve2;
    POINT1 g1;
    POINT2 g2;
    POINT1 hash;  


} pp_t;

typedef FIELD1_n ek_t;
typedef std::vector<ek_t> ek_v_t;

typedef FIELD1_n tk_t;

typedef FIELD1_n ak_t;
typedef POINT1 ctxt_t;
typedef std::vector<ctxt_t> ctxt_v_t;
typedef POINT1 tag_t;
typedef std::vector<tag_t> tag_v_t;
typedef uint16_t msg_t;

typedef struct PudaSigningKey
{
  mpz_class a;
  tk_t tk;
  PudaSigningKey(mpz_class a, tk_t tk)
  {
    this->a = a;
    this->tk = tk;
  }
}sk_t;

typedef std::vector<sk_t> sk_v_t;

typedef struct PudaVerifKey
{
  POINT2  vk_1;
  POINT2  vk_2;
} vk_t;


class Puda
{
private:
  pp_t pp;
  const size_t msg_length = 16;

  msg_t compute_dlog(POINT1 c);

public:
  Puda();
  ~Puda();

  std::tuple<ek_v_t, sk_v_t, ak_t, vk_t> Setup(size_t n);
  ctxt_t Enc(ek_t ek, msg_t m, int t); 
  tag_t Tag(sk_t sk, msg_t m, int t); 
  std::pair<msg_t,tag_t> Agg(ak_t ak, ctxt_v_t ctxts, tag_v_t tags, int t); 
  bool Verify(vk_t vk, msg_t sum, tag_t tag, int t);
};

}

#endif