#include <iomanip>
#include <iostream>
#include <gmpxx.h>


#include "ecc_secp256r1.hpp"


using namespace std;

typedef ecc::Point_secp256r1 POINT;
typedef ecc::Curve_secp256r1 CURVE;

int main(int argc, char const *argv[])
{

    int i = 0;
    int success = 0;

    CURVE curve; 


    cout << "Testing Elliptic Curve Cryptography (ECC) Operations" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    

    POINT Inf;

    POINT P("84977697328889810205905983495378814169915355456656637049711992216827273875390","113984765640120748176992606851862342793053973752254499151000631165261995767165",&curve);

    POINT Q("63697252059872284381272932401874909409951463282505777844481084789510570568792","42108181942940304799197775515120260512991621230487422734550324972312644964859",&curve);
    

    POINT PplusQ("101186946395279644513138790537604879293941435118431328907674518710966683828402","6816289991419636437079674250297745566237099260731735769842810406514765603894", &curve);

    POINT Ptimes10("21353238564127361844413850988930366307036826902481189565622865528243313548234"," 19693254829710921034570991117370582129849796669680234808809542666479612482892", &curve);

    POINT Ptimes99("7351186338741311390390579546112325810531162022156291610136117810248366013335"," 20620688547460148735246365938363003834064651421739100004113374821348606164774", &curve);

    POINT Ptimes90912389("39713820183789898512483171409752538453383718839221188993776377142904537596963"," 48365718026147700096726340623511188595478532931695481815446315261246227175991", &curve);

    POINT PminusQ("17495055239713755065764498232777582223458639405056673754653767594082808961074","114881897483998757494520577973324734261879933230870480577216288699002102291593", &curve);

     
    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    POINT R1 = curve.getRandomPoint();
    POINT R2 = curve.getRandomPoint();
    R2.setEncodedX(R1.getEncodedX());
    if(R2 == R1) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    
    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(curve.getDefaultGen().isValid()) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P.isValid()) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }
    
    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Q.isValid()) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Inf + P == P) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P + Inf == P) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P + P == P.pointDouble()) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P - P == Inf) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Inf * 1000 == Inf) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }



    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P+Q == PplusQ) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Ptimes10 == P * 10) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Ptimes99 == P * 99) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Ptimes90912389 == P * 90912389) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P-Q == PminusQ) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(P == curve.evaluateP(P.getX())) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(Q == curve.evaluateP(Q.getX())) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }


    cout << "--------------END OF TEST-------------------" << endl;
    
    return success;
}
