#include "crc.hpp"
#include "utilities.hpp"

#include <iostream>
#include <gmpxx.h>


using namespace std;

int main(int argc, char const *argv[])
{
    int success = 0;
    mpz_class a = utils::getRandom(1024);

    mpz_class n = appendCRC(a);
    if (validateCRC(n)) 
        success = 0;
    else 
        success = -1;

    n = removeCRC(n); 
    if (a == n )
        return success;
    else 
        return -1;
}
