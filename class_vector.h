#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


using namespace std;

class Vector {
private:
	float x1;
	float x2;
	float x3;
public:
	Vector() {
		x1 = 0;
		x2 = 0;
		x3 = 0;
	}
	Vector(float x, float y, float z) {
		x1 = x;
		x2 = y;
		x3 = z;
	}
	Vector(const Vector& other) {
		x1 = other.x1;
		x2 = other.x2;
		x3 = other.x3;
	}
	Vector& operator=(const Vector& other) {
		if (this == &other) return *this;
		x1 = other.x1;
		x2 = other.x2;
		x3 = other.x3;
		return *this;
	}
	float& operator[](const size_t i) {
		if (i == 0) return x1;
		else if (i == 1) return x2;
		else if (i == 2) return x3;
		else { printf("i >= 3! in []");}
	}
	const float& operator[](const size_t i) const {
		if (i == 0) return x1;
		else if (i == 1) return x2;
		else if (i == 2) return x3;
		else { printf("i >= 3! in []"); }
		return x1;
	}
	Vector operator-(const Vector& other) {
		Vector tmp(x1 - other[0], x2 - other[1], x3 - other[2]);
		return tmp;
	}
	Vector operator+(const Vector& other) {
		Vector tmp(x1+ other[0], x2 + other[1], x3 + other[2]);
		return tmp;
	}
	Vector operator*(float k) {
		Vector tmp(x1 * k, x2 * k, x3 * k);
		return tmp;
	}

	int operator==(Vector& a) {
		if (x1 == a[0] && x2 == a[1] && x3 == a[2]) {
			return 1;
		}
		return 0;
	}
	int operator!=(Vector& a) {
		if (x1 == a[0] && x2 == a[1] && x3 == a[2]) {
			return 0;
		}
		return 1;
	}
	void set(float a, float b, float c) {
		x1 = a;
		x2 = b;
		x3 = c;
	}
	Vector cross( const Vector& b) {
		return Vector(x2 * b[2] - x3 * b[1], x3 * b[0] - x1 * b[2], x1 * b[1] - x2 * b[0]);
	}
	float scalar( const Vector& b) {
		return x1 * b[0] + x2 * b[1] + x3 * b[2];
	}
	/*float scalarg(const Vector& b, Matrix& G) {
		return scalarG(*this,b,G);
	}*/
	void print(){
		cout << "(" << x1 << "," << x2 << "," << x3 << ")";
	}
	float module() {
		return sqrt(x1 * x1 + x2 * x2 + x3 * x3);
	}
	Vector unit_e() {
		Vector tmp(x1/this->module(), x2 / this->module(), x3 / this->module());
		return tmp;
	}
	void set_i(int i, float a) {
		if (i == 0) { x1 = a; }
		else if (i == 1) x2 = a;
		else if (i == 2) x3 = a;
		else { printf("i >= 3! in []"); }
	}
	float cos_angle(Vector u) {
		return (*this).scalar(u) / ((*this).module() * u.module());
	}

};

class line {
private:
	Vector r0;// r(t) = r0 + e*t
	Vector e;
	Vector tmp;
public:
	line() {
		r0.set(0,0,0);
		e.set(1, 0, 0);
	}
	line(Vector point, Vector direct) {
		r0 = point;
		e = direct;
	}
	line(float x, float y, float z, float a, float b, float c) {
		r0.set(x,y,z);
		e.set(a,b,c);
	}
	void set_p(float a, float b, float c) {
		r0.set(a, b, c);
	}
	void set_e(float a, float b, float c){
		e.set(a, b, c);
	}


	Vector get_p() {return r0;}
	Vector get_e() {return e;}
	void plus_e(Vector d) {
		e = e + d;
	}
	Vector intersection_plane( Vector P1, Vector P2, Vector P3) {
		float t, A, B, C, D, denominator;
		t = 0;
		Vector P;
		A = P1[1] * P2[2] + P2[1] * P3[2] + P3[1] * P1[2] - P1[1] * P3[2] - P2[1] * P1[2] - P3[1] * P2[2];
		B = P1[0] * P3[2] + P2[0] * P1[2] + P3[0] * P2[2] - P1[0] * P2[2] - P2[0] * P3[2] - P3[0] * P1[2] ;
		C = P1[0] * P2[1] + P2[0] * P3[1] + P3[0] * P1[1] - P1[0] * P3[1] - P2[0] * P1[1] - P3[0] * P2[1];
		D = P1[0] * P2[2] * P3[1] + P1[2] * P2[1] * P3[0] + P1[1] * P2[0] * P3[2]
		  - P1[0] * P2[1] * P3[2] - P1[2] * P2[0] * P3[1] - P1[1] * P2[2] * P3[0];

		denominator = e[0] * A + e[1] * B + e[2] *C;
		if (denominator != 0) {
			t = -(r0[0] * A + D) / denominator;// camera is on the axe 'x', numerator is shorter
		}
		else {
			cout << "denominator == 0";
		}
		P = r0 + e * t;
		return P;
	}
	int nearest_point(Vector a, Vector b) {
		if (a.scalar(a) - 2 * a.scalar(r0) <= b.scalar(b) - 2 * b.scalar(r0)) {
			return 0;
		}
		return 1;
	}

};

class Matrix {
protected:
	Vector s1;
	Vector s2;
	Vector s3;
	Vector tmp_o;
public:
	Matrix() {}
	Matrix(Vector a, Vector b, Vector c) {
		s1 = a;
		s2 = b;
		s3 = c;
	}
	Matrix& operator=(Matrix other) {
		if (this == &other) return *this;
		s1 = other[0];
		s2 = other[1];
		s3 = other[2];
		return *this;
	}
	Vector& operator[](const size_t i) {
		if (i == 0) return s1;
		else if (i == 1) return s2;
		else if (i == 2) return s3;
		else { printf("i >= 3! in []");}
		return s1;
	}
	Matrix T() {
		Matrix tmp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tmp[i][j] = (*this)[j][i];
			}
		}
		return tmp;
	}
	void set(Vector a, Vector b, Vector c) {
		s1 = a;
		s2 = b;
		s3 = c;
	}
	void set_i_j(int i, int j, float a) {
		if (i == 0) {
			s1.set_i(j, a);
		}
		if (i == 1) {
			s2.set_i(j, a);
		}
		if (i == 2) {
			s3.set_i(j, a);
		}
	}
	Matrix& operator*( Matrix& B) {
		Matrix tmp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					tmp[i][j] += (*this)[i][k] * B[k][j];
				}
			}
		}
		return tmp;
	}
	Matrix& operator*(float& a) {
		Matrix tmp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {	
				tmp[i][j] = (*this)[i][j] * a;
			}
		}
		return tmp;
	}
	/*Vector& operator*(Vector& v) {
	    tmp_o.set(s1.scalar(v), s2.scalar(v), s3.scalar(v));
		return tmp_o;
	}*/
	Vector operator*( Vector v) {
		Vector tmp(s1.scalar(v), s2.scalar(v), s3.scalar(v));
		return tmp;
	}
	Matrix inverse() {
		Matrix tmp;
		float det = this->det();
		if (det == 0) {
		//	cout << "Erorr det == 0 in inverse";
			return tmp;//return null matrix
		}
		
		Matrix A = *this;
		tmp[0][0] = A[1][1] * A[2][2] - A[2][1] * A[1][2];
		tmp[0][1] = A[2][1] * A[0][2] - A[0][1] * A[2][2];
		tmp[0][2] = A[0][1] * A[1][2] - A[1][1] * A[0][2];
		tmp[1][0] = A[2][0] * A[1][2] - A[1][0] * A[2][2];
		tmp[1][1] = A[0][0] * A[2][2] - A[2][0] * A[0][2];
		tmp[1][2] = A[1][0] * A[0][2] - A[0][0] * A[1][2];
		tmp[2][0] = A[1][0] * A[2][1] - A[2][0] * A[1][1];
		tmp[2][1] = A[2][0] * A[0][1] - A[0][0] * A[2][1];
		tmp[2][2] = A[0][0] * A[1][1] - A[0][1] * A[1][0];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tmp[i][j] = tmp[i][j]/det;
			}
		}
		return tmp;
	}
	float det() {
		return s1[0] * s2[1] * s3[2] + s2[0] * s1[2] * s3[1] + s2[2] * s1[1] * s3[0] -
			s1[2] * s2[1] * s3[0] - s1[0] * s2[2] * s3[1] - s1[1] * s2[0] * s3[2];
	}
};

class Rotation_Matrix : public Matrix {
public:
	Rotation_Matrix(){}
	Rotation_Matrix(float alpha, int axe) {
		if (axe == 3) {
			s1.set(cos(alpha), sin(alpha), 0);
			s2.set(-sin(alpha), cos(alpha), 0);
			s3.set(0, 0, 1);
		}
		else if (axe == 2) {
			s1.set(cos(alpha), 0, sin(alpha));
			s2.set(0, 1, 0);
			s3.set(-sin(alpha), 0, cos(alpha));
		}
		else if (axe == 1) {
			s1.set(1, 0, 0);
			s2.set(0,cos(alpha), sin(alpha));
			s3.set(0,-sin(alpha), cos(alpha));
		}
		else {
			cout << "error in Rotation_Matrix: axe = " << axe << endl;
		}
	}

//	using Matrix::operator=;
};

class Swap_Matrix : public Matrix {
public:
	Swap_Matrix() {}
	Swap_Matrix(int axe1, int axe2) {
		if (axe1 >0 && axe1 < 4 && axe2 > 0 && axe2 < 4 && axe1 != axe2) {
			this->set_i_j(axe1-1, axe2-1, 1);
			this->set_i_j(axe2-1, axe1-1, 1);
			this->set_i_j(5 - axe2 - axe1, 5 - axe2 - axe1, 1);// axe1 + axe2 + axe3 = const = 6
		}
		else {
			cout << "error in Swap_Matrix " << endl;
		}
	}

	//	using Matrix::operator=;
};

class parameters {
public:
	Vector camera, normal, up, lamp;
	float a0 ,alpha,limit ;
	int width , height;
	parameters(){
		a0 = 0;
		alpha = 0;
		limit = 0;
		width = 0;
		height = 0;
	}
};

class Vector_and_cos {
public:
	Vector P;
	float cos;
	Vector_and_cos() {
		cos = 10;
	}
	Vector_and_cos(const Vector_and_cos& other) {
		P = other.P;
		cos = other.cos;
	}
	Vector_and_cos& operator=(const Vector_and_cos& other) {
		if (this == &other) return *this;
		P = other.P;
		cos = other.cos;
		return *this;
	}
};

//Vector operator*(Matrix& A, const Vector& v) {
//	Vector tmp(A[0].scalar(v), A[1].scalar(v), A[2].scalar(v));
//	return tmp;
//}
//Matrix Gram(Vector e1, Vector e2, Vector e3) {
//	Matrix G(e1, e2, e3);
//	Matrix M = G.T();
//	G = G * M;
//	return G;
//}
