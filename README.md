Information zu Einstellungsmöglichkeiten der Simulation
-------------------------------------------------------

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
Legt die anfängliche Anzahl an Entitys der Rolle *predator* fest. Standartmäßig wird der Wert wird im Konstruktor des Structs *sim::Simulation* auf die längste Seitenlänge der Map gesetzt, um auch bei großen Maps eine ausreichende Anzahl an Raubtieren zu haben.  

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
Aktiviert (true) oder deaktiviert (false) die Optrion, ob die anfängliche Anzahl an Pflanzen nach jedem Schritt wiederhergestellt werden soll. In anderen Worten, ob Pflanzen "nachwachsen" können.
