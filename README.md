Information zu Einstellungsmöglichkeiten der Simulation
-------------------------------------------------------

Einstellungen können über Objekte des Structs sim::Simulation vorgenommen werden. Im folgenden werden die einzelnen Funktionen der Einstellungen erklärt. Die Standarteinstellungen stehen direkt beim syntax dabei.  

**Ausgaben in die Konsole:**
************************

```c++
static inline bool print_console = true;
```
Aktiviert (true) oder deaktiviert (false) die grundlegende Möglichkeit der Simulation, Ergebnisse in die Konsole auszugeben, unabhängig von anderen     Einstellungen.
```c++
static inline bool print_console_map;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der Map nach jedem Schritt (jedes Entity hat seinen Zug gemacht) der Simulation.
```c++
static inline bool **print_console_detailed_map = false;  
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der Map nach jedem Zug eines Entitys, also eine Ausgabe, sobald es eine veränderung gibt.
```c++
static inline bool print_console_score_map = false;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe des zweidimensionalen Vektors score, der bei der Findung des bestmöglichen Zugs erzeugt wird.
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
  
**Ausgabe in eine Datei:**
*********************
Der Name der Datei ist *"simulation_data.txt"*. Die Option *print_file_entity_count* kann in Kombination mit *print_file_positions* und *print_file_positions_compressed* aktiviert werden und wird automatisch deaktiviert, sollte sie mit nicht kompatiblen Optionen verwendet werden. Ansonsten gilt die Priorität:  
*positions_detailed* > *positions_detailed_compressed* > *positions_compressed* > *positions*  
```c++
static inline bool print_file_positions = false;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der Positionen pro Schritt der Simulation in die Datei
static inline bool print_file_positions_compressed = false;
static inline bool print_file_positions_detailed = false;
static inline bool print_file_positions_detailed_compressed = false;
```c++
static inline bool print_file_entity_count = false;
```
Aktiviert (true) oder deaktiviert (false) die Ausgabe der detaillierten
static inline bool print_file_entity_count = false;

static inline bool respawn_plants = true;
static inline int predator_max_age = 12;
static inline int predator_reproduction_threshold = 8;
static inline int predator_reproduction_cost = 4;
static inline int predator_quantity = 0;

static inline int prey_max_age = 12;
static inline int prey_reproduction_threshold = 8;
static inline int prey_reproduction_cost = 4;
static inline int prey_quantity = 0;

static inline int plant_quantity = 0;
