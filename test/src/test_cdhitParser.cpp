#include "cdhitParser.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool vectorComp(vector<string> v1, vector<string> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	else {
		vector<string>::iterator v_it = v1.begin(), v_it2;
		for (; v_it != v1.end(); ++v_it) {
			v_it2 = find(v2.begin(), v2.end(), *v_it);
			if (v_it2 == v2.end()) {
				return false;
			}
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	int ret = 0;

	if (argc != 2) {
		return -1;
	}
	string path = argv[1];

	cdhitParser test_parser;
	if (test_parser.is_open()) {
		cerr << "[ERROR] Parser::constructor" << endl;
		return -1;
	}

	test_parser.open(path + "/test_data/test.cdhit.clstr");
	if (!test_parser.is_open()) {
		cerr << "[ERROR] Parser::open(file_name)" << endl;
		return -1;
	}

	test_parser.close();
	if (test_parser.is_open()) {
		cerr << "[ERROR] Parser::close()" << endl;
		return -1;
	}

	cdhitParser parser(path + "/test_data/test.cdhit.clstr");

	if (!parser.is_open()) {
		cerr << "[ERROR] cdhitParser::constructor(file_name)" << endl;
		ret -= 1;
	}

	parser.parse();

	if (parser.getClusterNum() != 5) {
		cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getClusterNum()" << endl;
		ret -= 1;
	}

	map<unsigned int, size_t> cluster_size_answer;
	cluster_size_answer[0] = 6;
	cluster_size_answer[1] = 4;
	cluster_size_answer[2] = 1;
	cluster_size_answer[3] = 1;
	cluster_size_answer[4] = 3;

	for (unsigned int i = 0; i < 5; ++i) {
		size_t size = parser.getClusterSize(i);
		if (cluster_size_answer[i] != size) {
			cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getClusterSize()" << endl;
			ret -= 1;
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
		ret -= 1;
	}
	else {
		map<unsigned int, string>::iterator m_it = rep_answer.begin(), m_it2;
		for (; m_it != rep_answer.end(); ++m_it) {
			m_it2 = whole_rep.find(m_it->first);
			if (m_it2 == whole_rep.end()) {
				cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getWholeReps()" << endl;
				ret -= 1;
			}
		}
	}

	if (cluster_answer.size() != whole_cluster.size()) {
		cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getWhileClusters()" << endl;
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
				ret -= 1;
				break;
			}
		}
	}

	map<unsigned int, string>::iterator m_it = rep_answer.begin();
	for (; m_it != rep_answer.end(); ++m_it) {
		string rep = parser.getRep(m_it->first);
		if (rep != m_it->second) {
			cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getRep()" << endl;
			ret -= 1;
			break;
		}
	}

	map<unsigned int, vector<string> >::iterator m_it2 = cluster_answer.begin();
	for (; m_it2 != cluster_answer.end(); ++m_it2) {
		vector<string> cluster = parser.getCluster(m_it2->first);
		if (!vectorComp(cluster, m_it2->second)) {
			cerr << "[ERROR] cdhitParser::parse() or cdhitParser::getCluster()" << endl;
			ret -= 1;
			break;
		}
	}

	return ret;
}