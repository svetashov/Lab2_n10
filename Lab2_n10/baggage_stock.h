#pragma once
#include <list>
#include "Baggage.h"
#include <iostream>

class baggage_stock
{

typedef bool (*predicate)(Baggage b);
	
public:
	baggage_stock();

	// ���������� ������ ������
	void add(const Baggage& b) const;
	
	// ��������� ������ b1 �� b2
	void change(const Baggage& b1, const Baggage& b2) const;

	// �������� ������
	void remove(const Baggage& b);

	// �������� ���������� �� ���������� ������
	bool contains(const Baggage& b) const;

	// ����� ���� ������� � �������
	void print() const;

	// ����������, ���� �� ���������
	bool is_empty() const;

	// ������� ������ ���� ���� �������
	size_t weight() const;

	// ����� ������� �� ���������
	baggage_stock& find(predicate pred) const;

	friend std::istream& operator>> (std::istream& in, baggage_stock& stock);

	friend std::ostream& operator<< (std::ostream& out, const baggage_stock& stock);
	
private:
	std::list<Baggage> * baggages_;
};

