*   Aplikację napisz w języku C++ pod środowisko Linux (Ubuntu, Mint czy inne
    kompatybilne z nimi).
*   Kod powinien być zgodny z C++03. c++11
*   Powinieneś stworzyć skrypty budujące aplikację (najlepiej CMake).
*   Nie korzystaj z unikatowych zależności których zapewne na naszych
    komputerach nie będzie – zaoszczędzi nam to niepotrzebnych zmartwień
    związanych z „u mnie działa” czy „u mnie się buduje”.
*   Staraj się pisać kod „ładny”, bezpieczny, w miarę możliwości optymalny
    (pracujemy na systemach czasu rzeczywistego w których często czas
    procesora będzie dla Ciebie na wagę złota). Jeśli świadomie chcesz napisać
    gdzieś kod szybciej ale wiesz jak go zoptymalizować – napisz nam o tym w
    komentarzu i opisz jak byś go optymalizował.
*   Zadbaj o poprawne zarządzanie pamięcią – nie zostaw żadnych wycieków
    pamięci.
*   Użyj semaforów lub mutexów do synchronizacji wątków w procesie
    (pthread.h).
*   Komentuj dobrze kod.

Sma aplikacja powinna wyglądać następująco:
*   W main utwórz 7 wątków
*   T1 T2 i T3 będą wątkami-klientami
*   T4 i T5 będzie wątkiem serwerem dla klientów
*   T6 będzie wątkiem alokującym pamięć dla serwerów
*   T7 będzie wątkiem typu watchdog

Dla łatwiejszego zrozumienia dodam, że najprościej aby w aplikacji znajdowały się
przynajmniej dwa semafory/mutexy (wybór których z nich użyjesz zależy od Ciebie).
Jeden wspólny dla T1-5 (klienci dają zadania serwerowi) a drugi wspólny dla T4-6
(serwery dają zadanie dla alokatora pamięci).

Funkcjonalności samej aplikacji
Klienci:
*   Niech wątki klienckie losują liczby z zakresu od 0 do 2147483647 (typ int).
*   Niech dokonują losowania około 10x na sekundę (co 100ms).
*   Wylosowaną liczbę niech przekazują do serwerów (sposób przekazywania
    liczby możesz wybrać sam – możesz to zrobić nawet poprzez globalną tablicę
    inny kontener czy strukturę do której przekażesz uchwyt).
*   Wylosowane liczby niech klient sobie zapisuje w jakimś kontenerze (w formie
    intów) – przyda się to by móc stwierdzić czy wszystkie wylosowane liczby
    zostały przetworzone (wypisane) poprawnie przez serwery.
*   Przy zamykaniu aplikacji (ctrl+c w terminalu) przechwyć sygnał SIGINT,
    zatrzymaj losowanie liczb i przed zamknięciem aplikacji zapisz do plików w
    CWD przechowywane liczby w każdym z wątków (osobne 3 pliki).
    (najlepiej w formie tekstowej – aby porównanie liczb dla Ciebie i dla nas było
    najprostsze).

Serwery:
*   Serwer po otrzymaniu liczby powinien przekazać żądanie zaalokowania nowej
    pamięci do wątku zajmującego się alokacjami pamięci.
*   Po otrzymaniu uchwytu do zaalokowanej pamięci serwer powinien wykonać
    operację (zamiana liczby integer na jej tekstową reprezentacje)
    itoa(liczba_otrzymana_od_klienta, otrzymany_bufor_z_wątku_alokatora, 10);
*   I następnie wypisać na ekran zawartość tego bufora.
    Po wypisaniu zawartości bufora - powinien go zwolnić.
*   Dodatkowo jeśli serwer otrzyma od wątku-klienta liczbę z zakresu 0-1000
    powinien wejść w nieskończoną pętlę po wypisaniu bufora ale przed
    zwolnieniem pamięci. Jest to symulowanie np. zgubionego pakietu w
    komunikacji asynchronicznej bez potwierdzeń (czekasz na coś bez końca).
    Aby nie zamęczyć CPU proponuję:
    while(true)
    {
        usleep(1000);
    }
    // oczywiście w tej pętli możesz dodać też inny kod który umożliwi interakcję z
    wątkiem T7
    Z tej sytuacji (prowadzącej do deadlocka i możliwe, że do wycieku pamięci)
    wyratować aplikację powinien wątek T7 „watchdog”.

Alokator:
*   Na żądanie serwera alokuje pamięć np. malloc / calloc / new (sposób
    przekazywania uchwytu zaalokowanej pamięci do serwera jest dowolny)
    Watchdog:
*   Raz na sekundę sprawdza czy wątki pracują, a jeśli zauważy, że któryś wątek
    serwerowy w przeciągu sekundy nie wykonał żadnego nowego zadania to
    wdroży ”jakąś” (tutaj wybór należy do Ciebie) operację która przywróci,
    zablokowany wątek serwerowy do życia.

Mile widziane:
*   Kod rozdzielony na pliki *.h i *.cpp.
*   Pliki *.h i *.cpp w osobnych katalogach .
*   Safe-code (sprawdzanie czy funkcje systemowe nie zwróciły błędu).
*   Różne sposoby budowania przełączalne poprzez flagi (Release, Debug,
*   RelWithDebInfo) .
*   Tworzenie projektu Eclipse poprzez CMake (najlepiej Eclipse Neon).
*   Wzorce projektowe zastosowane w kodzie.