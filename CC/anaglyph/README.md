# anaglyph
Beispiele für die Verwendung von Anaglyphen-Stereo.

Das Beispiel redblue.cpp verwendet rot-blau-Stereo, wofür es in VTKRenderWindow eine
Funktion gibt.

Der Default, wenn man SetStereoTypeToAnaglyph() verwendet ist rot-cyan. 
Dieser Default wird in redcyan.cpp verwendet.

Wird SetStereoTypeToAnaglyph() verwendet kann man die color mask verändern.
Dies wird im Beispiel colormask.cpp eingesetzt. Die Interpretation der beiden
integer-Werte ist im Kommentar von colormask.cpp zu finden. rot-cyan entspricht
den beiden Werte (4,3) (die erste Zahl steht immer für das linke Auge, 4 entspricht rot).
Mit (4,1) erhält man rot-blau, und (4,2) ergibt rot-grün-Stereo.

Im Verzeichnis liegen Screen-Captures des Ergebnisses. Die Szene ist einfach, wir stellen
in einem Fenster mit einem Hintergrund von 90%-Grau einen Würfel dar, der weiß eingefärbt ist.
In allen Anwendungen können wir zwischen einem Fenster und Fullscreen wechseln.

Ohne Stereo:

!(https://github.com/MBrill/VTKExamples/blob/develop/CC/anaglyph/mono.png)

Rot-Blau Stereo:![Rot-Blau Stereo] (redblue41.png "Rot-Blau Stereo")

Rot-Grün Stereo:![Rot-Grün Stereo] (redgreen42.png "Rot-Grün Stereo")

Rot-Cyan Stereo:![Rot-Cyan Stereo] (redcyan43.png "Rot-Cyan Stereo")


