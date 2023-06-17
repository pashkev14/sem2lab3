#include "solve.h"

bool checkFiles(Files* files) {
	files->logFile << "Программа начала свою работу.\nПроизводится попытка открыть входные файлы.\n";
	if (files->sourceFile.is_open() && files->insertFile.is_open()) return true;
	if (!files->sourceFile.is_open()) {
		files->logFile << "Входной файл 1 не найден.\n";
		files->outFile << "Ошибка: входной файл 1 не найден.\n";
	}
	if (!files->insertFile.is_open()) {
		files->logFile << "Входной файл 2 не найден.\n";
		files->outFile << "Ошибка: входной файл 2 не найден.";
	}
	files->logFile << "Программа завершила свою работу.";
	return false;
}

void solve(Files* files) {
	if (!checkFiles(files)) return;
	files->logFile << "Производится запись с двух входных файлов в списки.\n";
	int index;
	files->insertFile >> index;
	files->sourceFile.unsetf(std::ios::skipws);
	files->insertFile.unsetf(std::ios::skipws);
	char tmp1, tmp2;
	files->insertFile >> tmp2;
	int charsCount1 = 0, charsCount2 = 0, startPos1 = files->sourceFile.tellg(), startPos2 = files->insertFile.tellg();
	bool eof1 = false, eof2 = false;
	Item* tmpItem;
	char* tmpStr;
	List* l1 = new List;
	List* l2 = new List;
	do {
		if (eof1 && eof2) break;
		files->sourceFile >> tmp1;
		files->insertFile >> tmp2;
		if (files->sourceFile.eof() && !eof1) {
			files->sourceFile.clear();
			files->sourceFile.seekg(startPos1, std::ios::beg);
			tmpItem = new Item;
			tmpStr = new char[(charsCount1 ? charsCount1 : 1)];
			tmpStr[0] = '\0';
			for (int i = 0; i < charsCount1; ++i) files->sourceFile >> tmpStr[i];
			files->sourceFile >> tmp1;
			tmpItem->val->setText(tmpStr, charsCount1);
			l1->appendItem(tmpItem);
			tmpItem = nullptr;
			delete[] tmpStr;
			tmpStr = nullptr;
			charsCount1 = 0;
			eof1 = true;
		}
		else if (tmp1 == '\n' && !eof1) {
			files->sourceFile.seekg(startPos1, std::ios::beg);
			tmpItem = new Item;
			tmpStr = new char[(charsCount1 ? charsCount1 : 1)];
			tmpStr[0] = '\0';
			for (int i = 0; i < charsCount1; ++i) files->sourceFile >> tmpStr[i];
			files->sourceFile >> tmp1;
			startPos1 = files->sourceFile.tellg();
			tmpItem->val->setText(tmpStr, charsCount1);
			l1->appendItem(tmpItem);
			tmpItem = nullptr;
			delete[] tmpStr;
			tmpStr = nullptr;
			charsCount1 = 0;
		}
		else if (!eof1) ++charsCount1;
		if (files->insertFile.eof() && !eof2) {
			files->insertFile.clear();
			files->insertFile.seekg(startPos2, std::ios::beg);
			tmpItem = new Item;
			tmpStr = new char[(charsCount2 ? charsCount2 : 1)];
			tmpStr[0] = '\0';
			for (int i = 0; i < charsCount2; ++i) files->insertFile >> tmpStr[i];
			files->insertFile >> tmp2;
			tmpItem->val->setText(tmpStr, charsCount2);
			l2->appendItem(tmpItem);
			tmpItem = nullptr;
			delete[] tmpStr;
			tmpStr = nullptr;
			charsCount2 = 0;
			eof2 = true;
		}
		else if (tmp2 == '\n' && !eof2) {
			files->insertFile.seekg(startPos2, std::ios::beg);
			tmpItem = new Item;
			tmpStr = new char[(charsCount2 ? charsCount2 : 1)];
			tmpStr[0] = '\0';
			for (int i = 0; i < charsCount2; ++i) files->insertFile >> tmpStr[i];
			files->insertFile >> tmp2;
			startPos2 = files->insertFile.tellg();
			tmpItem->val->setText(tmpStr, charsCount2);
			l2->appendItem(tmpItem);
			tmpItem = nullptr;
			delete[] tmpStr;
			tmpStr = nullptr;
			charsCount2 = 0;
		}
		else if (!eof2) ++charsCount2;
	}
	while (true);
	files->logFile << "Сформированы списки:\n";
	files->logFile << "Список 1:\n";
	files->outFile << "Сформированы списки:\n";
	files->outFile << "Список 1:\n";
	tmpItem = l1->getItem(0);
	while (tmpItem != nullptr) {
		if (tmpItem->val->getSize() == 1 && tmpItem->val->getChar(0) == '\0');
		else {
			for (int i = 0; i < tmpItem->val->getSize(); ++i) {
				files->logFile << tmpItem->val->getChar(i);
				files->outFile << tmpItem->val->getChar(i);
			}
		}
		files->logFile << "->\n";
		files->outFile << "->\n";
		tmpItem = tmpItem->next;
	}
	files->logFile << "NULL\n";
	files->logFile << "Список 2:\n";
	files->outFile << "NULL\n";
	files->outFile << "Список 2:\n";
	tmpItem = l2->getItem(0);
	while (tmpItem != nullptr) {
		if (tmpItem->val->getSize() == 1 && tmpItem->val->getChar(0) == '\0');
		else {
			for (int i = 0; i < tmpItem->val->getSize(); ++i) {
				files->logFile << tmpItem->val->getChar(i);
				files->outFile << tmpItem->val->getChar(i);
			}
		}
		files->logFile << "->\n";
		files->outFile << "->\n";
		tmpItem = tmpItem->next;
	}
	files->logFile << "NULL\n";
	files->outFile << "NULL\n";
	files->logFile << "Производится попытка вставить список 2 в список 1.\n";
	l1->insertList(l2, index, false);
	if (index < 0 || index >= l1->getSize()) {
		files->logFile << "Был указан индекс, выходящий за пределы списка 1. Программа все равно отработала вставку, но это действие не имело смысла.\n";
		files->outFile << "Был указан индекс, выходящий за пределы списка 1. Программа все равно отработала вставку, но это действие не имело смысла.\n";
	}
	files->logFile << "Список 1 после вставки списка 2 справа по индексу " << index << ":\n";
	files->outFile << "Список 1 после вставки списка 2 справа по индексу " << index << ":\n";
	tmpItem = l1->getItem(0);
	while (tmpItem != nullptr) {
		if (tmpItem->val->getSize() == 1 && tmpItem->val->getChar(0) == '\0');
		else {
			for (int i = 0; i < tmpItem->val->getSize(); ++i) {
				files->logFile << tmpItem->val->getChar(i);
				files->outFile << tmpItem->val->getChar(i);
			}
		}
		files->logFile << "->\n";
		files->outFile << "->\n";
		tmpItem = tmpItem->next;
	}
	files->logFile << "NULL\n";
	files->logFile << "Проверка на корректное удаление:\nДо:\n";
	files->logFile << l1 << ' ' << l1->first << ' ' << l1->last << '\n';
	files->logFile << l2 << ' ' << l2->first << ' ' << l2->last << '\n';
	files->outFile << "NULL\n";
	files->outFile << "Проверка на корректное удаление:\nДо:\n";
	files->outFile << l1 << ' ' << l1->first << ' ' << l1->last << '\n';
	files->outFile << l2 << ' ' << l2->first << ' ' << l2->last << '\n';
	delete l1;
	delete l2;
	files->logFile << "После:\n";
	files->logFile << l1 << ' ' << l1->first << ' ' << l1->last << '\n';
	files->logFile << l2 << ' ' << l2->first << ' ' << l2->last << '\n';
	files->outFile << "После:\n";
	files->outFile << l1 << ' ' << l1->first << ' ' << l1->last << '\n';
	files->outFile << l2 << ' ' << l2->first << ' ' << l2->last << '\n';
	files->logFile << "Программа завершила свою работу.";
}