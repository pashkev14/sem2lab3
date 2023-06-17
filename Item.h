#pragma once

#include "String.h"

struct Item {
	
	String* val;
	Item* next;

	Item() {
		this->val = new String;
		this->next = nullptr;
	}

	~Item() {
		delete this->val;
		this->next = nullptr;
	}

};