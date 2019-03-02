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

