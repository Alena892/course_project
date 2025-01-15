#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
struct hard_drive {
    char przv[10]; // производитель
    float space; // объем
    int sv; // скорость вращения
    char intrfs[10]; // интерфейс
    float sp_b; // объем буфера
    int s_data; //скорость обмена данных
};
typedef struct hard_drive hr_d;

//-------функции-------
// заполнение массива
int fill_array(hr_d* arr, int size) {
    printf("Варианты для заполнения полей\n1)Производитель - любое название\n2)Объем - вещественное число\n3)Скорость вращения - целое число\n4)Интерфейс - название (например, usb, ata, scsi)\n5)Объем буфера - вещественное число\n6)Скорость обмена данных - целое число\n");
    for (int i = 0; i < size; i++) {
        int valid_input = 0; // корректность ввода

        while (!valid_input) {
            printf("Введите данные о жестком диске через пробел в порядке: производитель, объем, скорость вращения, интерфейс, объем буфера, скорость обмена данных\n");
            int result = scanf("%9s %f %i %9s %f %i", arr[i].przv, &arr[i].space, &arr[i].sv, arr[i].intrfs, &arr[i].sp_b, &arr[i].s_data);

            if (result == 6) {
                valid_input = 1;
                printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
            }
            else {
                printf("Некорректные данные. Попробуйте еще раз.\n");
                while (getchar() != '\n'); // очистка буфера ввода
            }
        }
    }
    return size;
}
// печать массива
int print_array(hr_d* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
    }
    return size;
}
// запись в файл
int input_file(char* fname, hr_d* arr, int size) {
    FILE* out = fopen(fname, "wt"); // файл для записи массива
    if (!out) {
        printf("Ошибка открытия файла\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(out, "Производитель: %s Объем: %f Скорость вращения: %i Интерфейс: %s Объем буфера: %f Скорость обмена данных: %i\n",
            arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
    }
    fclose(out);
    return size;
}
// чтение из файла
int output_file(char* fname, hr_d* arr, int size) {
    FILE* in = fopen(fname, "rt"); // файл, откуда считывается массив
    if (!in) {
        printf("Ошибка открытия файла\n");
        return 1;
    }
    int count = 0; // количество считанных структур
    while (count < size && fscanf(in, "Производитель: %s Объем: %f Скорость вращения: %i Интерфейс: %s Объем буфера: %f Скорость обмена данных: %i\n", arr[count].przv, &arr[count].space, &arr[count].sv, arr[count].intrfs, &arr[count].sp_b, &arr[count].s_data) == 6) {
        count++;
    }
    if (count < size) {
        printf("В файле не хватает данных для считывания всех структур\n");
    }
    fclose(in);
    return count;
}
// поиск элемента
int find_element(hr_d* arr, int size) {
    char data[10], data1[10];// данные об интерфейсе
    float sp1, sp2; // данные об объеме: sp1 - минимальный объем; sp2 - максимальный
    int vybor, qt; // vybor - выбор поля, qt - количество искомых полей

    printf("Введите количество полей для поиска\n");
    qt = get_valid_input(1, 2);
    if (qt == 1) {
        printf("Введите поле для поиска (1-объем от и до, 2-интерфейс)\n");
        vybor = get_valid_input(1, 2);

        if (vybor == 1) {
            printf("Введите минимальный и максимальный объем для поиска (через пробел)\n");
            scanf("%f %f", &sp1, &sp2);

            for (int i = 0; i < size; i++) {
                if ((sp1 <= arr[i].space) && (arr[i].space <= sp2)) printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
            }
        }
        else if (vybor == 2) {
            printf("Введите интерфейс\n");
            scanf("%9s", data);
            for (int i = 0; i < size; i++) {
                if (strcmp(arr[i].intrfs, data) == 0)
                    printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n",
                        arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
            }
        }
    }
    else if (qt == 2) {
        printf("Поиск по двум полям:\n");
        printf("Введите минимальный и максимальный объем (через пробел)\n");
        scanf("%f %f", &sp1, &sp2);
        printf("Введите интерфейс\n");
        scanf("%9s", data1);
        for (int i = 0; i < size; i++) {
            if (((sp1 <= arr[i].space) && (arr[i].space <= sp2)) && (strcmp(arr[i].intrfs, data1) == 0)) printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
        }
    }
    return size;
}
// сортировка массива
int sort_massiv(hr_d* arr, int size) {
    int vybor1, vybor2; // выбор пользователя
    printf("Введите критерий сортировки (1-производитель, 2-объем, 3-скорость вращения, 4-интерфейс, 5-объем буфера, 6-скорость обмена данных)\n");
    vybor1 = get_valid_input(1, 6);
    printf("Выберите тип сортировки (1-по возрастанию, 2-по убыванию)\n");
    vybor2 = get_valid_input(1, 2);

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            int sort = 0;

            switch (vybor1) {
            case 1: sort = strcmp(arr[j].przv, arr[j + 1].przv); break;
            case 2: sort = (arr[j].space > arr[j + 1].space) ? 1 : -1; break;
            case 3: sort = (arr[j].sv > arr[j + 1].sv) ? 1 : -1; break;
            case 4: sort = strcmp(arr[j].intrfs, arr[j + 1].intrfs); break;
            case 5: sort = (arr[j].sp_b > arr[j + 1].sp_b) ? 1 : -1; break;
            case 6: sort = (arr[j].s_data > arr[j + 1].s_data) ? 1 : -1; break;
            }

            if ((vybor2 == 1 && sort > 0) || (vybor2 == 2 && sort < 0)) {
                hr_d temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n",
            arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
    }
    return size;
}
// добавление произвольного количества элементов
int add_elem(hr_d* arr, int size) {
    int vybor1, vybor2 = 0; // выбор пользователя
    hr_d* arr_add; // измененный массив
    printf("Введите количество элементов для добавления\n");
    vybor1 = get_valid_input(1, 100); // ограничение количества добавляемых элементов
    if (arr == NULL) {
        printf("Ошибка");
        return 0;
    }
    arr_add = arr;
    arr_add = realloc(arr, (size + vybor1) * sizeof(hr_d));
    if (arr_add == NULL) {
        printf("Ошибка выделения памяти\n");
        return size;
    }
    arr = arr_add;
    printf("Заполнение полей:\n1) Производитель - название\n2)Объем - вещественное число\n3)Скорость вращения - целое число\n4)Интерфейс - название\n5)Объем буфера - вещественное число\n6)Скорость обмена данных - целое число\n");
    for (int i = size; i < size + vybor1; i++) {
        printf("Введите данные о жестком диске в порядке: производитель, объем, скорость вращения, интерфейс, объем буфера, скорость обмена данных\n");
        int result = scanf("%9s %f %i %9s %f %i", arr[i].przv, &arr[i].space, &arr[i].sv, arr[i].intrfs, &arr[i].sp_b, &arr[i].s_data);
        if (result != 6) {
            printf("Некорректные данные. Попробуйте еще раз.\n");
            while (getchar() != '\n'); // очистка буфера ввода
            i--;
            continue;
        }
        printf("Производитель: %s, Объем: %f, Скорость вращения: %i, Интерфейс: %s, Объем буфера: %f, Скорость обмена данных: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
        printf("Если данные введены некорректно введите 1 и попробуйте еще раз, иначе введите 0\n");
        vybor2 = get_valid_input(0, 1);
        if (vybor2 == 1) i--;
    }
    return (size + vybor1);
}
// изменение элемента
int edit_elem(hr_d* arr, int size) {
    int vybor1, vybor2; // выбор пользователя
    printf("Введите индекс элемента, который нужно отредактировать\n");
    vybor1 = get_valid_input(0, size - 1);
    printf("Введите параметр для редактирования (1-производитель, 2-объем, 3-скорость вращения, 4-интерфейс, 5-объем буфера, 6-скорость обмена данных)\n");
    vybor2 = get_valid_input(1, 6);
    printf("Введите значение для вставки\n");
    switch (vybor2) {
    case 1: scanf("%9s", arr[vybor1].przv); break;
    case 2: scanf("%f", &arr[vybor1].space); break;
    case 3: scanf("%i", arr[vybor1].sv); break;
    case 4: scanf("%9s", &arr[vybor1].intrfs); break;
    case 5: scanf("%f", &arr[vybor1].sp_b); break;
    case 6: scanf("%i", arr[vybor1].s_data); break;
    default:
        printf("Введены неверные данные\n");
        break;
    }
    return size;
}
// функция проверки корректности ввода числа
get_valid_input(int min, int max) {
    int input;
    char buffer[256];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &input) == 1 && input >= min && input <= max) {
                return input;
            }
            else {
                printf("Некорректный ввод. Пожалуйста, введите число от %d до %d: ", min, max);
            }
        }
    }
    return 0;
}
// функция для проверки существования файла
file_have(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

//-----основная программа с интерфейсом-----
int main() {
    setlocale(LC_ALL, "RUS");
    hr_d* arr0 = NULL; // исходный массив
    hr_d* arr_out = NULL; // массив для вывода из файла
    int size0 = 0, size_out = 0; // размер массивов
    int vybor = 123, vybor1 = 0; // выбор вариантов
    char fname1[20] = "", fname2[20] = ""; // названия файлов

    // получение массива для работы
    printf("Выберите способ получения массива:\n1)Создать новый массив\n2)Считать массив из файла\n");
    vybor1 = get_valid_input(1, 2);
    switch (vybor1) {
    case 1:
        printf("Введите размер массива\n");
        size0 = get_valid_input(1, 100); // огранение размера массива
        arr0 = (hr_d*)malloc(size0 * sizeof(hr_d));
        fill_array(arr0, size0);
        print_array(arr0, size0);
        break;
    case 2:
        printf("Введите размер массива для вывода\n");
        size_out = get_valid_input(1, 100); // ограничим размер массива до 100
        printf("Введите название файла для вывода\n");
        scanf("%s", fname2);
        if (!file_have(fname2)) {
            printf("Файл с таким именем не существует. Введите корректное имя файла.\n");
            break;
        }
        arr_out = (hr_d*)malloc(size_out * sizeof(hr_d));
        size_out = output_file(fname2, arr_out, size_out);
        arr0 = arr_out;
        size0 = size_out;
        print_array(arr0, size0);
        break;
    default:
        break;
    }

    //-------основной цикл-------
    while (vybor != 0) {
        printf("Меню:\n1)Создание новой записи\n2)Поиск записи\n3)Запись в файл\n4)Чтение из файла\n5)Сортировка и печать\n6)Изменение отдельной записи\n7)Добавление произвольного числа записей\n8)Вывести текущий массив\n0)Выход\n");
        vybor = get_valid_input(0, 8);
        switch (vybor) {
        case 1:// создание новой записи
            printf("Введите размер массива\n");
            size0 = get_valid_input(1, 100); // ограничение размера массива
            arr0 = (hr_d*)malloc(size0 * sizeof(hr_d));
            fill_array(arr0, size0);
            print_array(arr0, size0);
            break;
        case 2:// поиск элемента
            find_element(arr0, size0);
            break;
        case 3:// запись в файл
            printf("Введите название файла\n");
            scanf("%s", fname1);
            input_file(fname1, arr0, size0);
            print_array(arr0, size0);
            break;
        case 4:// чтение из файла
            printf("Введите размер массива, который необходимо вывести\n");
            size_out = get_valid_input(1, 100); // ограничение размера массива
            printf("Введите название файла, из которого нужно вывести информацию\n");
            scanf("%s", fname2);
            if (!file_have(fname2)) {
                printf("Файл с таким именем не существует. Пожалуйста, введите корректное имя файла.\n");
                break;
            }
            arr_out = (hr_d*)malloc(size_out * sizeof(hr_d));
            size_out = output_file(fname2, arr_out, size_out);
            arr0 = arr_out;
            size0 = size_out;
            print_array(arr0, size0);
            break;
        case 5:// сортировка массива
            sort_massiv(arr0, size0);
            break;
        case 6:// изменение записи
            edit_elem(arr0, size0);
            break;
        case 7:// добавление произвольного количества элементов
            size0 = add_elem(arr0, size0);
            break;
        case 8:// вывод массива
            print_array(arr0, size0);
            break;
        default:
            break;
        }
    }
    free(arr0);// освобождение памяти
    free(arr_out);// освобождение памяти
}
