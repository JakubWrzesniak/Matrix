#pragma once
#include "CError.h"

CErrorMatrix::CErrorMatrix()
{
	iLastErrorCode = NO_ERROR; 
}

void CErrorMatrix::vSetErrorCode(int iError)
{
	if (iLastErrorCode != NO_ERROR)
		vSetErrorCodes(iLastErrorCode);
	iLastErrorCode = iError;
}

void CErrorMatrix::vClear()
{
	iLastErrorCode = NO_ERROR;
	vErrorCodes.clear();
}

void CErrorMatrix::vSetErrorCodes(int iErrorCode)
{
	vErrorCodes.push_back(iErrorCode);
}
