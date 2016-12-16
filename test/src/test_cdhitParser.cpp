#include "cdhitParser.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool vectorComp(const vector<string>& v1, const vector<string>& v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	else {
		vector<string>::const_iterator v_it = v1.begin(), v_it2;
		for (; v_it != v1.end(); ++v_it) {
			v_it2 = find(v2.begin(), v2.end(), *v_it);
			if (v_it2 == v2.end()) {
				return false;
			}
		}
	}

	return true;
}

bool PassOrFail(const bool condition, const string& msg, int* ret) {
	if (condition) {
		cerr << "[ERROR] " << msg << endl;
		*ret -= 1;
	}
	else {
		cerr << "[SUCCESS] " << msg << endl;
	}

	return condition;
}

string printVector(const vector<string>& v) {
	string line = "{";
	bool first = true;

	vector<string>::const_iterator v_it = v.begin();
	for (; v_it != v.end(); ++v_it) {
		if (!first) {
			line += ", ";
		}
		line += *v_it;
		first = false;
	}
	line += "}";

	return line;
}

string printMap(const map<unsigned int, string> m) {
	string line = "{";
	bool first = true;

	map<unsigned int, string>::const_iterator m_it = m.begin();
	for (; m_it != m.end(); ++m_it) {
		if (!first) {
			line += ", ";
		}
		line += to_string(m_it->first);
		line += ": ";
		line += m_it->second;
		first = false;
	}
	line += "}";

	return line;
}

string printMap2(const map<unsigned int, vector<string> > m) {
	string line = "{";
	bool first = true;

	map<unsigned int, vector<string> >::const_iterator m_it = m.begin();
	for (; m_it != m.end(); ++m_it) {
		if (!first) {
			line += ",\n";
		}
		line += to_string(m_it->first);
		line += ": ";
		line += printVector(m_it->second);
		first = false;
	}
	line += "}";

	return line;
}

int main(int argc, char* argv[]) {
	int ret = 0;

	if (argc != 2) {
		return -1;
	}
	string path = argv[1];

	cdhitParser test_parser;
	PassOrFail(test_parser.is_open(), "Parser::constructor()", &ret);

	test_parser.open(path + "/test_data/test.cdhit.clstr");
	PassOrFail(!test_parser.is_open(), "Parser::constructor(file_name)", &ret);

	test_parser.close();
	PassOrFail(test_parser.is_open(), "Parser::close()", &ret);

	cdhitParser parser(path + "/test_data/test.cdhit.clstr");

	PassOrFail(!parser.is_open(), "cdhitParser::constructor(file_name)", &ret);

	parser.parse();

	PassOrFail(parser.getClusterNum() != 5, "cdhitParser::parse() or cdhitParser::getClusterNum()", &ret);

	map<unsigned int, size_t> cluster_size_answer;
	cluster_size_answer[0] = 6;
	cluster_size_answer[1] = 4;
	cluster_size_answer[2] = 1;
	cluster_size_answer[3] = 1;
	cluster_size_answer[4] = 3;

	for (unsigned int i = 0; i < 5; ++i) {
		size_t size = parser.getClusterSize(i);

		if (PassOrFail(cluster_size_answer[i] != size, 
			"cdhitParser::parse() or cdhitParser::getClusterSize()", &ret)) {
			break;
		}
	}

	map<unsigned int, string> rep_answer;
	map<unsigned int, vector<string> > cluster_answer;

	rep_answer[0] = ">rep1";
	rep_answer[1] = ">rep2";
	rep_answer[2] = ">rep3";
	rep_answer[3] = ">rep4";
	rep_answer[4] = ">rep5";

	cluster_answer[0] = {">test1", ">test2", ">test3", ">rep1", ">test4", ">test5"};
	cluster_answer[1] = {">test6", ">test7", ">rep2", ">test8"};
	cluster_answer[2] = {">rep3"};
	cluster_answer[3] = {">rep4"};
	cluster_answer[4] = {">test9", ">rep5", ">test10"};

	map<unsigned int, vector<string> > whole_cluster = parser.getWholeClusters();
	map<unsigned int, string> whole_rep = parser.getWholeReps();

	if (rep_answer.size() != whole_rep.size()) {
		cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getWholeReps()" << endl;
		cerr << "        size not equal" << endl;
		ret -= 1;
	}
	else {
		map<unsigned int, string>::iterator m_it = rep_answer.begin(), m_it2;
		for (; m_it != rep_answer.end(); ++m_it) {
			m_it2 = whole_rep.find(m_it->first);
			if (m_it2 == whole_rep.end()) {
				cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getWholeReps()" << endl;
				cerr << "        parser.getWholeReps() : " << printMap(whole_rep) << endl;
				cerr << "        rep_answer : " << printMap(rep_answer) << endl;
				ret -= 1;
			}
			else if (m_it2->second != m_it->second) {
				cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getWholeReps()" << endl;
				cerr << "        parser.getWhileReps() : " << printMap(whole_rep) << endl;
				cerr << "        rep_answer : " << printMap(rep_answer) << endl;
				ret -= 1;
			}
		}
	}
	cerr << "[SUCCESS] cdhitParser::getWholeReps()" << endl;

	if (cluster_answer.size() != whole_cluster.size()) {
		cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getWholeClusters()" << endl;
		cerr << "        size not equal" << endl;
		ret -= 1;
	}
	else {
		map<unsigned int, vector<string> >::iterator m_it = cluster_answer.begin(), m_it2;
		for (; m_it != cluster_answer.end(); ++m_it) {
			m_it2 = whole_cluster.find(m_it->first);
			bool same = true;
			if (m_it2 == whole_cluster.end()) {
				same = false;
			}
			else if (!vectorComp(m_it->second, m_it2->second)) {
					same = false;
			}

			if (!same) {
				cerr << "[ERROR] cdhitParser::parse() or cditParser::getWholeClusters()" << endl;
				cerr << "        parser.getWholeClusters() : " << endl;
				cerr << printMap2(whole_cluster) << endl;
				cerr << "        cluster_answer : " << endl;
				cerr << printMap2(cluster_answer) << endl;
				ret -= 1;
				break;
			}
		}
	}
	cerr << "[SUCCESS] cdhitParser::getWholeClusters()" << endl;

	map<unsigned int, string>::iterator m_it = rep_answer.begin();
	for (; m_it != rep_answer.end(); ++m_it) {
		string rep = parser.getRep(m_it->first);
		if (rep != m_it->second) {
			cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getRep()" << endl;
			cerr << "        parser.getRep(" << m_it->first << ") : " << rep << endl;
			cerr << "        rep_answer[" << m_it->first << "] : " << m_it->second << endl;
			ret -= 1;
			break;
		}
	}
	cerr << "[SUCCESS] cdhitParser::getRep()" << endl;

	map<unsigned int, vector<string> >::iterator m_it2 = cluster_answer.begin();
	for (; m_it2 != cluster_answer.end(); ++m_it2) {
		vector<string> cluster = parser.getCluster(m_it2->first);
		if (!vectorComp(cluster, m_it2->second)) {
			cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getCluster()" << endl;
			cerr << "        parser.getCluster(" << m_it2->first << ") : " << printVector(cluster) << endl;
			cerr << "        cluster_answer[" << m_it2->first << "] : " << printVector(m_it2->second) << endl;
			ret -= 1;
			break;
		}
	}
	cerr << "[SUCCESS] cdhitParser::getCluster()" << endl;
	cerr << "[SUCCESS] cdhitParser::parse()" << endl;

	return ret;
}