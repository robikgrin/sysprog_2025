#include "program.h"

std::ostream &operator <<(std::ostream &str, const Program &prog) noexcept
{
	for(auto &instr: prog.instructions)
		str << *instr << '\n';
	return str;
}
