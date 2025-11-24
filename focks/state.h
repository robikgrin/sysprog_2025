#include <complex>
#include <vector>
#include <map>
#include <iostream>

using Fock = std::vector<int>;
using Amp = std::complex<double>;
using State = std::map<Fock, Amp>;


State add(const State &s1, const State &s2) {
    State result;
    auto it1 = s1.begin();
    auto it2 = s2.begin();

    while (it1 != s1.end() && it2 != s2.end()) {
        if (it1->first < it2->first) {
            // Состояние в s1 лексикографически меньше. Значит, такого состояния нет в s2. 
            // Добавляем состояние из s1 в result. Перемещаем итератор к следующему элементу s1.
            result.insert(result.end(), *it1);
            it1++;
        } 
        else if (it2->first < it1->first) {
            // Состояние в s2 лексикографически меньше. Значит, такого состояния нет в s1. 
            // Добавляем состояние из s2 в result. Перемещаем итератор к следующему элементу s2.
            result.insert(result.end(), *it2);
            it2++;
        } 
        else { 
            // Состояния равны => суммируем амплитуды. 
            Amp sum_amp = it1->second + it2->second;
            result.insert(result.end(), {it1->first, sum_amp});
            it1++;
            it2++;
        }
    }

    // Состояния в s2 закончились, а в s1 остались - дописывыем их к result
    while (it1 != s1.end()) {
        result.insert(result.end(), *it1);
        it1++;
    }

    // Состояния в s1 закончились, а в s2 остались - дописывыем их к result
    while (it2 != s2.end()) {
        result.insert(result.end(), *it2);
        it2++;
    }

    return result;
} 


void print(const State &s) {
    for (const auto& pair : s) {
        const Fock& fock = pair.first;
        const Amp& amp = pair.second;
        std::cout << '|';
        for (int n : fock) {
            std::cout << n << ' ';
        }
        std::cout <<  "> : "  << amp.real() << " + " << amp.imag() << 'j' << '\n';
    }
}