# Kowboj
Niesamowicie ekscytująca gra zręcznościowa pozwalająca wcielić się w postać kowboja przemierzającego bezkresne połacie amerykańskich prerii na grzbiecie swojego wiernego rumaka. Wszystko utrzymane w estetyce dzikiego zachodu!
## Instalacja
* Zalecana jest instalacja CLion od Jetbrains i odtworzenie gry za jego pomocą.
* Konieczna jest instalacja biblioteki Allegro5. Żeby to zrobić, najpierw trzeba pobrać i zainstalować MinGW (https://sourceforge.net/projects/mingw/), a następnie pobrać pliki allegro: paczkę MinGW 4.7.0 w wersji ZIP (https://www.allegro.cc/files/). Po rozpakowaniu paczki allegro, należy przekopiować wszystkie foldery do lokalizacji kompilatora MinGW.
* Po pobraniu kodu i grafik z repozytorium (https://github.com/sunsetcorp/projekt-WDP.git) i otworzeniu w CLion, trzeba się upewnić, czy w file>settings>build, execution, deployment>toolchains jest ustawione MinGW.
* Jeśli tak, pozostaje tylko kliknąć zieloną strzałkę w prawym rogu i oddać się rozgrywce.
## Jak grać?
Celem gry jest unikanie napotkanych przeszkód, każdy skok umożliwia zdobycie punktów.
* Grę rozpoczyna się naciśnięciem __spacji__.
* Przeskakiwać nad przeszkodami można za pomocą __spacji__ albo __strzałki w górę__.
* Po wpadnięciu w przeszkodę gra kończy się; klikając __spację__ można rozpocząć grę od nowa, zaś __enter__ wyłącza grę.
* Jeśli udało Ci się osiągnąć rekordowy wynik, zostaje on zapisany w highestscore.txt.
