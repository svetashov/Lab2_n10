#pragma once
#include <list>
#include "baggage.h"

class baggage_stock
{

typedef bool (*predicate)(baggage b);
	
public:
	baggage_stock();

	// ���������� ������ ������
	void add(baggage b);
	
	// ��������� ������ b1 �� b2
	void change(baggage b1, baggage b2);

	// �������� ������
	void remove(baggage b);

	// ����� ���� ������� � �����
	void output(std::streambuf buf) const;

	// ���� ������� �� ������
	void input(std::streambuf buf);

	// ������� ������ ���� ���� �������
	size_t weight() const;

	// ����� ������� �� ���������
	baggage_stock* find(predicate pred) const;
	
private:
	std::list<baggage> baggages;
};

