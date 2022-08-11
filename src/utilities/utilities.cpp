#include <gmpxx.h>
#include "utilities.hpp"



namespace utils
{
static gmp_randclass rand = gmp_randclass(gmp_randinit_default);

mpz_class getRandom(size_t bits)
{
    return rand.get_z_bits(bits);
}

size_t getRawMpz(uint8_t** arr, mpz_class n)
{
    size_t len;
    *arr = (uint8_t*) mpz_export(NULL,&len,1, 1,1,0,n.get_mpz_t());
    return len;
}
mpz_class setRawMpz(uint8_t* arr, size_t len)
{
    mpz_class r;
    mpz_import(r.get_mpz_t(), len, 1, 1, 1, 0, arr);
    return r;
}


}
