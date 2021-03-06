Einstellungsmöglichkeiten der Simulation
----------------------------------------

Einstellungen können über Objekte des Structs sim::Simulation vorgenommen werden. Im folgenden werden die einzelnen Funktionen der Einstellungen erklärt. Die Standarteinstellungen stehen direkt beim Syntax dabei. Ein Entity kann vier verschiedene Rollen annehmen: *null*, *predator*, *prey*, und *plant*. Mit Zug ist hier gemeint, dass ein Entity (sofern es möglich ist) eine Entscheidung trifft, um sich z.B. zu bewegen oder auch nichts zu tun. Wenn von Schritt die Rede ist, ist der Zustand gemeint, sobald jedes Entity in der Map seinen Zug gemacht hat.

****************************
**Ausgaben in die Konsole:**

```c++
static inline bool print_console = true;
```
Aktiviert (true) oder deaktiviert (false) die grundlegende Möglichkeit der Simulation, Ergebnisse in die Konsole auszugeben, unabhängig von anderen     Einstellungen.
```c++
static inline bool print_console_map;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der Map nach jedem Schritt der Simulation.
```c++
static inline bool **print_console_detailed_map = false;  
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der Map nach jedem Zug eines Entitys.
```c++
static inline bool print_console_score_map = false;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe des zweidimensionalen Vektors *score*, der bei der Findung des bestmöglichen Zugs erzeugt wird.
```c++
static inline bool print_console_entity_count = true;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der aktuellen Anzahl der Entitys. Wird einmal pro Schritt ausgeführt.
```c++
static inline bool print_console_animation_create = false;
```
Aktiviert (true) oder deaktiviert (false) eine einfache Animation in der Konsole. Ist diese Einstellung aktiviert, werden andere Ausgaben automatisch unterdrückt. Es wird empfohlen, diese Einstellung für kleinere Maps zu verwenden und nicht in Kombination mit dem Erzeugen von Dateien.
```c++
static inline int print_console_animation_pause_ms = 100;
```
Diese Einstellung gibt die Zeit in Millisekunden an, die mit dem Löschen gewartet wird, nachdem eine neue Map geladen wurde. Sollte die Animation zu langsam/schnell sein, kann das hier angepasst werden.  
  
**************************
**Ausgabe in eine Datei:**

Der Name der erstellten Datei ist *"simulation_data.txt"*. Die Option *print_file_entity_count* kann in Kombination mit *print_file_positions*, *print_file_positions_compressed* oder alleine aktiviert werden und wird automatisch deaktiviert, sollte sie mit nicht kompatiblen Optionen verwendet werden. Ansonsten gilt die Priorität bei nicht kompatiblen Einstellungen:  
*positions_detailed* > *positions_detailed_compressed* > *positions_compressed* > *positions*  
Die nachfolgenden Einstellungen aktivieren (true) oder deaktivieren (false) die Ausgabe verschiedener Daten in eine Datei.
```c++
static inline bool print_file_positions = false;
```
Diese Option speichert die komplette Map einmal pro Schritt ab, das umfasst auch Entitys mit der Rolle *null*. Sie ist kompatibel mit *print_file_entity_count*.
```c++
static inline bool print_file_positions_compressed = false;
```
Diese Option speichert alle Entitys einmal pro Schritt ab, außer Entitys mit der Rolle *null*. Sie ist kompatibel mit *print_file_entity_count*.
```c++
static inline bool print_file_positions_detailed_compressed = false;
```
Diese Option speichert alle Entitys außer Entitys mit der Rolle *null* einmal pro Zug in der Datei ab. Sie ist nicht kompatibel mit *print_file_entity_count* und deaktiviert diese automatisch.
```c++
static inline bool print_file_positions_detailed = false;
```
Diese Option speichert alle Entitys einmal pro Zug in der Datei ab, das umfasst auch Entitys mit der Rolle *null*. Sie ist nicht kompatibel mit *print_file_entity_count* und deaktiviert diese automatisch.
```c++
static inline bool print_file_entity_count = false;
```
Diese Option speichert die Anzahl der Entitys nach Rollen in der Datei ab. Sie ist nicht kompatibel mit den obigen zwei Einstellungen und wird durch diese automatisch deaktiviert.  

**************************
**Predator Einstellungen**

Die nachfolgenden Einstellungen beziehen sich auf Entitys der Rolle *predator*.
```c++
static inline int predator_max_age = 12;
```
Legt das maximale Alter fest, das erreicht werden kann. Sobald das überschritten wird, stirbt das Entity der Rolle *predator*.
```c++
static inline int predator_reproduction_threshold = 8;
```
Legt den Schwellenwert an Nahrung fest, der erreicht werden muss, um sich fortzupflanzen.
```c++
static inline int predator_reproduction_cost = 4;
```
Legt die Menge an Nahrung fest, die das Muttertier durch die Reproduktion verliert. Dieser Wert sollte idealerweise niedriger sein als *predator_reproduction_threshold*, damit das Muttertier nicht direkt nach der Geburt stirbt.
```c++
static inline int predator_quantity = 0;
```
Legt die anfängliche Anzahl an Entitys der Rolle *predator* fest. Standartmäßig wird der Wert im Konstruktor des Structs *sim::Simulation* auf die längste Seitenlänge der Map gesetzt, um auch bei großen Maps eine ausreichende Anzahl an Raubtieren zu haben.
```c++
static inline int predator_vision_range = 1;
```
Legt den Unkreis fest, in dem das Raubtier seine Umgebung analysieren und bewerten kann.
```c++
static inline int predator_movement_range = 1;
```
Legt die Anzahl an Feldern fest, die sich das Raubtier bewegen kann. Unabhängig von dem eingestellten Wert wird das Tier sich stets nur so weit bewegen, wie es auch sehen kann. Somit ist der effektive Wert stets kleiner gleich *predator_vision_range*.  

************************
**Prey Einstellungen**

Die nachfolgenden Einstellungen beziehen sich auf Entitys der Rolle *prey*.
```c++
static inline int prey_max_age = 12;
```
Legt das maximale Alter fest, das erreicht werden kann. Sobald das überschritten wird, stirbt das Entity der Rolle *prey*.
```c++
static inline int prey_reproduction_threshold = 8;
```
Legt den Schwellenwert an Nahrung fest, der erreicht werden muss, um sich fortzupflanzen.
```c++
static inline int prey_reproduction_cost = 4;
```
Legt die Menge an Nahrung fest, die das Muttertier durch die Reproduktion verliert. Dieser Wert sollte idealerweise niedriger sein als *prey_reproduction_threshold*, damit das Muttertier nicht direkt nach der Geburt stirbt.
```c++
static inline int prey_quantity = 0;
```
Legt die anfängliche Anzahl an Entitys der Rolle *prey* fest. Standartmäßig wird der Wert wird im Konstruktor des Structs *sim::Simulation* auf die längste Seitenlänge der Map gesetzt, um auch bei großen Maps eine ausreichende Anzahl an Beutetieren zu haben.
```c++
static inline int prey_vision_range = 1;
```
Legt den Unkreis fest, in dem das Beutetier seine Umgebung analysieren und bewerten kann.
```c++
static inline int prey_movement_range = 1;
```
Legt die Anzahl an Feldern fest, die sich das Beutetier bewegen kann. Unabhängig von dem eingestellten Wert wird das Tier sich stets nur so weit bewegen, wie es auch sehen kann. Somit ist der effektive Wert stets kleiner gleich *prey_vision_range*.  

***********************
**Plant Einstellungen**

Die nachfolgenden Einstellungen beziehen sich auf Entitys der Rolle *plant*.
```c++
static inline int plant_quantity = 0;
```
Legt die anfängliche Anzahl an Entitys der Rolle *plant* fest. Standartmäßig wird der Wert wird im Konstruktor des Structs *sim::Simulation* auf die längste Seitenlänge der Map gesetzt und mal zwei genommen, um auch bei großen Maps eine ausreichende Anzahl an Pflanzen zu haben.
```c++
static inline bool plants_respawn = true;
```
Aktiviert (true) oder deaktiviert (false) die Option, ob die anfängliche Anzahl an Pflanzen nach jedem Schritt wiederhergestellt werden soll. In anderen Worten, ob Pflanzen "nachwachsen" können.
```c++
static inline int plant_food_count = 4;
```
Legt fest, welchen Nährwert eine Pflanze besitzt.  

****************************
**Allgemeine Einstellungen**

```c++
static inline bool use_VT100_escape_sequence = true;
```
Diese Einstellung legt fest, ob [VT100 escape sequence] beim leeren der Konsole für die Animation benutzt wird (true). Das hat den Vorteil, dass die Animation flüssig läuft und im Gegensatz zur zweiten Möglichkeit kein Flackern beim Leeren erzeugt. Da manche Konsolen das nicht unterstützen, kann diese Option deaktiviert werden (false), wodurch stattdessen zum Leeren Systembefehle benutzt werden: unter Windows "*cls*", unter Linux/macOS "*clear*".  

Einstellungsmöglichkeiten der Map
---------------------------------

Einstellungen der Map werden über den Konstruktor automatisch aus der Datei "*mapSettings.txt*" geladen.

**************************
**Spawning-Einstellungen**

Entities werden über eine Member-Funktion gespawnt, indem zufällige Koordinaten in den Limits der Map generiert werden und im Anschluss geschaut wird, ob das Feld frei ist. Sollte das nicht der Fall sein, wird das wiederholt, bis ein freies Feld gefunden oder ein Limit erreicht wurde.

```c++
static inline uint16_t map_spawn_retry_max = 40;
```
Diese Einstellung legt das oben erwähnte Limit fest um zu verhindern, dass bei einer sehr vollen oder gänzlich vollen Map die Schleife unendlich läuft und das Programm hängen bleibt. Folglich bedeutet das, je höher der Wert und je voller die Map, desto mehr Zeit verbringt das Programm in der Schleife bzw. desto mehr Leistung geht hier verloren.

[VT100 escape sequence]: https://web.archive.org/web/20151004211730/http://www.termsys.demon.co.uk/vtansi.htm
