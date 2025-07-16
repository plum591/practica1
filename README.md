# Инструкция

## Иметь установленный cmake, mingw 

### Переходим к установке wxWidgets

* Перейти по ссылке https://wxwidgets.org/downloads/ 
* Спускаемся ниже к Latest Stable Release: 3.2.8
* Скачиваем бинарники MinGW-w64 8.1, а именно: Header Files, Dev.Files, Release DLLs
* Создаём в любом удобном месте папку для будущего wxWidgets. Для меня это будет D:/Libraries/wxWidgets
* Разархивируем там все эти 3 скачанных архива и при случае заменяем существующие, и у нас должно быть в папке wxWidgets такие папки и файлы: docs, include, lib
* Копируем путь D:/Libraries/wxWidgets и D:\Libraries\wxWidgets\lib\gcc810_x64_dll
* Через поисковик Windows (нажатием кнопки Win и просто вводом символом) переходим в Переменные среды, где в большом нижнем окошке Системные переменные добавляем к Path новый путь: D:\Libraries\wxWidgets\lib\gcc810_x64_dll
* Теперь копируем репозиторий как и где Вам удобно, а после в CMakeLists.txt можно увидеть сразу подсказки что и куда заменить

### либо можете посмотреть данный гайд: https://www.youtube.com/watch?v=VllB4vRSVvc