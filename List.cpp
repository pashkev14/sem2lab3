#include "List.h"

bool List::isEmpty() {
	return this->first == nullptr;
}

int List::getSize() {
	int length = 0;
	Item* p = this->first;
	while (p != nullptr) {
		++length;
		p = p->next;
	}
	return length;
}

Item* List::getItem(const int index) {
	int size = this->getSize();
	if (index < 0 || index >= size) return nullptr;
	int pos = 0;
	Item* p = this->first;
	while (pos != index) {
		++pos;
		p = p->next;
	}
	return p;
}

void List::appendItem(Item* val) {
	Item* tmp = new Item;
	tmp->val->setText(val->val->getText(), val->val->getSize());
	if (this->isEmpty()) {
		this->first = tmp;
		this->last = tmp;
	}
	else {
		this->last->next = tmp;
		this->last = tmp;
	}
}

void List::appendList(List* list) {
	for (int i = 0; i < list->getSize(); ++i) this->appendItem(this->getItem(i));
}

void List::insertItem(Item* val, const int index, bool left = true) {
	int size = this->getSize();
	if (index < 0 || (size && index >= size)) return;
	if (index + left == size - 1 || (index == 0 && size == 0)) this->appendItem(val);
	else if (index + (!left) == 0) {
		Item* tmp = new Item;
		tmp->val->setText(val->val->getText(), val->val->getSize());
		tmp->next = this->first;
		this->first = tmp;
		tmp = nullptr;
	}
	else {
		Item* tmp = new Item;
		tmp->val->setText(val->val->getText(), val->val->getSize());
		Item* prev = this->getItem(index - left);
		Item* next = this->getItem(index + (!left));
		prev->next = tmp;
		tmp->next = next;
		tmp = nullptr;
		prev = nullptr;
		next = nullptr;
	}
}

void List::insertList(List* list, const int index, bool left = true) {
	for (int i = 0; i < list->getSize(); ++i) this->insertItem(list->getItem(i), index + i, left);
}

void List::deleteItem(const int index) {
	if (this->isEmpty()) return;
	int size = this->getSize();
	if (index < 0 || index >= size) return;
	if (size == 1) {
		this->last = nullptr;
		delete this->first;
		this->first = nullptr;
	}
	else {
		Item* del = this->getItem(index);
		if (index == 0) {
			this->first = del->next;
			delete del;
		}
		else if (index == size - 1) {
			this->last = this->getItem(index - 1);
			this->last->next = nullptr;
			delete del;
		}
		else {
			Item* prev = this->getItem(index - 1);
			prev->next = this->getItem(index + 1);
			delete del;
			prev = nullptr;
		}
		del = nullptr;
		if (this->getSize() == 1) {
			this->last = this->first;
		}
	}
}

void List::deleteList() {
	int curIndex = this->getSize() - 1;
	while (this->first != nullptr) {
		this->deleteItem(curIndex);
		--curIndex;
	}
}