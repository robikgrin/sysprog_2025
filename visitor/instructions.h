#pragma once

#include <ostream>

/// Forward объявление класса.
class Visitor;

/**
 * @brief Абстрактная инструкция.
 */
class Instruction
{
public:
	/**
	 * @brief Создать инструкцию заданной длительности.
	 * @param duration - длительность.
	 */
	explicit Instruction(double duration) { setDuration(duration); }

	/**
	 * @brief Деструктор.
	 */
	virtual ~Instruction() = default;

	/**
	 * @brief Распечатать инструкцию в поток.
	 * @param str - поток вывода.
	 */
	virtual void print(std::ostream &str) const noexcept = 0;

	/**
	 * @brief Вернуть длительность инструкции.
	 */
	double getDuration() const noexcept { return duration; }

	/**
	 * @brief Установить длительность инструкции.
	 * @param val - новая длительность.
	 */
	void setDuration(double val);

	/**
	 * @brief Метод, необходимый для реализации паттерна "посетитель".
	 * @param visitor - посетитель.
	 */
	virtual void accept(Visitor *visitor) const = 0;

private:
	double duration;
};

/**
 * @brief Инструкция, которая выключает сигнал на заданную длительность.
 */
class Disable: public Instruction
{
public:
	/**
	 * @brief Создать инструкцию заданной длительности.
	 * @param duration - длительность.
	 */
	explicit Disable(double duration):
		Instruction(duration)
	{}

	/**
	 * @copydoc Instruction::print
	 */
	void print(std::ostream &str) const noexcept override;

	/**
	 * @brief `accept` для посетителя.
	 */
	void accept(Visitor *visitor) const override;
};

/**
 * @brief Инструкция, которая генерирует сигнал заданной частоты.
 */
class ConstFrequency: public Instruction
{
public:
	/**
	 * @brief Создать инструкцию заданной длительности с указанием частоты.
	 * @param duration - длительность.
	 * @param freq - частота.
	 */
	explicit ConstFrequency(double duration, double freq):
		Instruction(duration)
	{
		setFrequncy(freq);
	}

	/**
	 * @copydoc Instruction::print
	 */
	void print(std::ostream &str) const noexcept override;

	/**
	 * @brief Вернуть значение частоты.
	 */
	double getFrequncy() const noexcept { return freq; }

	/**
	 * @brief Установить значение частоты.
	 */
	void setFrequncy(double val);

	/**
	 * @brief `accept` для посетителя.
	 */
	void accept(Visitor *visitor) const override;

private:
	double freq;
};

/**
 * @brief Инструкция, которая генерирует сигнал с линейно изменяющейся частотой.
 */
class SweepFrequency: public Instruction
{
public:
	/**
	 * @brief Создать инструкцию заданной длительности с указанием начальной и
	 * конечной частоты.
	 * @param duration - длительность.
	 * @param start - начальная частота.
	 * @param stop - конечная частота.
	 */
	explicit SweepFrequency(double duration, double start, double stop):
		Instruction(duration)
	{
		setStartFreq(start);
		setStopFreq(stop);
	}

	/**
	 * @copydoc Instruction::print
	 */
	void print(std::ostream &str) const noexcept override;

	/**
	 * @brief Вернуть значение начальной частоты.
	 */
	double getStartFreq() const noexcept { return start; }

	/**
	 * @brief Установить значение начальной частоты.
	 */
	void setStartFreq(double val);

	/**
	 * @brief Вернуть значение конечной частоты.
	 */
	double getStopFreq() const noexcept { return stop; }

	/**
	 * @brief Установить значение конечной частоты.
	 */
	void setStopFreq(double val);

	/**
	 * @brief `accept` для посетителя.
	 */
	void accept(Visitor *visitor) const override;

private:
	double start;
	double stop;
};

/**
 * @brief Распечатать инструкцию в поток.
 * @param str - поток вывода.
 * @param instr - инструкция.
 * @return Ссылка на поток `str`.
 */
inline std::ostream &operator <<(std::ostream &str, const Instruction &instr) noexcept
{
	instr.print(str);
	return str;
}
