
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <iostream>   

#include "aes.hpp"
#include "utilities.hpp"
#include "crc.hpp"


namespace aes
{
string AES::iv;

void handleErrors(void)
{
    unsigned long errCode;

    printf("An error occurred\n");
    while((errCode = ERR_get_error()))
    {
        char *err = ERR_error_string(errCode, NULL);
        printf("%s\n", err);
    }
    abort();
}


void AES::init(const string iv)
{
    AES::iv = iv;
}

void AES::init()
{
    AES::iv = iv;
}

ctxt_t AES::encrypt(const msg_t plaintext, const mpz_class key) const
{
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, ciphertext_len = 0;
    unsigned char ciphertext[128];
    uint8_t *ptarr;
    uint8_t *keyarr;
    
    size_t pt_len  = utils::getRawMpz(&ptarr, plaintext);
    utils::getRawMpz(&keyarr, key);

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    /* Initialise the encryption operation. */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL,(unsigned char*)keyarr, (unsigned char*)AES::iv.c_str()))
        handleErrors();

    // /* Set IV length if default 12 bytes (96 bits) is not appropriate */
    // if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 14, NULL))
    //     handleErrors();

    // /* Initialise key and IV */
    // if(1 != EVP_EncryptInit_ex(ctx, NULL, NULL, (unsigned char*)keyarr, (unsigned char*)AES::iv.c_str())) handleErrors();

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)ptarr, pt_len))
        handleErrors();

    ciphertext_len = len;

    /* Finalise the encryption. Normally ciphertext bytes may be written at
     * this stage, but this does not occur in GCM mode
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    // /* Get the tag */
    // if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 14, tag))
    //     handleErrors();

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    // string c = string((char*)ciphertext, ciphertext_len);
    // string t = string((char*)tag, 16);
    return utils::setRawMpz(ciphertext,ciphertext_len);
}

msg_t AES::decrypt(const ctxt_t cipher, const mpz_class key) const
{
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, plaintext_len = 0;
    // unsigned char plaintext[128];
    unsigned char plaintext[128];
    uint8_t *ctxtarr;
    uint8_t *keyarr;
    
    size_t ctxt_len  = utils::getRawMpz(&ctxtarr, cipher);
    utils::getRawMpz(&keyarr, key);


    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    /* Initialise the decryption operation. */
    if(!EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, (unsigned char*)keyarr, (unsigned char*)AES::iv.c_str()))
        handleErrors();

    // /* Set IV length. Not necessary if this is 12 bytes (96 bits) */
    // if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 14, NULL))
    //     handleErrors();

    // /* Initialise key and IV */
    // if(!EVP_DecryptInit_ex(ctx, NULL, NULL, )) 
    //     handleErrors();


    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if(!EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)ctxtarr, ctxt_len))
        handleErrors();

    plaintext_len = len;

    // /* Set expected tag value. Works in OpenSSL 1.0.1d and later */
    // if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 14,(unsigned char*) cipher.tag.c_str()))
    //     handleErrors();

    /* Finalise the decryption. A positive return value indicates success,
     * anything else is a failure - the plaintext is not trustworthy.
     */
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    // plaintext[plaintext_len] = '\0';

    return utils::setRawMpz(plaintext, plaintext_len);
}    

ctxt_t AES::encryptCRC(const mpz_class key, const msg_t plaintext) const
{
    msg_t msg = appendCRC(plaintext);
    return encrypt(msg, key);
}

msg_t AES::decryptCRC(const mpz_class key, const ctxt_t cipher) const
{
    
    msg_t m =  decrypt(cipher, key);
    if(validateCRC(m))
    {
        m = removeCRC(m);
        return m;
    }
    else 
        return msg_t(0);
}


}
