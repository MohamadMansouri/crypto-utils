#ifndef __UTILS__
#define __UTILS__

#include <gmpxx.h>

namespace utils
{
mpz_class getRandom(size_t bits);

mpz_class setRawMpz(uint8_t* arr, size_t len);
size_t getRawMpz(uint8_t** arr, mpz_class n);

}








#endif