# MFCDeletFile
Zadanie na potrzeby rekrutacji
Wersja podstawowa: 
Napisać aplikację okienkową (za pomocą mfc) – preferowane rozwiązanie lub konsolową, w języku programowania C++ na platformę Windows, pozwalającą na wskazanie folderu na dysku, w którym usunięte zostaną (w całej strukturze podkatalogów) pliki spełniające określony warunek filtrowania oraz puste katalogi.
Przeszukiwany folder ma być drzewem podkatalogów posiadającym co najmniej trzy poziomy zagnieżdżenia.
Struktura podkatalogów ma być wynikowo pozbawiona pustych folderów (bez względu na to, czy w danym podkatalogu były wcześniej pliki).
Po uruchomieniu procesu usuwania plików/folderów aplikacja musi wyświetlać postęp działania (na przykład pasek postępu lub procentowy przyrost). Jednoznacznie ma być pokazany start i koniec procesu.
Warunki filtrowania plików:
a)	według czasu utworzenia
b)	według czasu modyfikacji
c)	według czasu ostatniego użycia
Aby obsłużyć wszystkie warunki filtrowania będzie niezbędne użycie WinAPI (nie trzeba do wszystkich warunków go używać).
Aplikacja powinna umożliwiać zdefiniowanie zakresu czasowego dla poszczególnych warunków filtrowania, w którym zarówno dolny, jak i górny przedział może być otwarty.
Parametry programu: ścieżka do folderu, warunek filtrowania, czas lub zakres czasowy.
Czas realizacji: 6 godzin

Wersja rozszerzona:
Wprowadzenie w aplikacji wielowątkowości przyspieszającej działanie programu.

plik "Main.zip" zawiera testowe drzewo katalogów
