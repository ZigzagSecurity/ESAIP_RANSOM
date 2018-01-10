#include "stdafx.h"
#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string>
#include <iostream>
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name 


using namespace std;
using namespace std::experimental::filesystem::v1;


void encryptfile(FILE * fpin, FILE* fpout, unsigned char* key, unsigned char* iv)
{
	//Using openssl EVP to encrypt a file
	const unsigned bufsize = 4096;
	unsigned char* read_buf = (unsigned char*)malloc(bufsize);
	unsigned char* cipher_buf;
	int blocksize;
	int out_len;

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	EVP_CipherInit(ctx, EVP_aes_256_cbc(), key, iv, 1); // if 0 = decrypt , 1 = encrypt
	blocksize = EVP_CIPHER_CTX_block_size(ctx);
	cipher_buf = (unsigned char*)malloc(bufsize + blocksize);

	// read file and write encrypted file until eof
	while (1)
	{
		int bytes_read = fread(read_buf, sizeof(unsigned char), bufsize, fpin);
		EVP_CipherUpdate(ctx, cipher_buf, &out_len, read_buf, bytes_read);
		fwrite(cipher_buf, sizeof(unsigned char), out_len, fpout);
		if (bytes_read < bufsize)
		{
			break;//EOF
		}
	}

	EVP_CipherFinal(ctx, cipher_buf, &out_len);
	fwrite(cipher_buf, sizeof(unsigned char), out_len, fpout);

	free(cipher_buf);
	free(read_buf);
}


void decryptfile(FILE * fpin, FILE* fpout, unsigned char* key, unsigned char* iv)
{
	//Using openssl EVP to encrypt a file
	const unsigned bufsize = 4096; // bytes to read
	unsigned char* read_buf = (unsigned char*)malloc(bufsize);
	unsigned char* cipher_buf;// decrypted text
	int blocksize;
	int out_len;

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

	EVP_CipherInit(ctx, EVP_aes_256_cbc(), key, iv, 0); // 0 = decrypt 	1= encrypt
	blocksize = EVP_CIPHER_CTX_block_size(ctx);
	cipher_buf = (unsigned char*)malloc(bufsize + blocksize);
	//cipher_buf = malloc(bufsize+blocksize);

	// read file and write encrypted file until eof
	while (1)
	{
		int bytes_read = fread(read_buf, sizeof(unsigned char), bufsize, fpin);
		EVP_CipherUpdate(ctx, cipher_buf, &out_len, read_buf, bytes_read);
		fwrite(cipher_buf, sizeof(unsigned char), out_len, fpout);
		if (bytes_read < bufsize)
		{
			break;//EOF
		}
	}

	EVP_CipherFinal(ctx, cipher_buf, &out_len);
	fwrite(cipher_buf, sizeof(unsigned char), out_len, fpout);

	free(cipher_buf);
	free(read_buf);
}


void get_file_encrypt(unsigned char* key, unsigned char* iv, const char* path) {

	char* new_name = (char*)malloc(strlen(path) + strlen(".prkl") + 1);
	strcpy(new_name, path);
	strcat(new_name, ".prkl");

	FILE* fpin;
	FILE* fpout;

	fpin = fopen(path, "r");
	fpout = fopen(new_name, "w");


	encryptfile(fpin, fpout, key, iv);

	fclose(fpin);
	fclose(fpout);
	remove(path);

	free(new_name);
}


void get_file_decrypt(unsigned char* key, unsigned char* iv, const char* path) {
	/*=============== decrypt the file ============*/
	char* encr_path = (char*)malloc(strlen(path));
	strcpy(encr_path, path);

	char *new_name = (char*)malloc(strlen(encr_path) + 1);
	strcpy(new_name, encr_path);
	new_name[strlen(new_name) - 5] = '\0';

	FILE* fpin;
	FILE* fpout;

	fpin = fopen(encr_path, "r");
	fpout = fopen(new_name, "w");

	decryptfile(fpin, fpout, key, iv);
	if (fpin != NULL)
		fclose(fpin);
	if (fpout != NULL)
		fclose(fpout);

	remove(encr_path);
	free(new_name);
	
}


