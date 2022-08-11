#include "field_secp256r1.hpp"



namespace field
{
Field_secp256r1_n::Field_secp256r1_n(mpz_class v) : PrimeField<Field_secp256r1_n>(v, mpz_class("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16))
{
}

Field_secp256r1_n::Field_secp256r1_n()
{
    p = mpz_class("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16);
}



Field_secp256r1_p::Field_secp256r1_p(mpz_class v) : PrimeField<Field_secp256r1_p>(v, mpz_class("ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16))
{
}

Field_secp256r1_p::Field_secp256r1_p()
{
    p = mpz_class("ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16);
}
}
