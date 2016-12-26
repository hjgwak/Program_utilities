#include "Muscle.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	int ret = 0;

	if (argc != 2) {
		return -1;
	}
	string path = argv[1];
	if (path[path.length() - 1] != '/') path += '/';

	Muscle muscle;
	pair<string, int> res;

	res = muscle.run();
	if (res.first != "error" || res.second != -1) {
		cerr << "[ERROR] Muscle.run()" << endl;
		cerr << "        muscle's path was not set, but run" << endl;

		ret -= 1;
	}

	Muscle muscle2("muscle", "/program/");

	res = muscle.run();
	if (res.first != "error" || res.second != -1) {
		cerr << "[ERROR] Muscle.run()" << endl;
		cerr << "        required options was not set, but run" << endl;

		ret -= 1;
	}

	muscle2.addOption("-in", path + "test_data/test_muscle.fasta");
	muscle2.addOption("-out", path + "test_output/test_muscle.fasta");

	res = muscle2.run();
	if (res.second != 0) {
		cerr << "[ERROR] muscle did not execute collectly" << endl;
		cerr << "        cmd: " + res.first << endl;
		ret -= 1;
	}

	ifstream result, answer;
	result.open(path + "test_output/test_muscle.fasta");
	answer.open(path + "test_answer/answer_muscle.fasta");

	string result_line, answer_line;
	while (getline(result, result_line) && getline(answer, answer_line)) {
		if (result_line != answer_line) {
			cerr << "[ERROR] Muscle.run()" << endl;
			ret -= 1;
			break;
		}
	}

	return ret;
}
