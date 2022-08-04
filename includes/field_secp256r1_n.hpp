#ifndef __FIELD_SECP256R1_N__
#define __FIELD_SECP256R1_N__

#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

#include "field_template.hpp"

class Field_secp256r1_n : public PrimeField<Field_secp256r1_n>
{
    public: 

        Field_secp256r1_n(mpz_class v);
        Field_secp256r1_n();

};

#endif