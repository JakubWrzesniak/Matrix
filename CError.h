#pragma once
#include <iostream>
#include <vector>
#include "Errors.h"
#include <string>
using namespace std;

class CErrorMatrix {
public:
	CErrorMatrix();
	int iGetErrorCode() { return iLastErrorCode; };
	void vSetErrorCode(int iError);
	string sErrorInfo() { return "ERROR CODE: " + to_string(iLastErrorCode); };
	vector<int> vGetErrorCodes() { return vErrorCodes; };
	void vClear();
private:
	int iLastErrorCode;
	vector<int> vErrorCodes;
	void vSetErrorCodes(int iErrorCode);
};