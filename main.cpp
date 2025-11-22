#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>
using namespace std;

class Fractions
{
private:
	int64_t numerator;
	uint64_t denominator;

	void irreducing_fraction()
	{
		if (denominator == 0) { throw invalid_argument("Деление на ноль!"); }
        if (numerator == 0) { denominator = 1; return; }

		int64_t a = (numerator < 0) ? -numerator : numerator;
		int64_t b = static_cast<int64_t>(denominator);
        while (b != 0) 
        {
            int64_t temp = b;
            b = a % b;
            a = temp;
        }
		numerator /= a;
		denominator /= static_cast<uint64_t>(a);
	}
public:
	Fractions(): numerator(0), denominator(1) {}
	Fractions(int64_t num): numerator(num), denominator(1) { irreducing_fraction(); }
    Fractions(int64_t num, int64_t den)
    {
        if (den == 0) { throw invalid_argument("Знаменатель не может быть нулем!"); }

        if (den < 0) 
        {
            numerator = -num;
            denominator = static_cast<uint64_t>(-den);
        }
        else 
        {
            numerator = num;
            denominator = static_cast<uint64_t>(den);
        }

        irreducing_fraction(); 
    }


	Fractions(const Fractions&) = default;

	int64_t get_numerator() const { return numerator; }
	uint64_t get_denominator() const { return denominator; }

	explicit operator double() const { return static_cast<double>(numerator) / static_cast<double>(denominator); }
	
	string str() const 
	{
		if (denominator == 1) { return to_string(numerator); }
		else { return to_string(numerator) + "/" + to_string(denominator); }
	}

    Fractions operator+() const { return *this; }
    Fractions operator-() const { return Fractions(-numerator, static_cast<int64_t>(denominator)); }

    Fractions& operator+=(const Fractions& other) 
    {
        int64_t new_num = numerator * static_cast<int64_t>(other.denominator) + other.numerator * static_cast<int64_t>(denominator);
        uint64_t new_den = denominator * other.denominator;

        numerator = new_num;
        denominator = new_den;
        numerator = new_num;
        denominator = new_den;
        irreducing_fraction();

        return *this;
    }

    Fractions& operator-=(const Fractions& other) 
    {
        int64_t new_num = numerator * static_cast<int64_t>(other.denominator) - other.numerator * static_cast<int64_t>(denominator);
        uint64_t new_den = denominator * other.denominator;

        numerator = new_num;
        denominator = new_den;
        numerator = new_num;
        denominator = new_den;
        irreducing_fraction();

        return *this;
    }

    Fractions& operator*=(const Fractions& other) 
    {
        numerator *= other.numerator;
        denominator *= other.denominator;
        irreducing_fraction();

        return *this;
    }

    Fractions& operator/=(const Fractions& other) 
    {
        if (other.numerator == 0)
        {
            numerator = 0;
            denominator = 1;
            return *this;
        }

        int64_t new_num = numerator * static_cast<int64_t>(other.denominator);
        uint64_t new_den = denominator * static_cast<uint64_t>(std::abs(other.numerator));

        if (other.numerator < 0) { new_num = -new_num; }

        numerator = new_num;
        denominator = new_den;
        irreducing_fraction();
        return *this;
    }

    bool is_zero() const { return numerator == 0; }
    bool is_positive() const { return numerator > 0; }
    bool is_negative() const { return numerator < 0; }

    friend Fractions operator+(Fractions lhs, const Fractions& rhs);
    friend Fractions operator-(Fractions lhs, const Fractions& rhs);
    friend Fractions operator*(Fractions lhs, const Fractions& rhs);
    friend Fractions operator/(Fractions lhs, const Fractions& rhs);

    friend bool operator==(const Fractions& lhs, const Fractions& rhs);
    friend bool operator!=(const Fractions& lhs, const Fractions& rhs);
    friend bool operator<(const Fractions& lhs, const Fractions& rhs);
    friend bool operator<=(const Fractions& lhs, const Fractions& rhs);
    friend bool operator>(const Fractions& lhs, const Fractions& rhs);
    friend bool operator>=(const Fractions& lhs, const Fractions& rhs);
};



Fractions operator+(Fractions lhs, const Fractions& rhs) { lhs += rhs; return lhs; }

Fractions operator-(Fractions lhs, const Fractions& rhs) { lhs -= rhs; return lhs; }

Fractions operator*(Fractions lhs, const Fractions& rhs) { lhs *= rhs; return lhs; }

Fractions operator/(Fractions lhs, const Fractions& rhs) { lhs /= rhs; return lhs; }

bool operator==(const Fractions& lhs, const Fractions& rhs) { return lhs.numerator * static_cast<int64_t>(rhs.denominator) == rhs.numerator * static_cast<int64_t>(lhs.denominator); }

bool operator!=(const Fractions& lhs, const Fractions& rhs) { return !(lhs == rhs); }

bool operator<(const Fractions& lhs, const Fractions& rhs) { return lhs.numerator * static_cast<int64_t>(rhs.denominator) < rhs.numerator * static_cast<int64_t>(lhs.denominator); }

bool operator<=(const Fractions& lhs, const Fractions& rhs) { return (lhs < rhs) || (lhs == rhs); }

bool operator>(const Fractions& lhs, const Fractions& rhs) { return !(lhs <= rhs); }

bool operator>=(const Fractions& lhs, const Fractions& rhs) { return !(lhs < rhs); }


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "=== ТЕСТИРОВАНИЕ КЛАССА Fractions ===" << endl;

    // Тест 1: Базовые конструкторы
    cout << "\n1. Тест конструкторов:" << endl;
    Fractions f1;                    // 0/1
    Fractions f2(5);                 // 5/1
    Fractions f3(6, 8);              // 3/4
    Fractions f4(-12, 16);           // -3/4
    Fractions f5(0, 100);            // 0/1

    cout << "f1: " << f1.str() << " = " << static_cast<double>(f1) << endl;
    cout << "f2: " << f2.str() << " = " << static_cast<double>(f2) << endl;
    cout << "f3: " << f3.str() << " = " << static_cast<double>(f3) << endl;
    cout << "f4: " << f4.str() << " = " << static_cast<double>(f4) << endl;
    cout << "f5: " << f5.str() << " = " << static_cast<double>(f5) << endl;

    // Тест 2: Автоматическое сокращение дробей
    cout << "\n2. Тест сокращения дробей:" << endl;
    Fractions f6(100, 50);           // 2/1
    Fractions f7(15, 25);            // 3/5
    Fractions f8(-9, 12);            // -3/4
    Fractions f9(0, 7);              // 0/1

    cout << "100/50 = " << f6.str() << endl;
    cout << "15/25 = " << f7.str() << endl;
    cout << "-9/12 = " << f8.str() << endl;
    cout << "0/7 = " << f9.str() << endl;

    // Тест 3: Арифметические операции
    cout << "\n3. Тест арифметических операций:" << endl;
    Fractions a(1, 2);
    Fractions b(1, 3);
    Fractions c(3, 4);

    cout << a.str() << " + " << b.str() << " = " << (a + b).str() << endl;
    cout << a.str() << " - " << b.str() << " = " << (a - b).str() << endl;
    cout << a.str() << " * " << b.str() << " = " << (a * b).str() << endl;
    cout << a.str() << " / " << b.str() << " = " << (a / b).str() << endl;

    // Тест 4: Составные присваивания
    cout << "\n4. Тест составных присваиваний:" << endl;
    Fractions x(1, 2);
    Fractions y(1, 3);

    cout << "x = " << x.str();
    x += y;
    cout << ", x += " << y.str() << " = " << x.str() << endl;

    x = Fractions(1, 2);
    x -= y;
    cout << "x -= " << y.str() << " = " << x.str() << endl;

    x = Fractions(1, 2);
    x *= y;
    cout << "x *= " << y.str() << " = " << x.str() << endl;

    x = Fractions(1, 2);
    x /= y;
    cout << "x /= " << y.str() << " = " << x.str() << endl;

    // Тест 5: Унарные операторы
    cout << "\n5. Тест унарных операторов:" << endl;
    Fractions pos(3, 4);
    Fractions neg = -pos;

    cout << "+" << pos.str() << " = " << (+pos).str() << endl;
    cout << "-" << pos.str() << " = " << neg.str() << endl;
    cout << "-" << neg.str() << " = " << (-neg).str() << endl;

    // Тест 6: Операции сравнения
    cout << "\n6. Тест сравнений:" << endl;
    Fractions p(1, 2);
    Fractions q(2, 4);  // эквивалентно 1/2
    Fractions r(3, 4);
    Fractions s(1, 3);

    cout << p.str() << " == " << q.str() << " : " << (p == q) << endl;
    cout << p.str() << " != " << r.str() << " : " << (p != r) << endl;
    cout << p.str() << " < " << r.str() << " : " << (p < r) << endl;
    cout << r.str() << " > " << s.str() << " : " << (r > s) << endl;
    cout << p.str() << " <= " << q.str() << " : " << (p <= q) << endl;
    cout << p.str() << " >= " << s.str() << " : " << (p >= s) << endl;

    // Тест 7: Свойства дробей
    cout << "\n7. Тест свойств дробей:" << endl;
    Fractions zero(0, 5);
    Fractions positive(3, 4);
    Fractions negative(-2, 3);

    cout << zero.str() << ".is_zero(): " << zero.is_zero() << endl;
    cout << positive.str() << ".is_positive(): " << positive.is_positive() << endl;
    cout << negative.str() << ".is_negative(): " << negative.is_negative() << endl;

    // Тест 8: Сложные выражения
    cout << "\n8. Тест сложных выражений:" << endl;
    Fractions result = (a + b) * c / Fractions(2, 1);
    cout << "((" << a.str() << " + " << b.str() << ") * " << c.str() << ") / 2 = " << result.str() << endl;
    cout << "В десятичном виде: " << static_cast<double>(result) << endl;

    // Тест 9: Большие числа (проверка на переполнение)
    cout << "\n9. Тест с большими числами:" << endl;
    Fractions big1(1234567, 7654321);
    Fractions big2(9876543, 1111111);

    cout << "Большая дробь 1: " << big1.str() << " ≈ " << static_cast<double>(big1) << endl;
    cout << "Большая дробь 2: " << big2.str() << " ≈ " << static_cast<double>(big2) << endl;

    Fractions big_sum = big1 + big2;
    cout << "Их сумма: " << big_sum.str() << " ≈ " << static_cast<double>(big_sum) << endl;

    // Тест 10: Цепочки операций
    cout << "\n10. Тест цепочек операций:" << endl;
    Fractions chain = Fractions(1, 2) + Fractions(1, 3) - Fractions(1, 6) * Fractions(2, 1);
    cout << "1/2 + 1/3 - 1/6 * 2 = " << chain.str() << " = " << static_cast<double>(chain) << endl;

    // Тест 11: Копирование
    cout << "\n11. Тест копирования:" << endl;
    Fractions original(3, 7);
    Fractions copy1 = original;      // конструктор копирования
    Fractions copy2(original);       // тоже конструктор копирования

    cout << "Оригинал: " << original.str() << endl;
    cout << "Копия 1: " << copy1.str() << endl;
    cout << "Копия 2: " << copy2.str() << endl;
    cout << "Оригинал == Копия: " << (original == copy1) << endl;

    // Тест 12: Деление на ноль
    cout << "\n12. Тест деления на ноль:" << endl;
    Fractions zero_frac(0, 1);
    Fractions normal(3, 4);

    Fractions div_by_zero = normal / zero_frac;
    cout << "3/4 / 0/1 = " << div_by_zero.str() << " (должен быть 0)" << endl;

    // Тест 13: Преобразование в double
    cout << "\n13. Тест преобразования в double:" << endl;
    Fractions d1(1, 3);
    Fractions d2(22, 7);  // приближение π
    Fractions d3(355, 113);  // лучшее приближение π

    cout << d1.str() << " = " << static_cast<double>(d1) << endl;
    cout << d2.str() << " = " << static_cast<double>(d2) << " (π ≈ 3.142857)" << endl;
    cout << d3.str() << " = " << static_cast<double>(d3) << " (π ≈ 3.141593)" << endl;

    cout << "\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;

    return 0;
}
