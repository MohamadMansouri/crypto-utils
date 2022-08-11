#ifndef __ECC_bn254__
#define __ECC_bn254__

#include <gmpxx.h>
#include "ecc_template.hpp"
#include "field_bn254.hpp"


namespace ecc
{
    
class KeyPair_bn254;
class Point_bn254;
class Curve_bn254;

class KeyPair_bn254 : public KeyPair<Curve_bn254, Point_bn254, field::Field_bn254_p, field::Field_bn254_n>
{
    using KeyPair::KeyPair;
};

class Point_bn254 : public Point<Curve_bn254, Point_bn254, field::Field_bn254_p, field::Field_bn254_n>
{
    using Point::Point;
};

class Curve_bn254 : public Curve<Curve_bn254, Point_bn254, field::Field_bn254_p, field::Field_bn254_n>
{
public:
    Curve_bn254();
    ~Curve_bn254();
};

}



#endif