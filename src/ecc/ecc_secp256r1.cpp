#include <assert.h>
#include <string.h>
#include <gmp.h>
#include <gmpxx.h>

#include "ecc_secp256r1.hpp"

gmp_randclass Curve_secp256r1::rand(gmp_randinit_default);


KeyPair::KeyPair(mpz_class s, Point P)
{
    sk = s;
    pk = P;
}

Point::Point(const Point& P)
{
    x = P.x;
    y = P.y;
    curve = P.curve;
    is_inf = P.is_inf;
}

Point::Point()
{
    curve = 0;
    is_inf = true;
}

Point::Point(const mpz_class& Px, const mpz_class& Py, Curve* c)
{
    x = Field_secp256r1_p(Px);
    y = Field_secp256r1_p(Py);
    curve = c;
    is_inf = false;
}

Point::Point(const Field_secp256r1_p& Px, const Field_secp256r1_p& Py, Curve* c)
{
    x = Px;
    y = Py;
    curve = c;
    is_inf = false;
}


Point::~Point()
{

}

bool Point::isValid() const 
{
    if (is_inf)
        return true;
    bool r = false;
    if(curve) 
    {
        r = !cmp(x.getField(),y.getField());
        r &= !cmp(x.getField(),curve->getPrime());
        r &= ((x*x*x + x*curve->getA() + curve->getB()) == y*y);
    } 
    return r; 
}

Point::Point(const std::string& Px, const std::string& Py, Curve* c, int base)
{
    mpz_class v;
    v.set_str(Px, base);
    x = Field_secp256r1_p(v);
    v.set_str(Py, base);
    y = Field_secp256r1_p(v);
    curve = c;
    is_inf = false;
}


Point::Point(const char* Px, const char* Py, Curve* c, int base) :
Point(std::string(Px), std::string(Py), c, base)
{
}

Point Point::operator+ (const Point& P) const
{

    if(is_inf)
        return P;

    if(P.is_inf)
        return *this;

    assert(*this->curve == *P.curve);

    if(this->x == P.x)
    {
        if(this->y == P.y)
            return this->pointDouble();
        else
            return Point();
    }


    Field_secp256r1_p S;
    Field_secp256r1_p Rx;
    Field_secp256r1_p Ry;

	// Calculate slope as Py - Qy / Px - Qx
    S = (this->y - P.y) / (this->x - P.x);
	
    // Calculate Rx as slope^2 - Px -Qx
    Rx = (S*S) - this->x - P.x;

	// Calculate Ry as (slope (Px - Rx) - Py)
    Ry = S * (this->x - Rx) - this->y;

	return Point(Rx, Ry, this->curve);
}

Point Point::operator- (const Point& P) const
{
    assert(*this->curve == *P.curve);

    Point Q(P.x, Field_secp256r1_p(0)-P.y, curve);

    
    return *this + Q;
}

Point Point::operator* (const mpz_class& a) const
{
    if(is_inf)
        return *this;

    Point P = *this;
    Point R;

	std::string bits = a.get_str(2);
	for (int i = bits.length() - 1; i >= 0; i--) 
    {
		if (bits[i] == '1') 
        {
			R += P;
		}
        if(i)
            P = P.pointDouble();
	}

	return R;
}

Point Point::operator* (const Field_secp256r1_n& a) const
{
    return *this * a.getRawValue();
}

Point& Point::operator+= (const Point& P)
{
    *this = *this + P;
    return *this;
}

Point& Point::operator-= (const Point& P)
{
    *this = *this - P;
    return *this;
}

Point& Point::operator*= (const Field_secp256r1_n& a)
{
    *this = *this * a;
    return *this;
}

Point& Point::operator= (const Point& P)
{
    x = P.x;
    y = P.y;
    curve = P.curve;
    is_inf = P.is_inf;
    return *this;
}


bool Point::operator== (const Point& P) const
{
    if(is_inf == true && P.is_inf == true)
        return true;
    
    return x == P.x && y == P.y && *curve == *P.curve && is_inf == P.is_inf;
}

std::ostream& operator<< (std::ostream& out, const Point& P )
{
    if(P.is_inf)
        return out << "(inf, inf)";
    return out << "(" << P.x.getRawValue() << "," << P.y.getRawValue() << ")";
}

Point Point::pointDouble() const
{
    Field_secp256r1_p T1;
    Field_secp256r1_p T2;
    Field_secp256r1_p S;
    Field_secp256r1_p Rx;
    Field_secp256r1_p Ry;


	// Calculate 3Px^2 + a, where a is EC parmater
    T1 = this->x.square() * mpz_class(3) + curve->getAField();

	// Calculate 2Py
    T2 = this->y * mpz_class(2);

	// Calculate s = (3Px^2 + a) / 2Py
    S = T1 / T2;

	// Calculate Rx = s^2 - 2Px
    Rx = S*S - this->x * mpz_class(2);

	// Calculate s (Px - Rx)
    Ry = S * (this->x - Rx) - this->y;

	return Point(Rx, Ry, curve);
}

Curve_secp256r1::Curve_secp256r1(void)
{
    prime.set_str("ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16);
    a.set_str("ffffffff00000001000000000000000000000000fffffffffffffffffffffffc", 16);
    b.set_str("5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b", 16);

    mpz_class Gx, Gy;
    Gx.set_str("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296", 16);
    Gy.set_str("4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5", 16);
    G = Point(Gx, Gy, this); 

    order.set_str("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16);
    cofactor.set_str("1", 16);
    

    a.set_str("ffffffff00000001000000000000000000000000fffffffffffffffffffffffc", 16);
    
}

Curve_secp256r1::~Curve_secp256r1(void)
{

}

bool operator==(const Curve& curve, const Curve& c)
{
    return
        !cmp(curve.prime,c.prime) &&
        !cmp(curve.a,c.a) &&
        !cmp(curve.b,c.b) &&
        !cmp(curve.order,c.order) &&
        !cmp(curve.cofactor,c.cofactor) &&
        curve.key_size_bits == c.key_size_bits;
}


Point Curve_secp256r1::getRandomPoint(void)
{
    mpz_class a = Curve_secp256r1::rand.get_z_range(order);
    return G * a;
}

Field_secp256r1_n Curve_secp256r1::getRandomScalar(void)
{
    mpz_class a = Curve_secp256r1::rand.get_z_range(order);
    return Field_secp256r1_n(a);
}

KeyPair Curve_secp256r1::generateKeyPair(void)
{
    mpz_class sk = Curve_secp256r1::rand.get_z_range(order);
    Point pk = G * sk;
    return KeyPair(sk,pk);
}


Point Curve_secp256r1::evaluatePx(const Field_secp256r1_p& Px)
{
    Field_secp256r1_p Py2 = Px*Px*Px + Px*a + Px*b; // FIXME: compute square root (if exist) else return INF
    return Point(Px, Py2, this);
}
    