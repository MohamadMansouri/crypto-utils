# Crypto Building Blocks

This repo contains the source code of some cryptographic tools which might be useful for researchers to easily and efficiently prototype new security protocols. It mainly uses the [GMP](https://gmplib.org/) library to perform computation on large numbers. We only use OpenSSL to import AES encryption functionality. 

It contains:
- A library for arithmetic field operations
- A library for elliptic curve cryptography: We currently support two curves secp256r1 and bn254 (pairing is not yet implemented). 
- Implementation of Shamir's Secret Sharing.
- Implementation of an Oblivious Transfer Protocol based on Dual-Mode Encryption. The protocol is presented in [crypto'08](https://link.springer.com/chapter/10.1007/978-3-540-85174-5_31). 	
- Implementation of PUDA Unforgeable Secure Aggregation protocol. The protocol is presented in [CANS'15](https://link.springer.com/content/pdf/10.1007/978-3-319-26823-1_1.pdf). 	
- Implementation of an Oblivious Programable Pseudo Random Function. The protocol is presented in [sacmat'22](https://dl.acm.org/doi/10.1145/3450569.3463572). 	
- More protocol prototypes and functionalities will be added regularly

# Requirements 
- GMP library (install from [here](https://gmplib.org/))
- OpenSSL (we only use AES for the implementation of OPPRF)

# Building
```
mkdir build
cd build && cmake ..
make
ctest --verbose