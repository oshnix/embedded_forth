﻿# Интерпретатор языка forth на C для линейки микроконтроллеров stm32F4  
Интерпретатор позволяет пользователям обрабатывать целочисленные данные, помещенные на стек forth.  
Проект был сгенерирован с помощью STM32CubeMX для среды EWARM, в которой и разрабатывался.   
В данный момент используется демонстрационная версия языка, в которой ввод осуществляется пользователем через консоль отладчика IDE. Для того, чтобы воспользоваться вводом программы из файла или иного места, достаточно:  
1. Переопределить стандартную функцию getchar своей.  
2. Заменить использование функции scanf в слове read_word любой другой функцией, принимающей указатель на char и записывающей по этому адресу нуль-терминированную строку (Не рекомендуется).

#Компиляция и запуск  
В данный момент проект сконфигурирован для использования с платой Nucleo-STM32F429.  
Для того, чтобы перенести его на другие устройства нужно:  
1. Отконфигурировать переферию любым удобным способом (Вручную, с помощью CubeMx, или воспользоваться шаблоном).  
2. Переопределить константы из файла main.h. В данный момент они выделяют 64КБ SRAM с конца оперативной памяти.  

