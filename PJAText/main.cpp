#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

/**
 * Funkcja sprawdzająca czy istnieje plik poday w argumencie programu
 * @param path - ścieżka do pliku
 * @return true - jeśli można otworzyć plik podany w ścieżce
 *         false - jeśli nie można otworzyć plik podany w ścieżce
 */
bool flag_f(const std::string &path) {
    std::fstream in(path);
    if (in.is_open()) {
//        std::cout << "**File Opened**\n";
        in.close();
        return true;
    } else {
        std::cout << "**** Podana sciezka jest nie prawidlowa ****";
        exit(10);
    }
}

/**
 *  Funkcja zliczająca ilość linii w pliku o podanym w parametrze
 * @param path - ścieżka do pliku
 * @return ilość linii w pliku
 */
int flag_n(const std::string &path) {
    std::fstream in(path);
    std::string str;
    int lines = 0;
    if (in) {
        while (std::getline(in, str)) {
            lines++;
        }
        in.close();
//        std::cout << "** File closed **" << '\n';
    } else
        std::cout << "ERROR\n";

    return lines;
}

/// Funkcja zliczająca liczbę cyfr w pliku o podanym w parametrze
/// @param path - ścieżka do pliku
/// \return liczba cyfr w pliku
int flag_d(const std::string &path) {

    std::fstream in(path);
    std::smatch match;
    std::regex r("[\\d]+");
    int i = 0;
    if (in.good()) {
        while (in.good()) {
            std::string str;
            while (std::getline(in, str)) {
                while (regex_search(str, match, r)) {
                    i++;
                    str = match.suffix().str();
                }
            }
        }
    }

    return i;
}

/// Funkcja zliczająca liczbę liczb w pliku o podanym w parametrze
/// @param path - ścieżka do pliku
/// \return liczba liczb w pliku
int flag_dd(const std::string &path) {
    std::fstream in(path);
    std::smatch match;
    std::regex r(R"([\s-][\d]+\b)");
    int i = 0;
    if (in.good()) {
        while (in.good()) {
            std::string str;
            while (std::getline(in, str)) {
                while (regex_search(str, match, r)) {
                    i++;
                    str = match.suffix().str();

                }
            }
        }
    }
    return i;
}

/// Funkcja sortująca zawartość pliku o podanym w parametrze
/// @param vec - vector stringów zawierający zawarrość pliku
/// \return string zawierający zawartość pliku posortowaną rosnąco (A->Z)
std::string flag_s(std::vector<std::string> &vec) {
    std::sort(vec.begin(), vec.end());
    std::string res;

    for (const auto &a : vec) {
        res += a;
        res += " ";
    }
    return res;
}

/// Funkcja sortująca zawartość pliku o podanym w parametrze
/// @param vec - vector stringów zawierający zawarrość pliku
/// \return string zawierający zawartość pliku posortowaną malejąco (Z->A)
std::string flag_rs(std::vector<std::string> &vec) {
    std::sort(vec.begin(), vec.end(), [](const std::string &a, const std::string &b) { return a > b; });
    std::string res;

    for (const auto &a : vec) {
        res += a;
        res += " ";
    }
    return res;
}

/// Funkcja zliczająca liczbę znaków w pliku podanym w parametrze
/// @param path - ścieżka do pliku
/// \return liczba znaków w pliku
int flag_c(const std::string &path) {
    std::fstream in(path);
    int count = 0;
    std::string str;
    while (in.good()) {
        std::getline(in, str);
        for (const char &a : str) {
            if (!isspace(a))
                count++;
        }
    }
    in.close();
    return count;
}

/// Funkcja zliczająca liczbę znaków w pliku podanym w parametrze
/// @param vec - vector stringów zawierający zawarrość pliku
/// \return liczba znaków w pliku
int flag_c(const std::vector<std::string> &vec) {
    int count = 0;
    for (auto &a : vec) {
        count += a.size();
    }
    return count;
}

/// Funkcja sprawdzająca istnienie anagramów słów podanych w argumencie wywołania w pliku
/// \param content - vector stringów zawierający wyrazy z pliku podanego w argumentach wywołaia programu
/// \param param - vector stringów zawierający wyrazy podane po fladze -a
/// \return string z wystąpieniami anagramów lub informacja o ich braku
std::string flag_a(const std::vector<std::string> &content, const std::vector<std::string> &param) {
    std::string res;
    std::string wyr1;
    std::string wyr2;
    for (auto &a : param) {
        for (auto &b : content) {
            if (a.size() == b.size()) {
                wyr1 = a;
                wyr2 = b;

                std::sort(wyr1.begin(), wyr1.end());
                std::sort(wyr2.begin(), wyr2.end());

                if (wyr1 == wyr2) {
                    res += b;
                }
            }
        }
    }
    return res.empty() ? "Nie znaleziono anagramow\n" : res;
}

/// Funkcja sprawdzająca istnienie palindromów słów podanych w argumencie wywołania w pliku
/// \param content - vector stringów zawierający wyrazy z pliku podanego w argumentach wywołaia programu
/// \param param - vector stringów zawierający wyrazy podane po fladze -p
/// \return string z wystąpieniami palindromów lub informacja o ich braku
std::string flag_p(const std::vector<std::string> &cont, const std::vector<std::string> &param) {

    std::string res;
    std::string wyr1;
    std::string wyr2;

    for (auto &a : param) {
        for (auto &b : cont) {
            if (a.size() == b.size()) {
                wyr1 = a;
                wyr2 = b;

                std::reverse(wyr1.begin(), wyr1.end());

                if (wyr1 == wyr2) {
                    res += wyr2;
                }
            }
        }
    }
    return res.empty() ? "Nie znaleziono palindromow\n" : res;
}

/// Funkcja zapisująca zawartość pliku podanego po parametrze -f do vectora stringów
/// \param path - ścieżka do pliku
/// \return vector stringów z zawartością pliku
std::vector<std::string> import(const std::string &path) {
    std::vector<std::string> result;
    std::fstream in(path);
    if (in.good()) {
        std::string str;
        while (!in.eof()) {
            in >> str;

            result.push_back(str);
        }
        in.close();
    }

    return result;
}

///Funkcja wyświetlająca informacje o prograie
/// \return informacje o programie
std::string show_info() {
    return std::string("\t\t\t **** PJAText ****\n "
                       "PJAText jest to  program, sluzacy do operacji na plikach tekstowych\nzapisanych  w  formacie  ANSI (tylko  znaki  ASCII).\n\n"
                       "Brak flagi [--help] \n\tPokazuje opis programu\n\n"
                       "--file [-f]  \n\tpo tej fladze nalezy podac  sciezka do pliku zrodlowego\n\n"
                       "--newlines [-n] \n\t wyswietlia liczbe linii z pliku zrodlowego\n\n"
                       "--digits [-d] \n\twyswietlia liczbe cyfr z pliku zrodlowego\n\n"
                       "--numbers [-dd] \n\twyswietlia liczbe liczb z pliku zrodlowego \n\n"
                       "--chars [-c] \n\twyswietlia liczbe znakow z pliku zrodlowego \n\n"
                       "--anagrams [-a] \n\tpowinna byc ostatnia sprecyzowana  flaga  i oczekiwac, ze nastapi po niej nieokreslona liczba slow.\n"
                       "\twyswietli anagramy znajdujace sie w pliku\n\n"
                       "--palindroms [-p] \n\tpowinna byc ostatnia sprecyzowana  flaga  i oczekiwac, ze nastapi po niej nieokreslona liczba slow.\n"
                       "\twyswietli palindromy znajdujace sie w pliku\n\n"
                       "--sorted [-s]  \n\twyswietlia  wszystkie  slowa  z  pliku  w kolejnosci alfabetycznej\n\n"
                       "--reverse-sorted [-rs] \n\twyswietlia  wszystkie  slowa  z  pliku  w kolejnosci odwrotnej od alfabetycznej\n\n"
                       "--output [-o] \n\tprogram swoj output przekieruje do pliku, ktorego sciezka jest okreslona tuz po tej fladze\n\n"
                       "--input [-i] \n\tflaga ta poprzedza sciezke do pliku wejsciowego. Plik wejsciowy to taki, ktorego zawartosc bedzie\n"
                       "\tinterpretowana jako reszta polecen (flag) uruchomienia programu.\n\n");

}


int main(int argc, char **argv) {


/**
 *Lista argumentów przekazanych do main()
 */
    std::vector<std::string> args(argv + 1, argv + argc);

    if (args.empty() or args.size() == 1 && args[0] == "--help") {
        std::cout << show_info();
        return 0;
    }


    if (args.size() == 2 && args[0] == "-i" or args[0] == "--input") {
//        std::cout << args[0] << ',' << args[1];
        std::string in_path = args[1];
        args.clear();

        std::string res;
        std::fstream file_in;
        file_in.open(in_path, std::ios::in);
        while (file_in.good()) {
            file_in >> res;
            args.push_back(res);
        }
        std::cout << "**** Dane zostaly odebrane z: " << in_path << " ****\n";
        file_in.close();
    }
/**
 *lista par Flaga -> Argument
 */
    std::vector<std::pair<std::string, std::string>> pairs;
/**
 *Vector stringow zawierajacy zawartosc pliku
 */
    std::vector<std::string> content;
/**
 *Ścieżka sprezyzowana po fladze -f
 */
    std::string path;
/**
 *Tekst do wyświetlenia
 */
    std::string output;
/**
 *Ścieżka do pliku wyjściowego
 */
    std::string out_path;
    bool is_out;
/**
 *Vector parametrów dla flag -a i -p
 */
    std::vector<std::string> param;

    for (int i = 0; i < args.size(); i++) {
        if (args[i] == "-f" or args[i] == "--file") {
            if (flag_f(args[i + 1]))
                path = args[i + 1];
            pairs.emplace_back(std::string("-f"), std::string(args[i + 1]));
        } else if (args[i] == "-n" or args[i] == "--newline") {
            pairs.emplace_back(std::string("-n"), std::string());
        } else if (args[i] == "-d" or args[i] == "--digits") {
            pairs.emplace_back(std::string("-d"), std::string());
        } else if (args[i] == "-dd" or args[i] == "--numbers") {
            pairs.emplace_back(std::string("-dd"), std::string());
        } else if (args[i] == "-c" or args[i] == "--chars") {
            pairs.emplace_back(std::string("-c"), std::string());
        } else if (args[i] == "-a" or args[i] == "--anagrams") {
            std::string arg;
            for (int j = i + 1; j < args.size(); j++) {
                if (!args[j].at(0) == '-') {
                    arg += args[j] + " ";
                    param.emplace_back(args[j]);
                } else {
                    output += "Bledne wywolanie flagi " + args[i] +
                              ", nieprawidlowy parametr " + args[j] + '\n' +
                              "Flaga " + args[i] + " powinna byc ostatnim argumentem wywolania, " +
                              "\noraz jej parametry NIE powinny zawierac innych argumentow" + '\n';
                    break;
                }
            }
            pairs.emplace_back(std::string("-a"), arg);
            break;
        } else if (args[i] == "-p" or args[i] == "--palindroms") {
            std::string arg;
            for (int j = i + 1; j < args.size(); j++) {
                if (!args[j].at(0) == '-') {
                    arg += args[j] + " ";
                    param.emplace_back(args[j]);
                } else {
                    output += "Bledne wywolanie flagi " + args[i] +
                              ", nieprawidlowy parametr " + args[j] + '\n' +
                              "Flaga " + args[i] + " powinna byc ostatnim argumentem wywolania, " +
                              "\noraz jej parametry NIE powinny zawierac innych argumentow" + '\n';
                    break;
                }
            }
            pairs.emplace_back(std::string("-p"), arg);
            break;
        } else if (args[i] == "-s" or args[i] == "--sorted") {
            pairs.emplace_back(std::string("-s"), std::string());
        } else if (args[i] == "-rs" or args[i] == "--reverse-sorted") {
            pairs.emplace_back(std::string("-rs"), std::string());
        } else if (args[i] == "-o" or args[i] == "--output") {
            pairs.emplace_back(std::string("-o"), std::string(args[i + 1]));
        } else if (args[i] == "-i" or args[i] == "--input") {
            pairs.emplace_back(std::string("-i"), std::string(args[i + 1]));
        } else if (args[i].at(0) == '-') {
            output += "Nie znane polecenie! " + args[i] + '\n';
        }
    }

/*    for (auto a : pairs) {
        std::cout << a.first << " -> " << a.second << '\n';
    }
    std::cout << '\n';
    for (auto a : param) {
        std::cout << a << ", ";
    }*/


    for (const auto &a : pairs) {
        if (!path.empty() && a.first == "-n") {
            output += "Liczba linii w pliku: " + std::to_string(flag_n(path)) + '\n';
        }
        if (!path.empty() && a.first == "-d") {
            output += "Liczba cyfr w pliku: " + std::to_string(flag_d(path)) + '\n';
        }
        if (!path.empty() && a.first == "-dd") {
            output += "Liczba liczb w pliku (oddzielone spacjami): " + std::to_string(flag_dd(path)) + '\n';
        }
        if (!path.empty() && a.first == "-c") {
            if (!content.empty()) {
                output += "Liczba znakow w pliku: " + std::to_string(flag_c(content)) + '\n';
            } else
                output += "Liczba znakow w pliku: " + std::to_string(flag_c(path)) + '\n';
        }
        if (!path.empty() && a.first == "-a") {
            if (content.empty())
                content = import(path);
            output += "Anagramy w pliku: " + flag_a(content, param) + '\n';
        }
        if (!path.empty() && a.first == "-p") {
            if (content.empty())
                content = import(path);
            output += "Palindromy w pliku: " + flag_p(content, param) + '\n';
        }
        if (!path.empty() && a.first == "-s") {
            if (content.empty())
                content = import(path);
            output += "Posortowana zawartosc pliku (A->Z): \n" + flag_s(content) + '\n';
        }
        if (!path.empty() && a.first == "-rs") {
            if (content.empty())
                content = import(path);
            output += "Posortowana zawartosc pliku (Z->A): \n" + flag_rs(content) + '\n';
        }
        if (!path.empty() && a.first == "-o") {
            is_out = true;
            out_path = a.second;
        }

    }
    if (path.empty()) {
        output += "**** Brak podanego argumentu wywolania -f ****\n";
    }



//    for (const auto &a : pairs) {
//        std::cout << a.first << "-> " << a.second << '\n';
//    }

    if (is_out) {
        std::fstream file_out;
        file_out.open(out_path, std::ios::out);
        if (file_out.good()) {
            file_out << output;
            std::cout << "**** Dane zostaly zapisane w pliku: " << out_path << " ****\n";
        }
        file_out.close();
    } else {
        std::cout << output;
    }

    return 0;
}
