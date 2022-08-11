#ifndef __ECC__
#define __ECC__

#include <gmpxx.h>
#include <gmp.h>
#include "field_template.hpp"
#include "utilities.hpp"

namespace ecc
{
    
template <typename Curve_XXX, typename Point_XXX,  typename Field_XXX_p, typename Field_XXX_n> 
class Point
{

private:
    Field_XXX_p x;
    Field_XXX_p y;
    bool is_inf;


public:
    Curve_XXX* curve;

    Point(const Point_XXX& P);
    Point(const mpz_class& Px, const mpz_class& Py, Curve_XXX* c);
    Point(const Field_XXX_p& Px, const Field_XXX_p& Py, Curve_XXX* c);
    Point(const std::string& Px, const std::string& Py, Curve_XXX* c, int base=10);
    Point(const char* Px, const char* Py, Curve_XXX* c, int base=10);
    Point();
    ~Point();

    bool isValid() const;
    bool isInf() const {return is_inf;}
    Field_XXX_p getX() const {return x;}
    mpz_class getEncodedX() const; 
    void setEncodedX(mpz_class ex); 
    Field_XXX_p getY() const {return y;}

    Point_XXX& operator= (const Point_XXX& P);
    bool operator== (const Point_XXX& P) const;
    Point_XXX operator+ (const Point_XXX& P) const;
    Point_XXX& operator+= (const Point_XXX& P);
    Point_XXX operator- (const Point_XXX& P) const;
    Point_XXX& operator-= (const Point_XXX& P);
    Point_XXX operator* (const mpz_class& a) const;
    Point_XXX operator* (const Field_XXX_n& a) const;
    Point_XXX& operator*= (const mpz_class& a);
    Point_XXX& operator*= (const Field_XXX_n& a);
    template<typename T1, typename T2, typename T3, typename T4>
    friend std::ostream& operator<< (std::ostream& out, const Point<T1,T2,T3,T4>& P);

    Point_XXX pointDouble() const;
};



template<typename Curve_XXX, typename Point_XXX, typename Field_XXX_p, typename Field_XXX_n>
struct KeyPair
{
    mpz_class sk; 
    Point<Curve_XXX, Point_XXX, Field_XXX_p, Field_XXX_n> pk;

    KeyPair(mpz_class s, Point_XXX P)
    {
        sk = s;
        pk = P;
    }
};






template<typename Curve_XXX, typename Point_XXX, typename Field_XXX_p, typename Field_XXX_n>
class Curve
{
    protected: 
        static gmp_randclass rand;
        mpz_class prime;
        mpz_class a;
        mpz_class b;
        Point_XXX G;
        mpz_class order;
        mpz_class cofactor;

    
    public:

        template<typename T1, typename T2, typename T3, typename T4>
        friend bool operator==(const Curve<T1,T2,T3,T4>& curve, const Curve<T1,T2,T3,T4>& c);
        template<typename T1, typename T2, typename T3, typename T4>
        friend std::ostream& operator<<(std::ostream& out, const Curve<T1,T2,T3,T4>& c);

        mpz_class getOrder(void) const {return order; }
        mpz_class getPrime(void) const {return prime; }
        mpz_class getA(void) const {return a; }
        Field_XXX_p getAField(void) const {return Field_XXX_p(a); }
        mpz_class getB(void) const {return b; }
        Field_XXX_p getBField(void) const {return Field_XXX_p(b); }
        Point_XXX getDefaultGen(void) const { return G; }
        Point_XXX getRandomPoint(void) const;
        Field_XXX_n getRandomScalar(void) const;
        KeyPair<Curve_XXX,Point_XXX,Field_XXX_p,Field_XXX_n> generateKeyPair(void) const;
        Point_XXX evaluateP(const Field_XXX_p& x);
        Point_XXX evaluatePneg(const Field_XXX_p& x);
        Field_XXX_p evaluatePy2(const Field_XXX_p& x) const;
};




template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point(const Point_XXX& P)
{
    x = P.x;
    y = P.y;
    curve = P.curve;
    is_inf = P.is_inf;
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point()
{
    curve = 0;
    is_inf = true;
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point(const mpz_class& Px, const mpz_class& Py, Curve_XXX* c)
{
    x = Field_XXX_p(Px);
    y = Field_XXX_p(Py);
    curve = c;
    is_inf = false;
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point(const Field_XXX_p& Px, const Field_XXX_p& Py, Curve_XXX* c)
{
    x = Px;
    y = Py;
    curve = c;
    is_inf = false;
}



template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point::~Point()
{

}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point(const std::string& Px, const std::string& Py, Curve_XXX* c, int base)
{
    mpz_class v;
    v.set_str(Px, base);
    x = Field_XXX_p(v);
    v.set_str(Py, base);
    y = Field_XXX_p(v);
    curve = c;
    is_inf = false;
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point(const char* Px, const char* Py, Curve_XXX* c, int base) :
Point(std::string(Px), std::string(Py), c, base)
{
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
mpz_class Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::getEncodedX() const
{
    mpz_class res = x.getRawValue();
    mpz_mul_2exp(res.get_mpz_t(),res.get_mpz_t(),1);
    if (curve->evaluateP(x).getY() == y)
        res += 1;

    return res;

}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
void Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::setEncodedX(mpz_class ex)
{
    mpz_class res,bit;
    bit = mpz_tstbit(ex.get_mpz_t(),0);
    mpz_div_2exp(res.get_mpz_t(),ex.get_mpz_t(),1);

    if (bit)
        *this = curve->evaluateP(res);
    else
        *this = curve->evaluatePneg(res);
}



template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator+ (const Point_XXX& P) const
{

    if(is_inf)
        return P;

    if(P.is_inf)
        return *static_cast<const Point_XXX*>(this);

    assert(*this->curve == *P.curve);

    if(this->x == P.x)
    {
        if(this->y == P.y)
            return this->pointDouble();
        else
            return Point_XXX();
    }


    Field_XXX_p S;
    Field_XXX_p Rx;
    Field_XXX_p Ry;

	// Calculate slope as Py - Qy / Px - Qx
    S = (this->y - P.y) / (this->x - P.x);
	
    // Calculate Rx as slope^2 - Px -Qx
    Rx = (S*S) - this->x - P.x;

	// Calculate Ry as (slope (Px - Rx) - Py)
    Ry = S * (this->x - Rx) - this->y;

	return Point_XXX(Rx, Ry, this->curve);
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator- (const Point_XXX& P) const
{
    assert(*this->curve == *P.curve);

    Point_XXX Q(P.x, Field_XXX_p(0)-P.y, curve);

    
    return *this + Q;
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator* (const mpz_class& a) const
{
    return *this * Field_XXX_n(a);
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator* (const Field_XXX_n& a) const
{
    if(is_inf)
        return *static_cast<const Point_XXX*>(this);

    Point_XXX P = *static_cast<const Point_XXX*>(this);
    Point_XXX R;

	std::string bits = a.getRawValue().get_str(2);
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

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX& Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator+= (const Point_XXX& P)
{
    *this = *this + P;
    return *static_cast<Point_XXX*>(this);;
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX& Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator-= (const Point_XXX& P)
{
    *this = *this - P;
    return *static_cast<Point_XXX*>(this);;
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX& Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator*= (const Field_XXX_n& a)
{
    *this = *this * a;
    return *static_cast<Point_XXX*>(this);;
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX& Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator= (const Point_XXX& P)
{
    x = P.x;
    y = P.y;
    curve = P.curve;
    is_inf = P.is_inf;
    return *static_cast<Point_XXX*>(this);;
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
bool Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::operator== (const Point_XXX& P) const
{
    if(is_inf == true && P.is_inf == true)
        return true;
    
    return x == P.x && y == P.y && *curve == *P.curve && is_inf == P.is_inf;
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
std::ostream& operator<< (std::ostream& out, const Point<Curve_XXX,Point_XXX, Field_XXX_p, Field_XXX_n>& P )
{
    if(P.is_inf)
        return out << "(inf, inf)";
    return out << "(" << P.x.getRawValue() << "," << P.y.getRawValue() << ")";
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
bool Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::Point::isValid() const 
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


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Point<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::pointDouble() const
{
    Field_XXX_p T1;
    Field_XXX_p T2;
    Field_XXX_p S;
    Field_XXX_p Rx;
    Field_XXX_p Ry;


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

	return Point_XXX(Rx, Ry, curve);
}



template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
bool operator==(const Curve<Curve_XXX,Point_XXX, Field_XXX_p, Field_XXX_n>& curve, 
                const Curve<Curve_XXX,Point_XXX, Field_XXX_p, Field_XXX_n>& c)
{
    return
        !cmp(curve.prime,c.prime) &&
        !cmp(curve.a,c.a) &&
        !cmp(curve.b,c.b) &&
        !cmp(curve.order,c.order) &&
        !cmp(curve.cofactor,c.cofactor);
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
std::ostream& operator<<(std::ostream& out, const Curve<Curve_XXX,Point_XXX, Field_XXX_p, Field_XXX_n>& c)
{
    return out << "C(p="<<c.prime<<", a="<<c.a<<", b="<<c.b<<", n="<<c.order<<", cof="<<c.cofactor<<")";
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::getRandomPoint(void) const
{
    mpz_class a = Curve_XXX::rand.get_z_range(order);
    return G * a;
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Field_XXX_n Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::getRandomScalar(void) const
{
    mpz_class a = Curve_XXX::rand.get_z_range(order);
    return Field_XXX_n(a);
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
KeyPair<Curve_XXX, Point_XXX, Field_XXX_p, Field_XXX_n> Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::generateKeyPair(void) const
{
    mpz_class sk = Curve_XXX::rand.get_z_range(order);
    Point pk = G * sk;
    return KeyPair<Curve_XXX, Point_XXX, Field_XXX_p, Field_XXX_n>(sk,pk);
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::evaluateP(const Field_XXX_p& x)
{
    // this only works if p = 3 mod 4

    Field_XXX_p y2 = x*x*x + x*a + b;
    mpz_class pplus1 = y2.getField() + 1;
    mpz_class exp;
    mpz_divexact_ui(exp.get_mpz_t(), pplus1.get_mpz_t(),4);
    mpz_class res;
    mpz_powm(res.get_mpz_t(),y2.getRawValue().get_mpz_t(), exp.get_mpz_t(), prime.get_mpz_t());
    Field_XXX_p y = Field_XXX_p(res);
    if (y*y == y2)
        return Point_XXX(x, y, static_cast<Curve_XXX*>(this));
    else 
        return Point_XXX();
}


template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Point_XXX Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::evaluatePneg(const Field_XXX_p& x)
{
    // this only works if p = 3 mod 4

    Field_XXX_p y2 = x*x*x + x*a + b;
    mpz_class pplus1 = y2.getField() + 1;
    mpz_class exp;
    mpz_divexact_ui(exp.get_mpz_t(), pplus1.get_mpz_t(),4);
    mpz_class res;
    mpz_powm(res.get_mpz_t(),y2.getRawValue().get_mpz_t(), exp.get_mpz_t(), prime.get_mpz_t());
    Field_XXX_p y = Field_XXX_p(y2.getField()-res);
    if (y*y == y2)
        return Point_XXX(x, y, static_cast<Curve_XXX*>(this));
    else 
        return Point_XXX();
}



template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
Field_XXX_p Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::evaluatePy2(const Field_XXX_p& x) const
{
    return x*x*x + x*a + b; 
}

template<
        typename Curve_XXX,
        typename Point_XXX, 
        typename Field_XXX_p, 
        typename Field_XXX_n
        >
gmp_randclass Curve<
Curve_XXX, 
Point_XXX, 
Field_XXX_p, 
Field_XXX_n
>::rand(gmp_randinit_default);

} // namespace ecc


#endif

