#include "uECC.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void rand_hex(char str[], int length);

void key_print(uint8_t *key, unsigned int size);

struct Keys
{
    uint8_t *private_key;
    uint8_t *public_key;
    uint8_t *signature;
};

Keys initialize(char *private_key);

void getPrivateKey();

void getPublicKey();

char private_key[64];
uint8_t *public_key = (uint8_t *)malloc(64);
uint8_t *signature = (uint8_t *)malloc(20);

int main()
{
    Keys keys;

    srand(time(0));
    rand_hex(private_key, 64);
    
    keys = initialize(private_key);

    cout << "Private Key: ";
    getPrivateKey();
    cout << "Public Key: ";
    getPublicKey();

    return 0;
}

Keys initialize(char *private_key)
{
    Keys keys;
    uECC_Curve curve = uECC_secp256k1();

    if (!uECC_compute_public_key((uint8_t *)private_key, public_key, curve))
        cout << "Error computing the key" << endl;

    if (!uECC_sign((uint8_t *)private_key, public_key, 20, signature, curve))
        cout << "Error computing the signature" << endl;

    keys.private_key = (uint8_t *)private_key;
    keys.public_key = public_key;
    keys.signature = signature;

    return keys;
}

void key_print(uint8_t *key, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        printf("%02X", (unsigned)key[i]);
    }
}

void rand_hex(char str[], int length)
{
    //hexadecimal characters
    char hex_characters[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    int i;
    for (i = 0; i < length; i++)
    {
        str[i] = hex_characters[rand() % 16];
    }
    str[length] = 0;
}

void getPrivateKey()
{
    cout << private_key << endl;
}

void getPublicKey()
{
    key_print(public_key, 64);
}