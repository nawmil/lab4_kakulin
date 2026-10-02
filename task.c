#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *CreateTree(struct Node *root, int data)
{
    if (root == NULL)
    {
        root = (struct Node *)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    /*
    if (data == root->data)
    {
        printf("Значение %d уже есть в дереве\n", data);
        return root;
    }
    */
    if (data < root->data)
        root->left = CreateTree(root->left, data);
    else
        root->right = CreateTree(root->right, data);

    return root;
}

void PrintTree(struct Node *r, int l)
{
    if (r == NULL) {
        return;
    }
    PrintTree(r->right, l + 1);
    for (int i = 0; i < l; i++)
    {
        printf("\t");
    }
    printf("%d(%d)\n", r->data, l);
    PrintTree(r->left, l + 1);
}

int SearchAllLevels(struct Node *root, int value, int current_level)
{
    if (root == NULL) return 0;

    int count = 0;

    if (root->data == value) {
        printf("Значение %d найдено на уровне %d\n", value, current_level);
        count = 1;
    }

    count += SearchAllLevels(root->left, value, current_level + 1);
    count += SearchAllLevels(root->right, value, current_level + 1);

    return count;
}

void FreeSubtree(struct Node *root)
{
    if (root == NULL) return;
    FreeSubtree(root->left);
    FreeSubtree(root->right);
    free(root);
}

struct Node* DeleteLevel(struct Node *root, int current_level, int target_level)
{
    if (root == NULL) return NULL;

    if (current_level == target_level)
    {
        FreeSubtree(root);
        return NULL;
    }

    root->left = DeleteLevel(root->left, current_level + 1, target_level);
    root->right = DeleteLevel(root->right, current_level + 1, target_level);

    return root;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int D, start = 1;
    struct Node *root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start)
    {
        printf("Введите число: \n");
        scanf("%d", &D);
        if (D == -1)
        {
            printf("Построение дерева окончено\n");
            start = 0;
        }
        else{
            root = CreateTree(root, D);
        }
    }
    
    printf("\nИсходное дерево:\n");
    PrintTree(root, 0);

    int searchValue;
    printf("\nВведите значение для поиска: ");
    scanf("%d", &searchValue);

    printf("\nРезультаты поиска:\n");
    int foundCount = SearchAllLevels(root, searchValue, 0);

    if (foundCount == 0) {
        printf("Значение %d не найдено в дереве\n", searchValue);
    } else {
        printf("Всего найдено совпадений: %d\n", foundCount);
    }

    int levelToDelete;
    printf("\nВведите номер уровня для удаления: ");
    scanf("%d", &levelToDelete);

    root = DeleteLevel(root, 0, levelToDelete);

    printf("\nДерево после удаления уровня %d:\n", levelToDelete);
    PrintTree(root, 0);

    return 0;
}