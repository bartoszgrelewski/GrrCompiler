#include "code.hpp"

void Code::ifElseBlock()
{
	std::vector<int> branch = branchStack.top();
	branchStack.pop();
	for (unsigned long i = 1; i < branch.size(); i++)
		assemblyCode[branch[i]] += ' ' + std::to_string(CURR_PROGC + 1);

	branchStack.push({});
	branchStack.top().push_back(CURR_PROGC);
	jump();

	debug("If branch to else resolving [ifElseBlock]");
	debug_asm("ELSE");
}

void Code::elseBlock()
{
	std::vector<int> branch = branchStack.top();
	branchStack.pop();
	assemblyCode[branch[0]] += ' ' + std::to_string(CURR_PROGC);

	debug("Else skip branch resolving [elseBlock]");
	debug_asm("ELSE END");
}

void Code::ifBlock()
{
	std::vector<int> branch = branchStack.top();
	branchStack.pop();
	for (unsigned long i = 1; i < branch.size(); i++)
		assemblyCode[branch[i]] += ' ' + std::to_string(CURR_PROGC);

	debug("If skip branch resolving [ifBlock]");
}

void Code::beginWhile()
{
	insideLoop = true;
	debug_asm("WHILE")
}

void Code::whileBlock()
{
	std::vector<int> branch = branchStack.top();
	branchStack.pop();
	for (unsigned long i = 1; i < branch.size(); i++)
		assemblyCode[branch[i]] += ' ' + std::to_string(CURR_PROGC + 1);

	debug("While skip branch resolving [whileBlock]")
		jump(branch[0]);
	debug("While loop branch [whileBlock]")
		debug_asm("WHILE END");
	insideLoop = false;
	for (std::string variable : initializeErrors)
	{
		INIT_CHECK(variable, "[whileBlock]");
	}
}

void Code::repeatBlock()
{
	branchStack.push({});
	branchStack.top().push_back(CURR_PROGC);
	debug_asm("REPEAT");
	insideLoop = true;
}

void Code::repeatEndBlock()
{
	std::vector<int> branch = branchStack.top();
	branchStack.pop();

	std::vector<int> begin = branchStack.top();
	branchStack.pop();

	for (unsigned long i = 1; i < branch.size(); i++)
		assemblyCode[branch[i]] += ' ' + std::to_string(begin[0]);

	debug("Repeat loop branch resolving [repeatEndBlock]")

		debug_asm("REPEAT END");

	insideLoop = false;
	for (std::string variable : initializeErrors)
	{
		INIT_CHECK(variable, "[repeatEndBlock]");
	}
}