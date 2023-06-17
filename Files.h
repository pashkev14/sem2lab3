#pragma once

#include <fstream>

struct Files {

	std::ifstream sourceFile;
	std::ifstream insertFile;
	std::ofstream outFile;
	std::ofstream logFile;

	Files(const char* source = "source.txt", const char* insert = "insert.txt", const char* out = "out.txt", const char* log = "log.txt") {
		this->sourceFile.open(source);
		this->insertFile.open(insert);
		this->outFile.open(out);
		this->logFile.open(log);
	}

	~Files() {
		this->sourceFile.close();
		this->insertFile.close();
		this->outFile.close();
		this->logFile.close();
	}

};