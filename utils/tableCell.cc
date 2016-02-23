#include "tableCell.h"

tableCell::tableCell()
{
	_value = "EMTPY";
	_deleted = 0;
}
tableCell::tableCell(char *val)
{
	_value = val;
	_deleted = 0;
}

tableCell::tableCell(tableCell *x)
{
	_value = x->value();
	_deleted = x->deleted();
}
tableCell::~tableCell()
{
}
