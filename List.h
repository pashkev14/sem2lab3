#pragma once

#include "Item.h"

struct List {
	
	Item* first;
	Item* last;

	List() {
		this->first = nullptr;
		this->last = nullptr;
	}

	~List() {
		this->deleteList();
	}

	bool isEmpty();

	int getSize();

	Item* getItem(const int index);

	void appendItem(Item* val);

	void appendList(List* list);

	void insertItem(Item* val, const int index, bool left);

	void insertList(List* list, const int index, bool left);

	void deleteItem(const int index);

	void deleteList();

};