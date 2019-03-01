#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <time.h>
using namespace std;
#pragma warning(disable:4996) 
class LC {
public: LC() { system("chcp 1251 > nul"); }
		~LC() { cin.get(); cin.get(); }
}l;
/*Создайте шаблонный класс матрица.
Необходимо реализовать динамическое выделение памяти, очистку памяти, 
заполнение матрицы с клавиатуры, заполнение случайными значениями,
отображение матрицы, арифметические операции с помощью перегруженных операторов (+, -, *, /), 
поиск максимального и минимального элемента.
*/

template <class T>
class Matrix {
	T ** mas;
	int col, row;
public:
	Matrix() : mas(), row(), col() {}
	Matrix(T ** mas, int Col, int Row) :Matrix() {
		SetMatrix(mas, Col, Row);
	}
	Matrix(int Col, int Row) : Matrix() {
		SetSize(Col, Row);
	}
	Matrix(Matrix &M) : Matrix(M.mas, M.col, M.row) {}
	Matrix(Matrix &&M) {//Верно для двумерного массива действия ниже?
		mas = M.mas;
		row = M.row;
		col = M.col;
		M.mas = nullptr;
		M.row = M.col = 0;
	}
	~Matrix() {
		if (mas) {
			for (int i = 0; i < col; i++) {
				delete[]mas[i];
			}
			delete[]mas;
		}
	}
	void SetMatrix(T ** Mas, int Col, int Row) {
		if (mas) {
			for (int i = 0; i < col; i++) {
				delete[]mas[i];
			}
			delete[]mas;
		}
		mas = new T*[Col];
		for (int i = 0; i < Col; i++) {
			mas[i] = new T[Row];
		}
		for (int i = 0; i < Col; i++) {
			for (int j = 0; j < Row; j++) {
				mas[i][j] = Mas[i][j];
			}
		}
		col = Col;
		row = Row;
	}
	void SetSize(int Col, int Row) {

		if (col != Col&&row == Row) {
			SetCol(Col);
		}
		else if (col == Col&&row != Row) {
			SetRow(Row);
		}
		else if (col != Col&&row != Row) {
			SetCol(Col);
			SetRow(Row);
		}
	}
	void InitMatrix() {
		if (mas) {
			cout << "Заполняйте массив: ";
			for (int i = 0; i < col; i++) {
				for (int j = 0; j < row; j++) {
					cin >> mas[i][j];
				}
			}
		}
	}
	void InitMatrixRand() {
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				mas[i][j] = rand() % 15 + 1;
			}
		}
	}
	void PrintMatrix()const {
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {

				cout << fixed << setw(8) << setprecision(3) << mas[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	T** GetMas() const {
		return mas;
	}
	int GetCol()const {
		return col;
	}
	int GetRow()const {
		return row;
	}
	Matrix operator+(const Matrix &M) {
		Matrix<T>temp(mas, col, row);
		if (row == M.row&&col == M.col) {

			for (int i = 0; i < col; i++) {
				for (int j = 0; j < row; j++) {
					temp.mas[i][j] += M.mas[i][j];
				}
			}
		}
		return temp;
	}
	Matrix operator-(const Matrix &M) {
		Matrix<T>temp(mas, col, row);
		if (row == M.row&&col == M.col) {

			for (int i = 0; i < col; i++) {
				for (int j = 0; j < row; j++) {
					temp.mas[i][j] -= M.mas[i][j];
				}
			}
		}
		return temp;
	}
	Matrix operator*(const Matrix &M) {
		Matrix temp(col, M.row);
		if (row == M.col) {
			for (int k = 0; k < col; k++) {
				for (int i = 0; i < M.row; i++) {
					for (int j = 0; j < row; j++) {
						temp.mas[k][i] += M.mas[j][i] * mas[k][j];
					}
				}
			}
		}
		return temp;
	}
	Matrix operator*(double num) {
		Matrix temp(mas, col, row);

		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				temp.mas[i][j] *= num;
			}
		}
		return temp;
	}
	template <typename t>
	Matrix & operator=(const Matrix <t> &M) {

		if (mas) {
			for (int i = 0; i < col; i++) {
				delete[]mas[i];
			}
			delete[]mas;
		}
		mas = new T*[M.GetCol()];
		for (int i = 0; i < M.GetCol(); i++) {
			mas[i] = new T[M.GetRow()];
		}
		for (int i = 0; i < M.GetCol(); i++) {
			for (int j = 0; j < M.GetRow(); j++) {
				mas[i][j] = M.GetMas()[i][j];
			}
		}
		col = M.GetCol();
		row = M.GetRow();
		return *this;
	}
	Matrix & operator=(const Matrix &M) {

		if (this != &M) {
			SetMatrix(M.mas, M.col, M.row);
		}
		return *this;
	}
	Matrix operator/(Matrix & M);
protected:
	void SetCol(int Col) {
		T ** temp = new T*[Col];
		for (int i = 0; i < Col; i++) {
			temp[i] = new T[row];
		}
		if (mas) {
			int copy;
			(col > Col) ? copy = Col : copy = col;
			for (int i = 0; i < copy; i++) {
				for (int j = 0; j < row; j++) {
					temp[i][j] = mas[i][j];
				}
			}
			for (int i = 0; i < col; i++) {
				delete[]mas[i];
			}
			delete[]mas;
		}
		for (int i = col; i < Col; i++) {
			for (int j = 0; j < row; j++) {
				temp[i][j] = 0;
			}
		}
		mas = temp;
		col = Col;
	}
	void SetRow(int Row) {
		T ** temp = new T*[col];
		for (int i = 0; i < col; i++) {
			temp[i] = new T[Row];
		}
		if (mas) {
			int copy;
			(row > Row) ? copy = Row : copy = row;
			for (int i = 0; i < col; i++) {
				for (int j = 0; j < copy; j++) {
					temp[i][j] = mas[i][j];
				}
			}
			for (int i = 0; i < col; i++) {
				delete[]mas[i];
			}
			delete[]mas;
		}
		for (int i = 0; i < col; i++) {
			for (int j = row; j < Row; j++) {
				temp[i][j] = 0;
			}
		}
		mas = temp;
		row = Row;
	}
};

template <class T>
Matrix<T>Matrix<T>::operator/(Matrix & Mtemp) {
	Matrix<long double>M(Mtemp);
	Matrix<long double>temp;
	if (M.GetCol() == row) {
		if (M.GetCol() == M.GetRow() && M.GetCol() == 2) {
			temp.SetSize(2, 2);
			temp.GetMas()[0][0] = M.GetMas()[1][1];
			temp.GetMas()[0][1] = -1 * M.GetMas()[0][1];
			temp.GetMas()[1][0] = -1 * M.GetMas()[1][0];
			temp.GetMas()[1][1] = M.GetMas()[0][0];
			double det = 1.0 / (M.GetMas()[0][0] * M.GetMas()[1][1] - M.GetMas()[0][1] * M.GetMas()[1][0]);
			temp = temp*det;
		}
		else {
			temp.SetSize(M.col, M.row);

			for (int i = 0; i < M.col; i++) { //Единичная матрица
				for (int j = 0; j < M.row; j++) {
					temp.mas[i][j] = (i == j) ? 1 : 0;
				}
			}
			for (int i = 0; i < M.row; i++) { // Прямой ход
				for (int j = i + 1; j < M.col; j++) {
					if (M.mas[j][i] != 0) {
						double m = M.mas[i][i];
						double n = M.mas[j][i];
						for (int k = 0; k < M.row; k++) {
							M.mas[i][k] *= n;
							M.mas[j][k] *= m;
							M.mas[j][k] -= M.mas[i][k];
							temp.mas[i][k] *= n;
							temp.mas[j][k] *= m;
							temp.mas[j][k] -= temp.mas[i][k];
							M.mas[i][k] /= n;
							M.mas[j][k] /= m;
							temp.mas[i][k] /= n;
							temp.mas[j][k] /= m;
						}
					}
				}
			}
			for (int i = M.row - 1; i >= 0; i--) { //Обратный ход
				for (int j = i - 1; j >= 0; j--) {
					if (M.mas[j][i] != 0) {
						double m = M.mas[i][i];
						double n = M.mas[j][i];
						for (int k = M.row - 1; k >= 0; k--) {
							M.mas[i][k] *= n;
							M.mas[j][k] *= m;
							M.mas[j][k] -= M.mas[i][k];
							temp.mas[i][k] *= n;
							temp.mas[j][k] *= m;
							temp.mas[j][k] -= temp.mas[i][k];
							M.mas[i][k] /= n;
							M.mas[j][k] /= m;
							temp.mas[i][k] /= n;
							temp.mas[j][k] /= m;
						}
					}
				}
			}
			for (int i = 0; i < M.col; i++) {
				for (int j = 0; j < M.row; j++) {
					temp.mas[i][j] /= M.mas[i][i];
				}
			}

			// Тест:			
			temp.PrintMatrix();
			cout << "2 - Проверка: Обратная матрица * Исходная матрица =  " << endl;
			(Mtemp * temp).PrintMatrix();

		}
	}
	return (*this)*temp;
}

int main() {
	 
	srand(time(0));

	Matrix<long double>A(3, 3);
	Matrix<long double>B;
	Matrix<long double> C;
	//Иницализация матрицы рандомными числами
	A.InitMatrixRand();
	cout << "Матрица А:" << endl;
	//Вывод матрицы на экран
	A.PrintMatrix();
	//Задаю размер для второй матрицы
	B.SetSize(3, 3);
	//Инициализирую матрицу
	B.InitMatrixRand();
	cout << "Матрица B:" << endl;
	//Вывод матрицы на экран
	B.PrintMatrix();
	//Деление матрицы:	
	//В теории матрицы делить нельзя. Операция деления заменяется операцией умножения одной матрица на матрицу, 
	//которая обратна второй матрице.
	//Для того чтобы проверить правильно ли найдена обратная матрица нужно умножить найденную обратную матрицу на исходную
	//в результате чего мы должны получить единичную матрицу. 
	//Единичная матрица в нашем случае будет выглядить так: 1 0 0
	//													    0 1 0
	//                                                      0 0 1
	cout << "A/B:" << endl;
	cout << "1 - Находим обратную матрицу второго операнда(матрица B):"<<endl;
	C = A / B;
	cout << "3 - Результат вычисления: " << endl;
	C.PrintMatrix();

	return 0;
}