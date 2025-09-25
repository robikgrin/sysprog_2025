# Домашние задания по курсу "Основы системного программирования"

## Взлом пароля

С помощью `readelf` обнаружил, что надо менять `st_other` в `_Z12authenticatePKc` с `PROTECTED` на `DEFAULT`:

```console
readelf -s libsecret.so | grep authenticate
 6: 0000000000001119    19 FUNC    GLOBAL PROTECTED   12 _Z12authenticatePKc
 24: 0000000000001119    19 FUNC    GLOBAL PROTECTED   12 _Z12authenticatePKc
```

Для этого написал программу `vzlom.cpp`, которая патчит нужный символ на необходимую видимость. В нашем случае это `_Z12authenticatePKc` и `STV_DEFAULT`.

Потом делаем следующее

```console
(base) robert@qot-calc0:~/sysprog_2025$ ls
 elf.h   libsecret.so   main.cpp   vzlom_pop.cpp  'Задание 5 ELF.pdf'
(base) robert@qot-calc0:~/sysprog_2025$ g++ vzlom_pop.cpp -o vzlom_pop
(base) robert@qot-calc0:~/sysprog_2025$ ./vzlom_pop libsecret.so
symbol visibility changed successfully.
(base) robert@qot-calc0:~/sysprog_2025$ g++ main.cpp -o password -L. -lsecret
(base) robert@qot-calc0:~/sysprog_2025$ LD_LIBRARY_PATH=. ./password
Enter password: kushay kashu
Access GRANTED. Top secret = 462074591
```

Получили пароль `Top secret = 462074591`. Для проверки все файлы лежат в `vzlom_password`.
