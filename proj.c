#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
//--------------------------------------------------
void logsignIN()
{   FILE * fp;
    char n,s,l;
    char username[100];
    char password[100];
    char * allData[1000];
    for(int i = 0;i < 1000;i++)
    {
        allData[i] = (char*) malloc(100);
    }
    char endl[] = "\n";
    char currentCharacter;
    printf("hey! do you want to sign in in this game or you already done that.\n?");
    printf("if you wanna sign in please enter s ,and if you wanna loggin enter l\n ");
    scanf("%c" , &n);
    fp = fopen("users.txt", "a" );
    if(fp == NULL)
    {
        printf("error!! reopen the programm.");
    }
    //---------------------------------------------------------------this section is for sign in in this game.
    if(n == 's')
    {    
        printf("your username: ");
        scanf("%s",&username);
        printf("your password: ");
        scanf("%s",&password);
        fputs(username,fp);
        fputs(endl,fp);
        fputs(password,fp);
        fputs(endl,fp);
        fclose(fp);
    }
    //---------------------------------------------this section is for log in .
    else
    {  
        FILE * fp;
        int i = 0;
        fp = fopen("users.txt","r");
        int index = 0;
        while((currentCharacter = fgetc(fp)) != EOF)
        {
            if(currentCharacter == '\n')
            {
                index++;
                i = 0;
                continue;
            }
            allData[index][i] = currentCharacter;
            i++;
        }
        fclose(fp);
        int tryCount = 0;
        int compare1,compare2;
        while(1)
        {
            system("cls");
            printf("your username: ");
            scanf("%s",&username);
            printf("your password: ");
            scanf("%s",&password);
            for(int i = 0;i < index;i++)
            {
                compare1 = strcmp(allData[i],username);
                compare2 = strcmp(allData[i+1],password);
                if(compare1 == 0 && compare2 == 0)
                {
                    printf("you are logged in\n");
                    Sleep(2000);
                    return;
                }
            }
            printf("no match found\n");
            Sleep(2000);
            tryCount++;
            if(tryCount < 10)
            {
                printf("try again\n");
                Sleep(2000);
            }
            else
            {
                printf("too many failed attempts\nyou cannot log in until 5 minutes later\n");
                Sleep(3000000);
            }
        }
    }
}
//------------------------------------------------------------random word maker
void RandomelementMaker(char arr[],char word[],int line)
{
    int len = strlen(arr);
    int count = 0;
    for(int j =0;j < len;j++)
    {
        if(arr[j] == '\n')
        {
            count++;
        }
        if(line == count + 1 && line != 1)
        {
            int k = 0;
            while(arr[j + 1 + k] != '\n')
            {
                word[k] = arr[k + j + 1];
                k++;
            }
            break;
        }
        else if(line == count + 1 && line == 1)
        {
            int k = 0;
            while(arr[j + 1 + k] != '\n')
            {
                word[k] = arr[k + j];
                k++;
            }
            word[k] = arr[k + j];
            break;
        }
    }
}
//---------------------------------random line maker fucntion
int randomLineMaker(int countOFlines)
{
    int returnLine = rand() % (countOFlines - 1) + 1;
    return returnLine;
}
//--------------------------------------------------------text and background color
void textcolor(int color) 
{
    system("color 70");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (color + (7 * 16)));
}
//-----------------------------------------------------fucntion to take all the data from a file and store it in an array
void allDataTaker(char arr[],char address[])
{
    FILE * fileaddress;
    fileaddress = fopen(address,"r");
    char currentCharacter;
    int i = 0;
    while((currentCharacter = fgetc(fileaddress)) != EOF)
    {
        arr[i] = currentCharacter;
        i++;
    }
}
//--------------------------------------------------------------line counter function
int linesINfileCounter(FILE * fileaddress,char address[])
{
    char temp[5];
    int lines = 0;
    char currentCharacter;
    fileaddress = fopen(address,"r");
    while((currentCharacter = fgetc(fileaddress)) != EOF)
    {
        temp[0] = currentCharacter;
        if(temp[0] == '\n')
        {
            lines++;
        }
    }
    fclose(fileaddress);
    return lines;
}
//---------------------------------------------------------------------
float scoreCalculator(int wordlen,int mistakes,float elapsedtime,int levelNO)
{
    float a = 2 * wordlen;
    float b = mistakes;
    float c = elapsedtime;
    float d = (10.0 + levelNO) / 10.0;
    float score = (a - b) / c;
    score = score * d;
    return score;
}
//------------------SIMPLE 3 2 1 function
void fun123()
{
    textcolor(4);
    Sleep(1000);
    printf("3");
    Sleep(1000);
    printf("\r2");
    Sleep(1000);
    printf("\r1");
    Sleep(1000);
    printf("\rGO!!!");
    Sleep(500);
    system("cls"); 
} 
//----------------------------------------------------------------------level1 function
void level1(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level1file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level1Score = 0;
    char input[5];
    char inputchar;
    level1file = fopen("L01.txt","r");
    int lines = linesINfileCounter(level1file,"L01.txt");
    allDataTaker(allData,"L01.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel1 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level1Score = scoreCalculator(wordlen,mistakes,elapsedtime,1);
    printf("level1 score: %f\n",level1Score);
    fclose(level1file);
    *totalscore = *totalscore + level1Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level2
void level2(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level2file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level2Score = 0;
    char input[5];
    char inputchar;
    level2file = fopen("L02.txt","r");
    int lines = linesINfileCounter(level2file,"L02.txt");
    allDataTaker(allData,"L02.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel2 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level2Score = scoreCalculator(wordlen,mistakes,elapsedtime,2);
    printf("level2 score: %f\n",level2Score);
    fclose(level2file);
    *totalscore = *totalscore + level2Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level3
void level3(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level3file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level3Score = 0;
    char input[5];
    char inputchar;
    level3file = fopen("L03.txt","r");
    int lines = linesINfileCounter(level3file,"L03.txt");
    allDataTaker(allData,"L03.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel3 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level3Score = scoreCalculator(wordlen,mistakes,elapsedtime,3);
    printf("level3 score: %f\n",level3Score);
    fclose(level3file);
    *totalscore = *totalscore + level3Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level4
void level4(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level4file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level4Score = 0;
    char input[5];
    char inputchar;
    level4file = fopen("L04.txt","r");
    int lines = linesINfileCounter(level4file,"L04.txt");
    allDataTaker(allData,"L04.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel4 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level4Score = scoreCalculator(wordlen,mistakes,elapsedtime,4);
    printf("level4 score: %f\n",level4Score);
    fclose(level4file);
    *totalscore = *totalscore + level4Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level5
void level5(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level5file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level5Score = 0;
    char input[5];
    char inputchar;
    level5file = fopen("L05.txt","r");
    int lines = linesINfileCounter(level5file,"L05.txt");
    allDataTaker(allData,"L05.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel5 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level5Score = scoreCalculator(wordlen,mistakes,elapsedtime,5);
    printf("level5 score: %f\n",level5Score);
    fclose(level5file);
    *totalscore = *totalscore + level5Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level6
void level6(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level6file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level6Score = 0;
    char input[5];
    char inputchar;
    level6file = fopen("L06.txt","r");
    int lines = linesINfileCounter(level6file,"L06.txt");
    allDataTaker(allData,"L06.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel6 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level6Score = scoreCalculator(wordlen,mistakes,elapsedtime,6);
    printf("level6 score: %f\n",level6Score);
    fclose(level6file);
    *totalscore = *totalscore + level6Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level7
void level7(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level7file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level7Score = 0;
    char input[5];
    char inputchar;
    level7file = fopen("L07.txt","r");
    int lines = linesINfileCounter(level7file,"L07.txt");
    allDataTaker(allData,"L07.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel7 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level7Score = scoreCalculator(wordlen,mistakes,elapsedtime,7);
    printf("level7 score: %f\n",level7Score);
    fclose(level7file);
    *totalscore = *totalscore + level7Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level8
void level8(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level8file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level8Score = 0;
    char input[5];
    char inputchar;
    level8file = fopen("L08.txt","r");
    int lines = linesINfileCounter(level8file,"L08.txt");
    allDataTaker(allData,"L08.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel8 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level8Score = scoreCalculator(wordlen,mistakes,elapsedtime,8);
    printf("level8 score: %f\n",level8Score);
    fclose(level8file);
    *totalscore = *totalscore + level8Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level9
void level9(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level9file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level9Score = 0;
    char input[5];
    char inputchar;
    level9file = fopen("L09.txt","r");
    int lines = linesINfileCounter(level9file,"L09.txt");
    allDataTaker(allData,"L09.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel9 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level9Score = scoreCalculator(wordlen,mistakes,elapsedtime,9);
    printf("level9 score: %f\n",level9Score);
    fclose(level9file);
    *totalscore = *totalscore + level9Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level10
void level10(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level10file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level10Score = 0;
    char input[5];
    char inputchar;
    level10file = fopen("L10.txt","r");
    int lines = linesINfileCounter(level10file,"L10.txt");
    allDataTaker(allData,"L10.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel10 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level10Score = scoreCalculator(wordlen,mistakes,elapsedtime,10);
    printf("level10 score: %f\n",level10Score);
    fclose(level10file);
    *totalscore = *totalscore + level10Score;
    printf("total score by far: %f\n",*totalscore);
}
//--------------------------------------------------------level11
void level11(double * totalscore)
{
    system("cls");
    fun123();
    srand(time(NULL));
    FILE * level11file;
    char allData[100000];
    char word[10];
    int quantCount = 0;
    double level11Score = 0;
    char input[5];
    char inputchar;
    level11file = fopen("L11.txt","r");
    int lines = linesINfileCounter(level11file,"L11.txt");
    allDataTaker(allData,"L11.txt");
    int wordlen = 0;
    int mistakes = 0;
    double elapsedtime = 0;
    int start,end;
    start = clock();
    while(quantCount < 25)
    {
        int randline = randomLineMaker(lines);
        RandomelementMaker(allData,word,randline);
        int wordlentemp = strlen(word);
        wordlen = wordlen + wordlentemp;
        textcolor(0);
        printf("%s\n",word);
        for(int i = 0;i < wordlentemp;i++)
        {
            if(word[i] <= 'Z' && word[i] >=  'A')
            {
                word[i] = word[i] + 32;
            }
        }
        for(int i = 0;i < wordlentemp;i++)
        {
            inputchar = getch();
            if(inputchar == word[i])
            {
                textcolor(1);
                printf("%c",inputchar - 32);
            }
            else
            {
                mistakes++;
            }
        }
        printf("\n");
        quantCount++;
    }
    end = clock();
    textcolor(4);
    elapsedtime = ((float)(end - start)) / CLOCKS_PER_SEC;
    printf("----------------\nlevel11 stats\nelapsed time: %f\n",elapsedtime);
    printf("mistakes: %i\n",mistakes);
    level11Score = scoreCalculator(wordlen,mistakes,elapsedtime,11);
    printf("level11 score: %f\n",level11Score);
    fclose(level11file);
    *totalscore = *totalscore + level11Score;
    printf("total score by far: %f\n",*totalscore);
}
//----------------------------------------------------------
int main()
{
    logsignIN();
    textcolor(0);
    system("color 70");
    system("cls");
    double total = 0;
    int startchoice;
    printf("welcome to word game.\nyou should type in the words printed on the screen as fast as you can\neach correct alphabet that you type will be bolded and dyed blue\n");
    printf("do you want the 1st level to start?(yes = 1 / no  =  2)\n");
    scanf("%i",&startchoice);
    if(startchoice == 1)
    {
        level1(&total);
        printf("do you want the 2nd level to start?(yes = 1 / no  =  2)\n");
        scanf("%i",&startchoice);
        if(startchoice == 1)
        {
            level2(&total);
            printf("do you want the 3rd level to start?(yes = 1 / no  =  2)\n");
            scanf("%i",&startchoice);
            if(startchoice == 1)
            {
                level3(&total);
                printf("do you want the 4th level to start?(yes = 1 / no  =  2)\n");
                scanf("%i",&startchoice);
                if(startchoice == 1)
                {
                    level4(&total);
                    printf("do you want the 5th level to start?(yes = 1 / no  =  2)\n");
                    scanf("%i",&startchoice);
                    if(startchoice == 1)
                    {
                        level5(&total);
                        printf("do you want the 6th level to start?(yes = 1 / no  =  2)\n");
                        scanf("%i",&startchoice);
                        if(startchoice == 1)
                        {
                            level6(&total);
                            printf("do you want the 7th level to start?(yes = 1 / no  =  2)\n");
                            scanf("%i",&startchoice);
                            if(startchoice == 1)
                            {
                                level7(&total);
                                printf("do you want the 8th level to start?(yes = 1 / no  =  2)\n");
                                scanf("%i",&startchoice);
                                if(startchoice == 1)
                                {
                                    level8(&total);
                                    printf("do you want the 9th level to start?(yes = 1 / no  =  2)\n");
                                    scanf("%i",&startchoice);
                                    if(startchoice == 1)
                                    {
                                        level9(&total);
                                        printf("do you want the 10th level to start?(yes = 1 / no  =  2)\n");
                                        scanf("%i",&startchoice);   
                                        if(startchoice == 1)
                                        {
                                            level10(&total);
                                            printf("do you want the 11th level to start?(yes = 1 / no  =  2)\n");
                                            scanf("%i",&startchoice); 
                                            if(startchoice == 1)
                                            {
                                                level1(&total);
                                                printf("bye!!!");
                                            }
                                            else 
                                            {
                                                return 0;
                                            }
                                        }
                                        else 
                                        {
                                            return 0;
                                        }
                                    }
                                    else 
                                    {
                                        return 0;
                                    }
                                }
                                else 
                                {
                                    return 0;
                                }
                            }
                            else 
                            {
                                return 0;
                            }
                        }
                        else 
                        {
                            return 0;
                        }
                    }
                    else 
                    {
                        return 0;
                    }
                }
                else 
                {
                    return 0;
                }
            }
            else 
            {
                return 0;
            }
        }
        else 
        {
            return 0;
        }
    }
    else 
    {
        return 0;
    }
    return 0;
}