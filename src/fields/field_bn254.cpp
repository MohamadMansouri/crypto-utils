#include "field_bn254.hpp"



namespace field
{
Field_bn254_n::Field_bn254_n(mpz_class v) : PrimeField<Field_bn254_n>(v, mpz_class("2523648240000001BA344D8000000007FF9F800000000010A10000000000000D", 16))
{
}

Field_bn254_n::Field_bn254_n()
{
    p = mpz_class("2523648240000001BA344D8000000007FF9F800000000010A10000000000000D", 16);
}


Field_bn254_p::Field_bn254_p(mpz_class v) : PrimeField<Field_bn254_p>(v, mpz_class("2523648240000001BA344D80000000086121000000000013A700000000000013", 16))
{
}

Field_bn254_p::Field_bn254_p()
{
    p = mpz_class("2523648240000001BA344D80000000086121000000000013A700000000000013", 16);
}


}
