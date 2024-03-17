# $\mathbb{\color[RGB]{255,60,0}{Сравнение \ файлов \ (Графическое, \ Windows)}}$

&emsp;&emsp;Можно добавлять много файлов, сравнивать их между собой, менять местами, удалять.\
&emsp;&emsp;Для этого используется алгоритм Diff построчно и посимвольно.

## $\mathbb{\color[RGB]{255,90,0}{Основная \ информация}}$

### $\mathbb{\color[RGB]{255,127,0}{Стек \ технологий \ разработки}}$

- $\mathbb{\color[RGB]{252,193,83}{C++}}$
	+ Библиотека $\mathbb{\color[RGB]{252,193,83}{Win \ API}}$.
	+ Сам написал скроллящееся текстовое окно.
	+ Библиотека $\mathbb{\color[RGB]{252,193,83}{STL}}$.
	+ Красивое $\mathbb{\color[RGB]{252,193,83}{ООП}}$ с большой вложенностью классов.
	+ $\mathbb{\color[RGB]{252,193,83}{Шаблоны}}$.
	+ Много $\mathbb{\color[RGB]{252,193,83}{оптимизаций}}$ по сравнению файлов и отрисовке.
	+ Алгоритм Diff.

### $\mathbb{\color[RGB]{255,127,0}{Среды \ разработки}}$

- Visual Studio 2019
- $\mathbb{\color[RGB]{252,193,83}{Deleaker}}$

### $\mathbb{\color[RGB]{255,127,0}{Фото \ работы}}$

1. Сейчас сравниваются два разных файла с именем Creatures.cpp. Из левого получаем правый, за счёт удаления всего красного и добавления всего зелёного.

[<img src="Info/in_work.jpg"/>](Info/in_work.jpg)

1. Эти же файлы, но наоборот.

[<img src="Info/in_work_contrary.jpg"/>](Info/in_work_contrary.jpg)

## $\mathbb{\color[RGB]{255,90,0}{Дата}}$

&emsp;&emsp; $\mathbb{\color[RGB]{252,193,83}{Конец \ 2022г.}}$ Проект довольно сырой.

## $\mathbb{\color[RGB]{255,90,0}{Заключение}}$

&emsp;&emsp;В основном используется, чтобы узнать, различаются файлы или нет. Проект сырой и поэтому неудобно пользоваться.

 ${\color{red}FIXME}$ 1) При табуляции все ещё едет иногда.\
 ${\color{red}FIXME}$ 2) Посимвольно сравнение.\
 ${\color{red}FIXME}$ 3) Иногда не работает горизонтальный скролл.\
 ${\color{yellow}TODO}$ 1) Добавить возможность редактировать.\
 ${\color{yellow}TODO}$ 1.5) Сделать возможность обменивать куски местами, чтобы была возможность решать конфликты.\
 ${\color{yellow}TODO}$ 2) Добавить общий горизонтальный скролл, который скролит оба одновременно.\
 ${\color{yellow}TODO}$ 3) Обработать кнопки pgUp, pgDn, Home, End, стрелочки, увеличить скорость прокрутки по кнопкам.\
 ${\color{yellow}TODO}$ 4) Сделать настройку, чтобы прокручивать не попиксельно, а построчно.\
 ${\color{yellow}TODO}$ 5) Сделать менее яркие цвета, чтобы не мешали читать.
 