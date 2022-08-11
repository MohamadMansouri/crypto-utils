#ifndef __FIELD_SECP256R1__
#define __FIELD_SECP256R1__

#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

#include "field_template.hpp"

namespace field
{

class Field_secp256r1_n : public PrimeField<Field_secp256r1_n>
{
    public: 

        Field_secp256r1_n(mpz_class v);
        Field_secp256r1_n();

};

class Field_secp256r1_p : public PrimeField<Field_secp256r1_p>
{
    public: 

        Field_secp256r1_p(mpz_class v);
        Field_secp256r1_p();

};
    
} // namespace field


#endif