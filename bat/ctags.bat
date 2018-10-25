@ECHO ON
setlocal
set udir=h:
echo %udir%
set ctagsdir=%udir%/Vim/vim74/ctags.exe
echo %ctagsdir%
%udir%

chdir

::for /F %i in ('dir /b /a:d') do echo %i

dir /s/b *.h *.cpp *.jce *.c > src.files
%ctagsdir%  -R --c++-kinds=+px --fields=+iaS --extra=+q -L src.files

pause
endlocal
