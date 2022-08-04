#include <iomanip>
#include <iostream>
#include <gmpxx.h>

#include "constants.hpp"
#include "field_secp256r1_p.hpp"


using namespace std;

int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;

    cout << "Testing Field Operations" << endl;
    cout << "--------------START OF TEST-------------------" << endl;

    FIELD_p a(mpz_class("115792089210356248762697446911407573530086143415299914195533631308867097853953",10));
    FIELD_p b(mpz_class("114123486102945789471102938563810123456789012678123898127389245018481290378472",10));

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a+b == FIELD_p(mpz_class("114123486102945789471102938525810123456789012678133498127389245018481290378474",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a+a == FIELD_p(mpz_class("115792089210356248762697446873407573530086143415309514195533631308867097853955",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;            
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(b+b == FIELD_p(mpz_class("112454882995535330179508430178212673383491881940957482059244858728095482902993",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;            
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a-b == FIELD_p(mpz_class("1668603107410459291594508347597450073297130737176016068144386290385807475481",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(b-a == FIELD_p(mpz_class("114123486102945789471102938601810123456789012678114298127389245018481290378470",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a-a == FIELD_p(0)) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(b-b == FIELD_p(0)) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a*b == FIELD_p(mpz_class("64612386361951989056516811974132124533298328794823227983094747810559130757188",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a/b == FIELD_p(mpz_class("78022135255180380122285888469357818367183359894755157665029097915500245715072",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(b.invert() == FIELD_p(mpz_class("14571788612224318864831000442587039636655541211855231713863560926660394311888",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a.invert() == FIELD_p(mpz_class("8712139969365681565753642840680557109677220036619600254496360170439233380648",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(a.square() == FIELD_p(mpz_class("104352153261626623953452628323589261248798252725060068905010816622861221411144",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(b.square() == FIELD_p(mpz_class("42703936318985830561422526257309216918017484751181218668061004177165567807035",10))) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }
    
    cout << "--------------END OF TEST-------------------" << endl;
    return success;
}
