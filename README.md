# Silnik Gry 2D - Profesjonalny System Animacji i Map

Kompletny silnik gier 2D z zaawansowanym systemem animacji i pełną integracją edytora map Tiled. Projekt obejmuje renderowanie wielowarstwowych środowisk, dynamiczne animacje postaci i zaawansowane przetwarzanie map w formacie TMX.

## Kluczowe Funkcje

**System Animacji**
- Animacja postaci z płynnym przejściem między ruchami i stanem spoczynku
- Automatyczne odbicia lustrzane w zależności od kierunku ruchu
- Animowane kafelki mapy z konfigurowalnymi sekwencjami klatek

**Zaawansowane Mapy**
- Pełna kompatybilność z Tiled Map Editor (format TMX)
- Wielowarstwowy rendering z podziałem na tło, postać i warstwy foreground
- Automatyczne wykrywanie i ładowanie hitboxów zdefiniowanych w edytorze
- Obsługa skompresowanych map (Base64 + zlib)

**Rendering i Optymalizacja**
- Inteligentna kamera podążająca za postacią
- Canvas textures dla dynamicznych aktualizacji animowanych warstw
- Efektywne zarządzanie pamięcią i zasobami

## Technologie

- C++17 + SFML 2.5+ - rdzeń silnika
- TMXLite + pugixml - parsowanie zaawansowanych map
- Tiled Map Editor - integracja z profesjonalnym edytorem map

## Sterowanie

- **WASD**

Projekt stanowi solidną podstawę do rozwoju gier 2D, oferując gotowy system renderowania, animacji i zarządzania mapami. Idealny dla gier RPG lub przygodowych.
