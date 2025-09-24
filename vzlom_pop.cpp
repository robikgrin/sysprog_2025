#include <iostream>   
#include <fstream>  
#include <vector>    
#include <cstring>    
#include <elf.h>     

// Функция изменяет видимость (visibility) символа в ELF-библиотеке
void change_symb_visibility(const std::string &filename, const std::string &symbol_name, unsigned char new_visibility) {
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);

    //Не смогли открыть файл
    if (!file) {
        std::cerr << "could not open file " << filename << std::endl;
        return; 
    }

    // Читаем ELF header 
    Elf64_Ehdr elf_header;
    file.read(reinterpret_cast<char*>(&elf_header), sizeof(elf_header));

    // Переходим к таблице секций (e_shoff — смещение, где начинается массив секций)
    file.seekg(elf_header.e_shoff, std::ios::beg);

    // Читаем все заголовки секций в вектор (e_shnum - число заголовков)
    std::vector<Elf64_Shdr> section_headers(elf_header.e_shnum);
    for (auto &section : section_headers) {
        file.read(reinterpret_cast<char*>(&section), sizeof(section));
    }

    // Получаем секцию с именами секций
    Elf64_Shdr &shstrtab_section = section_headers[elf_header.e_shstrndx];

    // Читаем содержимое этой строковой таблицы
    file.seekg(shstrtab_section.sh_offset, std::ios::beg);
    std::string shstrtab;
    shstrtab.resize(shstrtab_section.sh_size);
    file.read(shstrtab.data(), shstrtab.size());

    // Указатели на нужные секции dynsym, dynstr
    Elf64_Shdr *dynsym_section = nullptr;
    Elf64_Shdr *dynstr_section = nullptr;

    for (const auto &section : section_headers) {
        std::string section_name(&shstrtab[section.sh_name]);
        if (section_name == ".dynsym") {
            dynsym_section = const_cast<Elf64_Shdr*>(&section);
        } else if (section_name == ".dynstr") {
            dynstr_section = const_cast<Elf64_Shdr*>(&section);
        }
    }

    // Если одна из секций не найдена - вываливаемся 
    if (!dynsym_section || !dynstr_section) {
        std::cerr << ".dynsym or .dynstr section not found." << std::endl;
        return;
    }

    // Читаем таблицу символов из секции .dynsym
    file.seekg(dynsym_section->sh_offset, std::ios::beg);
    size_t num_symbols = dynsym_section->sh_size / sizeof(Elf64_Sym); // количество символов
    std::vector<Elf64_Sym> symbols(num_symbols);
    file.read(reinterpret_cast<char*>(symbols.data()), dynsym_section->sh_size);

    // Читаем имена символов из dynstr
    file.seekg(dynstr_section->sh_offset, std::ios::beg);
    std::vector<char> dynstr(dynstr_section->sh_size);
    file.read(dynstr.data(), dynstr.size());

    bool symbol_found = false;
    for (auto &symbol : symbols) {
        // Получаем имя символа по индексу st_name (смещение в .dynstr)
        std::string name(&dynstr[symbol.st_name]);

        // Если имя совпало с искомым
        if (name == symbol_name) {
            symbol_found = true;

            // Меняем поле st_other: оно хранит видимость
            // Обнуляем последние два  бита (маска 0x3) и записываем новое значение
            symbol.st_other = (symbol.st_other & ~ELF64_ST_VISIBILITY(0x3)) | ELF64_ST_VISIBILITY(new_visibility);

            // Перемещаемся к нужной позиции в файле (смещение конкретного символа)
            file.seekp(dynsym_section->sh_offset + (&symbol - symbols.data()) * sizeof(Elf64_Sym), std::ios::beg);

            // Записываем изменённый символ обратно в файл
            file.write(reinterpret_cast<const char*>(&symbol), sizeof(symbol));
            break;
        }
    }

    // Если символ не нашли - ошибка
    if (!symbol_found) {
        std::cerr << "symbol " << symbol_name << " not found in .dynsym." << std::endl;
    } else {
        std::cout << "symbol visibility changed successfully." << std::endl;
    }

    file.close();
}

int main(int argc, char *argv[]) {
    // Проверяем, что передан хотя бы один аргумент (имя ELF-файла)
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <libsecret.so>" << std::endl;
        return 1;
    }

    // Имя файла берём из аргумента
    std::string filename = argv[1];

    std::string symbol_name = "_Z12authenticatePKc";

    unsigned char new_visibility = STV_DEFAULT;

    
    change_symb_visibility(filename, symbol_name, new_visibility);

    return 0;
}
