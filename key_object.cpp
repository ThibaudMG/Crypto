#include "uECC.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void hex_string(char str[], int length)
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

void key_print(uint8_t *vli, unsigned int size) {
    for(unsigned i=0; i<size; ++i) {
        printf("%02X", (unsigned)vli[i]);
    }
}

int main()
{
    uECC_Curve curve = uECC_secp256k1();
    uint8_t private_key[64];
    uint8_t* public_key = (uint8_t*) malloc(64);
    uint8_t* adress = (uint8_t*) malloc(20);

    
    srand(time(0));
    hex_string((char *) private_key, 64);
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

    return 0;
}