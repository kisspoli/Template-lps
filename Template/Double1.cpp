#include "Double1.h"
#include <sstream>

int my_pow(int a, unsigned int p) { //������� ���������� � �������
	int result = 1;
	while (p) {
		result *= a;
		p--;
	}
	return result;
}

unsigned int digits_count(int number) { //������� �������� ���������� ����
	if (number == 0)
		return 1;
	else {
		unsigned int count = 0;
		while (number > 0) {
			number /= 10;
			count += 1;
		}
		return count;
	}
}

Double1::Double1() //����������� �� ��������� 
{
	integer = 0;
	fractional = 0;
	zeros_count = 0;
	minus_sign = false;
}

//����������� � �����������
Double1::Double1(unsigned int _integer, unsigned int _fractional, unsigned int _zeros_count, bool _minus_sign) {
	this->integer = _integer;
	this->fractional = _fractional;
	this->zeros_count = _zeros_count;
	this->minus_sign = _minus_sign;
	this->strip_zeros();
}


unsigned int Double1::frac_digits_count() const //���������� ���� � ������� �����
{
	return digits_count(fractional) + zeros_count;
}

Double1 Double1::abs() const { //������� ������
	Double1 result = *this;
	result.minus_sign = false;
	return result;
}

void Double1::strip_zeros() { //������� �������� ������ ����� � ����� (������ ���������� � ���������� ����)
	if (this->fractional == 0) {
		zeros_count = 0;
	}
	else {
		while (this->fractional % 10 == 0)
			this->fractional /= 10;
	}
	if (this->integer == 0 && this->fractional == 0)
		this->minus_sign = false;
}

void Double1::read(std::string input) { //������� ������ ����� �� ������
	if (input[0] == '-') {
		minus_sign = true;
		input.erase(0, 1); //������� �������� �������� (��������� ������, ���������� ��������� ��������)
	}
	else
		minus_sign = false;
	if (input.find('.') != std::string::npos) {
		std::string token;
		std::istringstream ss(input);
		std::getline(ss, token, '.');
		integer = std::stoul(token); //����������� ������������������ �������� � ������� ����� ��� �����.
		std::getline(ss, token);
		fractional = std::stoul(token);
		this->strip_zeros();
		zeros_count = 0;
		if (fractional > 0)
			for (int i = 0; i < token.length() && token[i] == '0'; i++)
				zeros_count++;
	}
	else {
		integer = stoul(input);
		fractional = 0;
		zeros_count = 0;
	}
	if (integer == 0 && fractional == 0) {
		minus_sign = false;
	}
}

void Double1::read() //������� ������ � �������
{
	std::string input;
	std::cin >> input;
	read(input);
}

void Double1::read_f(std::ifstream& file) //������� ������ �� �����
{
	std::string input;
	file >> input;
	read(input);
}

void Double1::display() //������� ������ �� �������
{
	std::cout << to_string();
}

void Double1::display_f(std::string& file_name) //������� ������ � ����
{
	std::ofstream file(file_name);
	file << to_string();
}

std::string Double1::to_string() const //������� �������������� � ���������� ����
{	
	std::string value = "";
	if (this->minus_sign)
		value += '-';
	value += std::to_string(integer);
	if (fractional > 0) {
		value += '.';
		for (unsigned int i = 0; i < zeros_count; i++)
			value += '0';
		value += std::to_string(fractional);
	}
	return value;
}

Double1 Double1::operator+(const Double1& val) //���������� +
{
	Double1 result, tmp_val = val;
	if (this->minus_sign && !tmp_val.minus_sign) {
		return tmp_val - this->abs();
	}
	else if (!this->minus_sign && tmp_val.minus_sign) {
		return *this - tmp_val.abs();
	}
	else if (this->minus_sign && tmp_val.minus_sign) {
		result = this->abs() + tmp_val.abs();
		result.minus_sign = true;
		return result;
	}
	else {
		result.integer = this->integer + tmp_val.integer;
		if (this->fractional > 0 && tmp_val.fractional > 0)
			result.zeros_count = std::min(this->zeros_count, tmp_val.zeros_count);
		else
			result.zeros_count = std::max(this->zeros_count, tmp_val.zeros_count);
		int digits_diff = this->frac_digits_count() - tmp_val.frac_digits_count();
		if (digits_diff > 0) {
			tmp_val.fractional *= my_pow(10, digits_diff);
		}
		else {
			this->fractional *= my_pow(10, -1 * digits_diff);
		}
		result.fractional = this->fractional + tmp_val.fractional;
		if (digits_count(result.fractional) > digits_count(this->fractional) && digits_count(result.fractional) > digits_count(tmp_val.fractional)) {
			if (this->zeros_count == 0) {
				result.integer += 1;
				result.fractional %= my_pow(10, result.frac_digits_count()-1);
			}
			else
				result.zeros_count -= 1;
		}
		this->strip_zeros();
		result.strip_zeros();
		return result;
	}
}

Double1 Double1::operator-(const Double1& val) //���������� -
{
	Double1 result, tmp_val = val;
	if (*this < tmp_val) {
		result = tmp_val - *this;
		result.minus_sign = true;
		return result;
	}
	else if (!this->minus_sign && tmp_val.minus_sign) {
		result = *this + tmp_val.abs();
		return result;
	}
	else if (this->minus_sign && tmp_val.minus_sign) {
		result = tmp_val.abs() - this->abs();
		return result;
	}
	else {
		result.integer = this->integer - tmp_val.integer;
		if (this->fractional > 0 && tmp_val.fractional > 0)
			result.zeros_count = std::min(this->zeros_count, tmp_val.zeros_count);
		else
			result.zeros_count = std::max(this->zeros_count, tmp_val.zeros_count);
		int digits_diff = this->frac_digits_count() - tmp_val.frac_digits_count();
		if (digits_diff > 0) {
			tmp_val.fractional *= my_pow(10, digits_diff);
		}
		else {
			this->fractional *= my_pow(10, -1 * digits_diff);
		}
		if (this->fractional >= tmp_val.fractional) {
			result.fractional = this->fractional - tmp_val.fractional;
			if (digits_count(result.fractional) < digits_count(this->fractional) || digits_count(result.fractional) < digits_count(tmp_val.fractional)) {
				result.zeros_count += digits_count(this->fractional) - digits_count(result.fractional);
			}
		}
		else {
			result.integer -= 1;
			result.fractional = this->fractional + my_pow(10, tmp_val.frac_digits_count()) - tmp_val.fractional;
			result.zeros_count = 0;
		}
		this->strip_zeros();
		result.strip_zeros();
		return result;
	}
}

Double1 Double1::operator*(const Double1& val) //���������� *
{
	Double1 result, tmp_val = val;
	if (this->minus_sign && tmp_val.minus_sign) {
		return this->abs() * tmp_val.abs();
	}
	else if (!this->minus_sign && tmp_val.minus_sign) {
		result = *this * tmp_val.abs();
		result.minus_sign = true;
		return result;
	}
	else if (this->minus_sign && !tmp_val.minus_sign) {
		result = this->abs() * tmp_val;
		result.minus_sign = true;
		return result;
	}
	else {
		int frac_digits_diff = this->frac_digits_count() - tmp_val.frac_digits_count();
		unsigned int pow_result;
		if (frac_digits_diff > 0) {
			pow_result = my_pow(10, frac_digits_diff);
			tmp_val.fractional *= pow_result;
		}
		else {
			pow_result = my_pow(10, -1 * frac_digits_diff);
			this->fractional *= pow_result;
		}

		// ����������� ��� (a+b) * (c+d), ������������ � a*c+a*d+b*c+b*d, ��� a � c - ����� �����, b � d - �������
		// (3+0.99) * -(3+0.99) = 9 + 2.97 + 2.97 + 0.9801 = -15.9201

		// ��� ������� a*c
		Double1 first_part;
		first_part.integer = this->integer * tmp_val.integer;

		// ��� ������� b*d
		Double1 second_part;
		second_part.fractional = this->fractional * tmp_val.fractional;
		second_part.zeros_count = this->zeros_count + tmp_val.zeros_count;
		if (second_part.fractional < 10 * pow_result)
			second_part.zeros_count += 1;
		second_part.strip_zeros();

		// ��� ������� a*d
		Double1 third_part;
		this->strip_zeros();
		tmp_val.strip_zeros();
		third_part.fractional = (this->integer * tmp_val.fractional) % (my_pow(10, tmp_val.frac_digits_count()));
		third_part.strip_zeros();
		if (digits_count(this->integer * tmp_val.fractional) > tmp_val.frac_digits_count()) {
			third_part.integer = (this->integer * tmp_val.fractional) / (my_pow(10, tmp_val.frac_digits_count()));
			third_part.zeros_count = digits_count(this->integer * tmp_val.fractional) - digits_count(third_part.integer) - digits_count(third_part.fractional);
		}
		else {
			third_part.zeros_count = tmp_val.zeros_count - (digits_count(this->integer * tmp_val.fractional) - digits_count(tmp_val.fractional));
		}

		// ��� ������� b*c
		Double1 fourth_part;
		this->strip_zeros();
		tmp_val.strip_zeros();
		fourth_part.fractional = (tmp_val.integer * this->fractional) % (my_pow(10, this->frac_digits_count()));
		fourth_part.strip_zeros();
		if (digits_count(tmp_val.integer * this->fractional) > tmp_val.frac_digits_count()) {
			fourth_part.integer = (tmp_val.integer * this->fractional) / (my_pow(10, this->frac_digits_count()));
			third_part.zeros_count = digits_count(tmp_val.integer * this->fractional) - digits_count(fourth_part.integer) - digits_count(fourth_part.fractional);
		}
		else {
			fourth_part.zeros_count = this->zeros_count - (digits_count(tmp_val.integer * this->fractional) - digits_count(this->fractional));
		}

		result = first_part;
		result += second_part;
		result += third_part;
		result += fourth_part;
		this->strip_zeros();
		result.strip_zeros();
		return result;
	}
}

void Double1::operator+=(const Double1& val) { //���������� +=
	*this = *this + val;
}

void Double1::operator-=(const Double1& val) { //���������� -=
	*this = *this - val;
}

void Double1::operator*=(const Double1& val) {  //���������� *=
	*this = *this * val;
}

bool Double1::operator<(const Double1& val) //���������� <
{
	bool both_minus = false; 
	if (this->minus_sign && val.minus_sign)
		both_minus = true;
	if (*this == val)
		return false;
	else if (this->minus_sign && !val.minus_sign) //������ �������������, ������ ������������� 
		return true;
	else if (!this->minus_sign && val.minus_sign) //������ �������������, ������ �������������
		return false;
	//���������� ����� �����
	else if (this->integer < val.integer)
		return true ^ both_minus;
	//���������� 1, ���� ��� ������������� � ������ ������ ������� � 0, ���� ��� ������������� � ������ ������ �������
	else if (this->integer > val.integer)
		return false ^ both_minus;
	//���������� 0, ���� ��� ������������� � ������ ������ ������� � 1, ���� ��� ������������� � ������ ������ �������
	else if (this->fractional == 0 && val.fractional > 0) // ��������� ������� ����� �� ����
		return true ^ both_minus;
	//���������� 1, ���� ��� �������������, ������ ����� 0 � ������ ������ 0 � 0, ���� ��� �������������, ������ ����� 0 � ������ ������ 0
	else if (this->fractional > 0 && val.fractional == 0)
		return false ^ both_minus;
	//���������� 0, ���� ��� �������������, ������ ������ 0 � ������ ����� 0 � 1, ���� ��� �������������, ������ ������ 0 � ������ ����� 0
	else if (this->zeros_count > val.zeros_count)// ���������� ���������� �����
		return true ^ both_minus;
	//���������� 1, ���� ��� ������������� � � ������� ���������� ����� ������, ��� � ������� � 0, ���� ��� ������������� �
	// � ������� ���������� ����� ������, ��� � �������
	else if (this->zeros_count < val.zeros_count)
		return false ^ both_minus;
	//���������� 0, ���� ��� ������������� � � ������� ���������� ����� ������, ��� � ������� � 1, ���� ��� ������������� �
	// � ������� ���������� ����� ������, ��� � �������
	else { //���������� ������� �����
		int frac_digits_diff = this->frac_digits_count() - val.frac_digits_count();
		unsigned int pow_result;
		if (frac_digits_diff > 0) {
			pow_result = my_pow(10, frac_digits_diff);
			return (this->fractional < (val.fractional* pow_result)) ^ both_minus;
		}
		else {
			pow_result = my_pow(10, -1 * frac_digits_diff);
			return ((this->fractional * pow_result) < val.fractional) ^ both_minus;
		}
	}
	//���������� 1, ���� ��� ������������� � � ������� ������� ����� ������, ��� � ������� 
	//���������� 0, ���� ��� ������������� � � ������� ������� ����� ������, ��� � ������� 
	//���������� 0, ���� ��� ������������� � � ������� ������� ����� ������, ��� � ������� 
	//���������� 1, ���� ��� ������������� � � ������� ������� ����� ������, ��� � ������� 
}

bool Double1::operator<=(const Double1& val) //���������� <=
{
	return (*this < val) || (*this == val);
}

bool Double1::operator>(const Double1& val) //���������� >
{
	return !(*this < val) && !(*this == val);
}

bool Double1::operator>=(const Double1& val) //���������� >=
{
	return (*this > val) || (*this == val);
}

bool Double1::operator==(const Double1& val) //���������� ==
{
	return (this->integer == val.integer) && (this->fractional == val.fractional) &&
		(this->zeros_count == val.zeros_count) && (this->minus_sign == val.minus_sign);
}

bool Double1::operator!=(const Double1& val) //���������� !=
{
	return !(*this == val);
}

std::ostream& operator<<(std::ostream& out, const Double1& double1)
{
	out << double1.to_string();
	return out;
}

std::istream& operator>>(std::istream& in, Double1& double1)
{
	std::string input;
	in >> input;
	double1.read(input);
	return in;
}
