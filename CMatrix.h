#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
using namespace std;

template <typename T>
class CMatrix
{
public:
	CMatrix();
	CMatrix(int iMSize, int iNSize);
	//CMatrix(CMatrix tMatrix);
	~CMatrix();

	void vPrintMatrix();
	bool bCreateMatrix(int iMSize, int iNSize);

	T tGetValuFrom(int iM, int iN);
	bool bSetValueAt(int iM, int iN, T tNewValue);
	bool bIsSquareMatrix() { return iMSize == iNSize; };
	bool bSetIdentityMatrix();

	int iGetIMSize() { return iMSize; };
	int iGetINSize() { return iNSize; };

	bool bRedMatrixFromFilme(string sfile);

	CMatrix<T>* ctTranspose();
	int iScalarProduct(CMatrix<T>& tMatrix);

	CMatrix<T>* operator+ (CMatrix<T> &tMatrix);
	CMatrix<T>* operator- (CMatrix<T> &tMatrix);

	CMatrix<T>* operator* (int sC);
	template <typename S>
	CMatrix<S>* operator* (S sC);

	CMatrix<T>* operator* (CMatrix<int> &iMatrix);
	template <typename S>
	CMatrix<S>* operator* (CMatrix<S> &sMatrix);
private:
	T** tMatrix;
	int iMSize = 5;
	int iNSize = 5; 

	static void vFillDefMatrix(T** tMatrix, int iMSize, int iNSize);
};

template<typename T>
inline CMatrix<T>::CMatrix()
{
	tMatrix = new T* [iMSize];
	for (int i = 0; i < iMSize; i++)
		tMatrix[i] = new T[iNSize];
	vFillDefMatrix();
}

template<typename T>
inline CMatrix<T>::CMatrix(int iMSize, int iNSize)
{
	if (iMSize > 0 && iNSize > 0) {
		this->iMSize = iMSize;
		this->iNSize = iNSize;
	}
	else 
		cout << "Wymiary macierzy musza byc wieksze od 0" << endl;
	
	tMatrix = new T *[iMSize];
	
	for (int i = 0; i < iMSize; i++)
		tMatrix[i] = new T[iNSize];

	vFillDefMatrix(tMatrix, iMSize, iNSize);
}

template<typename T>
inline CMatrix<T>::~CMatrix()
{
	for (int i = 0; i < iMSize; i++) 
		delete[] tMatrix[i];
	delete tMatrix;
	
}

template<typename T>
inline void CMatrix<T>::vPrintMatrix()
{
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
		
		for (int i = 0; i < (this->iMSize > iMSize ? iMSize : this->iMSize ); i++) {
			for (int j = 0; j < (this->iNSize > iNSize ? iNSize : this->iNSize); j++) {
				tNewMatrix[i][j] = tMatrix[i][j];
			}
		}
		
		for (int i = 0; i < this->iMSize; i++)
			delete[] tMatrix[i];
		delete[] tMatrix;

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
inline bool CMatrix<T>::bRedMatrixFromFilme(string sFile)
{
	double num;
	vector<vector<double>> lines;
	ifstream file(sFile.c_str() , ios_base::in);
	if (!file.is_open()) {
		cout << "Nie mozna odnalezc pliku." << endl;
		return false; 
	}
	else {
		string line;
		vector<double> row;
		while (getline(file, line)) {
			stringstream ss;
			ss << line;
			double found;
			while (!ss.eof()) {
				ss >> found;
				row.push_back(found);
			}
			lines.push_back(row);
			row.clear();
		}
		file.close();
		return true;
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
inline CMatrix<T>* CMatrix<T>::operator+(CMatrix<T>& tMatrix)
{
	if (iMSize == tMatrix.iMSize && iNSize == tMatrix.iNSize) {
		CMatrix<T>* tNewMatrix = new CMatrix<T>(iMSize, iNSize);
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix->bSetValueAt(i, j, this->tMatrix[i][j] + tMatrix.tGetValuFrom(i, j));
		return tNewMatrix;
	}
	return this;
}

template<typename T>
inline CMatrix<T>* CMatrix<T>::operator-(CMatrix<T>& tMatrix)
{
	if (iMSize == tMatrix.iMSize && iNSize == tMatrix.iNSize) {
		CMatrix<T>* tNewMatrix = new CMatrix<T>(iMSize, iNSize);
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tNewMatrix->bSetValueAt(i, j, this->tMatrix[i][j] - tMatrix.tGetValuFrom(i, j));
		return tNewMatrix;
	}
	return this;
}

template<typename T>
inline CMatrix<T>* CMatrix<T>::operator*(int sC)
{
	CMatrix<T>* tNewMatrix = new CMatrix<T>(iMSize, iNSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tNewMatrix->bSetValueAt(i, j, tMatrix[i][j] * sC);
	return tNewMatrix;
}

template<typename T>
inline CMatrix<T>* CMatrix<T>::operator*(CMatrix<int> &iMatrix)
{
	if (iNSize == iMatrix.iGetIMSize()) {
		CMatrix<T> *tNewMatrix = new CMatrix<T>(iMSize, iMatrix.iGetINSize());
		for(int i = 0; i < iMSize ; i++)
			for (int j = 0; j < iMatrix.iGetINSize(); j++) {
				T s = 0;
				for (int k = 0 ;k < iNSize; k++)
					s += tMatrix[i][k] * iMatrix.tGetValuFrom(k,j);
				tNewMatrix->bSetValueAt(i,j,s);
			}
		return tNewMatrix;
	}
	else {
		cout << "Nie mozna pomnozyc podanych macierzy." << endl;
		return new CMatrix<T>(iMSize, iNSize);
	}
}

template<typename T>
template<typename S>
inline CMatrix<S>* CMatrix<T>::operator*(S sC)
{
	CMatrix<S>* tNewMatrix = new CMatrix<S>(iMSize, iNSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tNewMatrix->bSetValueAt(i, j, tMatrix[i][j] * sC);
	return tNewMatrix;
}

template<typename T>
template<typename S>
inline CMatrix<S>* CMatrix<T>::operator*(CMatrix<S> &sMatrix)
{
	CMatrix<S>* tNewMatrix = new CMatrix<S>(iMSize, sMatrix.iGetINSize());
	if (iNSize == sMatrix.iGetIMSize()) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < sMatrix.iGetINSize(); j++) {
				S s = 0;
				for (int k = 0; k < iNSize; k++)
					s += tMatrix[i][k] * sMatrix.tGetValuFrom(k, j);
				tNewMatrix->bSetValueAt(i, j, s);
			}
	}
	else {
		cout << "Nie mozna pomnozyc podanych macierzy." << endl;
	}
	return tNewMatrix;
}

template<typename T>
inline void CMatrix<T>::vFillDefMatrix(T** tMatrix, int iMSize, int iNSize)
{
	for (int i = 0; i < iMSize; i++) {
		for (int j = 0; j < iNSize; j++)
			tMatrix[i][j] = NULL;
	}
}


