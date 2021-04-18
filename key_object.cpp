#include "uECC.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void rand_hex(char str[], int length);

void key_print(uint8_t *vli, unsigned int size);

struct Keys{
        uint8_t* private_key;
        uint8_t* public_key;
        uint8_t* signature;
};

Keys initialize(uint8_t* private_key);

char* getPrivateKey();

char* getPublicKey();

uint8_t private_key[64];
uint8_t* public_key = (uint8_t*) malloc(64);
uint8_t* adress = (uint8_t*) malloc(20);

int main()
{
    srand(time(0));
    rand_hex((char *) private_key, 64);
    Keys keys;
    keys = initialize(private_key);

    cout << (string) getPrivateKey() << endl;
    cout << (string) getPublicKey() <<endl;
    /*srand(time(0));
    rand_hex((char *) private_key, 64);
    cout << "Private Key (Hex): " << private_key << endl;

    if (uECC_compute_public_key(private_key, public_key, curve)){
        cout << "Public Key (Hex): "; 
        key_print(public_key, 64);        
    } else
        cout << "Error computing the key" << endl;


    if (uECC_sign(private_key, public_key, 20, adress, curve)){
        cout << "\nAdress: 0x"; 
        key_print(adress, 64); 
    } else
        cout << "Error computing the signature" << endl;
*/
    return 0;
}

Keys initialize(uint8_t* private_key){
    Keys keys;
    uECC_Curve curve = uECC_secp256k1();
    uint8_t* public_key = (uint8_t*) malloc(64);
    uint8_t* signature = (uint8_t*) malloc(20);

    if (!uECC_compute_public_key(private_key, public_key, curve))
        cout << "Error computing the key" << endl;

    if (!uECC_sign(private_key, public_key, 20, signature, curve))
        cout << "Error computing the signature" << endl;

    keys.private_key = private_key;
    keys.public_key = public_key;
    keys.signature = signature;

    return keys;
}

void key_print(uint8_t *vli, unsigned int size) {
    for(unsigned i=0; i<size; ++i) {
        printf("%02X", (unsigned)vli[i]);
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

char* getPrivateKey(){
    char* private_key_string = "";
    for(unsigned i=0; i<64; ++i) {
        private_key_string += private_key[i];
    }
    return private_key_string;
}

char* getPublicKey(){
    char* public_key_string = "";
    for(unsigned i=0; i<128; ++i) {
        public_key_string += public_key[i];
    }
    return public_key_string;
}