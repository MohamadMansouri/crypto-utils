
#include <assert.h>
#include <gmp.h>
#include <gmpxx.h>

#include "field_secp256r1_n.hpp"




Field_secp256r1_n::Field_secp256r1_n(mpz_class v) : PrimeField<Field_secp256r1_n>(v, mpz_class("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16))
{
}

Field_secp256r1_n::Field_secp256r1_n()
{
    p = mpz_class("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16);
}