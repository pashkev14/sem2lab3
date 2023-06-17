#pragma once

class String {
	
private:

	char* m_text;
	int m_size;

	void setSize(const int size);

public:

	String(const char* text = " ", const int size = 1) {
		this->m_text = new char[size];
		for (int i = 0; i < size; ++i) this->m_text[i] = text[i];
		this->m_size = size;
	}

	~String() {
		delete[] this->m_text;
	}

	void setText(const char* text, const int size);

	int getSize();

	char getChar(const int index);

	char* getText();

};