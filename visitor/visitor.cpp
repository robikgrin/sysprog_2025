#include "visitor.h"

Program Optimizer::run(const Program &prog) {
    // Очищаем состояние для нового запуска
    optimizedProgram.instructions.clear();
    lastDisable = nullptr;
    lastConstFreq = nullptr;

    // Проходим по всем инструкциям исходной программы
    for (const auto& instr : prog.instructions) {
        instr->accept(this);
    }

    // Возвращаем результат
    return std::move(optimizedProgram);
}

void Optimizer::visit(const Disable &instr) {
    double d = instr.getDuration();
    if (d <= 1e-9) return; // Игнорируем нулевую длительность

    if (lastDisable) {
        // Объединяем с предыдущим
        lastDisable->setDuration(lastDisable->getDuration() + d);
    } else {
        // Создаем новую инструкцию
        optimizedProgram.push<Disable>(d);
        lastDisable = static_cast<Disable*>(optimizedProgram.instructions.back().get());
        
        // Сбрасываем указатель на частоту, так как цепочка частот прервалась
        lastConstFreq = nullptr;
    }
}

void Optimizer::visit(const ConstFrequency &instr) {
    double d = instr.getDuration();
    if (d <= 1e-9) return; 

    // если частоты не отличаются, то объединяем
    if (lastConstFreq && std::abs(lastConstFreq->getFrequncy() - instr.getFrequncy()) < 1e-9) {
        // Объединяем с предыдущей
		lastConstFreq->setDuration(lastConstFreq->getDuration() + d);
    } else {
        optimizedProgram.push<ConstFrequency>(d, instr.getFrequncy());
        lastConstFreq = static_cast<ConstFrequency*>(optimizedProgram.instructions.back().get());
    }
	lastDisable = nullptr;
}


void Optimizer::visit(const SweepFrequency &instr) {
    double d = instr.getDuration();
    if (d <= 1e-9) return;

    if (std::abs(instr.getStartFreq() - instr.getStopFreq()) < 1e-9) {
        ConstFrequency temp(d, instr.getStartFreq());
		this->visit(temp);
    } else {
        optimizedProgram.push<SweepFrequency>(d, instr.getStartFreq(), instr.getStopFreq());
    
		// Прерываем цепочки объединения
		lastDisable = nullptr;
		lastConstFreq = nullptr;
    }
}