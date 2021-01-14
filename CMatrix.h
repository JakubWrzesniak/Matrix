#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <map>
#include "CError.h"

#define DEFAULT_SIZE  5

using namespace std;

template <typename T>
class CMatrix
{
public:
	CMatrix();
	CMatrix(int iMSize, int iNSize);
	CMatrix(CMatrix<T>& cOther);
	CMatrix(CMatrix<T>&& cOther);
	~CMatrix();

	bool bCreateMatrix(int iMSize, int iNSize, CErrorMatrix* ccErrorCode); 
	void vFillDefMatrix(T tValue);	
	
	T tScalarProduct(CMatrix<T>& tMatrix, CErrorMatrix* cErrorCode);

	bool bIsSquareMatrix() { return iMSize == iNSize; };
	bool bSetIdentityMatrix(CErrorMatrix* cErrorCode);
	
	bool bReadMatrixFromFile(string sFileName, CErrorMatrix* cErrorCode);

	CMatrix<T> cTColumnVector(int iCol, CErrorMatrix* cErrorCode);
	CMatrix<T> cTRowVector(int iRow, CErrorMatrix* cErrorCode);
	
	int iGetIMSize() { return iMSize; };
	int iGetINSize() { return iNSize; };

	bool bSetValueAt(int iM, int iN, T tNewValue, CErrorMatrix* cErrorCode);

	bool bCreateMatrixFromVector(vector<vector<T>> vTMatrix, CErrorMatrix* cErrorCode);

	T tGetValuFrom(int iM, int iN, CErrorMatrix* cErrorCode);
	T* operator[] (int iM) ;
	CMatrix<T>& ctTranspose(CErrorMatrix* cErrorCode);
	void operator~();

	CMatrix<T>& operator= (const CMatrix<T>& cOther);
	void operator= (CMatrix<T>&& cOther);

	CMatrix<T> cAdd(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode);
	CMatrix<T> operator+ (const CMatrix<T>& cOther);
	CMatrix<T>& operator += (const CMatrix<T>& cOther);

	CMatrix<T> cSub(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode);
	CMatrix<T> operator- (const CMatrix<T>& cOther);
	CMatrix<T>& operator -= (const CMatrix<T>& cOther);

	CMatrix<T> cMult(const T tVal);
	CMatrix<T> operator* (const T tVal);
	CMatrix<T>& operator *= (const T tVal);

	CMatrix<T> cMult(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode);
	CMatrix<T> operator* (const CMatrix<T> &cOther);
	CMatrix<T>& operator*= (const CMatrix<T>& cOther);

	void vPrintMatrix() { cout << *this; };

	friend ostream& operator<< (ostream& os, const CMatrix<T>& cOther) 
	{
		if (cOther.tMatrix != NULL)
			for (int i = 0; i < cOther.iMSize; i++) {
				os << "| ";
				for (int j = 0; j < cOther.iNSize; j++)
					os << cOther.tMatrix[i][j] << " ";
				os << " |" << endl;
			}
		return os;
	}


private:
	T** tMatrix;
	int iMSize;
	int iNSize; 

	void vDeleteMatrix();
	void vCopy(T** tOther);
	bool vInitialMatrix(int iMSize, int iNSize);
};

template<typename T>
inline CMatrix<T>::CMatrix()
{
	vInitialMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
	vFillDefMatrix(0);
}

template<typename T>
inline CMatrix<T>::CMatrix(int iMSize, int iNSize)
{
	if (!vInitialMatrix(iMSize, iNSize))
		vInitialMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
	vFillDefMatrix(0);
}

template<typename T>
inline CMatrix<T>::CMatrix(CMatrix<T>& cOther)
{
	vDeleteMatrix();
	if (cOther.iMSize > 0 && cOther.iNSize > 0) {
		iMSize = cOther.iMSize;
		iNSize = cOther.iNSize;
		vCopy(cOther.tMatrix);
	}
	else
		vInitialMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
	
}

template<typename T>
inline  CMatrix<T>::CMatrix(CMatrix<T>&& cOther)
{
	iMSize = cOther.iMSize;
	iNSize = cOther.iNSize;
	tMatrix = cOther.tMatrix;
	cOther.tMatrix = NULL;
}

template<typename T>
inline CMatrix<T>::~CMatrix()
{
	vDeleteMatrix();
}

template<typename T>
inline void CMatrix<T>::vDeleteMatrix()
{
	if (tMatrix != NULL) {
		for (int i = 0; i < iMSize; i++)
			if (tMatrix[i] != NULL)
				delete[] tMatrix[i];
		delete[] tMatrix;
	}
}

template<typename T>
inline void CMatrix<T>::vCopy(T** tOther)
{
	tMatrix = new T * [iMSize];
	for (int i = 0; i < iMSize; i++)
		tMatrix[i] = new T[iNSize];
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = tOther[i][j];
}

template<typename T>
inline bool CMatrix<T>::vInitialMatrix(int iMSize, int iNSize)
{
	if (iMSize > 0 && iNSize > 0) {
		tMatrix = new T * [iMSize];
		for (int i = 0; i < iMSize; i++)
			tMatrix[i] = new T[iNSize];
		this->iMSize = iMSize;
		this->iNSize = iNSize;
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
inline bool CMatrix<T>::bCreateMatrix(int iMSize, int iNSize, CErrorMatrix* cErrorCode)
{
	bool flag = false;
	if (iMSize <= 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iNSize <= 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_N_SIZE); flag = true; }
	if (!flag){
		vDeleteMatrix();
		if(vInitialMatrix(iMSize, iNSize))
			vFillDefMatrix(0);
		return true;
	}
	return false;
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::operator=(const CMatrix<T>& cOther)
{
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	if (bCreateMatrix(cOther.iMSize, cOther.iNSize,cErrorCode))
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tMatrix[i][j] = cOther.tMatrix[i][j];
	if(cErrorCode->iGetErrorCode() != 0) throw std::invalid_argument(cErrorCode->sErrorInfo());
	return *this;
}

template<typename T>
inline void CMatrix<T>::operator=(CMatrix<T>&& cOther)
{
	iMSize = cOther.iMSize;
	iNSize = cOther.iNSize;
	tMatrix = cOther.tMatrix;
	cOther.tMatrix = NULL;
}

template<typename T>
inline T CMatrix<T>::tGetValuFrom(int iM, int iN, CErrorMatrix* cErrorCode)
{
	bool flag = false;
	if (iM < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iN < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_N_SIZE); flag = true; }
	if (iM >= iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iN >= iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	return (!flag) ? tMatrix[iM][iN] : std::numeric_limits<T>::quiet_NaN();
}

template<typename T>
inline T* CMatrix<T>::operator[](int iM)
{
	if (iM < 0) throw std::invalid_argument("ERROR CODE:" + to_string(INVALID_ARGUMENT));
	if (iM >= iMSize) throw std::out_of_range("ERROR CODE:" + to_string(INCORRECT_SIZE));
	return tMatrix[iM];
}

template<typename T>
inline bool CMatrix<T>::bSetValueAt(int iM, int iN, T tNewValue, CErrorMatrix* cErrorCode)
{
	bool flag = false;
	if (iM < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iN < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_N_SIZE); flag = true; }
	if (iM >= iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iN >= iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if(!flag) {
		tMatrix[iM][iN] = tNewValue;
		return true;
	}
		return false;
}

template<typename T>
inline bool CMatrix<T>::bSetIdentityMatrix(CErrorMatrix* cErrorCode)
{
	if (!bIsSquareMatrix()) cErrorCode->vSetErrorCode(INVALID_ARGUMENT);
	else
	{
		vFillDefMatrix(0);
		for (int i = 0; i < iMSize; i++)
			tMatrix[i][i] = 1;
		return true;
	}
		return false;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cTColumnVector(int iCol, CErrorMatrix* cErrorCode)
{
	CMatrix<T> newTMatrix(1, iMSize);
	bool flag = false;
	if (iCol < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT); flag = true; }
	if (iCol >= iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE); flag = true; }
	if(!flag)
		for (int i = 0; i < iMSize; i++)
			newTMatrix[0][i] = tMatrix[i][iCol];
	return std::move(newTMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cTRowVector(int iRow, CErrorMatrix* cErrorCode)
{
	CMatrix<T> newTMatrix(1, iNSize);
	bool flag = false;
	if (iRow < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT); flag = true; }
	if (iRow >= iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE); flag = true; }
	if(!flag)
		for (int i = 0; i < iNSize; i++)
			newTMatrix[0][i] = tMatrix[iRow][i];
	return std::move(newTMatrix);
}

template<typename T>
inline bool CMatrix<T>::bReadMatrixFromFile(string sFileName, CErrorMatrix* cErrorCode)
{
	vector<vector<T>> vTMatrix;
	ifstream file(sFileName.c_str(), ios_base::in);

	if (!file.is_open()) {
		cErrorCode->vSetErrorCode(INVALID_FILE_NAME);
		return false;
	}
	else {
		string line;
		vector<T> row;
		T data;
		string blad;
		while (getline(file, line)) {
			istringstream ss(line);
			while (!ss.eof()) {
				ss >> data;
				if (ss.fail()) {
					ss.clear();
					ss >> blad;
					cErrorCode->vSetErrorCode(INCORRECT_VALUE);
					if(blad[0] != '.')
						row.push_back(0);
				}
				else
					row.push_back(data);
			}
			vTMatrix.push_back(row);
			row.clear();
		}
		file.close();
		return bCreateMatrixFromVector(vTMatrix, cErrorCode);
	}
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::ctTranspose(CErrorMatrix* cErrorCode)
{
	bool flag = false;
	if (iMSize < 0) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iNSize < 0) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		CMatrix<T> tNewMatrix(iNSize, iMSize);
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix.tMatrix[j][i] = tMatrix[i][j];
		*this = std::move(tNewMatrix);
	}
	return *this;
}

template<typename T>
inline void CMatrix<T>::operator~()
{
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	ctTranspose(cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw std::logic_error(cErrorCode->sErrorInfo());
	delete cErrorCode;
}

template<typename T>
inline T CMatrix<T>::tScalarProduct(CMatrix<T>& tMatrix, CErrorMatrix* cErrorCode)
{
	T result = std::numeric_limits<T>::quiet_NaN();
	bool flag = false;
	if (tMatrix.iGetIMSize() != 1) {cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true;}
	if (iMSize != 1) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (tMatrix.iGetINSize() != iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if(!flag) {
		result = 0;
		for (int i = 0; i < iNSize; i++)
			result += tGetValuFrom(0, i, cErrorCode) * tMatrix.tGetValuFrom(0, i, cErrorCode);
	}
	return result;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cAdd(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode)
{
	CMatrix<T> tNewMatrix(iMSize, iNSize);
	bool flag = false;
	if (iMSize != cOther.iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iNSize != cOther.iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix.tMatrix[i][j] = tMatrix[i][j] + cOther.tMatrix[i][j], cErrorCode;
	}
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator+(const CMatrix<T>& cOther) {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tNewMatrix = cAdd(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw std::invalid_argument(cErrorCode->sErrorInfo());
	delete cErrorCode;
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::operator+=(const CMatrix<T>& cOther)
{
	if (iMSize != cOther.iMSize) throw std::invalid_argument("ERROR CODE: " + to_string(INCORRECT_SIZE_M));
	if (iNSize != cOther.iNSize) throw std::invalid_argument("ERROR CODE: " + to_string(INCORRECT_SIZE_N));
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = tMatrix[i][j] + cOther.tMatrix[i][j];
	return *this;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cSub(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode)
{
	CMatrix<T> tNewMatrix(iMSize, iNSize);
	bool flag = false;
	if (iMSize != cOther.iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iNSize != cOther.iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if(!flag) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix.tMatrix[i][j] = tMatrix[i][j] - cOther.tMatrix[i][j];
	}
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator-(const CMatrix<T>& cOther)
{
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tNewMatrix = cSub(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw std::invalid_argument(cErrorCode->sErrorInfo());
	delete cErrorCode;
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::operator-=(const CMatrix<T>& cOther)
{
	if (iMSize != cOther.iMSize) throw std::invalid_argument("ERROR CODE: " + to_string(INVALID_ARGUMENT_M_SIZE));
	if (iNSize != cOther.iNSize) throw std::invalid_argument("ERROR CODE: " + to_string(INVALID_ARGUMENT_N_SIZE));
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tMatrix[i][j] = tMatrix[i][j] - cOther.tMatrix[i][j];
	return *this;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cMult(const T tVal)
{
	CMatrix<T> tNewMatrix(iMSize, iNSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tNewMatrix.tMatrix[i][j] = tMatrix[i][j] * tVal;
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator*(const T tVal)
{
	return cMult(tVal);
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::operator*=(const T tVal)
{
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = tMatrix[i][j] * tVal;
	return *this;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cMult(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode)
{
	CMatrix<T> tNewMatrix(iMSize, cOther.iNSize);
	if (iNSize != cOther.iMSize) cErrorCode->vSetErrorCode(INCORRECT_SIZE_MULTIPLAYING);
	else{
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < cOther.iNSize; j++) {
				T s = 0;
				for (int k = 0; k < iNSize; k++)
					s += tMatrix[i][k] * cOther.tMatrix[i][j];
				tNewMatrix.tMatrix[i][j] = s;
			}
	}
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator*(const CMatrix<T>& cOther)
{
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tNewMatrix = cMult(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw std::invalid_argument(cErrorCode->sErrorInfo());
	delete cErrorCode;
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::operator*=(const CMatrix<T>& cOther)
{
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tNewMatrix = cMult(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw std::invalid_argument(cErrorCode->sErrorInfo());
	*this = std::move(tNewMatrix);
	delete cErrorCode;
	return *this;
}

template<typename T>
inline void CMatrix<T>::vFillDefMatrix(T iValue)
{
	for (int i = 0; i < iMSize; i++) {
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = iValue;
	}
}

template<typename T>
inline bool CMatrix<T>::bCreateMatrixFromVector(vector<vector<T>> vTMatrix, CErrorMatrix* cErrorCode)
{
	if (vTMatrix.size() > 0) {
		map<int, int> mColLength;
		map<int, int>::iterator it;

		int iMaxNumOfCol = -1;
		int iNumOfCol;
		int length = 0;

		for (int i = 0; i < vTMatrix.size(); i++) {
			length = vTMatrix[i].size();
			it = mColLength.find(length);
			if (it != mColLength.end()) mColLength[length] = it->second + 1;
			else mColLength.insert(pair<int, int>(length, 1));
		}

		if (mColLength.size() != 1) cErrorCode->vSetErrorCode(INCORRECT_ROW_LENGTH);

		for (it = mColLength.begin(); it != mColLength.end(); ++it) {
			if (it->second > iMaxNumOfCol) {
				iMaxNumOfCol = it->second;
				iNumOfCol = it->first;
			}
		}

		if (bCreateMatrix(vTMatrix.size(), iNumOfCol, cErrorCode)) {
			vFillDefMatrix(0);
			for (int i = 0; i < iMSize; i++)
				for (int j = 0; j < (vTMatrix[i].size() < iNSize ? vTMatrix[i].size() : iNSize); j++)
					tMatrix[i][j] = vTMatrix[i][j];
			return true;
		}
	}
	else {
		cErrorCode->vSetErrorCode(INCORRECT_VECTOR_SIZE);
		return false;
	}
}


