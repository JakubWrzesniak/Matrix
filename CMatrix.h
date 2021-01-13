#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <map>
#include <limits>

using namespace std;

const static int DEFAULT_SIZE = 5; 

template <typename T>
class CMatrix
{
public:
	CMatrix();
	CMatrix(int iMSize, int iNSize);
	CMatrix(string sFileName);
	CMatrix(CMatrix<T>& cOther);
	CMatrix(CMatrix<T>&& cOther);
	~CMatrix();

	void vPrintMatrix();
	bool bCreateMatrix(int iMSize, int iNSize);
	void vFillDefMatrix(T tValue);	
	
	T tScalarProduct(CMatrix<T>& tMatrix);

	bool bIsSquareMatrix() { return iMSize == iNSize; };
	bool bSetIdentityMatrix();
	
	bool bRedMatrixFromFile(string sFileName);

	CMatrix<T> cTColumnVector(int iCol);
	CMatrix<T> cTRowVector(int iRow);
	CMatrix<T> ctTranspose();

	int iGetIMSize() { return iMSize; };
	int iGetINSize() { return iNSize; };

	bool bSetValueAt(int iM, int iN, T tNewValue);

	bool bCreateMatrixFromVector(vector<vector<T>> vTMatrix);
	bool operator = (const vector<vector<T>> vTMatrix);

	T tGetValuFrom(int iM, int iN);
	T* operator[] (int iM) { return tMatrix[iM]; };

	void operator = (const CMatrix<T>& cOther);

	CMatrix<T> cAdd(const CMatrix<T>& cOther);
	CMatrix<T> operator+ (const CMatrix<T>& cOther);
	void operator += (const CMatrix<T>& cOther);

	CMatrix<T> cSub(const CMatrix<T>& cOther);
	CMatrix<T> operator- (const CMatrix<T>& cOther);
	void operator -= (const CMatrix<T>& cOther);

	CMatrix<T> cMult(const T tVal);
	CMatrix<T> operator* (const T tVal);
	void operator *= (const T tVal);

	CMatrix<T> cMult(const CMatrix<T>& cOther);
	CMatrix<T> operator* (const CMatrix<T> &cOther);
	void operator*= (const CMatrix<T>& cOther);

private:
	T** tMatrix;
	int iMSize = -1;
	int iNSize = -1; 
};

template<typename T>
inline CMatrix<T>::CMatrix()
{
	if(bCreateMatrix(DEFAULT_SIZE, DEFAULT_SIZE))
	vFillDefMatrix(0);
}

template<typename T>
inline CMatrix<T>::CMatrix(int iMSize, int iNSize)
{
	if(bCreateMatrix(iMSize, iNSize))
	vFillDefMatrix(0);
}

template<typename T>
inline CMatrix<T>::CMatrix(string sFileName)
{
	if (!bRedMatrixFromFile(sFileName)) {
		bCreateMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
		vFillDefMatrix(0);
	}
		
}

template<typename T>
inline CMatrix<T>::CMatrix(CMatrix<T>& cOther)
{
	cout << "KOPIUJE!" << endl;
	iMSize = cOther.iMSize;
	iNSize = cOther.iNSize;
	tMatrix = new T * [iMSize];

	for (int i = 0; i < iMSize; i++)
		tMatrix[i] = new T[iNSize];
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = cOther.tGetValuFrom(i, j);
}

template<typename T>
inline  CMatrix<T>::CMatrix(CMatrix<T>&& cOther)
{
	cout << "PRZENOSZE" << endl;
	iMSize = cOther.iMSize;
	iNSize = cOther.iNSize;
	tMatrix = cOther.tMatrix;
	cOther.tMatrix = NULL;
}

template<typename T>
inline CMatrix<T>::~CMatrix()
{
	cout << "USUWAM" << endl;
	vPrintMatrix();
	if (tMatrix != NULL) {
		for (int i = 0; i < iMSize; i++)
			if(tMatrix[i] != NULL)
			delete[] tMatrix[i];
		delete tMatrix;
	}
	cout << "USUNIETE" << endl;
	
}

template<typename T>
inline void CMatrix<T>::vPrintMatrix()
{
	if(tMatrix != NULL)
	for (int i = 0; i < iMSize; i++) {
		cout << "| ";
		for (int j = 0; j < iNSize; j++)
			cout << tMatrix[i][j] << " ";
		cout << " |" << endl;
	}
}

template<typename T>
inline bool CMatrix<T>::bCreateMatrix(int iMSize, int iNSize)
{
	if (iMSize > 0 && iNSize > 0) {
		T** tNewMatrix = new T *[iMSize];

		for (int i = 0; i < iMSize; i++)
			tNewMatrix[i] = new T[iNSize];

		if (tMatrix != NULL) {
			for (int i = 0; i < this->iMSize; i++)
					delete[] tMatrix[i];
			delete[] tMatrix;
		}
	
		tMatrix = tNewMatrix;
		this->iMSize = iMSize;
		this->iNSize = iNSize;
		return true;
	}
	else 
		return false;
}

template<typename T>
inline void CMatrix<T>::operator=(const CMatrix<T>& cOther)
{
	if (bCreateMatrix(cOther.iMSize, cOther.iNSize))
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tMatrix[i][j] = cOther.tMatrix[i][j];
	else {
		bCreateMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
		vFillDefMatrix(0);
	}
}

template<typename T>
inline T CMatrix<T>::tGetValuFrom(int iM, int iN)
{
	return (iM < iMSize&& iN < iNSize) ? tMatrix[iM][iN] : std::numeric_limits<T>::quiet_NaN();
}

template<typename T>
inline bool CMatrix<T>::bSetValueAt(int iM, int iN, T tNewValue)
{
	if (iM < iMSize && iN < iNSize) {
		tMatrix[iM][iN] = tNewValue;
		return true;
	}
	else 
		return false;
}

template<typename T>
inline bool CMatrix<T>::bSetIdentityMatrix()
{
	if (bIsSquareMatrix()) {
		vFillDefMatrix(0);
		for (int i = 0; i < iMSize; i++)
			tMatrix[i][i] = 1;
		return true;
	}
	else 
		return false;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cTColumnVector(int iCol)
{
	CMatrix<T> newTMatrix(1, iNSize);
	if (iCol < iNSize) 
		for (int i = 0; i < iMSize; i++)
			newTMatrix[0][i] = tMatrix[i][iCol];
	
	return std::move(newTMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cTRowVector(int iRow)
{
	CMatrix<T> newTMatrix (1, iMSize);
	if (iRow < iMSize) 
		for (int i = 0; i < iNSize; i++)
			newTMatrix[0][i] = tMatrix[iRow][i];
	return newTMatrix;
}

template<typename T>
inline bool CMatrix<T>::bRedMatrixFromFile(string sFileName)
{
	vector<vector<T>> vTMatrix;
	ifstream file(sFileName.c_str() , ios_base::in);
	string blad;

	if (!file.is_open()) 
		return false; 
	else {
		string line;
		vector<T> row;
		T data;

		while (getline(file, line)) {
			istringstream ss(line);
			while (!ss.eof()) {
				ss >> data;
				if (ss.fail()) {
					ss.clear();
					ss >> blad;
					row.push_back(0);
				}
				else
					row.push_back(data);
			}
			vTMatrix.push_back(row);
			row.clear();
		}

		file.close();
		return bCreateMatrixFromVector(vTMatrix);
	}
}

template<typename T>
inline CMatrix<T> CMatrix<T>::ctTranspose()
{
	CMatrix<T> tNewMatrix(iNSize, iMSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tNewMatrix->bSetValueAt(j, i, tMatrix[i][j]);
	return std::move(tNewMatrix);
}

template<typename T>
inline T CMatrix<T>::tScalarProduct(CMatrix<T>& tMatrix)
{
	T result = std::numeric_limits<T>::quiet_NaN();
	if (tMatrix.iGetIMSize() == 1 && iMSize == 1 && tMatrix.iGetINSize() == iNSize) {
		result = 0;
		for (int i = 0; i < iNSize; i++)
			result += tGetValuFrom(0, i) * tMatrix.tGetValuFrom(0, i);
	}
	return result;
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cAdd(const CMatrix<T>& cOther)
{
	CMatrix<T> tNewMatrix(iMSize, iNSize);
	if (iMSize == cOther.iMSize && iNSize == cOther.iNSize)
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix.bSetValueAt(i, j, tMatrix[i][j] + cOther.tMatrix[i][j]);
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator+(const CMatrix<T>& cOther) {
	return cAdd(cOther);
}

template<typename T>
inline void CMatrix<T>::operator+=(const CMatrix<T>& cOther)
{
	if (iMSize == cOther.iMSize && iNSize == cOther.iNSize)
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				bSetValueAt(i, j, tMatrix[i][j] + cOther.tMatrix[i][j]);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cSub(const CMatrix<T>& cOther)
{
	CMatrix<T> tNewMatrix(iMSize, iNSize);
	if (iMSize == cOther.iMSize && iNSize == cOther.iNSize)
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix.bSetValueAt(i, j, tMatrix[i][j] - cOther.tMatrix[i][j]);
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator-(const CMatrix<T>& cOther)
{
	return cSub(cOther);
}

template<typename T>
inline void CMatrix<T>::operator-=(const CMatrix<T>& cOther)
{
	if (iMSize == cOther.iMSize && iNSize == cOther.iNSize)
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				bSetValueAt(i, j, tMatrix[i][j] - cOther.tMatrix[i][j]);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cMult(const T tVal)
{
	CMatrix<T> tNewMatrix(iMSize, iNSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tNewMatrix.bSetValueAt(i, j, tMatrix[i][j] * tVal);
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator*(const T tVal)
{
	return cMult(tVal);
}

template<typename T>
inline void CMatrix<T>::operator*=(const T tVal)
{
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			bSetValueAt(i, j, tMatrix[i][j] * tVal);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::cMult(const CMatrix<T>& cOther)
{
	CMatrix<T> tNewMatrix(iMSize, cOther.iNSize);
	if (iNSize == cOther.iMSize) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < cOther.iNSize; j++) {
				T s = 0;
				for (int k = 0; k < iNSize; k++)
					s += tMatrix[i][k] * cOther.tMatrix[i][j];
				tNewMatrix.bSetValueAt(i, j, s);
			}
	}
	return std::move(tNewMatrix);
}

template<typename T>
inline CMatrix<T> CMatrix<T>::operator*(const CMatrix<T>& cOther)
{
	return cMult(cOther);
}

template<typename T>
inline void CMatrix<T>::operator*=(const CMatrix<T>& cOther)
{
	if (iNSize == cOther.iMSize) {
		if (iNSize != cOther.iNSize);
		bCreateMatrix(iMSize, cOther.iNSize);
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < cOther.iNSize; j++) {
				T s = 0;
				for (int k = 0; k < iNSize; k++)
					s += tMatrix[i][k] * cOther.tMatrix[i][j];
				bSetValueAt(i, j, s);
			}
	}
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
inline bool CMatrix<T>::bCreateMatrixFromVector(vector<vector<T>> vTMatrix)
{
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

	for (it = mColLength.begin(); it != mColLength.end(); ++it) {
		cout << it->first << " => " << it->second << endl;
		if (it->second > iMaxNumOfCol) {
			iMaxNumOfCol = it->second;
			iNumOfCol = it->first;
		}
	}

	if (bCreateMatrix(vTMatrix.size(), iNumOfCol)) {
		vFillDefMatrix(0);
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < (vTMatrix[i].size()<iNSize ? vTMatrix[i].size() : iNSize ); j++)
				tMatrix[i][j] = vTMatrix[i][j];
		return true;
	}
	else 
		return false;
}

template<typename T>
inline bool CMatrix<T>::operator=(const vector<vector<T>> vTMatrix)
{
	return bCreateMatrixFromVector(vTMatrix);
}


