#ifndef __FIELD_SECP256R1_P__
#define __FIELD_SECP256R1_P__

#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

#include "field_template.hpp"

class Field_secp256r1_p : public PrimeField<Field_secp256r1_p>
{
    public: 

        Field_secp256r1_p(mpz_class v);
        Field_secp256r1_p();

};

#endif