#include <iostream>

using namespace std;

const int mSize = 100;

void operation1(double* mas, int size)
{
    double k;
    cout << "Введите коэффициент усиления: ";
    cin >> k;
    for (int i = 0; i < size; i++)
        mas[i] = mas[i] * k;
}

void operation2(double* mas, int size)
{
    double k;
    cout << "Введите коэффициент ослабления: ";
    cin >> k;
    if (k == 0)
    {
        cout << "Коэффициент не может быть равен 0" << endl;
        return;
    }
    for (int i = 0; i < size; i++)
        mas[i] = mas[i] / k;
}

void operation3(double* mas, int size)
{
    double threshold;
    cout << "Введите порог: ";
    cin >> threshold;
    for (int i = 0; i < size; i++)
    {
        if (mas[i] < threshold)
            mas[i] = 0;
    }
}

void operation4(double* mas, int size)
{
    double maxAmp;
    cout << "Введите максимальную амплитуду: ";
    cin >> maxAmp;
    for (int i = 0; i < size; i++)
    {
        if (mas[i] > maxAmp)
            mas[i] = maxAmp;
    }
}

void applyProcessing(double* mas, int size, void (*processor)(double*, int))
{
    if (processor != nullptr)
        processor(mas, size);
}

void print(double* mas, int size)
{
    for (int i = 0; i < size; i++)
        cout << mas[i] << " ";
    cout << endl;
}

void restoremas(double* mas, double* original, int size)
{
    for (int i = 0; i < size; i++)
        mas[i] = original[i];
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    double mas[mSize];
    double original[mSize];
    int size = 0;

    void (*processors[4])(double*, int) =
    {
        operation1,
        operation2,
        operation3,
        operation4
    };

    void (*processor)(double*, int) = nullptr;

    int choice;
    int op;

    do
    {
        cout << "1. Сгенерировать данные\n";
        cout << "2. Показать данные\n";
        cout << "3. Выбрать и выполнить обработку\n";
        cout << "4. Восстановить исходные данные\n";
        cout << "5. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Введите количество элементов: ";
            cin >> size;
            if (size < 0) size = 0;
            if (size > mSize) size = mSize;

            for (int i = 0; i < size; i++)
            {
                mas[i] = rand() % 201 - 100;
                original[i] = mas[i];
            }
            cout << "Данные сгенерированы\n";
            break;

        case 2:
            if (size == 0)
                cout << "Сначала сгенерируйте данные\n";
            else
            {
                cout << "Текущий массив: ";
                print(mas, size);
            }
            break;

        case 3:
            if (size == 0)
            {
                cout << "Сначала сгенерируйте данные!\n";
                break;
            }

            cout << "1. Увеличить громкость\n";
            cout << "2. Уменьшить громкость\n";
            cout << "3. Обнулить малые значения\n";
            cout << "4. Ограничить амплитуду\n";
            cout << "Выберите операцию: ";
            cin >> op;

            if (op < 1 || op > 4)
            {
                cout << "Неверный номер операции\n";
                break;
            }

            processor = processors[op - 1];

            cout << "Массив до обработки:    ";
            print(mas, size);

            applyProcessing(mas, size, processor);

            cout << "Массив после обработки: ";
            print(mas, size);
            break;

        case 4:
            if (size == 0)
                cout << "Сначала сгенерируйте данные\n";
            else
            {
                restoremas(mas, original, size);
                cout << "Исходные данные восстановлены\n";
            }
            break;

        case 5:
            cout << "Выход из программы\n";
            break;

        default:
            cout << "Такого пункта нет в меню\n";
        }
    } while (choice != 5);
    


}