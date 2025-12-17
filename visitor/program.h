#pragma once

#include "instructions.h"
#include <vector>
#include <memory>
#include <ostream>

/**
 * @brief Класс программы - набора инструкций.
 */
struct Program
{
	/**
	 * @brief Вектор указателей на объекты-инструкции.
	 */
	std::vector<std::unique_ptr<Instruction>> instructions;

	/**
	 * @brief Создать инструкцию и добавить её в программу.
	 * @tparam Instr - тип инструкции.
	 * @tparam Args - типы аргументов конструктора инструкции (обычно
	 * автоматически выводятся компилятором).
	 * @param args - аргументы, которые передаются в конструктор инструкции.
	 *
	 * Этот метод введён для упрощения добавления инструкций в программу. С его
	 * помощью можно писать так:
	 * ```
	 * Program prog;
	 * prog.push<ConstFrequency>(1.1, 1);
	 * prog.push<Disable>(2.2);
	 * ```
	 *
	 * Запись выше эквивалента следующему:
	 * ```
	 * Program prog;
	 * prog.instructions.push_back(std::make_unique<ConstFrequency>(1.1, 1));
	 * prog.instructions.push_back(std::make_unique<Disable>(2.2));
	 * ```
	 */
	template<typename Instr, typename... Args>
	void push(Args&&... args)
	{
		instructions.push_back(std::make_unique<Instr>(std::forward<Args>(args)...));
	}

	/**
	 * @brief Проверить пуста ли программа.
	 * @return `true`, если программа не содержит инструкций, иначе `false`.
	 */
	bool empty() const noexcept { return instructions.empty(); }
};

/**
 * @brief Распечатать программу	в поток.
 * @param str - поток вывода.
 * @param prog - программа.
 * @return Ссылка на поток `str`.
 */
std::ostream &operator <<(std::ostream &str, const Program &prog) noexcept;
