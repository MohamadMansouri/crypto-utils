#ifndef __FIELD_BN254__
#define __FIELD_BN254__

#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

#include "field_template.hpp"

namespace field
{
class Field_bn254_n : public PrimeField<Field_bn254_n>
{
    public: 

        Field_bn254_n(mpz_class v);
        Field_bn254_n();

};

class Field_bn254_p : public PrimeField<Field_bn254_p>
{
    public: 

        Field_bn254_p(mpz_class v);
        Field_bn254_p();

};

}

#endif