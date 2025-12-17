#pragma once

#include "program.h"

/**
 * @brief Абстрактный посетитель.
 */
class Visitor
{
public:
	virtual ~Visitor() = default;
	virtual void visit(const Disable &instr) = 0;
	virtual void visit(const ConstFrequency &instr) = 0;
	virtual void visit(const SweepFrequency &instr) = 0;
};

/**
 * @brief Оптимизатор программы.
 */
class Optimizer: public Visitor
{
public:
	/**
	 * @brief Запустить оптимизатор.
	 * @param prog - программа для оптимизации.
	 * @return Оптимизированная программа.
	 */
	Program run(const Program &prog);

	// Я сделал
	/**
	* @brief `visit` для Disable.
	* @param instr - инструкция.
	*/
	void visit(const Disable &instr) override;
	/**
	* @brief `visit` для ConstFrequency.
	* @param instr - инструкция.
	*/
    void visit(const ConstFrequency &instr) override;
	/**
	* @brief `visit` для SweepFrequency.
	* @param instr - инструкция.
	*/
    void visit(const SweepFrequency &instr) override;

	private:
		Program optimizedProgram;
		Disable *lastDisable = nullptr;
		ConstFrequency *lastConstFreq = nullptr;
	/////
};

