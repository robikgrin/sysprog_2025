#include "instructions.h"
#include "visitor.h"
#include <stdexcept>

void Instruction::setDuration(double val)
{
	if(val < 0)
		throw std::invalid_argument("Instruction::setDuration: duration must be non-negative");
	duration = val;
}

void Disable::print(std::ostream &str) const noexcept
{
	str << "Disable(t = " << getDuration() << ")";
}

void ConstFrequency::print(std::ostream &str) const noexcept
{
	str << "ConstFrequency(t = " << getDuration() << ", f = " << freq << ")";
}

void ConstFrequency::setFrequncy(double val)
{
	if(val <= 0)
		throw std::invalid_argument("ConstFrequency::setFrequncy: frequency must be positive");
	freq = val;
}

void SweepFrequency::print(std::ostream &str) const noexcept
{
	str << "SweepFrequency(t = " << getDuration()
		<< ", f1 = " << start << ", f2 = " << stop << ")";
}

void SweepFrequency::setStartFreq(double val)
{
	if(val <= 0)
		throw std::invalid_argument("SweepFrequency::setStartFreq: frequency must be positive");
	start = val;
}

void SweepFrequency::setStopFreq(double val)
{
	if(val <= 0)
		throw std::invalid_argument("SweepFrequency::setStopFreq: frequency must be positive");
	stop = val;
}


// accept for visitor
void Disable::accept(Visitor *visitor) const{
	visitor->visit(*this);
}

void ConstFrequency::accept(Visitor *visitor) const{
	visitor->visit(*this);
}

void SweepFrequency::accept(Visitor *visitor) const{
	visitor->visit(*this);
}
////////////////