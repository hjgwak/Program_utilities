#ifndef __MUSCLE_H__
#define __MUSCLE_H__

#include "Program.h"
#include <vector>

class Muscle : public Program {
public:
	//constructors
	Muscle();
	Muscle(const std::string name, const std::string path);

	//setters

	//actions
	std::pair<std::string, int> run();

private:
	void setRequired();
	bool checkValid() const;

	std::vector<std::string> required;
};

#endif // !__MUSCLE_H__