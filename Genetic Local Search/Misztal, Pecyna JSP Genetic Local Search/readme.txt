Kod trzeba skompilowa� przy u�yciu c++11 komend� g++ -std=c++11, plik main to JSP.cpp, czyli kompilacja wygl�da w spos�b nast�puj�cy:
g++ -std=c++11 JSP.cpp vertex.cpp jobsData.cpp chromosome.cpp graph.cpp

skompilowany plik uruchamia si� z nast�puj�cymi opcjami <nazwa pliku> <rodzaj instancji> <liczba pierwszych zadan>, gdzie liczba pierwszych zada� jest opcjonalna, je�li nie wyst�pi za�adowane b�d� wszystkie zadania, czyli:

./a.out abz7.txt o

oznacza uruchomienie instancji abz7 jako orlib, a

./a.out tai24.txt t 3

oznacza oznacza uruchomienie instancji tai20 jako taillard z pierwszymi 3 zadaniami.

Program zwraca plik tekstowy czasy.txt z wypisanymi polepszeniami makespanu w czasie w formacie: <najlepszy makespan> <srednia z populacji> <najgorszy makespan> <czas>,
oraz plik solution.txt do testowania w sprawdzarce w formacie podanym na Pana stronie.

Instancja testowa musi znajdowa� si� w tym samym pliku co program.