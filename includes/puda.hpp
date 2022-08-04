#include <tuple>
#include <vector>
#include "constants.hpp"


typedef struct PudaPublicParam
{
     Point g1, g2;

} puda_pp_t;

typedef FIELD_n puda_ek_t;
typedef std::vector<puda_ek_t> puda_ek_v_t;

typedef FIELD_n puda_tk_t;
typedef std::vector<puda_tk_t> puda_tk_v_t;

typedef FIELD_n puda_ak_t;
typedef Point puda_ctxt_t;
typedef  std::vector<puda_ctxt_t> puda_ctxt_v_t;
typedef Point puda_tag_t;
typedef  std::vector<puda_tag_t> puda_tag_v_t;

typedef struct PudaVerifKey
{
  Point  vk_1;
  Point  vk_2;
} puda_vk_t;


class Puda
{
private:

public:
    Puda(/* args */);
    ~Puda();

    std::tuple<puda_pp_t, puda_ek_v_t, puda_tk_v_t, puda_ak_t, puda_vk_t> Setup();
    Point Enc(puda_ek_t ek, Point m, int t); 
    Point Tag(puda_tk_t tk, Point m, int t); 
    std::pair<Point,puda_tag_t> Agg(puda_ak_t tk, puda_ctxt_v_t ctxts, puda_tag_v_t tags); 
    bool Verify(puda_vk_t vk, Point sum, puda_tag_t tag);
};

