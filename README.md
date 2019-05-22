# Esercitazione interfacce di base

Tutto il necessario per lo svolgimento di esercitazioni base per interfacce (codice&nbsp;C, linking, comunicazione inter-processo, socket).

## Download toolkit

Toolkit portabile per Windows, composto da compilatore e linker minimali: [TinyCC](http://download.savannah.gnu.org/releases/tinycc/).
Scaricare sia toolkit che header Win32, assicurarsi che l'eseguibile `tcc` sia nel *path*.

Windows:
```
tcc file.c -o file.exe -lWs2_32
```

Linux/macOS:
```
gcc file.c -o file
```
