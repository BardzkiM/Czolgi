# Czolgi
Projekt_Cpp

1. Gdzie znajdują się diagramy związane z projektem ?
2. Co jest potrzebne do uruchomienia kodu ?
3. Jak uruchomić kod ? 
4. Jak działa gra “Czołgi 2D” ?
5. Kto napisał projekt ?

Ad1. Diagramy (Klas, ELH, Maszyny Stanowej) znajdują się w folderze diagramy (Czolgi\Diagramy).

Ad2. Kod gry został napisany w języku C++ z wykorzystaniem biblioteki graficznej SFML, w środowisku Visual Studio 2015. Dlatego do uruchomienia kodu zalecane jest posiadanie skonfigurowanego Visual Studio, pod kątem SMFL (z założenia środowisko to, jest już przystosowane do tej dodatkowej biblioteki, jednak warto się upewnić. W razie problemów z instalacją:
https://www.youtube.com/watch?v=Z6alClFOGoM ).

Ad3. Jak uruchomić kod?

Pobierz z Githuba udostępnione repozytorium (https://github.com/BardzkiM/Czolgi.git).
Otwórz folder ’boost_1_60_0’ (Czolgi\Project1\boost_1_60_0)
Do tego folderu, w którym się znajduje, rozpakuj plik PREFIX.exe  -wypakuje on archiwum sfx potrzebne do poprawnego działania kodu).

![alt tag](https://cloud.githubusercontent.com/assets/12682459/15190790/165d3ed8-17b2-11e6-8d1d-a9efd04c787c.PNG)

Uruchom Visual Studio 2015.
Otwórz projekt z grą.

![alt tag](https://cloud.githubusercontent.com/assets/12682459/15190804/264ffbf0-17b2-11e6-8c71-1ce06d3c94a4.png)

Wybierz Project1 -> Project1.sln
Uruchom Local Windows Debugger (lub wciśnij kombinację klawiszy Ctrl+F5)

![alt tag](https://cloud.githubusercontent.com/assets/12682459/15190845/4ae00550-17b2-11e6-84ad-debac3b08640.png)

Ciesz się grą :)

Ad4. Jak działa gra
<ol type="a">
W celu rozpoczęcia gry należy w menu wybrać opcję "Start gry". Następnie, gdy gra przeniesie nas do panelu wyboru serwera:<br><br>
<li> gra w trybie <b> single-player </b>:<br>
    wciskamy spację, następnie "Enter" (potwierdzamy tym samym wybór serwera jako localhost i przystępujemy do gry)</li><br>
<li> gra w trybie multiplayer -<b> my jesteśmy serwerem - i nie chcemy brać udziału w grze</b>:<br>
    wciskamy spację, czekamy na podłączenie dwóch klientów. Po wyświetleniu w konsoli dwóch aktywnych klientów, wciskamy ponownie spację, czym potwierdzamy, że jesteśmy serwerem i nie bierzemy udziału w grze</li><br>
<li> gra w trybie multiplayer - <b>my jesteśmy serwerem i chcemy wziąć udział w grze</b>:<br>
    wciskamy spację i czekamy na podłączenie się klienta (drugiego gracza). Po wyświetleniu w konsoli aktywego klienta, wciskamy Enter, przechodząc bezpośrednio do gry.</li><br>
<li> gra w trybie multiplayer - <b>my jesteśmy klientem</b>:<br>
    wpisujemy adres IP serwera (pod warunkiem, że serwer jest już uruchomiony(!)), akceptujemy wybór Enterem i czekamy na uruchomienie gry przez serwer.</li>
</ol>

Gra obsługiwana jest za pomocą strzałek - poruszanie czołgiem. Strzelanie odbywa się za pomocą spacji.

Ad5. Projekt współtworzyli:
<ul>
    <li>Michał Bardzki - kierownik,</li>
    <li>Dominik Pawlik,</li>
    <li>Piotr Fic,</li>
    <li>Anna Gawor,</li>
    <li>Mikołaj Midura.</li>
</ul>

