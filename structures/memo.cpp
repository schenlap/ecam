#include "memo.h"


Memo::Memo(QString *text, QString *textval, MemoPrio prio, bool active, QObject *parent) :
	QObject(parent),
	_text(text),
	_textval(textval),
	_prio(prio),
	_active(active)
{
}


QString Memo::name() {
	return *_text;
}


QString Memo::val() {
	return *_textval;
}


void Memo::set_active(bool act) {
	_active = act;
}
