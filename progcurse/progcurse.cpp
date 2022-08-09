#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void translate(char* v, int N) //перевод слова из файла
{
    FILE* fo;
    int fff = fopen_s(&fo, "dictionary.txt", "r");
    int n, i = 0, k = 0, j;
    char* l = new char[N];
    char* u = new char[N];
    if (fff == 0)
    {
        for (i = 0;; i++)
            if (v[i] != 0)
                u[i] = v[i];
            else
            {
                u[i] = 0;
                break;
            }
        n = strlen(v);
        while ((k == 0) && (!feof(fo)))
        {
            i = 0;
            fgets(l, N, fo);
            for (i = 0;; i++)
            {
                if (v[i] == l[i])
                    if ((i == n - 1) && (l[i + 1] == ' '))
                    {
                        k++;
                        v[i + 1] = 0;
                        l[i + 1] = 0;
                    }
                if ((v[i] != l[i]) || (i >= n))
                    break;
            }
            i++;
            if (k == 1)
            {
                j = i;
                for (i = 0; l[j] != '\n'; j++, i++)
                    v[i] = l[j];
            }
        }
        if (k == 0)
            for (i = 0;; i++)
                if (u[i] != 0)
                    v[i] = u[i];
                else
                {
                    v[i] = 0;
                    break;
                }
        v[i] = 0;
    }
    else 
        cout << "Error: dictionary.txt doesnt open";
    fclose(fo);
   
    delete[] l;
}
void zapis_slov_and_znak(char* v, char* l, int* i) //вывод строки массива с переводом и вывод знаков препинания
{
    FILE* fo;
    fopen_s(&fo, "text_eng.txt", "at");
    fputs(v, fo);
    int& j = *i;
    while ((l[j] == ' ') || (l[j] == '.') || (l[j] == ',') || (l[j] == '!') || (l[j] == '?') || (l[j] == ':') || (l[j] == ';'))
    {
        fputc(l[j], fo);
        (*i)++;
    }
    fclose(fo);
}
void new_strok() //добавление значка \n для имитации конца строки в текстовом файле
{
    FILE* fo;
    fopen_s(&fo, "text_eng.txt", "at");
    fprintf(fo, "\n");
    fclose(fo);
}
void zanul(char* l) //зануление строки
{
    for (int i = 0; l[i] != '\n'; i++)
        l[i] = 0;
}
void funk(int N) //общая функция для работы программы
{
    FILE* fo;
    char* l = new char[N];
    char* v = new char[N];
    int i = 0, k = 0, j = 0, f = 0;
    fopen_s(&fo, "text_eng.txt", "w");
    fclose(fo);
    int fff=fopen_s(&fo, "text_rus.txt", "r");
    if (fff == 0)
    {
        while (!feof(fo))
        {
            j = 0;
            i = 0;
            fgets(l, N, fo);
            while (l[i] != '\n')
            {
                while ((l[i] != ' ') && (l[i] != '.') && (l[i] != ',') && (l[i] != '!') && (l[i] != '?') && (l[i] != ':') && (l[i] != '\n') || (l[j] == ';'))
                    v[j++] = l[i++];
                v[j] = 0;
                translate(v, N);
                zapis_slov_and_znak(v, l, &i);
                j = 0;
            }
            zanul(l);
            new_strok();
        }
    }
    else
        cout << "Error: text_rus.txt doesnt open";
    fclose(fo);
    delete[] l;
    delete[] v;
}

int main()
{
    int N = 255;
    char* v = new char[N];
    funk(N);
    delete[] v;
    return 0;
}