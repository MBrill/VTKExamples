# Erstes VTK-Beispiel
Mit diesem Beispiel verifizieren wir, dass die Header und Bibliotheken des VTK-Builds gefunden werden.

Das Beispiel selbst erstellt ein unstrukturiertes Gitter mit einer Menge von Punkten und daraus dann Körper wie Würfel, Tetraeder und weitere.

Damit das Build funktioniert sollten zwei Umgebungsvariablen gesetzt sein:
- VTK_DIR: das Verzeichnis, in dem die Header und Bibliotheken installiert wurden.
- VTK_ROOT: das bin-Verzeichnis unterhalb des Installationsverzeichnisses, in dem die dll/so-Dateien liegen.
- Das Verzeichnis VTK_ROOT sollte im Pfad oder im Suchpfad für so-Dateien liegen, so dass sie während der Ausführung der Anwendung gefunden werden.
