# Базовый функционал
*пер* - переменная \
*знач* - значение

// - комментарий

### Работа с переменными
```
новая_переменная(пер, пер/знач);
удалить_переменную(пер, ...);
```

### Работа с ввод\выводом
```
ввод(пер);

ввывод(пер/знач);

очистить_вывод();

пауза();

```

### Работа с циклами
```
цикл(пер/знач, пер/знач, пер/знач, {ТЕЛО});

повторять(пер/знач, {ТЕЛО});
```

### Работа с файлами
```
создать(пер/знач);

удалить(пер/знач);

прочитать(пер/знач, пер/знач);

написать(пер/знач, пер/знач);

переместить(пер/знач, пер/знач);

новая_папка(пер/знач);

закрыть(пер/знач);

открыть(пер/знач);
```

### Работа с папками
```
новая_папка(пер/знач);

удалить_папку(пер/знач);
```


### Работа со строками
```
сложить_строки(пер, пер/знач, пер/знач);

найти_подстроку(пер, пер/знач, пер/знач, пер/знач);

длина_строки(пер, пер/знач);
```

### Работа с массивами
```
добавление_в_массив(пер, пер/знач);

удаление_из_массива(пер, пер/знач);

получение_элемента(пер, пер/знач, пер/знач);

длина_массива(пер, пер/знач);

обратный_массив(пер, пер/знач);

очищение_массива(пер);

удаление_элемента(пер, пер/знач);

сортировка_массива(пер);
```

### Функции времени
```
текущая_дата(пер);

текущее_время(пер);
```

### Математические функции
```
сумма(пер, пер/знач, пер/знач);

вычитание(пер, пер/знач, пер/знач);

умножение(пер, пер/знач, пер/знач);

деление(пер, пер/знач, пер/знач);

степень(пер, пер/знач, пер/знач);

модуль(пер, пер/знач, пер/знач);

логарифм(пер, пер/знач, пер/знач);

логическое_и(пер, пер/знач, пер/знач);

логическое_или(пер, пер/знач, пер/знач);

случайное_число(пер, пер/знач<min>, пер/знач<max>);

округление(пер, пер/знач);

абсолютное_значение(пер, пер/знач);

факториал(пер, пер/знач);

перевод_в_двоичную(пер, пер/знач);

перевод_в_десятичную(пер, пер/знач);

экспонента(пер, пер/знач);
```


## Пример
### Создание переменной и вывод
```
новая_переменная(а, 100);
вывод(а);  // 100
```

### Цикл с выводом
```
повторять(10, {
    вывод("Привет, Мир!);
});
```

### Ввод двух значение и вывод их
```
ввод(а, б);
вывод(а, б);
```

### Сложение двух переменных
```
новая_переменная(а, 2);
новая_переменная(б, 12);
умножение(рез, а, б);
вывод(рез);
```

### Работа с циклом
```
цикл(счетчик, 0, 10, 1, {
    вывод(счетчик);
});

пауза();
```