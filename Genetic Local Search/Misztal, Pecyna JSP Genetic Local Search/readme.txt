Kod trzeba skompilowaæ przy u¿yciu c++11 komend¹ g++ -std=c++11, plik main to JSP.cpp, czyli kompilacja wygl¹da w sposób nastêpuj¹cy:
g++ -std=c++11 JSP.cpp vertex.cpp jobsData.cpp chromosome.cpp graph.cpp

skompilowany plik uruchamia siê z nastêpuj¹cymi opcjami <nazwa pliku> <rodzaj instancji> <liczba pierwszych zadan>, gdzie liczba pierwszych zadañ jest opcjonalna, jeœli nie wyst¹pi za³adowane bêd¹ wszystkie zadania, czyli:

./a.out abz7.txt o

oznacza uruchomienie instancji abz7 jako orlib, a

./a.out tai24.txt t 3

oznacza oznacza uruchomienie instancji tai20 jako taillard z pierwszymi 3 zadaniami.

Program zwraca plik tekstowy czasy.txt z wypisanymi polepszeniami makespanu w czasie w formacie: <najlepszy makespan> <srednia z populacji> <najgorszy makespan> <czas>,
oraz plik solution.txt do testowania w sprawdzarce w formacie podanym na Pana stronie.

Instancja testowa musi znajdowaæ siê w tym samym pliku co program.