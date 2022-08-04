#ifndef __ECC__
#define __ECC__

#include <gmpxx.h>
#include "field_secp256r1_p.hpp"
#include "field_secp256r1_n.hpp"


class Point; 
class Curve;


class Point
{

private:
    Field_secp256r1_p x;
    Field_secp256r1_p y;
    bool is_inf;

public:
    Curve* curve;

    Point(const Point& P);
    Point(const mpz_class& Px, const mpz_class& Py, Curve* c);
    Point(const Field_secp256r1_p& Px, const Field_secp256r1_p& Py, Curve* c);
    Point(const std::string& Px, const std::string& Py, Curve* c, int base=10);
    Point(const char* Px, const char* Py, Curve* c, int base=10);
    Point();
    ~Point();

    bool isValid() const;

    Point& operator= (const Point& P);
    bool operator== (const Point& P) const;
    Point operator+ (const Point& P) const;
    Point& operator+= (const Point& P);
    Point operator- (const Point& P) const;
    Point& operator-= (const Point& P);
    Point operator* (const mpz_class& a) const;
    Point operator* (const Field_secp256r1_n& a) const;
    Point& operator*= (const mpz_class& a);
    Point& operator*= (const Field_secp256r1_n& a);
    friend std::ostream& operator<< (std::ostream& out, const Point& P);

    Point pointDouble() const;
};



typedef struct KeyPair
{
    mpz_class sk; 
    Point pk;

    KeyPair(mpz_class s, Point P); 
} KeyPair;







class Curve
{
    protected: 
        mpz_class prime;
        mpz_class a;
        mpz_class b;
        Point G;
        mpz_class order;
        mpz_class cofactor;
        size_t key_size_bits;
    
    public:

        friend bool operator==(const Curve& curve, const Curve& c);

        mpz_class getOrder(void) const {return order; }
        mpz_class getPrime(void) const {return prime; }
        mpz_class getA(void) const {return a; }
        Field_secp256r1_p getAField(void) const {return Field_secp256r1_p(a); }
        mpz_class getB(void) const {return b; }
        Field_secp256r1_p getBField(void) const {return Field_secp256r1_p(b); }
        Point getDefaultGen(void) const { return G; }
        virtual Point getRandomPoint(void) = 0;
        virtual Field_secp256r1_n getRandomScalar(void) = 0;
        virtual KeyPair generateKeyPair(void) = 0;
        virtual Point evaluatePx(const Field_secp256r1_p& Px) = 0;
};


class Curve_secp256r1 final: public Curve
{
    private:
        static gmp_randclass rand;

    public:
        Curve_secp256r1(void);
        ~Curve_secp256r1(void);

        Point getRandomPoint(void) override;
        Field_secp256r1_n getRandomScalar(void) override;
        KeyPair generateKeyPair(void) override;
        Point evaluatePx(const Field_secp256r1_p& Px) override;
};



#endif