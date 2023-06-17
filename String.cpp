#include "String.h"

void String::setSize(const int size) {
	this->m_size = size;
}

void String::setText(const char* text, const int size) {
	if (this->m_text != nullptr) delete[] this->m_text;
	this->m_text = new char[size];
	for (int i = 0; i < size; ++i) this->m_text[i] = text[i];
	this->setSize(size);
}

int String::getSize() {
	return this->m_size;
}

char String::getChar(const int index) {
	if (index < 0 || index >= this->getSize()) return 0;
	return this->m_text[index];
}

char* String::getText() {
	return this->m_text;
}