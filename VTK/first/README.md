# Erstes VTK-Beispiel
Mit diesem Beispiel verifizieren wir, dass die Header und Bibliotheken des VTK-Builds gefunden werden.

Das Beispiel selbst erstellt ein unstrukturiertes Gitter mit einer Menge von Punkten und daraus dann K�rper wie W�rfel, Tetraeder und weitere.

Damit das Build funktioniert sollten zwei Umgebungsvariablen gesetzt sein:
- VTK_DIR: das Verzeichnis, in dem die Header und Bibliotheken installiert wurden.
- VTK_ROOT: das bin-Verzeichnis unterhalb des Installationsverzeichnisses, in dem die dll/so-Dateien liegen.
- Das Verzeichnis VTK_ROOT sollte im Pfad oder im Suchpfad f�r so-Dateien liegen, so dass sie w�hrend der Ausf�hrung der Anwendung gefunden werden.
