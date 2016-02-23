#include subpage.h

subPage::subPage()
{
	_numLines = 0;
	_index = 0;
}
subPage::~subPage()
{
	if (_numLines)
	{
		for (int i = 0; i < _numLines; i++)
			delete _content[i];
		delete _content;
	}
}
void subPage::addLine(mstring line)
{
	if (_numLines)
	{
		// copy what we where pointing at	
		struct pageLine tempSubPage[_numLines];
		for (int i = 0; i < _numLines; i++)
			tempSubPage[i]->value = _content[i]->value;

		
		// get rid of what we were pointing at
		for (int i = 0; i < _numLines; i++)
			delete _content[i];
		delete _content;
	}
	_numLines++;
	_content = (pageLine**)malloc(_numLines * sizeof(pageLine));
	// copy our contents back and add our new line
	for (int i = 0; i < (_numLines - 1); i++)
		_content[i]->value = tempSubPage[i]->value;
	_content[_numLines]->value = line;
		
}
