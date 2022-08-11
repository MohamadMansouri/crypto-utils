#ifndef __PRIMEFIELD__
#define __PRIMEFIELD__

#include <iostream>
#include <assert.h>

#include <gmp.h>
#include <gmpxx.h>

namespace field
{

template <typename Field_XXX> 
class PrimeField
{
protected:
    mpz_class value;
    mpz_class p;

public:


    PrimeField();
    PrimeField(const mpz_class& v);
    PrimeField(const mpz_class& v, const mpz_class& prime);
    ~PrimeField();

    // static Field_XXX getRandom();
    mpz_class getRawValue() const {return value;}
    mpz_class getField() const {return p;}
    void setField(mpz_class prime) {p=prime;}


    Field_XXX invert() const;
    Field_XXX square() const;

    bool operator==(const Field_XXX& a) const;
    Field_XXX& operator=(const Field_XXX& a);
    Field_XXX operator+ (const Field_XXX& a) const;
    Field_XXX& operator+= (const Field_XXX& a);
    Field_XXX operator- () const;
    Field_XXX operator- (const Field_XXX& a) const;
    Field_XXX& operator-= (const Field_XXX& a);
    Field_XXX operator* (const Field_XXX& a) const;
    Field_XXX operator* (const mpz_class& a) const;
    Field_XXX& operator*= (const Field_XXX& a);
    Field_XXX& operator*= (const mpz_class& a);
    Field_XXX operator/ (const Field_XXX& a) const;
    Field_XXX& operator/= (const Field_XXX& a);
    template <typename T>
    friend std::ostream& operator<< (std::ostream& out, const PrimeField<T>& a);
};



template <typename Field_XXX> 
PrimeField<Field_XXX>::PrimeField()
{

}


template <typename Field_XXX> 
PrimeField<Field_XXX>::PrimeField(const mpz_class& v)
{
    mpz_mod(value.get_mpz_t(),v.get_mpz_t(), p.get_mpz_t());
}


template <typename Field_XXX> 
PrimeField<Field_XXX>::PrimeField(const mpz_class& v, const mpz_class& prime)
{
    mpz_mod(value.get_mpz_t(),v.get_mpz_t(), prime.get_mpz_t());
    PrimeField<Field_XXX>::p = prime;
}

template <typename Field_XXX> 
PrimeField<Field_XXX>::~PrimeField()
{
}

// template <typename Field_XXX> 
// gmp_randclass PrimeField<Field_XXX>::rand(gmp_randinit_default);

// template <typename Field_XXX> 
// mpz_class PrimeField<Field_XXX>::p{};


// template <typename Field_XXX> 
// Field_XXX PrimeField<Field_XXX>::getRandom()
// {
//     return Field_XXX(Field_XXX::rand.get_z_range(p));
// }

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::invert() const
{
    mpz_class res;
    mpz_invert(res.get_mpz_t(), value.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::square() const
{
    mpz_class res = value * value;
    mpz_mod(res.get_mpz_t(),res.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}



template <typename Field_XXX> 
bool PrimeField<Field_XXX>::operator==(const Field_XXX& a) const
{
    return
    !cmp(this->value,a.value) && 
    !cmp(this->p,a.p); 
}

template <typename Field_XXX> 
Field_XXX& PrimeField<Field_XXX>::operator=(const Field_XXX& a)
{
    this->value = a.value; 
    this->p = a.p; 
    return *static_cast<Field_XXX*>(this);

}


template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::operator+(const Field_XXX& a) const
{
    assert(!cmp(p, a.p));
    mpz_class res = value + a.value;
    mpz_mod(res.get_mpz_t(),res.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}

template <typename Field_XXX> 
Field_XXX& PrimeField<Field_XXX>::operator+=(const Field_XXX& a)
{
    assert(!cmp(p, a.p));
    value += a.value;
    mpz_mod(value.get_mpz_t(),value.get_mpz_t(), p.get_mpz_t());
    return *static_cast<Field_XXX*>(this);

}

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::operator-() const
{
    mpz_class res = -value;
    mpz_mod(res.get_mpz_t(),res.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::operator-(const Field_XXX& a) const
{
    assert(!cmp(p, a.p));
    mpz_class res = value - a.value;
    mpz_mod(res.get_mpz_t(),res.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}

template <typename Field_XXX> 
Field_XXX& PrimeField<Field_XXX>::operator-=(const Field_XXX& a)
{
    assert(!cmp(p, a.p));
    value -= a.value;
    mpz_mod(value.get_mpz_t(),value.get_mpz_t(), p.get_mpz_t());
    return *static_cast<Field_XXX*>(this);
}

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::operator*(const Field_XXX& a) const
{
    assert(!cmp(p, a.p));
    
    mpz_class res = value * a.value;
    mpz_mod(res.get_mpz_t(),res.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::operator*(const mpz_class& a) const
{
    mpz_class res = value * a;
    mpz_mod(res.get_mpz_t(),res.get_mpz_t(), p.get_mpz_t());
    return Field_XXX(res);
}

template <typename Field_XXX> 
Field_XXX& PrimeField<Field_XXX>::operator*=(const Field_XXX& a)
{
    assert(!cmp(p, a.p));
    value *= a.value;
    mpz_mod(value.get_mpz_t(),value.get_mpz_t(), p.get_mpz_t());
    return *static_cast<Field_XXX*>(this);
}

template <typename Field_XXX> 
Field_XXX& PrimeField<Field_XXX>::operator*=(const mpz_class& a)
{
    value *= a;
    mpz_mod(value.get_mpz_t(),value.get_mpz_t(), p.get_mpz_t());
    return *static_cast<Field_XXX*>(this);
}

template <typename Field_XXX> 
Field_XXX PrimeField<Field_XXX>::operator/(const Field_XXX& a) const
{
    assert(!cmp(p, a.p));
    return *this * a.invert();
}

template <typename Field_XXX> 
Field_XXX& PrimeField<Field_XXX>::operator/=(const Field_XXX& a)
{
    assert(!cmp(p, a.p));
    *this *= a.invert();
    return *static_cast<Field_XXX*>(this);

}
template <typename Field_XXX> 
std::ostream& operator<< (std::ostream& out, const PrimeField<Field_XXX>& a)
{
    return out << a.value << "  mod "<< a.p;
}


    
}

#endif