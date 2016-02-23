#include "tableCell.h"

tableCell::tableCell()
{
	_value = "EMTPY";
}
tableCell::tableCell(char *val)
{
	_value = val;
}
tableCell::~tableCell()
{
	/*
	cout << "Got here " << "_value is: "<< value() << endl;
	cout << "Got here " << "_next is: "<< next() << endl;
	cout << "Got here " << "_first is: "<< first() << endl;
	if (_next != NULL)
		delete _next;
	if (_first != NULL)
		delete _first;
	cout << "Then I Got here" <<  "Value is: "<< value() << endl;
	*/
}
