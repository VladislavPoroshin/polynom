// Polynom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Polynom.h"
int main()
{
	/*


	List A;
	Pair B = { 1,1 };
	Pair C = { 2,2 };
	A.PushBack(B);
	A.PushBack(C);
	//cout << A[0].Coef << endl;
	//A.Eraise(0);
	int size = A.size();
	for(int i=0; i<size; i++)
		cout << A[i].Coef << endl;
	//cout << A[0].Coef << endl;

	cout << endl;

	vector<Pair> W;
	W.push_back(C);
	W.push_back(B);
	sort(W.begin(), W.end());
	for (int i = 0; i < W.size(); i++)
		cout << W[i].Deg << endl;

	*/


	//string str = "x";
	//Polynom Test(str);

	//cout << Test << endl;

	//Polynom p1;
	//Polynom p2("x");
	//p1.parse("x");
	//cout << (p2 == p1) << endl;



	cout << "This program adds, subtracts and multiplies polynomials of the form f(x,y,z), where the degree of each argument is from 0 to 9. When adding a polynomial, do not use the << * >> sign, and the coefficient of the polynomial term must appear before all arguments. When entering a polynomial, make sure that it does not contain similar terms, an example of correct input:" << endl;
	cout << " 2x^2yz + 2xz - x^3 + 6" << endl;
	cout << "2x+z-6y-8" << endl;
	cout << "enter the first polynomial" << endl;
	Polynom Pol1;
	cin >> Pol1;
	cout << "enter the second polynomial" << endl;
	Polynom Pol2;
	cin >> Pol2;
	cout << "enter an operation for polynomials: << * >> or << + >> or << - >>" << endl;
	char op;
	cin >> op;
	if (op == '*') {
		Polynom Pol3 = Pol1 * Pol2;
		cout << "result: " << Pol3 << endl;
	}
	if (op == '+') {
		Polynom Pol3 = Pol1 + Pol2;
		cout << "result: " << Pol3 << endl;
	}
	if (op == '-') {
		Polynom Pol3 = Pol1 - Pol2;
		cout << "result: " << Pol3 << endl;
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
