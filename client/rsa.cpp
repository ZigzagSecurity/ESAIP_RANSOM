#include "stdafx.h"
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string>
#include <iostream>
#include <openssl\err.h>


using namespace std;

bool generate_key()
{
	int             ret = 0;
	RSA             *r = NULL;
	BIGNUM          *bne = NULL;
	BIO             *bp_public = NULL, *bp_private = NULL;

	int             bits = 2048;
	unsigned long   e = RSA_F4;

	char msg[2048 / 8];
	void *encrypt;
	int encrypt_length;
	void* err;
	void* decrypt;


	// 1. generate rsa key
	bne = BN_new();
	ret = BN_set_word(bne, e);
	if (ret != 1) {
		goto free_all;
	}

	//initialize the esa structure
	r = RSA_new();
	//generates the keys and store them in r
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	//if the generation failed, erase everything
	if (ret != 1) {
		goto free_all;
	}

	//input the msg to encrypt
	printf("Message to encrypt : ");
	fgets(msg, 2048 / 8, stdin);
	msg[strlen(msg) - 1] = '\0'; //get rid of the newline character

	//let's encrypt
	encrypt = malloc(RSA_size(r));
	err = malloc(130);
	if ((encrypt_length = RSA_public_encrypt(strlen(msg) + 1, (unsigned char*)msg, (unsigned char*)encrypt, r, RSA_PKCS1_OAEP_PADDING)) == -1) {
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), (char*)err);
		fprintf(stderr, "Error encrypting message : %s\n", err);
	}

	//let's decrypt
	decrypt = malloc(RSA_size(r));
	if (RSA_private_decrypt(encrypt_length, (unsigned char*)encrypt, (unsigned char*)decrypt, r, RSA_PKCS1_OAEP_PADDING) == -1) {
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), (char*) err);
		fprintf(stderr, "Error decrypting message: %s\n", err);
	}
	else {
		printf("Decrypted message : %s\n", decrypt);
	}


	//freeze terminal
	cin.ignore();


	// 4. free
free_all:

	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);

	return (ret == 1);
}





int main(int argc, char* argv[])
{
	generate_key();
	return 0;
}
