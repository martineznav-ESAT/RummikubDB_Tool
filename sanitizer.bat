@echo ---------------------------------------------------
@echo  Proceso por lotes iniciado.
@echo ---------------------------------------------------
@echo off

cl /nologo /Zi /GR- /EHs /MD /fsanitize=address %1 ^
.\Code\*.cc ^
.\Code\ScreenModules\*.cc ^
.\Libs\CustomLibs\*.cc ^
-I .\Libs\Lib_Graph\ESAT_rev248\include .\Libs\Lib_Graph\ESAT_rev248\bin\ESAT.lib ^
opengl32.lib user32.lib gdi32.lib shell32.lib Ws2_32.lib

@echo ---------------------------------------------------
@echo  Proceso por lotes finalizado.
@echo ---------------------------------------------------