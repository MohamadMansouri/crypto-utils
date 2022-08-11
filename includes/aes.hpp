#ifndef __AES__
#define __AES__

#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string>
#include <gmpxx.h>

namespace aes
{
#define CRYPTO_KEYBYTES 16
#define CRYPTO_NSECBYTES 0 
#define CRYPTO_NPUBBYTES 16 
#define CRYPTO_ABYTES 16 
#define CRYPTO_NOOVERLAP 1 

using std::string;
static const string iv = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";


typedef mpz_class ctxt_t;
typedef mpz_class msg_t;

class AES
{
private: 
    static string iv;

public:    
    AES() {}
    ~AES() {}
    static void init();
    static void init(const string iv);
    ctxt_t encrypt(const mpz_class key, const msg_t plaintext) const;
    ctxt_t encryptCRC(const mpz_class key, const msg_t plaintext) const;

    msg_t decrypt(const mpz_class key, const ctxt_t cipher) const;
    msg_t decryptCRC(const mpz_class key, const ctxt_t cipher) const;
};

}
#endif