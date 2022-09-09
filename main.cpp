#include <iostream>
#include <algorithm> // Для знаходження НСД (для скорочення дробу, якщо можливо)
using namespace std;

class Pair{
    double first, second; //власне поля
public:
    Pair () { // Конструктор без параметрів (використовується при створенні масивів, бо масиви не надають параметри)
        cout << "Created pair with no given values." << endl;
    }
    Pair (double f, double s) { // Конструктор з параметрами
        cout << "Created pair. ";
        if (s == 0){ // Знаменник не повинен дорівнювати нулю, тому знищуємо пару, якщо при створенні пари друге поле прирівнюють до нуля.
            cout << endl << "\"Second\" can't equal to 0! This pair is destroyed." << endl;
            this->~Pair(); // Виклик деструктора для пари, що створюється
        }
        else{
            first = f;
            second = s;
            cout << "First: " << first << " | Second: " << second << endl;
        }
    }

    int ipart() {
        return int(first / second);
    }

    Pair operator+(const Pair& right) const{
        Pair left;
        left.first = this->first;
        left.second = this->second;
        int nsk = (left.second * right.second) / __gcd(int(left.second), int(right.second)); // Шукаємо НСК (для додавання дробів)
        left.first *= nsk / left.second;
        int nom = right.first * nsk / right.second;
        left.first += nom;
        left.second = nsk;
        int left_gcd = __gcd(int(left.first), int(left.second)); // Частина скорочення дробу (можна було винести у окрему функцію)
        left.first /= left_gcd;
        left.second /= left_gcd;
        return left;
    }
    Pair operator+(const int& num) const{
        Pair left;
        left.first = this->first;
        left.second = this->second;
        left.first += num * left.second; // Додаємо число за правилами математики
        int left_gcd = __gcd(int(left.first), int(left.second));
        left.first /= left_gcd;
        left.second /= left_gcd;
        return left;
    }

    Pair operator++(){
        first += second;
        int gcd = __gcd(int(first), int(second));
        if (gcd > 1) {
            first /= gcd;
            second /= gcd;
        }
        return *this;
    }

    Pair operator++(int){ // Тип використовується лише щоб показати, що це префіксний унарний оператор
        Pair temp = *this;
        first += second;
        int gcd = __gcd(int(first), int(second));
        if (gcd > 1) {
            first /= gcd;
            second /= gcd;
        }
        return temp;
    }
    // Всі наступні методи викликаються для об'єктів, що не належать до описаного класу, тому вони описуються як дружні до класу.
    friend Pair operator+(int num, Pair& right);
    friend ostream& operator<<(ostream& os, const Pair& pair);
    friend istream& operator>>(istream& is, Pair& pair);
};

Pair operator+(int num, Pair& right){
    right.first += num * right.second;
    int gcd = __gcd(int(right.first), int(right.second));
    if (gcd > 1) {
        right.first /= gcd;
        right.second /= gcd;
    }
    return right;
}

ostream &operator<<(ostream &os, const Pair& pair) {
    os << pair.first << " / " << pair.second;
    return os;
}

istream &operator>>(istream &is, Pair &pair) {
    is >> pair.first >> pair.second;
    if (pair.second == 0) {
        cout << "'pair.second' can't equal to 0! Retry." << endl;
        is >> pair.first >> pair.second;
    }
    return is;
}

int main() { // Закоментовані рядки коментувалися для перевірки
    Pair a_pair(3, 0);
    Pair b_pair(2, 3);
    Pair c_pair(6, 4);
    cout << a_pair << endl;
//    cout << "Введіть пару: ";
//    cin >> a_pair;
//    cout << a_pair << endl;
    int num = 3;
    cout << "Ціла частина дробу: " << a_pair.ipart() << endl;
    cout << "b + c = " << b_pair << " + " << c_pair << " = " << (b_pair + c_pair);
    cout << "b + c + num = " << b_pair << " + " << c_pair << " + " << num << " = " << (b_pair + c_pair + num) << endl;
    cout << "b + num + c = " << b_pair << " + " << num << " + " << c_pair << " = " << (b_pair + num + c_pair) << endl;
    cout << "num + c = " << num << " + " << c_pair << " = " << (num + c_pair) << endl;
    cout << "c_pair++: " << c_pair++ << " c_pair: " << c_pair << endl;
    cout << "++c_pair: " << ++c_pair << endl;
//    Pair mas[4];
//    for (int i = 0; i < 4; i++){
//        cout << "mas[" << i << "]: " << mas[i] << endl;
//    }
//    for (auto & elem : mas){
//        cout << "Введіть пару: ";
//        cin >> elem;
//    }
//    for (Pair & elem : mas){
//        cout << "Дріб: " << elem << " Ціла частина: " << elem.ipart() << endl;
//    }
    return 0;
}
