#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Pair {
	int Coef;
	int Deg;
	friend auto operator<(const Pair& a, const Pair& b)
	{
		return a.Deg < b.Deg;
	}
	friend auto operator<=(const Pair& a, const Pair& b)
	{
		return a.Deg <= b.Deg;
	}
	friend auto operator>=(const Pair& a, const Pair& b)
	{
		return a.Deg >= b.Deg;
	}
	friend auto operator>(const Pair& a, const Pair& b)
	{
		return a.Deg > b.Deg;
	}
	friend bool operator==(const Pair& a, const Pair& b)
	{
		if ((a.Deg == b.Deg) && (a.Coef == b.Coef))
			return(true);
		else
			return(false);
	}
};

class List {

	struct Node
	{
		Pair Duo;
		Node* pNext;
		friend bool operator==(const Node& a, const Node& b)
		{
			if ((a.Duo == b.Duo) && (a.pNext == b.pNext) && (a.pNext == nullptr))
				return(true);
			if ((a.Duo == b.Duo) && (a.pNext->Duo == b.pNext->Duo))
				return(true);
			else
				return(false);
		}
	};

	Node* pFirst;
	size_t sz;

	class ListIterator {
		friend class List;
	public:
		typedef Node iterator_type;
		typedef input_iterator_tag iterator_category;
		typedef iterator_type iterator_value;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

	private:
		iterator_type* value;
	public:
		ListIterator(Node* p) : value(p) {}
		ListIterator(ListIterator& it) : value(it.value) {}
		ListIterator(const ListIterator& it) : value(it.value) {}
		typename ListIterator::reference operator*() {
			return(*value);
		}
		ListIterator& operator++() {
			if (value->pNext == nullptr)
				value = nullptr;
			else
				value = value->pNext;
			return(*this);
		}
		bool operator!=(ListIterator const& other) {
			return(value != other.value);
		}
		bool operator==(ListIterator const& other) {
			return(!(value != other.value));
		}
	};

public:
	List() {
		pFirst = new Node;
		pFirst->Duo.Coef = 0;
		pFirst->Duo.Deg = -100;
		pFirst->pNext = nullptr;
		sz = 1;
	}
	~List() {
		Node* p;
		while (pFirst->pNext != nullptr)
		{
			p = pFirst;
			pFirst = pFirst->pNext;
			delete p;
		}
		delete pFirst;
	}
	List(const List& A) {
		pFirst = A.pFirst;
		sz = A.sz;
		Node* pNew = pFirst = new Node{ *A.pFirst };
		for (; pNew->pNext != nullptr; pNew = pNew->pNext)
			pNew->pNext = new Node{ *pNew->pNext };
	}
	size_t size() {
		return(sz);
	}
	Pair& Front() {
		return(pFirst->Duo);
	}
	void PopFront() {
		if (sz > 1) {
			Node* p = pFirst;
			pFirst = pFirst->pNext;
			delete p;
			sz--;
		}
	}
	void PushFront(Pair& Duo) {
		Node* node = new Node{ Duo, pFirst };
		pFirst = node;
		sz++;
	}
	void PushBack(Pair& Duo) {
		Node* node = new Node{ Duo, nullptr };
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if ((*it).pNext == nullptr) {
				(*it).pNext = node;
				sz++;
				break;
			}
		}
	}
	typedef ListIterator iterator;
	iterator begin() {
		return(iterator(pFirst));
	}
	iterator end() {
		return(iterator(nullptr));
	}
	List& operator=(const List& A) {
		if (this != &A) {
			pFirst = A.pFirst;
			sz = A.sz;
			Node* pNew = pFirst = new Node{ *A.pFirst };
			for (; pNew->pNext != nullptr; pNew = pNew->pNext)
				pNew->pNext = new Node{ *pNew->pNext };
		}
		return(*this);
	}
	Pair& operator[](int N) {
		Pair A;
		int k = 0;
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if (k == N) {
				return((*it).Duo);
			}
			k++;
		}
		return(A);
	}
	void Eraise(int N) {
		if (N == 0)
			this->PopFront();
		else if (N + 1 < sz) {
			Node* res = new Node;
			int k = 0;
			for (iterator it = this->begin(); it != this->end(); ++it) {
				if (k == N) {
					*res = (*it);
					break;
				}
				k++;
			}
			k = 0;
			for (iterator it = this->begin(); it != this->end(); ++it) {
				if (k == N-1) {
					(*it).pNext = res->pNext;
					break;
				}
				k++;
			}
			delete res;
			sz--;
		}
	}
	friend bool operator==(const List& a,const List& b)
	{
		if (a.sz != b.sz)
			return(false);
		List A = a;
		List B = b;
		iterator it1 = A.begin();
		iterator it2 = B.begin();
		while ((it1 != A.end()) || (it2 != B.end())) {
			Node p1 = *it1;
			Node p2 = *it2;
			if(!(p1 == p2))
				return(false);
			++it1;
			++it2;
		}
		return(true);
	}
};

class Polynom {
	List Pol;
public:

	//Polynom(const Polynom& A) : Pol(A.Pol) {}

	Polynom() = default;
	Polynom(string str) {
		this->parse(str);
	}

	//Polynom& operator=(const Polynom& A) {
	//	if (this != &A) {
	//		this->Pol = A.Pol;
	//	}
	//	return(*this);
	//}

	Pair str_to_pair(string str) {
		Pair Duo{ 0,0 };
		int flag = 1;
		if (str[0] == '-')
			flag *= -1;
		str.erase(0,1);
		if ((str[0] < '0') || (str[0] > '9'))
			Duo.Coef = flag;
		else {
			int tmp = 0;
			while (1) {
				if ((str[0] >= '0') && (str[0] <= '9')) {
					tmp *= 10;
					tmp += str[0] - '0';
					str.erase(0, 1);
				}
				else
					break;
			}
			Duo.Coef = tmp * flag;
		}
		int tmp = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == 'x') {
				if ((i + 2 < str.length()) && (str[i + 2] >= '0') && (str[i + 2] <= '9'))
					tmp += 100 * (str[i + 2] - '0');
				else
					tmp += 100;
			}
			if (str[i] == 'y') {
				if ((i + 2 < str.length()) && (str[i + 2] >= '0') && (str[i + 2] <= '9'))
					tmp += 10 * (str[i + 2] - '0');
				else
					tmp += 10;
			}
			if (str[i] == 'z') {
				if ((i + 2 < str.length()) && (str[i + 2] >= '0') && (str[i + 2] <= '9'))
					tmp += (str[i + 2] - '0');
				else
					tmp += 1;
			}
		}
		Duo.Deg = tmp;
		return(Duo);
	}
	void parse(string str) {
		vector<Pair> monoms;
		string tmp = "";
		if (str[0] != '-')
			tmp += '+';
		for (int i = 0; i < str.length()+1; i++) {
			if ((i > 0) && ((str[i] == '+') || (str[i] == '-') || (i == str.length()))) {
				Pair p = str_to_pair(tmp);
				monoms.push_back(p);
				tmp = "";
			}
			tmp += str[i];
		}
		sort(monoms.begin(), monoms.end());
		for (int i = 0; i < monoms.size(); i++) {
			Pol.PushFront(monoms[i]);
		}
	}
	friend ostream& operator<<(ostream& os, Polynom& A)
	{
		for (List::iterator it = A.Pol.begin(); it != A.Pol.end(); ++it) {
			if (A.Pol.size() <= 1) {
				cout << 0;
				return os;
			}
			int Coef = (*it).Duo.Coef;
			int Deg = (*it).Duo.Deg;
			if (Coef == 0)
				continue;
			if (Deg == 0) {
				if ((it == A.Pol.begin()) && (Coef > 0))
					cout << Coef;
				else if (Coef > 0)
					cout << '+' << Coef;
				else
					cout << Coef;
				continue;
			}
			if ((it != A.Pol.begin()) && (Coef == 1))
				cout << '+';
			else if (Coef == 1);
			else if (Coef == -1)
				cout << '-';
			else {
				if ((it == A.Pol.begin()) && (Coef > 1))
					cout << Coef;
				else if (Coef > 1)
					cout << '+' << Coef;
				else
					cout << Coef;
			}
			int tmp[3] = { 0 };
			for (int i = 2; i >= 0; i--) {
				tmp[i] = Deg % 10;
				Deg /= 10;
			}
			if (tmp[0] == 1)
				cout << 'x';
			if (tmp[0] > 1)
				cout << "x^" << tmp[0];
			if (tmp[1] == 1)
				cout << 'y';
			if (tmp[1] > 1)
				cout << "y^" << tmp[1];
			if (tmp[2] == 1)
				cout << 'z';
			if (tmp[2] > 1)
				cout << "z^" << tmp[2];
		}
		return os;
	}
	friend istream& operator>>(istream& is, Polynom& A) {
		string str = "";
		getline(cin, str);
		while (1) {
			int i = str.find(' ');
			if ((i < 0) || i >= str.length())
				break;
			str.erase(i, 1);
		}
		A.parse(str);
		return is;
	}
	friend Polynom operator*(int Const, Polynom A) {
		for (List::iterator it = A.Pol.begin(); it != A.Pol.end(); ++it) {
			(*it).Duo.Coef *= Const;
		}
		return (A);
	}
	Polynom operator*(int Const) {
		for (List::iterator it = this->Pol.begin(); it != this->Pol.end(); ++it) {
			(*it).Duo.Coef *= Const;
		}
		return(*this);
	}
	Polynom operator+(Polynom& A) {
		Polynom tmp;
		List::iterator it1 = this->Pol.begin();
		List::iterator it2 = A.Pol.begin();
		Pair Duo = { 0,0 };
		while ((it1 != this->Pol.end()) || (it2 != A.Pol.end())) {
			if ((*it1).Duo.Deg > (*it2).Duo.Deg) {
				Duo = (*it1).Duo;
				++it1;
			}
			else if ((*it1).Duo.Deg < (*it2).Duo.Deg) {
				Duo = (*it2).Duo;
				++it2;
			}
			else {
				Duo.Coef = (*it2).Duo.Coef + (*it1).Duo.Coef;
				Duo.Deg = (*it2).Duo.Deg;
				++it1;
				++it2;
			}
			if (Duo.Coef != 0)
				tmp.Pol.PushBack(Duo);
		}
		if (tmp.Pol.size() > 1) {
			Duo = tmp.Pol.Front();
			tmp.Pol.PopFront();
			tmp.Pol.PushBack(Duo);
		}
		return(tmp);
	}
	Polynom operator*(Polynom& A) {
		Polynom res;
		for (List::iterator it1 = this->Pol.begin(); it1 != this->Pol.end(); ++it1) {
			if ((*it1).Duo.Coef == 0)
				continue;
			Polynom tmp;
			for (List::iterator it2 = A.Pol.begin(); it2 != A.Pol.end(); ++it2) {
				if ((*it2).Duo.Coef == 0)
					continue;
				Pair Duo = { (*it1).Duo.Coef * (*it2).Duo.Coef,(*it1).Duo.Deg + (*it2).Duo.Deg };
				if (Duo.Deg > 999)
					throw out_of_range("incorrect degree");
				tmp.Pol.PushBack(Duo);
			}
			if (tmp.Pol.size() > 1) {
				Pair Duo = tmp.Pol.Front();
				tmp.Pol.PopFront();
				tmp.Pol.PushBack(Duo);
			}
			res = res + tmp;
		}
		return(res);
	}
	friend Polynom operator-(Polynom A, Polynom B) {
		B = B * (-1);
		return(A + B);
	}
	friend bool operator==(const Polynom& a,const Polynom& b)
	{
		if (a.Pol == b.Pol)
			return(true);
		else
			return(false);
	}
};


