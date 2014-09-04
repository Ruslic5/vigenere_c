/* 

Шифр Виженера.

Реализовать (де-)шифрование букв входного файла шифром Виженера с записью результата в выходной файл.
Символы, не являющиеся буквами переписываются без изменения, регистр букв сохра-няется.
Ключ, являющийся последовательностью букв, и режим шифрова-ние/дешифрование указывается пользователем.
Считать, что коды латин-ских букв, как строчных, так и заглавных, имеет последовательные значения, и это единственные символы с кодами в интервале [1;127], для который isalpha истинно.
Проверить это утверждение при запуске программы и от-казаться работать, если это не так.
Алгоритм реализовывать с учётом этого свойства. Ключ накладывается на последовательность шифрованных букв и повторяется сколько необходимо раз, если он короче неё.
Каждая бук-ва ключа, соответствующая букве текста, указывает, на сколько позиций по порядку в алфавите необходимо сдвинуть её значение.
Число позиций равно 0 для буквы «A», 1 для «B» и так далее, регистр символов в ключе не учитывать.
Если сдвиг приводит к выходу за границы латинского алфавита, перейти циклически к другом его концу.
В режиме шифрования прибавлять сдвиг, при дешифровании - отнимать.

Пример входного файла:

There is no cow level.

Требуемый выходной файл для приведённого выше входного файла, режи-ма шифрования и ключа «sEcReT»:

Llgii bk rq tsp dixvp.

*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    /*
     * 1 - режим шифрования
     * 2 - режим дешифрования
     * argv[1] - ключ
     * argv[2] - режим (де)шифрования
     * argv[3] - входной файл
     * argv[4] - выходной файл
    */

    char i, input1, output1, key[254]={0}, latin[26]={"abcdefghijklmnopqrstuvwxyz"}, LATIN[26]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    FILE* input=fopen(argv[3],"r");
    FILE* output=fopen(argv[4],"w");
    if (!input)
    {
        fputs("Failed open file or file doesn't exist!\n", stderr);
        exit(1);
    }
    strcpy(key,argv[1]);
    int k=strlen(key);
    //Длина ключа
    int mode=strtoul(argv[2],&argv[2],0);

    for(i=0;i<k;++i)
    //Понижение ключа в нижний регистр
    {
        key[i]=tolower(key[i])-'a';
    }

    for(i=0; i<26;++i)
    //Проверка на коды символов
    {
        if (isalpha(i) && !strchr(latin,i) && !strchr(LATIN,i))
        {
            fputs("Something about error!", stderr);
            exit(1);
        }
        if ((latin[i]!=latin[0]+i) || (LATIN[i]!=LATIN[0]+i))
        {
            fputs("Wrong code of the letters", stderr);
            exit(1);
        }
    }

    int p=0;
    while ((input1=fgetc(input))!=EOF)
    {
        if (isalpha(input1))
        //Ветка обработки букв
        {
            if (mode==1)
            //Ветка шифрования
            {
                if (islower(input1))
                    output1=((input1+key[p%k]-'a') % 26)+'a';
                if (isupper(input1))
                    output1=((input1+key[p%k]-'A') % 26)+'A';
            }
            else if(mode==2)
            //Ветка дешифрования
            {
                if (islower(input1))
                    output1=((input1-'a'+26-key[p%k]) % 26)+'a';
                else if (isupper(input1))
                    output1=((input1-'A'+26-key[p%k]) % 26)+'A';
            }
            ++p;
        }
        else
        //Ветка обработки всех остальных символов
        {
            output1=input1;
        }
        fprintf(output,"%c", output1);
        printf("%c", output1);
    }
    //printf("\n");
    fclose(input);
    fclose(output);
    return 0;
}
