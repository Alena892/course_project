#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
struct hard_drive {
    char przv[10]; // �������������
    float space; // �����
    int sv; // �������� ��������
    char intrfs[10]; // ���������
    float sp_b; // ����� ������
    int s_data; //�������� ������ ������
};
typedef struct hard_drive hr_d;

//-------�������-------
// ���������� �������
int fill_array(hr_d* arr, int size) {
    printf("�������� ��� ���������� �����\n1)������������� - ����� ��������\n2)����� - ������������ �����\n3)�������� �������� - ����� �����\n4)��������� - �������� (��������, usb, ata, scsi)\n5)����� ������ - ������������ �����\n6)�������� ������ ������ - ����� �����\n");
    for (int i = 0; i < size; i++) {
        int valid_input = 0; // ������������ �����

        while (!valid_input) {
            printf("������� ������ � ������� ����� ����� ������ � �������: �������������, �����, �������� ��������, ���������, ����� ������, �������� ������ ������\n");
            int result = scanf("%9s %f %i %9s %f %i", arr[i].przv, &arr[i].space, &arr[i].sv, arr[i].intrfs, &arr[i].sp_b, &arr[i].s_data);

            if (result == 6) {
                valid_input = 1;
                printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
            }
            else {
                printf("������������ ������. ���������� ��� ���.\n");
                while (getchar() != '\n'); // ������� ������ �����
            }
        }
    }
    return size;
}
// ������ �������
int print_array(hr_d* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
    }
    return size;
}
// ������ � ����
int input_file(char* fname, hr_d* arr, int size) {
    FILE* out = fopen(fname, "wt"); // ���� ��� ������ �������
    if (!out) {
        printf("������ �������� �����\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(out, "�������������: %s �����: %f �������� ��������: %i ���������: %s ����� ������: %f �������� ������ ������: %i\n",
            arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
    }
    fclose(out);
    return size;
}
// ������ �� �����
int output_file(char* fname, hr_d* arr, int size) {
    FILE* in = fopen(fname, "rt"); // ����, ������ ����������� ������
    if (!in) {
        printf("������ �������� �����\n");
        return 1;
    }
    int count = 0; // ���������� ��������� ��������
    while (count < size && fscanf(in, "�������������: %s �����: %f �������� ��������: %i ���������: %s ����� ������: %f �������� ������ ������: %i\n", arr[count].przv, &arr[count].space, &arr[count].sv, arr[count].intrfs, &arr[count].sp_b, &arr[count].s_data) == 6) {
        count++;
    }
    if (count < size) {
        printf("� ����� �� ������� ������ ��� ���������� ���� ��������\n");
    }
    fclose(in);
    return count;
}
// ����� ��������
int find_element(hr_d* arr, int size) {
    char data[10], data1[10];// ������ �� ����������
    float sp1, sp2; // ������ �� ������: sp1 - ����������� �����; sp2 - ������������
    int vybor, qt; // vybor - ����� ����, qt - ���������� ������� �����

    printf("������� ���������� ����� ��� ������\n");
    qt = get_valid_input(1, 2);
    if (qt == 1) {
        printf("������� ���� ��� ������ (1-����� �� � ��, 2-���������)\n");
        vybor = get_valid_input(1, 2);

        if (vybor == 1) {
            printf("������� ����������� � ������������ ����� ��� ������ (����� ������)\n");
            scanf("%f %f", &sp1, &sp2);

            for (int i = 0; i < size; i++) {
                if ((sp1 <= arr[i].space) && (arr[i].space <= sp2)) printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
            }
        }
        else if (vybor == 2) {
            printf("������� ���������\n");
            scanf("%9s", data);
            for (int i = 0; i < size; i++) {
                if (strcmp(arr[i].intrfs, data) == 0)
                    printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n",
                        arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
            }
        }
    }
    else if (qt == 2) {
        printf("����� �� ���� �����:\n");
        printf("������� ����������� � ������������ ����� (����� ������)\n");
        scanf("%f %f", &sp1, &sp2);
        printf("������� ���������\n");
        scanf("%9s", data1);
        for (int i = 0; i < size; i++) {
            if (((sp1 <= arr[i].space) && (arr[i].space <= sp2)) && (strcmp(arr[i].intrfs, data1) == 0)) printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
        }
    }
    return size;
}
// ���������� �������
int sort_massiv(hr_d* arr, int size) {
    int vybor1, vybor2; // ����� ������������
    printf("������� �������� ���������� (1-�������������, 2-�����, 3-�������� ��������, 4-���������, 5-����� ������, 6-�������� ������ ������)\n");
    vybor1 = get_valid_input(1, 6);
    printf("�������� ��� ���������� (1-�� �����������, 2-�� ��������)\n");
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
        printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n",
            arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
    }
    return size;
}
// ���������� ������������� ���������� ���������
int add_elem(hr_d* arr, int size) {
    int vybor1, vybor2 = 0; // ����� ������������
    hr_d* arr_add; // ���������� ������
    printf("������� ���������� ��������� ��� ����������\n");
    vybor1 = get_valid_input(1, 100); // ����������� ���������� ����������� ���������
    if (arr == NULL) {
        printf("������");
        return 0;
    }
    arr_add = arr;
    arr_add = realloc(arr, (size + vybor1) * sizeof(hr_d));
    if (arr_add == NULL) {
        printf("������ ��������� ������\n");
        return size;
    }
    arr = arr_add;
    printf("���������� �����:\n1) ������������� - ��������\n2)����� - ������������ �����\n3)�������� �������� - ����� �����\n4)��������� - ��������\n5)����� ������ - ������������ �����\n6)�������� ������ ������ - ����� �����\n");
    for (int i = size; i < size + vybor1; i++) {
        printf("������� ������ � ������� ����� � �������: �������������, �����, �������� ��������, ���������, ����� ������, �������� ������ ������\n");
        int result = scanf("%9s %f %i %9s %f %i", arr[i].przv, &arr[i].space, &arr[i].sv, arr[i].intrfs, &arr[i].sp_b, &arr[i].s_data);
        if (result != 6) {
            printf("������������ ������. ���������� ��� ���.\n");
            while (getchar() != '\n'); // ������� ������ �����
            i--;
            continue;
        }
        printf("�������������: %s, �����: %f, �������� ��������: %i, ���������: %s, ����� ������: %f, �������� ������ ������: %i\n", arr[i].przv, arr[i].space, arr[i].sv, arr[i].intrfs, arr[i].sp_b, arr[i].s_data);
        printf("���� ������ ������� ����������� ������� 1 � ���������� ��� ���, ����� ������� 0\n");
        vybor2 = get_valid_input(0, 1);
        if (vybor2 == 1) i--;
    }
    return (size + vybor1);
}
// ��������� ��������
int edit_elem(hr_d* arr, int size) {
    int vybor1, vybor2; // ����� ������������
    printf("������� ������ ��������, ������� ����� ���������������\n");
    vybor1 = get_valid_input(0, size - 1);
    printf("������� �������� ��� �������������� (1-�������������, 2-�����, 3-�������� ��������, 4-���������, 5-����� ������, 6-�������� ������ ������)\n");
    vybor2 = get_valid_input(1, 6);
    printf("������� �������� ��� �������\n");
    switch (vybor2) {
    case 1: scanf("%9s", arr[vybor1].przv); break;
    case 2: scanf("%f", &arr[vybor1].space); break;
    case 3: scanf("%i", arr[vybor1].sv); break;
    case 4: scanf("%9s", &arr[vybor1].intrfs); break;
    case 5: scanf("%f", &arr[vybor1].sp_b); break;
    case 6: scanf("%i", arr[vybor1].s_data); break;
    default:
        printf("������� �������� ������\n");
        break;
    }
    return size;
}
// ������� �������� ������������ ����� �����
get_valid_input(int min, int max) {
    int input;
    char buffer[256];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &input) == 1 && input >= min && input <= max) {
                return input;
            }
            else {
                printf("������������ ����. ����������, ������� ����� �� %d �� %d: ", min, max);
            }
        }
    }
}
// ������� ��� �������� ������������� �����
file_have(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

//-----�������� ��������� � �����������-----
int main() {
    setlocale(LC_ALL, "RUS");
    hr_d* arr0 = NULL; // �������� ������
    hr_d* arr_out = NULL; // ������ ��� ������ �� �����
    int size0 = 0, size_out = 0; // ������ ��������
    int vybor = 123, vybor1 = 0; // ����� ���������
    char fname1[20] = "", fname2[20] = ""; // �������� ������

    // ��������� ������� ��� ������
    printf("�������� ������ ��������� �������:\n1)������� ����� ������\n2)������� ������ �� �����\n");
    vybor1 = get_valid_input(1, 2);
    switch (vybor1) {
    case 1:
        printf("������� ������ �������\n");
        size0 = get_valid_input(1, 100); // ��������� ������� �������
        arr0 = (hr_d*)malloc(size0 * sizeof(hr_d));
        fill_array(arr0, size0);
        print_array(arr0, size0);
        break;
    case 2:
        printf("������� ������ ������� ��� ������\n");
        size_out = get_valid_input(1, 100); // ��������� ������ ������� �� 100
        printf("������� �������� ����� ��� ������\n");
        scanf("%s", fname2);
        if (!file_have(fname2)) {
            printf("���� � ����� ������ �� ����������. ������� ���������� ��� �����.\n");
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

    //-------�������� ����-------
    while (vybor != 0) {
        printf("����:\n1)�������� ����� ������\n2)����� ������\n3)������ � ����\n4)������ �� �����\n5)���������� � ������\n6)��������� ��������� ������\n7)���������� ������������� ����� �������\n8)������� ������� ������\n0)�����\n");
        vybor = get_valid_input(0, 8);
        switch (vybor) {
        case 1:// �������� ����� ������
            printf("������� ������ �������\n");
            size0 = get_valid_input(1, 100); // ����������� ������� �������
            arr0 = (hr_d*)malloc(size0 * sizeof(hr_d));
            fill_array(arr0, size0);
            print_array(arr0, size0);
            break;
        case 2:// ����� ��������
            find_element(arr0, size0);
            break;
        case 3:// ������ � ����
            printf("������� �������� �����\n");
            scanf("%s", fname1);
            input_file(fname1, arr0, size0);
            print_array(arr0, size0);
            break;
        case 4:// ������ �� �����
            printf("������� ������ �������, ������� ���������� �������\n");
            size_out = get_valid_input(1, 100); // ����������� ������� �������
            printf("������� �������� �����, �� �������� ����� ������� ����������\n");
            scanf("%s", fname2);
            if (!file_have(fname2)) {
                printf("���� � ����� ������ �� ����������. ����������, ������� ���������� ��� �����.\n");
                break;
            }
            arr_out = (hr_d*)malloc(size_out * sizeof(hr_d));
            size_out = output_file(fname2, arr_out, size_out);
            arr0 = arr_out;
            size0 = size_out;
            print_array(arr0, size0);
            break;
        case 5:// ���������� �������
            sort_massiv(arr0, size0);
            break;
        case 6:// ��������� ������
            edit_elem(arr0, size0);
            break;
        case 7:// ���������� ������������� ���������� ���������
            size0 = add_elem(arr0, size0);
            break;
        case 8:// ����� �������
            print_array(arr0, size0);
            break;
        default:
            break;
        }
    }
    free(arr0);// ������������ ������
    free(arr_out);// ������������ ������
}