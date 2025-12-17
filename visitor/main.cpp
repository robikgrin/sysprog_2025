#include "program.h"
#include "visitor.h"
#include <iostream>

int main()
{
	Program prog;
	prog.push<ConstFrequency>(1.1, 3.14);
	prog.push<Disable>(2.2);
	prog.push<Disable>(3.3);
	prog.push<ConstFrequency>(1.2, 3.14);
	prog.push<Disable>(0);
	prog.push<ConstFrequency>(3.8, 3.14);
	prog.push<ConstFrequency>(0, 666);
	prog.push<SweepFrequency>(1.3, 3.14, 4.56);
	prog.push<SweepFrequency>(0, 4.56, 666);
	prog.push<SweepFrequency>(1.4, 4.56, 4.56);
	std::cout << "Program before optimization:\n" << prog;

	std::cout << "\nRunning optimizer...\n";
	Optimizer optimizer;
	Program prog2 = optimizer.run(prog);
	std::cout << "\nProgram after optimization:\n" << prog2;

/*	ПРИМЕР ВЫВОДА ПРОГРАММЫ:

	Program before optimization:
	ConstFrequency(t = 1.1, f = 3.14)
	Disable(t = 2.2)
	Disable(t = 3.3)
	ConstFrequency(t = 1.2, f = 3.14)
	Disable(t = 0)
	ConstFrequency(t = 3.8, f = 3.14)
	ConstFrequency(t = 0, f = 666)
	SweepFrequency(t = 1.3, f1 = 3.14, f2 = 4.56)
	SweepFrequency(t = 0, f1 = 4.56, f2 = 666)
	SweepFrequency(t = 1.4, f1 = 4.56, f2 = 4.56)

	Running optimizer...

	Program after optimization:
	ConstFrequency(t = 1.1, f = 3.14)
	Disable(t = 5.5)
	ConstFrequency(t = 5, f = 3.14)
	SweepFrequency(t = 1.3, f1 = 3.14, f2 = 4.56)
	ConstFrequency(t = 1.4, f = 4.56)
*/
	return 0;
}
