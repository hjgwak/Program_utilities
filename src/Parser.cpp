#include "Parser.h"

using namespace std;

//constructors && distructors
Parser::Parser() {
	//do nothing
}

Parser::Parser(const char* file_name) {
	this->file.open(file_name, ifstream::in);
}

Parser::Parser(const string& file_name) {
	this->file.open(file_name, ifstream::in);
}

Parser::~Parser() {
	this->close();
}

//setters
void Parser::open(const char* file_name) {
	if (!this->file.is_open()) {
		this->file.open(file_name, ifstream::in);
	}
}

void Parser::open(const string& file_name) {
	if (!this->file.is_open()) {
		this->file.open(file_name, ifstream::in);
	}
}

void Parser::close() {
	if (this->file.is_open()) {
		this->file.close();
	}
}

//getters
bool Parser::is_open() const {
	return this->file.is_open();
}