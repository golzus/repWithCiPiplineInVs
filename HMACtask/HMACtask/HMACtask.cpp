// HMACtask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//libcrypto.lib;opencv_world420d.lib;
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <openssl/hmac.h>
#include <sstream>
#pragma warning(disable : 4996)
#define My_Sicret "A12jh"
#include <iomanip>
#include <gtest/gtest.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h> 
#include <stdio.h> 
using namespace cv;
using namespace std;

//A function that checks for equality between a given HMAC and the image
bool IsEqual1(/*string path */string key)
{
	string path = "C:\\Users\\1\\Desktop\\IMG_0433.JPG";
	//string path= "C:\\Users\\1\\Desktop\\IMG_3191.JPG";
	string temp = My_Sicret;
	ifstream filep(path, ios::binary);
	if (!filep) {
		cerr << "Failed to open file." << endl;
		return NULL;
	}
	// Read file content into a string
	string data((istreambuf_iterator<char>(filep)), istreambuf_iterator<char>());
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hashLen = 0;

	//do HMAC
	HMAC_CTX* HM = HMAC_CTX_new();
	HMAC_Init_ex(HM, temp.c_str(), temp.length(), EVP_sha256(), NULL);
	HMAC_Update(HM, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
	HMAC_Final(HM, hash, &hashLen);
	HMAC_CTX_free(HM);



	stringstream ss;
	for (unsigned int i = 0; i < hashLen; ++i) {
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	string s = ss.str();
	cout << "in is equal the key is: " << ss.str() << endl;
	if (s==key)
	{
		cout << "is same!!!!!!" << endl;
		return true;
	}
	return false;
}

//A function that get picture and make HMAC
string makehmac()
{

	string path ="C:\\Users\\1\\Desktop\\IMG_0433.JPG";
	//string path ="C:\\Users\\1\\Desktop\\IMG_3191.JPG";
	
	string temp = My_Sicret;
	ifstream filep(path, ios::binary);
	if (!filep) {
		cerr << "Failed to open file." << endl;
		return NULL;
	}
	// Read file content into a string
	string data((istreambuf_iterator<char>(filep)), istreambuf_iterator<char>());
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hashLen = 0;

	//do HMAC
	HMAC_CTX* HM = HMAC_CTX_new();
	HMAC_Init_ex(HM, temp.c_str(), temp.length(), EVP_sha256(), NULL);
	HMAC_Update(HM, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
	HMAC_Final(HM, hash, &hashLen);
	HMAC_CTX_free(HM);


	stringstream ss;
	for (unsigned int i = 0; i < hashLen; ++i) {
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	cout << "in hmac the key is: " << ss.str() << endl;
	return ss.str();
}
int main()
{
	
	string sss = makehmac();
	//cout << sss;
	//cout << makehmac();
	cout << IsEqual1(sss);

}



