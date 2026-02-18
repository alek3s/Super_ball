// Sport5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.



//Sport5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//game.xlsx - название файла в корне директории (нужно переименовывать и удалять все лишнее)


#include <cstdlib> // для использования функции exit()
#include <string>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

//структура содержит все данные о тиражах
struct Tiragi
{
    int id;          //идентификатор каждой записи - номер тиража

    int Date_Day;   //день тиража
    int Date_Month; //месяц тиража
    int Date_Year;  //год тиража

    int Ball_1;     //выпавшие шары
    int Ball_2;
    int Ball_3;
    int Ball_4;
    int Ball_5;
    int Ball_6;  
};

//структура содержит все данные о шарах (все характеристики)
//номер шара = номер порядковый массива + 1
struct Ball
{

    int Weight = 0;      //вес шара ( всего выпадений)
    double Often = 0.0;  //частота выпадания(среднее количество тиражей через которое выпадает шар)
    int Last = 0;        //число тиражей которое прошло с момента последнего выпадения шара
    bool YES = false;    //рекомендация к выбору в следующем тираже

    int MinInterval = 0; //минимальный интервал тиражей между выпаданиями шара
    int MaxInterval = 0; //максимальный интервал тиражей между выпаданиями шара 

};


int SDTiragi = 0;       //для ввода количества тиражей вручную
int SDBall = 0;         //для ввода количества чисел, учавствующих в тираже
int Count = 0;          //счетчик количества тиражей считаных из файла

int main()
{
    char buf;           //промежуточный буфер

    int flag = 1;       // флаг отслеживания табуляции, разрыва цыфр и перехода на новую строку
                        // 1 раз - между символами
                        // 2 раза - табуляция
                        // 3 раза - пререход на новую строку
    
    int flag_2 = 1;//флаг количества раздельных чисел в строке

    int fff = 0;
    int meniu = 4;
    setlocale(LC_ALL, "rus");
    //создаем объект класса ofstream для записи в файл
    ofstream File_Write;

    //создаем объект класса ofstream для чтения из файла
    ifstream File_Read;

    string str;

    cout << "введите количество SDTiragi " << '\n';
    cout << "SDTiragi -> ";
    cin >> SDTiragi;
    Tiragi* DTiragi = new Tiragi[SDTiragi];//динамический массив из структур)тут результаты тиражей в памяти)

    //создаем динамический масив структур шаров с их характеристиками
    cout << "введите количество  SDBall" << '\n';
    cout << "SDBool -> ";

    cin >> SDBall;
    Ball* DBall = new Ball[SDBall];


    //организовываем считывание файла при первом запуске программы
    File_Read.open("game.txt", ios::binary || ios::in);
    if (File_Read.is_open())
    {
        meniu = 8;
        Count = 0;
        while (!File_Read.eof())
        {
            File_Read >> buf;

            if ((58 > buf) && (buf >= 48))//если это цифра
            {
                cout << buf;//выводим на экран
                str.push_back(buf);
                flag = 0;
            }
            else
            {
                if (buf == '\0')
                {

                    flag++;
                    switch (flag)
                    {
                    case 1:
                        break;
                    case 2://если это табуляция
                        switch (flag_2)
                        {
                        case 1://если это первое число в строке 
                            DTiragi[Count].id = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 2://если это второе число в строке 
                            DTiragi[Count].Date_Day = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 3://если это третье число в строке 
                            DTiragi[Count].Date_Month = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 4://если это четвертое число в строке 
                            DTiragi[Count].Date_Year = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 5://если это пятое число в строке 
                            DTiragi[Count].Ball_1 = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 6://если это шестое число в строке 
                            DTiragi[Count].Ball_2 = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 7://если это седьмое число в строке 
                            DTiragi[Count].Ball_3 = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 8://если это восьмое число в строке 
                            DTiragi[Count].Ball_4 = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 9://если это третье число в строке 
                            DTiragi[Count].Ball_5 = atoi(str.c_str());
                            flag_2++;
                            break;
                        case 10://если это третье число в строке 
                            DTiragi[Count].Ball_6 = atoi(str.c_str());
                            flag_2++;
                            break;
                        default:
                            break;
                        }
                        cout << "  ";
                        str = "";// очищаем строку
                        break;
                    case 3:
                        cout << "\n";
                        str = "";
                        flag_2 = 1;//следующий проход это новая строка
                        Count++;//считаем тиражи
                        break;
                    default:
                        break;
                    }

                }
            }
        }
    }
    else
    {
        cout << "Файл не может быть открыт!\n"; // сообщить об этом
    }
    File_Read.close();//закрываем файл
    buf = 0;
    //все готово для анализа 


    while (1)
    {
        if (meniu == 1)//смотрим вес каждого шара в тиражах
        {
            //очищаем массив структур шаров
            for (int a = 0; a < SDBall; a++)
            {
                DBall[a].Last = 0;
                DBall[a].Often = 0.0;
                DBall[a].Weight = 0;
                DBall[a].YES = false;
            }
            for (int a = 0; a < SDBall; a++)//выбираем первый шар
            {
                for (int b = 0; b < Count; b++)//пересматриваем все тиражи и вычисляем вес и частоту каждого шара
                {
                    if ((a + 1) == DTiragi[b].Ball_1) { DBall[a].Weight++; DBall[a].Often = (static_cast<double>(Count) / DBall[a].Weight); }
                    if ((a + 1) == DTiragi[b].Ball_2) { DBall[a].Weight++; DBall[a].Often = (static_cast<double>(Count) / DBall[a].Weight); }
                    if ((a + 1) == DTiragi[b].Ball_3) { DBall[a].Weight++; DBall[a].Often = (static_cast<double>(Count) / DBall[a].Weight); }
                    if ((a + 1) == DTiragi[b].Ball_4) { DBall[a].Weight++; DBall[a].Often = (static_cast<double>(Count) / DBall[a].Weight); }
                    if ((a + 1) == DTiragi[b].Ball_5) { DBall[a].Weight++; DBall[a].Often = (static_cast<double>(Count) / DBall[a].Weight); }
                    if ((a + 1) == DTiragi[b].Ball_6) { DBall[a].Weight++; DBall[a].Often = (static_cast<double>(Count) / DBall[a].Weight); }
                }
            }
            //ищем сколько тиражей прошло после последнего выпадания
            for (int a = 0; a < SDBall; a++)
            {
                for (int b = Count - 1; b >= 0; b--)//пересматриваем все тиражи
                {

                    if ((a + 1) == DTiragi[b].Ball_1) { DBall[a].Last = Count - b; break; }
                    if ((a + 1) == DTiragi[b].Ball_2) { DBall[a].Last = Count - b; break; }
                    if ((a + 1) == DTiragi[b].Ball_3) { DBall[a].Last = Count - b; break; }
                    if ((a + 1) == DTiragi[b].Ball_4) { DBall[a].Last = Count - b; break; }
                    if ((a + 1) == DTiragi[b].Ball_5) { DBall[a].Last = Count - b; break; }
                    if ((a + 1) == DTiragi[b].Ball_6) { DBall[a].Last = Count - b; break; }
                }
            }
            //анализируем наиболее вероятные шары к выпаданию в следующем тираже (которые давно не выпадали)
            for (int a = 0; a < SDBall; a++)
            {

                if (0 > (DBall[a].Often - static_cast<double>(DBall[a].Last)))
                {
                    //рекомендуем к использованию
                    DBall[a].YES = true;
                }
            }

            //открываем файл для записи
            ofstream File_Write("1.txt", ios_base::out | ios_base::trunc);

            if (!File_Write.is_open()) // если файл небыл открыт
            {
                cout << "Файл не может быть открыт или создан!!!\n"; // напечатать соответствующее сообщение
                return 1; // выполнить выход из программы
            }
            //очищаем экран
            system("cls");
            cout << "Файл  '1.txt'  открыт, началась запись. " << "\n";
            for (int a = 0; a < 49; a++)//выводим масив
                // который показывает сколько раз за все тиражы выпадало определенный шар
            {
                File_Write << "    " << a << "    " << "Шар номер" << "    " << a + 1 << "   " << "выпадал" << "  " << DBall[a].Weight << "  " << "раз" << '\n';
            }
            //выводим результат поиска выпадания двух чисел (вес и частоту)
            for (int j = 0; j < 49; j++)
            {
                if (DBall[j].Weight > 0)
                {
                    File_Write << j << "    " << "число :" << "    "
                        << (j + 1)
                        << "    "
                        << "выпадало" << "    "
                        << DBall[j].Weight << "    " << "раз"
                        << "    " << "частота:"
                        << "    " << "выпадает каждый" << "    "
                        << DBall[j].Often
                        << "    " << "тираж" << "    "
                        << "последний раз выпадал" << "    "
                        << DBall[j].Last
                        << "    " << "тиражей назад"
                        << "\n";
                }
            }
            //выводим результат наиболее ожидаемых вероятных шаров одиночек
            for (int j = 0; j < 49; j++)
            {
                if (DBall[j].YES == true)
                {
                    File_Write << "возможно выпадение числа :" << "    " << (j + 1) << "\n";

                }
            }

            system("cls");
            cout << "Файл  '1.txt'  ЗАПИСАН! " << "\n";
            File_Write.close();
            meniu = 8;
        }
        if (meniu == 2)//смотрим веc двух шаров в тиражах
        {

            bool a_ok = false;
            bool b_ok = false;
            int a = 0;
            int b = 0;
            int c = 0;
            int i = 0;
            int j = 0;

            int DinamichMasivSize = 0;//размер масива 
            struct MyStruct//структура для хранения парномеров
            {
                int Ball_1;
                int Ball_2;
                int count;
            };
            //узнаем количество проходов для выделения памяти под массив
            for (a = 1; a < 49; a++)//выбираем первый шар
            {
                for (b = a + 1; b <= 49; b++)//выбираем второй шар
                {
                    DinamichMasivSize++;
                }
            }

            MyStruct* DinamichMasiv = new MyStruct[DinamichMasivSize];//массив для сохранения результатов поиска выпадения двух чисел

            for (a = 1; a < 49; a++)//выбираем первый шар
            {
                for (b = a + 1; b <= 49; b++)//выбираем второй шар
                {

                    //записываем в масив проверяемую пару чисел
                    DinamichMasiv[i].Ball_1 = a;
                    DinamichMasiv[i].Ball_2 = b;
                    DinamichMasiv[i].count = 0;

                    for (c = 0; c < Count; c++)//пересматриваем все тиражи
                    {
                        if (a == DTiragi[c].Ball_1)
                        {
                            a_ok = true;
                            //ищем второй шар
                            if (b == DTiragi[c].Ball_1) { b_ok = true; }
                            if (b == DTiragi[c].Ball_2) { b_ok = true; }
                            if (b == DTiragi[c].Ball_3) { b_ok = true; }
                            if (b == DTiragi[c].Ball_4) { b_ok = true; }
                            if (b == DTiragi[c].Ball_5) { b_ok = true; }
                            if (b == DTiragi[c].Ball_6) { b_ok = true; }

                        }
                        if (a == DTiragi[c].Ball_2)
                        {
                            a_ok = true;
                            //ищем второй шар
                            if (b == DTiragi[c].Ball_1) { b_ok = true; }
                            if (b == DTiragi[c].Ball_2) { b_ok = true; }
                            if (b == DTiragi[c].Ball_3) { b_ok = true; }
                            if (b == DTiragi[c].Ball_4) { b_ok = true; }
                            if (b == DTiragi[c].Ball_5) { b_ok = true; }
                            if (b == DTiragi[c].Ball_6) { b_ok = true; }

                        }
                        if (a == DTiragi[c].Ball_3)
                        {
                            a_ok = true;
                            //ищем второй шар
                            if (b == DTiragi[c].Ball_1) { b_ok = true; }
                            if (b == DTiragi[c].Ball_2) { b_ok = true; }
                            if (b == DTiragi[c].Ball_3) { b_ok = true; }
                            if (b == DTiragi[c].Ball_4) { b_ok = true; }
                            if (b == DTiragi[c].Ball_5) { b_ok = true; }
                            if (b == DTiragi[c].Ball_6) { b_ok = true; }
                        }
                        if (a == DTiragi[c].Ball_4)
                        {
                            a_ok = true;
                            //ищем второй шар
                            if (b == DTiragi[c].Ball_1) { b_ok = true; }
                            if (b == DTiragi[c].Ball_2) { b_ok = true; }
                            if (b == DTiragi[c].Ball_3) { b_ok = true; }
                            if (b == DTiragi[c].Ball_4) { b_ok = true; }
                            if (b == DTiragi[c].Ball_5) { b_ok = true; }
                            if (b == DTiragi[c].Ball_6) { b_ok = true; }
                        }
                        if (a == DTiragi[c].Ball_5)
                        {
                            a_ok = true;
                            //ищем второй шар
                            if (b == DTiragi[c].Ball_1) { b_ok = true; }
                            if (b == DTiragi[c].Ball_2) { b_ok = true; }
                            if (b == DTiragi[c].Ball_3) { b_ok = true; }
                            if (b == DTiragi[c].Ball_4) { b_ok = true; }
                            if (b == DTiragi[c].Ball_5) { b_ok = true; }
                            if (b == DTiragi[c].Ball_6) { b_ok = true; }
                        }
                        if (a == DTiragi[c].Ball_6)
                        {
                            a_ok = true;
                            //ищем второй шар
                            if (b == DTiragi[c].Ball_1) { b_ok = true; }
                            if (b == DTiragi[c].Ball_2) { b_ok = true; }
                            if (b == DTiragi[c].Ball_3) { b_ok = true; }
                            if (b == DTiragi[c].Ball_4) { b_ok = true; }
                            if (b == DTiragi[c].Ball_5) { b_ok = true; }
                            if (b == DTiragi[c].Ball_6) { b_ok = true; }
                        }
                        //сохраняем результаты после каждой строки
                        if (a_ok && b_ok)
                        {
                            DinamichMasiv[i].count++;
                            a_ok = false;
                            b_ok = false;
                        }
                    }
                    i++;

                }
            }
            //открываем файл для записи
            ofstream File_Write("2.txt", ios_base::out | ios_base::trunc);

            if (!File_Write.is_open()) // если файл небыл открыт
            {
                cout << "Файл не может быть открыт или создан!!!\n"; // напечатать соответствующее сообщение
                return 1; // выполнить выход из программы
            }
            //очищаем экран
            system("cls");
            cout << "Файл  '2.txt'  открыт, началась запись. " << "\n";

            //выводим результат поиска выпадания двух чисел
            for (j = 0; j < i; j++)
            {
                if (DinamichMasiv[j].count > 0)
                {
                    File_Write << j << "    " << "числа : " << "    "
                        << DinamichMasiv[j].Ball_1
                        << "    " << "и" << "    "
                        << DinamichMasiv[j].Ball_2 << "    "
                        << "выпадали в одном тираже вместе" << "    "
                        << DinamichMasiv[j].count << "    " << "раз" << "\n";
                }
            }
            system("cls");
            cout << "Файл  '2.txt'  ЗАПИСАН! " << "\n";
            File_Write.close();
        }

        if (meniu == 8)
        {
            //system("cls");//очистка экрана
            cout << "                 МЕНЮ:\n";
            cout << "  1.Анализ одиночных номеров. \n";
            cout << "  2.Проверить вес каждого двойного номера \n";
            cout << "  3.Проверить вес каждого тройного номера\n";
            cout << "  4.Проверить вес каждого четверного номера\n";
            cout << "  5.Проверить вес каждого пятерного номера\n";
            cout << "  6.Проверить вес каждого шестерного номера\n";

            cout << "  8.Очистить экран\n";
            cout << "  9.Выход\n\n";

        }
        if (meniu == 9)
        {
            break;
        }
        if (meniu == 10)//смотрим вес каждого шара в тиражах
        {
            //очищаем массив структур шаров
            for (int a = 0; a < SDBall; a++)
            {
                DBall[a].Last = 0;
                DBall[a].Often = 0.0;
                DBall[a].Weight = 0;
                DBall[a].YES = false;
            }
            //открываем файл для записи
            ofstream File_Write("10.txt", ios_base::out | ios_base::trunc);

            if (!File_Write.is_open()) // если файл небыл открыт
            {
                cout << "Файл не может быть открыт или создан!!!\n"; // напечатать соответствующее сообщение
                return 1; // выполнить выход из программы
            }

            for (int c = 0; c < Count; c++)// идем по тиражам
            {
                //очищаем массив структур шаров
                for (int a = 0; a < SDBall; a++)
                {
                    DBall[a].Last = 0;
                    DBall[a].Often = 0.0;
                    DBall[a].Weight = 0;
                    DBall[a].YES = false;
                }
                //выводим номер тиража и выпавшие номера
                File_Write << "Тираж № " << c + 1 << "(" << DTiragi[c].id << ")" << "Номера : " << DTiragi[c].Ball_1 << ", "
                    << DTiragi[c].Ball_2 << ", " << DTiragi[c].Ball_3 << ", " << DTiragi[c].Ball_4 << ", "
                    << DTiragi[c].Ball_5 << ", " << DTiragi[c].Ball_6 << ", " << '\n';




                for (int a = 0; a < SDBall; a++)//выбираемномер шара               
                {
                    for (int b = 0; b <= c; b++) //пересматриваем все тиражи и вычисляем вес и частоту каждого шара
                    {
                        if ((a + 1) == DTiragi[b].Ball_1)
                        {
                            DBall[a].Weight++;
                            DBall[a].Often = (static_cast<double>(c + 1) / DBall[a].Weight);
                        }
                        if ((a + 1) == DTiragi[b].Ball_2)
                        {
                            DBall[a].Weight++;
                            DBall[a].Often = (static_cast<double>(c + 1) / DBall[a].Weight);
                        }
                        if ((a + 1) == DTiragi[b].Ball_3)
                        {
                            DBall[a].Weight++;
                            DBall[a].Often = (static_cast<double>(c + 1) / DBall[a].Weight);
                        }
                        if ((a + 1) == DTiragi[b].Ball_4)
                        {
                            DBall[a].Weight++;
                            DBall[a].Often = (static_cast<double>(c + 1) / DBall[a].Weight);
                        }
                        if ((a + 1) == DTiragi[b].Ball_5)
                        {
                            DBall[a].Weight++;
                            DBall[a].Often = (static_cast<double>(c + 1) / DBall[a].Weight);
                        }
                        if ((a + 1) == DTiragi[b].Ball_6)
                        {
                            DBall[a].Weight++;
                            DBall[a].Often = (static_cast<double>(c + 1) / DBall[a].Weight);
                        }
                    }
                }
                //ищем сколько тиражей прошло после последнего выпадания
                for (int a = 0; a < SDBall; a++)
                {
                    for (int b = c; b >= 0; b--)//пересматриваем все тиражи
                    {

                        if ((a + 1) == DTiragi[b].Ball_1) { DBall[a].Last = c - b; break; }
                        if ((a + 1) == DTiragi[b].Ball_2) { DBall[a].Last = c - b; break; }
                        if ((a + 1) == DTiragi[b].Ball_3) { DBall[a].Last = c - b; break; }
                        if ((a + 1) == DTiragi[b].Ball_4) { DBall[a].Last = c - b; break; }
                        if ((a + 1) == DTiragi[b].Ball_5) { DBall[a].Last = c - b; break; }
                        if ((a + 1) == DTiragi[b].Ball_6) { DBall[a].Last = c - b; break; }
                    }
                }
                //анализируем наиболее вероятные шары к выпаданию в следующем тираже (которые давно не выпадали)
                for (int a = 0; a < SDBall; a++)
                {

                    if (0 > (DBall[a].Often - static_cast<double>(DBall[a].Last)))
                    {
                        //рекомендуем к использованию
                        DBall[a].YES = true;
                    }
                }

                //ищем самый малый интервал и самый большой 

                for (int a = 0; a < SDBall; a++)//выбираем число
                {
                    bool one = false;//первое нахождение
                    bool two = false;//второе нахождение
                    int poz = 0;//предыдущая позиция(номер тиража)
                    for (int C = 0; C < Count; C++)//прогоняем по тиражам
                    {
                        if ((a + 1) == DTiragi[c].Ball_1)
                        {
                            one = true;
                            poz = DTiragi[c].id;
                            //break;
                        }
                        if ((a + 1) == DTiragi[c].Ball_2)
                        {
                            //break;
                        }
                        if ((a + 1) == DTiragi[c].Ball_3)
                        {
                            //break;
                        }
                        if ((a + 1) == DTiragi[c].Ball_4)
                        {
                            //break;
                        }
                        if ((a + 1) == DTiragi[c].Ball_5)
                        {
                            //break;
                        }
                        if ((a + 1) == DTiragi[c].Ball_6)
                        {
                            //break;
                        }


                    }

                }
                //выводим результат в файл



                for (int j = 0; j < 49; j++)
                {
                    if (DBall[j].Weight > 0)
                    {
                        File_Write << "число :" << " "
                            << (j + 1) << " " << "выпадало"
                            << " " << DBall[j].Weight << " "
                            << "раз" << " " << "Частота:" << " " << "выпадает каждый" << " " << DBall[j].Often << " " << "тираж"
                            << " " << "последний раз выпадал" << " " << DBall[j].Last << " " << "тиражей назад" << "\n";
                    }
                }
                File_Write << "\n\n";
                //выводим результат наиболее ожидаемых вероятных шаров одиночек
                File_Write << "возможно выпадение числа : ";
                for (int j = 0; j < 49; j++)
                {
                    if (DBall[j].YES == true)
                    {
                        File_Write << (j + 1) << ", ";

                    }
                }
                File_Write << "\n\n";


            }
            system("cls");
            cout << "Файл  '10.txt'  ЗАПИСАН! " << "\n";
            meniu = 8;
        }
        cout << "меню " << "\n";
        cin >> meniu;
    }
    system("pause");
    return 0;
}
/*if (meniu == 3) //смотрим веc трех шаров в тиражах
        {

            bool a_1_ok = false;
            bool a_2_ok = false;
            bool a_3_ok = false;
            int a_1 = 0;
            int a_2 = 0;
            int a_3 = 0;

            int c = 0;
            int i = 0;
            int j = 0;

            int DinamichMasivSize = 0;//размер масива

            struct MyStruct//структура для хранения парномеров
            {
                int Ball_1;
                int Ball_2;
                int Ball_3;
                int count;
            };
            //узнаем количество проходов для выделения памяти под массив
            for (a_1 = 1; a_1 < (49 - 1); a_1++)//выбираем первый шар
            {
                for (a_2 = a_1 + 1; a_2 < 49; a_2++)//выбираем второй шар
                {
                    for (a_3 = a_2 + 1; a_3 <= 49; a_3++)//выбираем второй шар
                    {
                        DinamichMasivSize++;
                    }
                }
            }
            MyStruct* DinamichMasiv = new MyStruct[DinamichMasivSize];//массив для сохранения результатов поиска выпадения двух чисел

            for (a_1 = 1; a_1 < (49 - 1); a_1++)//выбираем первый шар
            {
                for (a_2 = a_1 + 1; a_2 < 49; a_2++)//выбираем второй шар
                {
                    for (a_3 = a_2 + 1; a_3 <= 49; a_3++)//выбираем второй шар
                    {

                        //записываем в масив проверяемую пару чисел
                        DinamichMasiv[i].Ball_1 = a_1;
                        DinamichMasiv[i].Ball_2 = a_2;
                        DinamichMasiv[i].Ball_3 = a_3;
                        DinamichMasiv[i].count = 0;

                        for (c = 0; c < Count; c++)//пересматриваем все тиражи
                        {
                            if (a_1 == DTiragi[c].Ball_1)//ищем первый шар
                            {
                                a_1_ok = true;
                                if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_2)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар

                                }
                                if (a_2 == DTiragi[c].Ball_3)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_4)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_5)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_6)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }

                            }
                            if (a_1 == DTiragi[c].Ball_2)
                            {
                                a_1_ok = true;
                                if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_2)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар

                                }
                                if (a_2 == DTiragi[c].Ball_3)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_4)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_5)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_6)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }

                            }
                            if (a_1 == DTiragi[c].Ball_3)
                            {
                                a_1_ok = true;
                                if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_2)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар

                                }
                                if (a_2 == DTiragi[c].Ball_3)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_4)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_5)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_6)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }

                            }
                            if (a_1 == DTiragi[c].Ball_4)
                            {
                                a_1_ok = true;
                                if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_2)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар

                                }
                                if (a_2 == DTiragi[c].Ball_3)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_4)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_5)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_6)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }

                            }
                            if (a_1 == DTiragi[c].Ball_5)
                            {
                                a_1_ok = true;
                                if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_2)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар

                                }
                                if (a_2 == DTiragi[c].Ball_3)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_4)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_5)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_6)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }

                            }
                            if (a_1 == DTiragi[c].Ball_6)
                            {
                                a_1_ok = true;
                                if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_2)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар

                                }
                                if (a_2 == DTiragi[c].Ball_3)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_4)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_5)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }
                                if (a_2 == DTiragi[c].Ball_6)
                                {
                                    a_2_ok = true;
                                    if (a_3 == DTiragi[c].Ball_1) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_2) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_3) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_4) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_5) { a_3_ok = true; }//ищем треттий шар
                                    if (a_3 == DTiragi[c].Ball_6) { a_3_ok = true; }//ищем треттий шар
                                }

                            }
                            //сохраняем результаты после каждой строки
                            if (a_1_ok && a_2_ok && a_3_ok)
                            {
                                DinamichMasiv[i].count++;
                                a_1_ok = false;
                                a_2_ok = false;
                                a_3_ok = false;
                            }
                        }
                        i++;

                    }
                }
            }

            //открываем файл для записи
            ofstream File_Write("3.txt", ios_base::out | ios_base::trunc);

            if (!File_Write.is_open()) // если файл небыл открыт
            {
                cout << "Файл не может быть открыт или создан!!!\n"; // напечатать соответствующее сообщение
                return 1; // выполнить выход из программы
            }
            //очищаем экран
            system("cls");
            cout << "Файл  '3.txt'  открыт, началась запись. " << "\n";
            //выводим результат поиска выпадания двух чисел
            for (j = 0; j < i; j++)
            {
                if (DinamichMasiv[j].count > 0)
                {
                    File_Write << j << "числа:" << "    "
                        << DinamichMasiv[j].Ball_1 << "    "
                        << "и" << "    "
                        << DinamichMasiv[j].Ball_2 << "    "
                        << "и" << "    "
                        << DinamichMasiv[j].Ball_3 << "    "
                        << "выпадали вместе" << "    "
                        << DinamichMasiv[j].count << "    "
                        << "раз" << "\n";
                }
            }
            system("cls");
            cout << "Файл  '3.txt'  ЗАПИСАН! " << "\n";
            File_Write.close();

        }
        if (meniu == 4) //смотрим веc четырех шаров в тиражах)
        {

            bool a_1_ok = false;
            bool a_2_ok = false;
            bool a_3_ok = false;
            bool a_4_ok = false;

            int a_1 = 0;
            int a_2 = 0;
            int a_3 = 0;
            int a_4 = 0;

            int c = 0;
            int i = 0;
            int j = 0;

            int DinamichMasivSize = 0;//размер масива

            struct MyStruct//структура для хранения парномеров
            {
                int Ball_1;
                int Ball_2;
                int Ball_3;
                int Ball_4;
                int count;
            };
            //узнаем сколько проходов для выделения памяти под массив
            for (a_1 = 1; a_1 < (49 - 2); a_1++)//выбираем первый шар
            {
                for (a_2 = a_1 + 1; a_2 < (49 - 1); a_2++)//выбираем второй шар
                {
                    for (a_3 = a_2 + 1; a_3 < 49; a_3++)//выбираем треттий шар
                    {
                        for (a_4 = a_3 + 1; a_4 <= 49; a_4++)
                        {
                            DinamichMasivSize++;
                        }
                    }
                }
            }
            MyStruct* DinamichMasiv = new MyStruct[DinamichMasivSize];//массив для сохранения результатов поиска выпадения двух чисел

            for (a_1 = 1; a_1 < (49 - 2); a_1++)//выбираем первый шар
            {
                for (a_2 = a_1 + 1; a_2 < (49 - 1); a_2++)//выбираем второй шар
                {
                    for (a_3 = a_2 + 1; a_3 < 49; a_3++)//выбираем треттий шар
                    {
                        for (a_4 = a_3 + 1; a_4 <= 49; a_4++)
                        {


                            //записываем в масив проверяемую четверку чисел
                            DinamichMasiv[i].Ball_1 = a_1;
                            DinamichMasiv[i].Ball_2 = a_2;
                            DinamichMasiv[i].Ball_3 = a_3;
                            DinamichMasiv[i].Ball_4 = a_4;
                            DinamichMasiv[i].count = 0;

                            for (c = 0; c < Count; c++)//пересматриваем все тиражи
                            {
                                if (a_1 == DTiragi[c].Ball_1)//ищем первый шар
                                {
                                    a_1_ok = true;
                                    if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                    {
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_2)
                                    {
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }

                                    }
                                    if (a_2 == DTiragi[c].Ball_3)
                                    {
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_4)
                                    {
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_5)
                                    {
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_6)
                                    {
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }

                                }
                                if (a_1 == DTiragi[c].Ball_2)
                                {
                                    a_1_ok = true;
                                    if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_2)
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }

                                    }
                                    if (a_2 == DTiragi[c].Ball_3)
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_4)
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_5)
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_6)
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }

                                }
                                if (a_1 == DTiragi[c].Ball_3)
                                {
                                    a_1_ok = true;
                                    if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                    {

                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_2)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }

                                    }
                                    if (a_2 == DTiragi[c].Ball_3)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_4)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_5)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_6)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }

                                }
                                if (a_1 == DTiragi[c].Ball_4)
                                {
                                    a_1_ok = true;
                                    if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_2)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }

                                    }
                                    if (a_2 == DTiragi[c].Ball_3)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_4)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_5)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_6)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }

                                }
                                if (a_1 == DTiragi[c].Ball_5)
                                {
                                    a_1_ok = true;
                                    if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_2)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }

                                    }
                                    if (a_2 == DTiragi[c].Ball_3)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_4)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_5)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_6)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }

                                }
                                if (a_1 == DTiragi[c].Ball_6)
                                {
                                    a_1_ok = true;
                                    if (a_2 == DTiragi[c].Ball_1) //ищем второй шар
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_2)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }

                                    }
                                    if (a_2 == DTiragi[c].Ball_3)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_4)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_5)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }
                                    if (a_2 == DTiragi[c].Ball_6)
                                    {
                                        a_2_ok = true;
                                        a_2_ok = true;
                                        if (a_3 == DTiragi[c].Ball_1)//ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар

                                        }
                                        if (a_3 == DTiragi[c].Ball_2) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_3) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_4) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_5) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                        if (a_3 == DTiragi[c].Ball_6) //ищем треттий шар
                                        {
                                            a_3_ok = true;
                                            if (a_4 == DTiragi[c].Ball_1) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_2) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_3) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_4) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_5) { a_4_ok = true; }//ищем четвертый шар
                                            if (a_4 == DTiragi[c].Ball_6) { a_4_ok = true; }//ищем четвертый шар
                                        }
                                    }

                                }

                                //сохраняем результаты после каждой строки
                                if (a_1_ok && a_2_ok && a_3_ok && a_4_ok)
                                {
                                    DinamichMasiv[i].count++;
                                    a_1_ok = false;
                                    a_2_ok = false;
                                    a_3_ok = false;
                                    a_4_ok = false;
                                }
                            }
                            i++;

                        }
                    }
                }
            }
            //открываем файл для записи
            ofstream File_Write("4.txt", ios_base::out | ios_base::trunc);

            if (!File_Write.is_open()) // если файл небыл открыт
            {
                cout << "Файл не может быть открыт или создан!!!\n"; // напечатать соответствующее сообщение
                return 1; // выполнить выход из программы
            }
            //очищаем экран
            system("cls");
            cout << "Файл  '4.txt'  открыт, началась запись. " << "\n";
            //выводим результат поиска выпадания двух чисел
            //выводим результат поиска выпадания двух чисел
            for (j = 0; j < i; j++)
            {
                if (DinamichMasiv[j].count > 0)
                {
                    File_Write << j << "числа:" << "    "
                        << DinamichMasiv[j].Ball_1 << "    "
                        << "и" << "    "
                        << DinamichMasiv[j].Ball_2 << "    "
                        << "и" << "    "
                        << DinamichMasiv[j].Ball_3 << "    "
                        << "и" << "    "
                        << DinamichMasiv[j].Ball_4 << "    "
                        << "выпадали в одном тираже вместе" << "    "
                        << DinamichMasiv[j].count << "    "
                        << "раз" << "\n";
                }
            }
            system("cls");
            cout << "Файл  '4.txt'  ЗАПИСАН! " << "\n";
            File_Write.close();

        }*/

        // Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
        // Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

        // Советы по началу работы 
        //   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
        //   2. В окне Team Explorer можно подключиться к системе управления версиями.
        //   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
        //   4. В окне "Список ошибок" можно просматривать ошибки.
        //   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
        //   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
