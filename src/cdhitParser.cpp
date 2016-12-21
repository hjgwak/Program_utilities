#include "cdhitParser.h"
#include <sstream>

using namespace std;

//constructors && distructors
cdhitParser::cdhitParser() : Parser() {
	this->clusters.clear();
	this->representatives.clear();
	this->parsed = false;
}

cdhitParser::cdhitParser(const char* file_name) {
	this->clusters.clear();
	this->representatives.clear();
	this->open(file_name);
	this->parsed = false;
}

cdhitParser::cdhitParser(const string& file_name) {
	this->clusters.clear();
	this->representatives.clear();
	this->open(file_name);
	this->parsed = false;
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
	vector<string> ret = {"OUT OF RANGE"};
	if (num > this->clusters.size()) {
		return ret;
	}
	ret.pop_back();
	ret.push_back("NOT FOUND");

	map<unsigned int, vector<string> >::const_iterator m_it = this->clusters.find(num);

	return (m_it != this->clusters.end()) ? m_it->second : ret;
}

string cdhitParser::getRep(const unsigned int num) const {
	if (num > this->representatives.size()) {
		return "OUT OF RANGE";
	}

	map<unsigned int, string>::const_iterator m_it = this->representatives.find(num);

	return (m_it != this->representatives.end()) ? m_it->second : "NOT FOUND";
}

size_t cdhitParser::getClusterSize(const unsigned int num) const {
	if (num > this->clusters.size()) {
		return 0;
	}

	map<unsigned int, vector<string> >::const_iterator m_it = this->clusters.begin();
	for (; m_it != this->clusters.end(); ++m_it) {
		if (m_it->first == num) {
			return m_it->second.size();
		}
	}
}

size_t cdhitParser::getClusterNum() const {
	return this->clusters.size();
}


//actions
static vector<string> tokenize(const string& str, const char delim = ' ') {
	vector<string> ret;
	string temp = str;

	istringstream stm(temp);
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
				if (tokens[3] == "*") {
					representative = seq_name;
				}
			}
		}
		this->clusters[clstr_num] = cluster;
		this->representatives[clstr_num] = representative;

		this->parsed = true;

		return true;
	}

	return false;
}