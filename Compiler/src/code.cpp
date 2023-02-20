#include "code.hpp"
#include <iostream>
#include <map>
#include <string>

extern int yyerror(std::string);

Code::Code()
{
	assemblyCode.push_back("");
	div_adr = -1;
	mul_adr = -1;
	mod_adr = -1;
}

void Code::beginMain()
{
	debug_asm_blk("__MAIN__");
	assemblyCode[0] = "JUMP " + std::to_string(assemblyCode.size());
}

void Code::read(std::string id)
{
	if (!variables.exists(id))
		yyerror("Variable not defined: \"" + id + "\"");
	else
	{
		get(ADR(id));
		variables.initialize(id);
		debug("Variable \"" << id << "\" read "
							<< "[read]");
	}
}

void Code::write(Value *val)
{
	if (val->isNum)
	{
		set(val->num);
		put(0);
		debug("Const \"" << val->num << "\" write [write]");
	}
	else
	{
		EXISTS_CHECK(val->id, "[write]");
		INIT_CHECK(val->id, "[write]");

		put(ADR(val->id));
		debug("Variable \"" << val->id << "\" write " << val->num << "[write]");
	}
}

void Code::assign(std::string id, Value *val)
{
	EXISTS_CHECK(id, "[assign]");

	if (val->isNum)
	{
		set(val->num);
		store(ADR(id));
		variables.initialize(id);
		debug("Variable \"" << id << "\" assignment with const " << val->num << "[assign]");
	}
	else
	{
		EXISTS_CHECK(val->id, "[write]");
		INIT_CHECK(val->id, "[write]");

		load(ADR(val->id));
		store(ADR(id));
		variables.initialize(id);
		debug("Variable \"" << id << "\" assignment with variable " << val->id << "[assign]");
	}
}

void Code::call(std::string id, std::vector<std::string> callVariables)
{
	std::map<std::string, std::pair<int, std::vector<std::string>>>::iterator it = procedures.find(id);
	if (it == procedures.end())
	{
		yyerror("Procedure not found\"" + id + "\"");
		return;
	}

	std::vector<std::string> procedureVariables = it->second.second;

	if (callVariables.size() != procedureVariables.size())
	{
		yyerror("Wrong number of arguments passed to procedure \"" + id + "\"");
		return;
	}

	for (unsigned long i = 0; i < callVariables.size(); i++)
	{
		EXISTS_CHECK(callVariables[i], "[assign]");
		// INIT_CHECK(callVariables[i] , "[assign]");
	}

	// copy call variables
	for (unsigned long i = 0; i < callVariables.size(); i++)
	{
		load(ADR(callVariables[i]));
		store(ADR(procedureVariables[i]));
	}

	// MOZE SIE WYSYPAC (ADRES SKOKU)
	set(CURR_PROGC + 3);
	store(ADR(id));

	debug_asm_blk("CALL " + id);
	// skok do kontekstu
	jump(it->second.first);

	// copy back to call variables
	for (unsigned long i = 0; i < callVariables.size(); i++)
	{
		load(ADR(procedureVariables[i]));
		store(ADR(callVariables[i]));
		variables.initialize(callVariables[i]);
	}

	debug("Procedure \"" << id << "\" call created [call]");
}

void Code::createProcedure(std::string id, std::vector<std::string> callVariables)
{
	if (procedures.find(id) != procedures.end())
	{
		yyerror("Redefinition of procedure\"" + id + "\"");
	}
	else
	{
		for (unsigned long i = 0; i < callVariables.size(); i++)
			callVariables[i] = id + callVariables[i];

		// declare variables
		for (auto var : callVariables)
		{
			declareVariable(var);
			variables.initialize(var);
		}

		// declare variable named same as context as call return pointer
		declareVariable(id);

		// MOZE SIE WYSYPAC (ADRES SKOKU)
		procedures[id] = std::make_pair(assemblyCode.size(), callVariables);
		debug("Procedure \"" << id << "\" registration [createProcedure]");
		debug_asm_blk("__" + id + "__");
	}
}

void Code::procedureEnd(std::string id)
{
	if (!variables.exists(id))
		yyerror("CRITICAL Procedure return call creation failed undefined reference\"" + id + "\"");

	jumpi(ADR(id));
	debug("Procedure \"" << id << "\" return call [procedureEnd]");
}

void Code::declareVariable(std::string id)
{
	if (!variables.createVariable(id))
		yyerror("Redefinition of variable\"" + id + "\"");

	debug("Variable \"" << id << "\" declation [declare]");
}