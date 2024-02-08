#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Double1 {
	unsigned int integer; //целая часть
	unsigned int fractional; //дробная часть
	unsigned int zeros_count; //количество нулей
	bool minus_sign; // знак (есть минус или нет)
	void strip_zeros(); //удаление лишних нулей в конце
	void read(std::string input); 
public:
	Double1();
	Double1(unsigned int integer, unsigned int fractional, unsigned int zeros_count, bool minus_sign);
	//~Double1() {};
	unsigned int frac_digits_count() const;
	Double1 abs() const;
	void read();
	void read_f(std::ifstream& file);
	void display();
	void display_f(std::string& file_name);
	std::string to_string() const;
	Double1 operator+(const Double1& val);
	Double1 operator-(const Double1& val);
	Double1 operator*(const Double1& val);
	void operator+=(const Double1& val);
	void operator-=(const Double1& val);
	void operator*=(const Double1& val);
	bool operator<(const Double1& val);
	bool operator>(const Double1& val);
	bool operator<=(const Double1& val);
	bool operator>=(const Double1& val);
	bool operator==(const Double1& val);
	bool operator!=(const Double1& val);
	friend std::ostream& operator<<(std::ostream& out, const Double1& double1); //новое
	friend std::istream& operator>>(std::istream& in, Double1& double1); //новое
};