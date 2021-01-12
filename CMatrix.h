#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <map>

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

	T* operator[] (int iM);
	T tGetValuFrom(int iM, int iN);
	bool bSetValueAt(int iM, int iN, T tNewValue);
	bool bIsSquareMatrix() { return iMSize == iNSize; };
	bool bSetIdentityMatrix();

	CMatrix<T>* cTColumnVector(int iCol);
	CMatrix<T>* cTRowVector(int iRow);

	int iGetIMSize() { return iMSize; };
	int iGetINSize() { return iNSize; };

	bool bRedMatrixFromFile(string sFileName);

	CMatrix<T>* ctTranspose();
	int iScalarProduct(CMatrix<T>& tMatrix);

	CMatrix<T> cAdd(const CMatrix<T>& cOther);
	CMatrix<T> operator+ (const CMatrix<T>& cOther);

	CMatrix<T> cSub(const CMatrix<T>& cOther);
	CMatrix<T> operator- (const CMatrix<T>& cOther);

	CMatrix<T> cMult(const T tVal);
	CMatrix<T> operator* (const T tVal);

	CMatrix<T> cMult(const CMatrix<T>& cOther);
	CMatrix<T> operator* (const CMatrix<T> &cOther);

private:
	T** tMatrix;
	int iMSize = -1;
	int iNSize = -1; 

	static void vFillDefMatrix(T** tMatrix, int iMSize, int iNSize);
	bool bCreateMatrixFromVector(vector<vector<T>> vTMatrix, int iN);
};

template<typename T>
inline CMatrix<T>::CMatrix()
{
	bCreateMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
}

template<typename T>
inline CMatrix<T>::CMatrix(int iMSize, int iNSize)
{
	bCreateMatrix(iMSize, iNSize);
}

template<typename T>
inline CMatrix<T>::CMatrix(string sFileName)
{
	if (!bRedMatrixFromFile(sFileName)) 
		bCreateMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
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
inline CMatrix<T>::CMatrix(CMatrix<T>&& cOther)
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
		vFillDefMatrix(tNewMatrix, iMSize, iNSize);
		
		if (tMatrix != NULL) {
			for (int i = 0; i < this->iMSize; i++)
				if (tMatrix[i] != NULL)
					delete[] tMatrix[i];
			delete[] tMatrix;
		}
	

		tMatrix = tNewMatrix;
		this->iMSize = iMSize;
		this->iNSize = iNSize;
		return true;
	}
	else {
		cout << "Wymiary macierzy musza byc wieksze od 0" << endl;
		return false;
	}
}



template<typename T>
inline T* CMatrix<T>::operator[](int iM)
{
	return tMatrix[iM];
}

template<typename T>
inline T CMatrix<T>::tGetValuFrom(int iM, int iN)
{
	if (iM < iMSize && iN < iNSize) {
		return tMatrix[iM][iN];
	}
	else {
		cout << "Wykroczono poza obszar tablicy" << endl;
		return NULL;
	}
}

template<typename T>
inline bool CMatrix<T>::bSetValueAt(int iM, int iN, T tNewValue)
{
	if (iM < iMSize && iN < iNSize) {
		tMatrix[iM][iN] = tNewValue;
		return true;
	}
	else {
		cout << "Wykroczono poza obszar tablicy" << endl;
		return false;
	}
}

template<typename T>
inline bool CMatrix<T>::bSetIdentityMatrix()
{
	if (bIsSquareMatrix()) {
		vFillDefMatrix(tMatrix, iMSize, iNSize);
		for (int i = 0; i < iMSize; i++)
			tMatrix[i][i] = 1;
		return true;
	}
	else {
		cout << "Macierz nie jest macierza kwadratowa." << endl;
		return false;
	}
}

template<typename T>
inline CMatrix<T>* CMatrix<T>::cTColumnVector(int iCol)
{
	CMatrix<T>* newTMatrix = new CMatrix<T>(1, iNSize);
	if (iCol < iNSize) {
		for (int i = 0; i < iMSize; i++)
			newTMatrix[0][i] = tMatrix[i][iCol];
	}
	else {
		cout << "Kolumna o podanym numerze nie istnieje" << endl;
	}
	return newTMatrix;
}

template<typename T>
inline CMatrix<T>* CMatrix<T>::cTRowVector(int iRow)
{
	CMatrix<T>* newTMatrix = new CMatrix<T>(1, iMSize);
	if (iRow < iMSize) {
		for (int i = 0; i < iNSize; i++)
			newTMatrix[0][i] = tMatrix[iRow][i];
	}
	else {
		cout << "Rzad o podanym numerze nie istnieje" << endl;
	}
	return newTMatrix;
}

template<typename T>
inline bool CMatrix<T>::bRedMatrixFromFile(string sFileName)
{
	ifstream file(sFileName.c_str() , ios_base::in);
	if (!file.is_open()) {
		cout << "Nie mozna odnalezc pliku." << endl;
		return false; 
	}
	else {
		vector<vector<T>> vTMatrix;
		map<int, int> mColLength;
		map<int, int>::iterator it;
		int iMaxNumOfCol=-1;
		int iNumOfCol;
		int length = 0;
		string line;
		vector<T> row;
		T data;

		while (getline(file, line)) {
			stringstream ss;
			ss << line;
			while (!ss.eof()) {
				ss >> data;
				row.push_back(data);
				length++;
			}
			vTMatrix.push_back(row);
			it = mColLength.find(length);
			if (it != mColLength.end()) mColLength[length] = it->second + 1;
			else mColLength.insert(pair<int,int>(length, 1));
			length = 0;
			row.clear();
		}
		file.close();
		for (it = mColLength.begin(); it != mColLength.end(); ++it) {
			cout << it->first <<" => " << it->second << endl;
			if (it->second > iMaxNumOfCol) {
				iMaxNumOfCol = it->second;
				iNumOfCol = it->first;
			}
		}
		return bCreateMatrixFromVector(vTMatrix, iNumOfCol);
	}
}

template<typename T>
inline CMatrix<T>* CMatrix<T>::ctTranspose()
{
	CMatrix<T>* tNewMatrix = new CMatrix<T>(iNSize, iMSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tNewMatrix->bSetValueAt(j, i, tMatrix[i][j]);
	return tNewMatrix;
}

template<typename T>
inline int CMatrix<T>::iScalarProduct(CMatrix<T>& tMatrix)
{
	double result = numeric_limits<double>::min();
	if (tMatrix.iGetIMSize() == 1 && iMSize == 1 && tMatrix.iGetINSize() == iNSize) {
		result = 0;
		for (int i = 0; i < iNSize; i++)
			result += tGetValuFrom(0, i) * tMatrix.tGetValuFrom(0, i);
	}
	else {
		cout << "Nie mozna wyliczc iloczynu sklaranego podanych wektorwo";
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
inline void CMatrix<T>::vFillDefMatrix(T** tMatrix, int iMSize, int iNSize)
{
	for (int i = 0; i < iMSize; i++) {
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = NULL;
	}
}

template<typename T>
inline bool CMatrix<T>::bCreateMatrixFromVector(vector<vector<T>> vTMatrix, int iN)
{
	if (bCreateMatrix(vTMatrix.size(), iN)) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < (vTMatrix[i].size() ? vTMatrix[i].size() : iNSize ); j++)
				tMatrix[i][j] = vTMatrix[i][j];
		return true;
	}
	else {
		return false;
	}
}


