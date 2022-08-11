#ifndef __ECC_SECP256R1__
#define __ECC_SECP256R1__

#include <gmpxx.h>
#include "ecc_template.hpp"
#include "field_secp256r1.hpp"


namespace ecc
{
class KeyPair_secp256r1;
class Point_secp256r1;
class Curve_secp256r1;

class KeyPair_secp256r1 : public KeyPair<Curve_secp256r1, Point_secp256r1, field::Field_secp256r1_p, field::Field_secp256r1_n>
{
    using KeyPair::KeyPair;
};

class Point_secp256r1 : public Point<Curve_secp256r1, Point_secp256r1, field::Field_secp256r1_p, field::Field_secp256r1_n>
{
    using Point::Point;
};

class Curve_secp256r1 : public Curve<Curve_secp256r1, Point_secp256r1, field::Field_secp256r1_p, field::Field_secp256r1_n>
{
public:
    Curve_secp256r1();
    ~Curve_secp256r1();
};

}



#endif