#include "cdhitParser.h"
#include <sstream>

using namespace std;

//constructors && distructors
cdhitParser::cdhitParser() : Parser() {
	this->clusters.clear();
	this->representatives.clear();
}

cdhitParser::cdhitParser(const char* file_name) {
	this->clusters.clear();
	this->representatives.clear();
	this->open(file_name);
}

cdhitParser::cdhitParser(const string& file_name) {
	this->clusters.clear();
	this->representatives.clear();
	this->open(file_name);
}

cdhitParser::~cdhitParser() {
	this->close();
}

//getters
map<unsigned int, vector<string> > cdhitParser::getWholeClusters() const {
	return this->clusters;
}

map<unsigned int, string> cdhitParser::getWholeReps() const {
	return this->representatives;
}

vector<string> cdhitParser::getCluster(const unsigned int num) const {
	vector<string> ret;
	if (num > this->clusters.size()) {
		return ret;
	}

	map<unsigned int, vector<string> >::const_iterator m_it = this->clusters.begin();

	for (; m_it != this->clusters.end(); ++m_it) {
		if (m_it->first == num) {
			ret = m_it->second;
			break;
		}
	}

	return ret;
}

string cdhitParser::getRep(const unsigned int num) const {
	if (num > this->representatives.size()) {
		return "";
	}

	map<unsigned int, string>::const_iterator m_it = this->representatives.begin();
	for (; m_it != this->representatives.end(); ++m_it) {
		if (m_it->first == num) {
			return m_it->second;
		}
	}

	return "";
}


//actions
static vector<string> tokenize(string& str, char delim = ' ') {
	vector<string> ret;

	istringstream stm(str);
	string token;
	while (getline(stm, token, delim))
		ret.push_back(token);

	return ret;
}

bool cdhitParser::parse() {
	if (this->file.is_open()) {
		string line;
		string representative;
		vector<string> cluster;
		bool is_first = true;
		int clstr_num = 0;

		while (getline(this->file, line)) {
			if (line[0] == '>') {
				if (is_first) {
					is_first = false;
					continue;
				}

				this->clusters[clstr_num] = cluster;
				this->representatives[clstr_num] = representative;

				cluster.clear();
				representative = "";
				++clstr_num;
			}
			else {
				vector<string> tokens = tokenize(line);
				string seq_name = tokens[1].substr(0, tokens[1].size() - 3);
				
				cluster.push_back(seq_name);
				if (tokens[2] == "*") {
					representative = seq_name;
				}
			}
		}
		this->clusters[clstr_num] = cluster;
		this->representatives[clstr_num] = representative;

		return true;
	}

	return false;
}