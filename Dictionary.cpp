#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>

#include <random>

#include <windows.h>

class Word
{
private:
    std::string eng_word = "";
    std::string rus_word = "";
    std::string note = "";
    std::string example = "";
public:
    Word()
    {
        std::cout << "Введите английское слово: ";
        std::cin >> eng_word;
        std::cout << "Введите русское слово: ";
        std::cin >> rus_word;
    }

    Word(std::string eng, std::string rus)
    {
        this->eng_word = eng;
        this->rus_word = rus;
    }

    std::string GetRusWord() const
    {
        return rus_word;
    }

    std::string GetEngWord() const
    {
        return eng_word;
    }

    void AddNote(std::string nt)
    {
        note += nt;
    }

    void RemoveNote()
    {
        note = "";
    }

    std::string GetNote() const
    {
        return note;
    }

    void AddExample(std::string xmpl)
    {
        example += xmpl;
    }

    void RemoveExample()
    {
        example = "";
    }

    std::string GetExample() const
    {
        return example;
    }

};


class Dictionary
{
private:
    std::vector<Word> dict = {
        Word("day", "день"),
        Word("money", "деньги"),
        Word("number", "число"),
        Word("oil", "нефть"),
        Word("part", "часть"),
        Word("people", "люди"),
        Word("time", "время"),
        Word("water", "вода"),
        Word("way", "путь"),
        Word("work", "работа"),
        Word("year", "год"),
        Word("bad", "плохой"),
        Word("good", "хороший"),
        Word("long", "длинный"),
        Word("new", "новый"),
        Word("other", "другой"),
        Word("short", "короткий"),
        Word("name", "имя"),
        Word("surname", "фамилия"),
        Word("life", "жизнь"),
        Word("kid", "ребёнок"),
        Word("adult", "взрослый"),
        Word("age", "возраст"),
        Word("arm", "рука"),
        Word("brain", "мозг"),
        Word("bone", "кость"),
        Word("lips", "губы"),
        Word("leg", "нога"),
        Word("dark", "тёмный"),
        Word("active", "активный"),
    };

public:
    void AddWord()
    {
        std::cout << "\n";
        Word word;
        dict.push_back(word);
    }

    void RemoveWord()
    {
        std::cout << "Введите английское слово для удаления: ";
        std::string str;
        std::cin >> str;

        auto iter = std::remove_if(dict.begin(), dict.end(), [&str](const Word& word) {
            return (word.GetEngWord() == str);
            });

        dict.erase(iter, dict.end());
    }

    void AddExampleWord()
    {
        std::string word;
        std::cout << "\nВведите слово для добавления примера использования: ";
        std::cin >> word;

        if (FindWord(word))
        {
            std::cin.ignore();
            std::string str;
            std::cout << "Введите предложение, которое хотите добавить: ";
            std::getline(std::cin, str);

            auto iter = std::find_if(dict.begin(), dict.end(), [&word](const Word& w)
                {
                    return w.GetEngWord() == word || w.GetRusWord() == word;
                }
            );

            (*iter).AddExample(str);
        }
        else
        {
            std::cout << "Данное слово в словаре отсутствует." << std::endl;
        }
        std::cout << "\n";
    }

    void ShowExampleWord()
    {
        std::string word;
        std::cout << "\nВведите слово для просмотра примера использования: ";
        std::cin >> word;

        if (FindWord(word))
        {
            auto iter = std::find_if(dict.begin(), dict.end(), [&word](const Word& w)
                {
                    return w.GetEngWord() == word || w.GetRusWord() == word;
                }
            );

            if ((*iter).GetExample() != "")
            {
                std::cout << "Пример использования:" << std::endl;
                std::cout << (*iter).GetExample() << std::endl;
            }
            else
                std::cout << "У слова \"" << (*iter).GetEngWord() << " - " << (*iter).GetRusWord() << "\" пример использования отсутствует." << std::endl;
        }
        else
        {
            std::cout << "Данное слово в словаре отсутствует." << std::endl;
            std::cout << std::endl;
        }
        std::cout << "\n";
    }

    void AddNoteWord()
    {
        std::string word;
        std::cout << "\nВведите слово к которому хотите добавить заметку: ";
        std::cin >> word;

        if (FindWord(word))
        {
            std::cin.ignore();
            std::string str;
            std::cout << "Введите заметку, которую хотите добавить к слову: ";
            std::getline(std::cin, str);

            auto iter = std::find_if(dict.begin(), dict.end(), [&word](const Word& w)
                {
                    return w.GetEngWord() == word || w.GetRusWord() == word;
                }
            );

            (*iter).AddNote(str);
        }
        else
        {
            std::cout << "Данное слово в словаре отсутствует." << std::endl;
        }
    }

    void ShowWordNote()
    {
        std::string word;
        std::cout << "\nВведите слово, заметку которого хотите посмотреть: ";
        std::cin >> word;

        if (FindWord(word))
        {
            auto iter = std::find_if(dict.begin(), dict.end(), [&word](const Word& w)
                {
                    return w.GetEngWord() == word || w.GetRusWord() == word;
                }
            );

            if ((*iter).GetNote() != "")
            {
                std::cout << "Данное слово содержит следующую заметку:" << std::endl;
                std::cout << (*iter).GetNote() << std::endl;
            }
            else
                std::cout << "У слова \"" << (*iter).GetEngWord() << " - " << (*iter).GetRusWord() << "\" заметка отсутствует." << std::endl;
         }
        else
        {
            std::cout << "Данное слово в словаре отсутствует." << std::endl;
            std::cout << std::endl;
        }
    }

    void ShowDict()
    {
        if (dict.size() == 0)
        {
            std::cout << "\tСловарь пуст..." << std::endl;
        }
        else
        {
            int width_eng = 9;
            int width_rus = 13;
            int column = 0;

            std::cout << "\n---------------------------------------------------------" << std::endl;

            for (auto& elem : dict)
            {
                std::cout << std::left << std::setw(width_eng) << elem.GetEngWord() << " - " << std::setw(width_rus) << elem.GetRusWord();
                column++;

                if (column == 2)
                {
                    std::cout << std::endl;
                    column = 0;
                }
            }
            std::cout << "\nКол-во пар слов в словаре: " << dict.size() << std::endl;
            std::cout << "---------------------------------------------------------" << std::endl;
        }

    }

    void FindWord()
    {
        std::cout << "Введите английское или русское слово для поиска: ";
        std::string str;
        std::cin >> str;

        auto result = std::find_if(dict.begin(), dict.end(), [&str](const Word& word)
            {
                return word.GetEngWord() == str || word.GetRusWord() == str;
            }
        );

        if (result == dict.end())
            std::cout << "Данное слово отсутствует в словаре!\n" << std::endl;
        else
            std::cout << "Данное слово присутствует в словаре!\n" << std::endl;
    }

    bool FindWord(std::string input_word)
    {
        auto result = std::find_if(dict.begin(), dict.end(), [&input_word](const Word& word)
            {
                return word.GetEngWord() == input_word || word.GetRusWord() == input_word;
            }
        );

        return (result != dict.end());
    }

    void FindMatches()
    {
        int width_eng = 9;
        int width_rus = 13;
        int column = 0;
        std::list<Word> list;
        std::string str;

        std::cout << "Введите кусочек слова: ";
        std::cin >> str;

        for (auto const& word : dict)
        {
            if (word.GetEngWord().starts_with(str) || word.GetRusWord().starts_with(str))
                list.push_back(word);
        }

        std::cout << "\n---------------------------------------------------------" << std::endl;
        std::cout << "По запросу \"" << str << "\" были найдены следующие слова:" << std::endl;

        for (auto const& elem : list)
        {
            std::cout << std::left << std::setw(width_eng) << elem.GetEngWord() << " - " << std::setw(width_rus) << elem.GetRusWord();
            column++;

            if (column == 2)
            {
                std::cout << std::endl;
                column = 0;
            }

        }
        std::cout << "\n---------------------------------------------------------" << std::endl;
        std::cout << "\n";

    }

    void Sort()
    {
        int number;
        std::cout << "\nПо каким словам произвести сортировку?" << std::endl;
        std::cout << "Если по английским введите 1, если по русским введите 2: ";
        std::cin >> number;

        if (number > 2 || number < 1)
        {
            std::cout << "Вы ввели неверное значение!" << std::endl;
            std::cout << "Сортировка не может быть выполнена.\n" << std::endl;
            return;
        }

        std::sort(dict.begin(), dict.end(), [&number](const Word& w1, const Word& w2)
            {
                return ((number == 1) ? (w1.GetEngWord() < w2.GetEngWord()) : (w1.GetRusWord() < w2.GetRusWord()));
            });

        std::cout << "Сортировка выполнена!\n" << std::endl;
    }

    void Shuffle()
    {
        std::shuffle(dict.begin(), dict.end(), std::mt19937(std::random_device()()));
        std::cout << "Сортировка выполнена!\n" << std::endl;
    }

    void Game()
    {
        int total = 0;
        int correct = 0;
        int wrong = 0;
        int number;

        std::cout << "\nДобро пожаловать в ВИКТОРИНУ!" << std::endl;
        std::cout << "Сейчас мы проверим ваши знания." << std::endl;
        std::cout << "Если хотите остановить викторину введите 0(ноль)." << std::endl;
        std::cout << "Перед викториной рекомендуется перемешать слова. Удачи!!! :)" << std::endl;
        std::cout << "Какие слова желаете переводить?(1 - английские, 2 - русские): " << std::endl;

        std::cin >> number;
        if (number > 2 || number < 1)
        {
            std::cout << "Вы ввели неверное значение!" << std::endl;
            std::cout << "Викторина закрыта. Вы удалены из аудитории!\n" << std::endl;
            return;
        }
        
        for (auto& word : dict)
        {
            std::string str;
            std::cout << "Введите перевод слова " << ((number == 1) ? word.GetEngWord() : word.GetRusWord()) << ": ";
            std::cin >> str;

            if (str == "0") break;
            if (str == ((number == 1) ? word.GetRusWord() : word.GetEngWord()))
                correct++;
            else
                wrong++;

            total++;
        }

        std::cout << "\nВы были протестированы на следующем количестве слов: " << total << std::endl;
        if (total > 0)
        {
            std::cout << "Количество верных ответов: " << correct << std::endl;
            std::cout << "Процент верных ответов: " << (correct * 100 / total) << "%" << std::endl;
            std::cout << std::endl;
        }
        std::cout << "Викторина окончена. Возвращайтесь снова :)\n" << std::endl;
    }
};



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "#########################################################" << std::endl;
    std::cout << "\tДобро пожаловать в программу СЛОВАРЬ" << std::endl;
    std::cout << "#########################################################" << std::endl;

    Dictionary dict;

    std::string choice;

    do
    {
        std::cout << "1. Показать словарь" << std::endl;
        std::cout << "2. Добавить слово в словарь" << std::endl;
        std::cout << "3. Удалить слово из словаря" << std::endl;
        std::cout << "4. Сортировка словаря" << std::endl;
        std::cout << "5. Сортировка словаря случайным образом" << std::endl;
        std::cout << "6. Узнать есть ли слово в словаре" << std::endl;
        std::cout << "7. Найти все похожие слова в словаре" << std::endl;
        std::cout << "8. Викторина по всем словам" << std::endl;
        std::cout << "9. Добавить заметку к слову" << std::endl;
        std::cout << "10. Просмотреть заметку к слову" << std::endl;
        std::cout << "11. Добавить пример использования к слову" << std::endl;
        std::cout << "12. Просмотреть пример использования к слову" << std::endl;
        std::cout << "EXIT <- Введите 0 чтобы совершить выход из программы" << std::endl;
        std::cin >> choice;

        if (choice == "1") { dict.ShowDict(); }
        else if (choice == "2") {
            dict.AddWord();
            std::cout << "Слово добавлено.\n" << std::endl;
        }
        else if (choice == "3") {
            dict.RemoveWord();
            std::cout << "Слово удалено.\n" << std::endl;
        }
        else if (choice == "4") { dict.Sort(); }
        else if (choice == "5") { dict.Shuffle(); }
        else if (choice == "6") { dict.FindWord(); }
        else if (choice == "7") { dict.FindMatches(); }
        else if (choice == "8") { dict.Game(); }
        else if (choice == "9") { dict.AddNoteWord(); }
        else if (choice == "10") { dict.ShowWordNote(); }
        else if (choice == "11") { dict.AddExampleWord(); }
        else if (choice == "12") { dict.ShowExampleWord(); }

    } while (choice != "0");


    return 0;
}