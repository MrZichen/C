#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_NAME_LENGTH 1024

typedef struct {
    char name[MAX_NAME_LENGTH];
    char gender[MAX_NAME_LENGTH];
    char age[MAX_NAME_LENGTH];
    char number[MAX_NAME_LENGTH];
    char address[MAX_NAME_LENGTH];
} Linkman;

typedef struct {
    Linkman* persons; // �洢��ϵ����Ϣ������
    int capacity; // ���������
    int size; // ��ǰ��ϵ������
} AddressList;

void save(AddressList* list); // ����ͨѶ¼���ݵ��ļ�
void load(AddressList* list); // ���ļ�����ͨѶ¼����
void init(AddressList* list); // ��ʼ��ͨѶ¼
void insert(AddressList* list); // ������ϵ��
void change(AddressList* list); // �޸���ϵ��
void find(AddressList* list); // ������ϵ��
void show(AddressList* list); // ��ʾ������ϵ��
void empty(AddressList* list); // ���ͨѶ¼
void sort(AddressList* list); // ��ͨѶ¼��������
void update(AddressList* list); // ����ͨѶ¼����
int menu(); // ��ʾ�˵�ѡ���ȡ�û�����

// ����ͨѶ¼���ݵ��ļ�
void save(AddressList* list) {
    FILE* fp = fopen("address_list.txt", "w");
    if (fp == NULL) {
        printf("�򿪴浵�ļ�ʧ��\n");
        return;
    }

    // ����ͨѶ¼�е���ϵ�ˣ�����Ϣд���ļ�
    for (int i = 0; i < list->size; i++) {
        Linkman* person = &list->persons[i];
        fprintf(fp, "%s,%s,%s,%s,%s\n", person->name, person->gender, person->age, person->number, person->address);
    }

    fclose(fp);
    printf("�浵�ɹ�\n");
}

// ���ļ�����ͨѶ¼����
void load(AddressList* list) {
    FILE* fp = fopen("address_list.txt", "r");
    if (fp == NULL) {
        printf("�򿪴浵�ļ�ʧ��\n");
        return;
    }

    // ѭ����ȡ�ļ��е����ݣ�ֱ�������ļ�ĩβ
    while (1) {
        // �����ǰ��ϵ�������Ѵﵽ�������ޣ�����չ��������
        if (list->size >= list->capacity) {
            list->capacity += 100;
            list->persons = realloc(list->persons, sizeof(Linkman) * list->capacity);
        }

        Linkman* person = &list->persons[list->size];
        // ���ļ��а�ָ����ʽ��ȡ��ϵ�˵ĸ����ֶ�
        if (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", person->name, person->gender, person->age, person->number, person->address) == EOF) {
            break;
        }

        list->size++;
    }

    fclose(fp);
    printf("�����ɹ���\n");
}

// ��ʼ��ͨѶ¼
void init(AddressList* list) {
    list->size = 0;
    list->capacity = 100;
    list->persons = (Linkman*)malloc(sizeof(Linkman) * list->capacity);
}

// ������ϵ��
void insert(AddressList* list) {
    if (list->size >= list->capacity) {
        list->capacity += 100;
        list->persons = realloc(list->persons, sizeof(Linkman) * list->capacity);
    }

    Linkman* person = &list->persons[list->size];
    printf("��������ϵ��������");
    scanf("%s", person->name);
    printf("��������ϵ���Ա�");
    scanf("%s", person->gender);
    printf("��������ϵ�����䣺");
    scanf("%s", person->age);
    printf("��������ϵ�˵绰��");
    scanf("%s", person->number);
    printf("��������ϵ��סַ:");
    scanf("%s", person->address);

    list->size++;
    printf("������ϵ�˳ɹ�\n");
    Sleep(2000);
    system("cls");
    save(list);
}

// �޸���ϵ��
void change(AddressList* list) {
    int id;
    printf("������Ҫ�޸ĵ���ϵ�˵���ţ�");
    scanf("%d", &id);
    if (id < 1 || id > list->size) {
        printf("�����Ч\n");
        return;
    }

    Linkman* person = &list->persons[id - 1];
    printf("��ϵ��������%s\n", person->name);
    printf("�������µ���ϵ��������");
    scanf("%s", person->name);
    printf("��ϵ���Ա�%s\n", person->gender);
    printf("�������µ���ϵ���Ա�");
    scanf("%s", person->gender);
    printf("��ϵ�����䣺%s\n", person->age);
    printf("�������µ���ϵ�����䣺");
    scanf("%s", person->age);
    printf("��ϵ�˵绰��%s\n", person->number);
    printf("�������µ���ϵ�˵绰��");
    scanf("%s", person->number);
    printf("��ϵ��סַ��%s\n", person->address);
    printf("�������µ���ϵ��סַ��");
    scanf("%s", person->address);

    printf("�޸ĳɹ�\n");
    Sleep(2000);
    system("cls");
    save(list);
}

// ������ϵ��
void find(AddressList* list) {
    char name[MAX_NAME_LENGTH];
    printf("������Ҫ���ҵ���ϵ��������");
    scanf("%s", name);

    for (int i = 0; i < list->size; i++) {
        Linkman* person = &list->persons[i];
        if (strcmp(person->name, name) == 0) {
            printf("��ϵ��������%s\n", person->name);
            printf("��ϵ���Ա�%s\n", person->gender);
            printf("��ϵ�����䣺%s\n", person->age);
            printf("��ϵ�˵绰��%s\n", person->number);
            printf("��ϵ��סַ��%s\n", person->address);
            return;
        }
    }

    printf("δ�ҵ���ϵ��\n");
}

// ��ʾ������ϵ��
void show(AddressList* list) {
    if (list->size == 0) {
        printf("ͨѶ¼Ϊ��\n");
        return;
    }

    for (int i = 0; i < list->size; i++) {
        Linkman* person = &list->persons[i];
        printf("��ţ�%d\n", i + 1);
        printf("��ϵ��������%s\n", person->name);
        printf("��ϵ���Ա�%s\n", person->gender);
        printf("��ϵ�����䣺%s\n", person->age);
        printf("��ϵ�˵绰��%s\n", person->number);
        printf("��ϵ��סַ��%s\n", person->address);
        printf("------------------------\n");
    }
}

// ���ͨѶ¼
void empty(AddressList* list) {
    list->size = 0;
    printf("ͨѶ¼�����\n");
    Sleep(2000);
    system("cls");
    save(list);
}

// ��ͨѶ¼��������
void sort(AddressList* list) {
    // ʹ��ð�������ͨѶ¼�������򣬰�����ϵ���������ֵ�˳������
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = 0; j < list->size - i - 1; j++) {
            Linkman* person1 = &list->persons[j];
            Linkman* person2 = &list->persons[j + 1];
            if (strcmp(person1->name, person2->name) > 0) {
                // ����������ϵ�˵�λ��
                Linkman temp = *person1;
                *person1 = *person2;
                *person2 = temp;
            }
        }
    }

    printf("ͨѶ¼������\n");
    Sleep(2000);
    system("cls");
    save(list);
}

// ����ͨѶ¼����
void update(AddressList* list) {
    save(list);
    load(list);
}

// ��ʾ�˵�ѡ���ȡ�û�����
int menu() {
    int choice;
    printf("*********************************\n");
    printf("*         ͨѶ¼����ϵͳ        *\n");
    printf("*        1. ������ϵ��          *\n");
    printf("*        2. �޸���ϵ��          *\n");
    printf("*        3. ������ϵ��          *\n");
    printf("*        4. ��ʾ������ϵ��      *\n");
    printf("*        5. ���ͨѶ¼          *\n");
    printf("*        6. ��ͨѶ¼����        *\n");
    printf("*        0. �˳�ϵͳ            *\n");
    printf("*********************************\n");
    printf("��ѡ�������");
    scanf("%d", &choice);
    return choice;
}

int main() {
    AddressList list;
    init(&list); // ��ʼ��ͨѶ¼

    load(&list); // ���ļ�����ͨѶ¼����

    while (1) {
        int choice = menu(); // ��ʾ�˵�ѡ��
        switch (choice) {
            case 0:
                save(&list); // ����ͨѶ¼���ݵ��ļ�
                printf("��лʹ��ͨѶ¼����ϵͳ���ټ���\n");
                return 0;
            case 1:
                insert(&list); // ������ϵ��
                break;
            case 2:
                change(&list); // �޸���ϵ��
                break;
            case 3:
                find(&list); // ������ϵ��
                break;
            case 4:
                show(&list); // ��ʾ������ϵ��
                break;
            case 5:
                empty(&list); // ���ͨѶ¼
                break;
            case 6:
                sort(&list); // ��ͨѶ¼��������
                break;
            default:
                printf("��Ч��ѡ������������\n");
                break;
        }
    }

    return 0;
}

