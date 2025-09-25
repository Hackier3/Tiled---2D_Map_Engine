# Silnik Gry 2D - Pełny parser map Tiled z animacjami

Ten projekt rozwiązuje prawdziwy problem, z którym spotyka się każdy, kto próbował użyć Tiled Map Editor w profesjonalnym projekcie: **generowany kod przez Tiled jest po prostu zbyt podstawowy i ograniczony**.

Podczas gdy Tiled oferuje świetny edytor, to jego eksport daje tylko surowe dane - bez prawdziwego systemu animacji, bez zaawansowanych hitboxów, bez dynamicznego renderowania. Ten silnik wypełnia tę lukę.

## Co tak naprawdę potrafi ten silnik:

**Zamiast zwykłego ładowania PNG-ów:**
- Czyta bezpośrednio definicje animacji z plików TMX (każda klatka z własnym czasem trwania)
- Automatycznie konfiguruje flipowanie, rotacje i transformacje kafelków
- Parsuje skompresowane warstwy map (Base64 + zlib) zamiast prostych CSV

**Zamiast ręcznego ustawiania kolizji:**
- Wyciąga hitboxy prosto z Tileda - prostokąty, okręgi, wielokąty, punkty
- Zachowuje precyzyjne pozycjonowanie zdefiniowane w edytorze
- Automatycznie przypisuje kolizje do odpowiednich kafelków

**Zamiast statycznych tekstur:**
- Dynamiczne canvas textures które aktualizują tylko zmienione obszary
- Niezależne timeline'y animacji dla każdego animowanego kafelka
- Płynne przejścia oparte o deltaTime a nie sztywne interwały

## Jak to działa w praktyce:

Tworzysz mapę w Tiled jak zawsze - dodajesz animacje, ustawiasz hitboxy, definiujesz warstwy. Ale zamiast używać ich ograniczonego eksportu, ładujesz mapę bezpośrednio do tego silnika. 

Silnik sam:
- Rozpoznaje które kafelki są animowane i konfiguruje ich sekwencje
- Wyciąga wszystkie kolizje i przekształcenia
- Buduje optymalny system renderowania wielowarstwowego
- Ustawia kamere która płynnie podąża za postacią

## Dla kogo jest ten projekt:

Dla każdego kto chce używać Tileda nie jako prostego edytora map, ale jako pełnoprawnego narzędzia do tworzenia gier. To nie jest kolejny "hello world" z SFML - to kompletne rozwiązanie które zamienia pliki TMX w działający silnik gry.

**Technologie:** C++17, SFML, TMXLite, pugixml, zlib

---

To nie jest kolejna podstawowa implementacja - to rozwiązanie realnego problemu który dotyka każdego developera używającego Tiled Map Editor w poważnych projektach.
