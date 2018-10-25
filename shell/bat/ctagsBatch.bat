@ECHO ON
setlocal
set udir=h:
echo %udir%
set ctagsdir=%udir%\Vim\vim74\ctags.exe
echo %ctagsdir%
%udir%

cd  %udir%\code\
::dir /b /a:d >dir.list
cd
::sleep 1
::for /F %%i in ('dir /b /a:d') do echo %%i
for /F %%i in ('dir /b /a:d') do (
    dir /s /b %%i\*.h %%i\*.cpp %%i\*.jce %%i\*.c > %%i\src.files
    ::%ctagsdir%  -R --c++-kinds=+px --fields=+iaS --extra=+q -L %%i\src.files
    start /b %ctagsdir%  -R --c++-kinds=+px --fields=+iaS --extra=+q -L %%i\src.files -f %%i\tags
)

pause
endlocal
