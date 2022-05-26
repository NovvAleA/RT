#pragma once
#include "class_vector.h"
#include < cmath >
#include "BMP.h"
#include <omp.h>

class figure {
protected:
	//unsigned char color[3];
	Vector_and_cos P_c;
	Vector centre;
	Vector constv_m1_0_0;
	Vector constv_1_0_0;
	float Volume;
public:
	Vector TRUaxe1, TRUaxe2, TRUaxe3, TRUcentre, VECTa0;
	Vector get_centre() {
		return centre;
	}
	void set_centre(Vector v) {
		centre = v;
	}
	Matrix J_minus_one(Vector a, Vector b, Vector c) {
		Matrix M(a, b, c);
		M = M.T();
		M = M.inverse();
		return M;
	}
	virtual float volume() = 0;
	//virtual Vector intersection(line) = 0;      
	int line_in_trihedral_angle(line l, Matrix J_inverse) {
		Vector u = J_inverse * l.get_e();
		if (u[0] >= 0 && u[1] >= 0 && u[2] >= 0) {
			return 1;
		}
		return 0;
	}
	virtual void simple_figure(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) = 0;
	virtual Vector_and_cos point_and_angle(line l, Vector lamp) = 0;
};

class sphere : public figure {
private:
	float R;
	double pi = 3.141592;
	Vector tmp, tmp1;
	Vector normal;
	Vector P;
	//float t1;
	//float t2;
	//float D_4;//  D/4
	//float a_coef;// coefficient: a_coef*t^2 + 2*b_2coef*t + c = 0
	//float b_2coef;
	Vector camera;
public:
	sphere(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) {
		TRUcentre = c;
		TRUaxe1 = a1;
		TRUaxe2 = a2;
		TRUaxe3 = a3;
		VECTa0 = a0;
	}
	sphere(Vector c, float r, float a0_) {
		centre = c;
		R = r;
		constv_m1_0_0.set(-1, 0, 0);
		constv_1_0_0.set(1, 0, 0);
		P.set(0, 0, 0);
		/*t1 = 0;
		t2 = 0;
		D_4 = 0;
		a_coef = 0;
		b_2coef = 0;*/
		camera.set(-a0_, 0, 0);
	}
	void simple_figure(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) override {
		centre = c;
		R = a1[0];
		if (R <= 0) {
			cout << "R < 0 !";
		}
		constv_m1_0_0.set(-1, 0, 0);
		constv_1_0_0.set(1, 0, 0);
		P.set(0, 0, 0);
		/*t1 = 0;
		t2 = 0;
		D_4 = 0;
		a_coef = 0;
		b_2coef = 0;*/
		camera = a0;
	}
	float dist(line l) {
		Vector temp1, temp2;
		temp1 = camera - centre;
		temp2 = l.get_e().cross(temp1);
		return temp2.module() / l.get_e().module();
	}
	float volume() override{
		return 4 * pi * pow(R,3)/ 3;
	}
	Vector intersection(line l)  {
	//	t1 = dist(l);
		if (dist(l) <= R) { 
			Vector tmp_1_0_0(1, 0, 0);
			return tmp_1_0_0;
	    }
		Vector tmp_m1_0_0(-1, 0, 0);
		return tmp_m1_0_0;
	}
	Vector point_of_intersection(line l) {
		float t1 = 0, t2 = 0, D_4 = 0, a_coef = 0, b_2coef = 0;
		tmp = camera - centre;
		a_coef = l.get_e().scalar(l.get_e());
		b_2coef = l.get_e().scalar(tmp);
		D_4 = b_2coef * b_2coef - a_coef * (tmp.scalar(tmp) + R); ;
		t1 = (-b_2coef - sqrt(D_4)) / a_coef;
		return camera + l.get_e() * t1;
	}
	float intersection_and_angle(line l, Vector lamp) {
		if (intersection(l)[0] != -1) {
			float t1 = 0, t2 = 0, D_4 = 0, a_coef = 0, b_2coef = 0;
			tmp = camera - centre;
			a_coef = l.get_e().scalar(l.get_e());
			b_2coef = l.get_e().scalar(tmp);
			D_4 = b_2coef* b_2coef - a_coef * (tmp.scalar(tmp) - R * R);
			//if (D_4 >= 0) {}else {cout << "D_4 < 0\n";}  //just insurance
			t1 = -b_2coef / a_coef;
			t1 -= sqrt(D_4) / a_coef;
			P = camera + l.get_e() * t1;
			//P = point_of_intersection(l);
			normal = P - centre;
			//lamp_direction = lamp - P
			return normal.cos_angle(lamp - P);
		}
		return 10;
	}
	Vector_and_cos point_and_angle(line l, Vector lamp) {
		Vector_and_cos Point;
		if (intersection(l)[0] != -1) {
			Vector temp_cc, temp_P, tmp_normal;
			float t1 = 0, t2 = 0, D_4 = 0, a_coef = 0, b_2coef = 0;

			temp_cc = camera - centre;
			a_coef = l.get_e().scalar(l.get_e());
			b_2coef = l.get_e().scalar(temp_cc);
			D_4 = b_2coef * b_2coef - a_coef * (temp_cc.scalar(temp_cc) - R * R);
			//if (D_4 >= 0) {}else {cout << "D_4 < 0\n";}  //just insurance
			t1 = -b_2coef / a_coef;
			t1 -= sqrt(D_4) / a_coef;
			temp_P = camera + l.get_e() * t1;
			//P = point_of_intersection(l);
			tmp_normal = temp_P - centre;
			//lamp_direction = lamp - P
			Point.P = temp_P;
			Point.cos = tmp_normal.cos_angle(lamp - temp_P);
			return Point;
		}
		return Point;
	}
};

class parallelepiped : public figure {
private:
	Vector axe1;
	Vector axe2;
	Vector axe3;
	Vector edge;
	Vector arr[3];
	int arr_i[3];
	int _0_or_1;
	float cos_a;
	Vector A, A1, B, B1, C, C1, D, D1;
	Matrix J[12];//matrixes of transion
	Matrix Ji[12];//Jinverse - vector of inverse matrix of transion
	Vector normal[12];//normal for simplexes
	Vector simplex[12][3];
	Vector camera;
	Vector P; // service vector, the meaning depends on the function
	int counter;

public:
	parallelepiped(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) {
		TRUcentre = c;
		TRUaxe1 = a1;
		TRUaxe2 = a2;
		TRUaxe3 = a3;
		VECTa0 = a0;
	}
	void simple_figure(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) override {
		constv_m1_0_0.set(-1, 0, 0);
		constv_1_0_0.set(1, 0, 0);
		counter = 0;
		centre = c;
		axe1 = a1;
		axe2 = a2;
		axe3 = a3;
		camera = a0;
		Vector tmp;  // service vector

		tmp = axe1 - centre;
		edge[0] = tmp.module();
		tmp = axe2 - centre;
		edge[1] = tmp.module();
		tmp = axe3 - centre;
		edge[2] = tmp.module();
		tmp.set(0, 0, 0);

		A = centre;   // 'center' is vertice A, not on a center of cube	
		B = A + axe1;//vertices
		D = A + axe2;
		C = D + axe1;
		A1 = A + axe3;
		B1 = B + axe3;
		C1 = C + axe3;
		D1 = D + axe3;

		simplex[0][0] = A; // triples of numbers are oriented for a vector product
		simplex[0][1] = B;
		simplex[0][2] = C;
		normal[0] = tmp - axe3;// tmp == (0,0,0)

		simplex[1][0] = C;
		simplex[1][1] = D;
		simplex[1][2] = A;
		normal[1] = normal[0];

		simplex[2][0] = B1;
		simplex[2][1] = B;
		simplex[2][2] = A;
		normal[2] = tmp - axe2;

		simplex[3][0] = A;
		simplex[3][1] = A1;
		simplex[3][2] = B1;
		normal[3] = normal[2];

		simplex[4][0] = A;
		simplex[4][1] = D;
		simplex[4][2] = D1;
		normal[4] = tmp - axe1;

		simplex[5][0] = D1;
		simplex[5][1] = A1;
		simplex[5][2] = A;
		normal[5] = normal[4];

		simplex[6][0] = C1;
		simplex[6][1] = B1;
		simplex[6][2] = A1;
		normal[6] = axe3;

		simplex[7][0] = A1;
		simplex[7][1] = D1;
		simplex[7][2] = C1;
		normal[7] = axe3;

		simplex[8][0] = C1;
		simplex[8][1] = D1;
		simplex[8][2] = D;
		normal[8] = axe2;

		simplex[9][0] = D;
		simplex[9][1] = C;
		simplex[9][2] = C1;
		normal[9] = normal[8];

		simplex[10][0] = B;
		simplex[10][1] = B1;
		simplex[10][2] = C1;
		normal[10] = axe1;

		simplex[11][0] = C1;
		simplex[11][1] = C;
		simplex[11][2] = B;
		normal[11] = normal[10];

		for (int i = 0; i < 12; i++) {
			J[i].set(simplex[i][0] - camera, simplex[i][1] - camera, simplex[i][2] - camera);
			Ji[i] = J_minus_one(simplex[i][0] - camera, simplex[i][1] - camera, simplex[i][2] - camera);
		}
	}
	float volume() override {
		return edge[0]*edge[1]*edge[2];
	}
	float intersection_and_angle(line l, Vector lamp){
		counter = 0;
       
		for (int i = 0; i < 12; i++) {
			if (Ji[i].det() != 0) {
				if (line_in_trihedral_angle(l, Ji[i])) {
					if (i == 0) {
						cout << "";
					}
					arr[counter] = l.intersection_plane(simplex[i][0], simplex[i][1], simplex[i][2]);//point of intersection line with simplex
					arr_i[counter] = i;
					counter++;
				}
			}
		}
		if (counter == 1) {
			return normal[arr_i[0]].cos_angle(lamp - arr[0]);//
		}
		if (counter == 2) {
			_0_or_1 = l.nearest_point(arr[0], arr[1]);
			cos_a = normal[arr_i[_0_or_1]].cos_angle(lamp - arr[_0_or_1]);//calculate the angle
            return cos_a;                              //between the lamp and the nearest intersection point		              	 
		}
		if (counter == 3) {
			cout << "??? three points of intersection\n";
		}
		return 10;
	}
	Vector_and_cos point_and_angle(line l, Vector lamp) {
		Vector_and_cos Point;
		int counter_p = 0;
		vector<Vector> arr_points;
		vector<int> arr_ind;
	
		for (int i = 0; i < 12; i++) {
			if (Ji[i].det() != 0) {
				if (line_in_trihedral_angle(l, Ji[i])) {
					if (i == 0) {
						cout << "";
					}
					arr_points.push_back( l.intersection_plane(simplex[i][0], simplex[i][1], simplex[i][2]));//point of intersection line with simplex
					arr_ind.push_back( i);
					counter_p++;
				}
			}
		}
		if (counter_p == 1) {
			Point.P = arr[0];
			Point.cos = normal[arr_ind[0]].cos_angle(lamp - arr_points[0]);
			return Point;//
		}
		if (counter_p == 2) {
			bool a = 0;
			a = l.nearest_point(arr_points[0], arr_points[1]);//calculate the angle between the lamp and
			Point.cos = normal[arr_ind[a]].cos_angle(lamp - arr_points[a]);// the nearest intersection point
			Point.P = arr_points[a];
			return Point;
		}
		return Point;
	}

};

class tetrahedron : public figure {
private:
	Vector axe1;
	Vector axe2;
	Vector axe3;
	Vector arr[3];
	int arr_i[3];
	int _0_or_1;// 0 or 1
	float sgn_sc;// -1 or +1
	float cos_a;
	Vector A, B, C, D;
	Matrix J[4];//matrixes of transion
	Matrix Ji[4];//Jinverse - vector of inverse matrix of transion
	Vector normal[4];//normal for simplexes
	Vector simplex[4][3];
	Vector camera;
	Matrix AXES;
	Vector P; // service vector, the meaning depends on the function
	int counter;
public:
	tetrahedron(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) {
		TRUcentre = c;
		TRUaxe1 = a1;
		TRUaxe2 = a2;
		TRUaxe3 = a3;
		VECTa0 = a0;
	}
	void simple_figure(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) override {
		constv_m1_0_0.set(-1, 0, 0);
		constv_1_0_0.set(1, 0, 0);
		counter = 0;
		centre = c;
		axe1 = a1;
		axe2 = a2;
		axe3 = a3;
		camera = a0;
		Vector tmp;  // service vector

		AXES.set(axe1, axe2, axe3);
		Volume = abs(AXES.det() / 3);

		A = centre;   // 'center' is vertice A, not on a center of cube	
		B = A + axe1;//vertices
		C = A + axe2;
		D = A + axe3;
		

		simplex[0][0] = A; // triples of numbers are oriented for a vector product
		simplex[0][1] = B;
		simplex[0][2] = C;

		tmp = axe1.cross(axe2);// tmp == (0,0,0)
		sgn_sc = tmp.scalar(axe3);
		tmp.set(0, 0, 0);

		if (sgn_sc > 0) {
			normal[0] = tmp - axe3;
		}
		if (sgn_sc < 0) {
			normal[0] = axe3;
		}
		if (sgn_sc == 0) {
			cout << "Erorr! tetrahedron in plane";
		}

		simplex[1][0] = A;
		simplex[1][1] = C;
		simplex[1][2] = D;
		normal[1] = tmp + axe3.cross(axe2)* sgn_sc;

		simplex[2][0] = A;
		simplex[2][1] = B;
		simplex[2][2] = D;
		normal[2] = tmp + axe1.cross(axe3) * sgn_sc;

		simplex[3][0] = C;
		simplex[3][1] = D;
		simplex[3][2] = B;
		normal[3] = tmp + (axe1.cross(axe2) + axe2.cross(axe3)+ axe3.cross(axe1))* sgn_sc;;

		for (int i = 0; i < 4; i++) {
			J[i].set(simplex[i][0] - camera, simplex[i][1] - camera, simplex[i][2] - camera);
			Ji[i] = J_minus_one(simplex[i][0] - camera, simplex[i][1] - camera, simplex[i][2] - camera);
		}
	}
	float volume() override {
		return Volume;
	}
	float intersection_and_angle(line l, Vector lamp) {
		counter = 0;
		for (int i = 0; i < 4; i++) {
			if (Ji[i].det() != 0) {
				if (line_in_trihedral_angle(l, Ji[i])) {
					if (i == 0) {
						cout << "";
					}
					arr[counter] = l.intersection_plane(simplex[i][0], simplex[i][1], simplex[i][2]);//point of intersection line with simplex
					arr_i[counter] = i;
					counter++;
				}
			}
		}
		if (counter == 1) {
			return normal[arr_i[0]].cos_angle(lamp - arr[0]);//
		}
		if (counter == 2) {
			_0_or_1 = l.nearest_point(arr[0], arr[1]);
			cos_a = normal[arr_i[_0_or_1]].cos_angle(lamp - arr[_0_or_1]);//calculate the angle
			return cos_a;                              //between the lamp and the nearest intersection point		              	 
		}
		if (counter == 3) {
			cout << "??? three points of intersection\n";
		}
		return 10;
	}
	Vector_and_cos point_and_angle(line l, Vector lamp) {
		Vector_and_cos Point;
		int counter_p = 0;
		vector<Vector> arr_points;
		vector<int> arr_ind;

		for (int i = 0; i < 4; i++) {
			if (Ji[i].det() != 0) {
				if (line_in_trihedral_angle(l, Ji[i])) {
					if (i == 0) {
						cout << "";
					}
					arr_points.push_back(l.intersection_plane(simplex[i][0], simplex[i][1], simplex[i][2]));//point of intersection line with simplex
					arr_ind.push_back(i);
					counter_p++;
				}
			}
		}
		if (counter_p == 1) {
			Point.P = arr[0];
			Point.cos = normal[arr_ind[0]].cos_angle(lamp - arr_points[0]);
			return Point;//
		}
		if (counter_p == 2) {
			bool a = 0;
			a = l.nearest_point(arr_points[0], arr_points[1]);//calculate the angle between the lamp and
			Point.cos = normal[arr_ind[a]].cos_angle(lamp - arr_points[a]);// the nearest intersection point
			Point.P = arr_points[a];
			return Point;
		}
		return Point;
	}
};


int nearest_from_point(vector<Vector_and_cos> arr);
int drow_figures(vector<figure*> arr, parameters& PRM);

 int drow_parall(int h_per, int w_per, float a0, float alpha, Vector lamp, Vector mode,
	Vector a1, Vector a2, Vector a3, Vector c, int color);

 int drow_tetrah(int h_per, int w_per, float a0, float alpha, Vector lamp, Vector mode,
	 Vector a1, Vector a2, Vector a3, Vector c, int color);

 int drow_sphere(int h_per, int w_per, float a0, float alpha, Vector lamp, Vector mode,
	 Vector a1, Vector a2, Vector a3, Vector c, int color);
/*
* 
		J1 = J_minus_one(A - camera, B - camera, C - camera);
		J2 = J_minus_one(D - camera, B - camera, C - camera);
		J3 = J_minus_one(A - camera, B - camera, B1 - camera);
		J4 = J_minus_one(A - camera, A1 - camera, B1 - camera);
		J5 = J_minus_one(A - camera, C - camera, C1 - camera);
		J6 = J_minus_one(A - camera, A1 - camera, C1 - camera);
		J7 = J_minus_one(A1 - camera, B1 - camera, C1 - camera);
		J8 = J_minus_one(D1 - camera, B1 - camera, C1 - camera);
		J9 = J_minus_one(C - camera, C1 - camera, D1 - camera);
		J10 = J_minus_one(C - camera, D - camera, D1 - camera);
		J11 = J_minus_one(B - camera, B1 - camera, D1 - camera);
		J12 = J_minus_one(B - camera, D - camera, D1 - camera);




		J[0] = J_minus_one(A - camera, B - camera, C - camera);
		J[1] = J_minus_one(D - camera, B - camera, C - camera);
		J[2] = J_minus_one(A - camera, B - camera, B1 - camera);
		J[3] = J_minus_one(A - camera, A1 - camera, B1 - camera);
		J[4] = J_minus_one(A - camera, C - camera, C1 - camera);
		J[5] = J_minus_one(A - camera, A1 - camera, C1 - camera);
		J[6] = J_minus_one(A1 - camera, B1 - camera, C1 - camera);
		J[7] = J_minus_one(D1 - camera, B1 - camera, C1 - camera);
		J[8] = J_minus_one(C - camera, C1 - camera, D1 - camera);
		J[9] = J_minus_one(C - camera, D - camera, D1 - camera);
		J[10] = J_minus_one(B - camera, B1 - camera, D1 - camera);
		J[11] = J_minus_one(B - camera, D - camera, D1 - camera);



		J.set(A - camera, C - camera, C1 - camera);
		J = J.T();
		J = J.inverse();

		J1 = J_minus_one(J1);
		J1.set(A - camera, B - camera, C - camera);
		J1 = J1.T();
		J1 = J1.inverse();

		G2 = Gram(D - camera, B - camera, C - camera);
		G3 = Gram(A - camera, B - camera, B1 - camera);
		G4 = Gram(A - camera, A1 - camera, B1 - camera);
		G5 = Gram(A - camera, C - camera, C1 - camera);
		G6 = Gram(A - camera, A1 - camera, C1 - camera);
		G7 = Gram(A1 - camera, B1 - camera, C1 - camera);
		G8 = Gram(D1 - camera, B1 - camera, C1 - camera);
		G9 = Gram(C - camera, C1 - camera, D1 - camera);
		G10 = Gram(C - camera, D - camera, D1 - camera);
		G11 = Gram(B - camera, B1 - camera, D1 - camera);
		G12 = Gram(B - camera, D - camera, D1 - camera);
		
		J[0] = J_minus_one(A - camera, B - camera, D - camera);
		J[1] = J_minus_one(C - camera, B - camera, D - camera);
		J[2] = J_minus_one(A - camera, B - camera, B1 - camera);
		J[3] = J_minus_one(A - camera, A1 - camera, B1 - camera);
		J[4] = J_minus_one(A - camera, D - camera, D1 - camera);
		J[5] = J_minus_one(A - camera, A1 - camera, D1 - camera);
		J[6] = J_minus_one(A1 - camera, B1 - camera, D1 - camera);
		J[7] = J_minus_one(C1 - camera, B1 - camera, D1 - camera);
		J[8] = J_minus_one(D - camera, D1 - camera, C1 - camera);
		J[9] = J_minus_one(D - camera, C - camera, C1 - camera);
		J[10] = J_minus_one(B - camera, B1 - camera, C1 - camera);
		J[11] = J_minus_one(B - camera, C - camera, C1 - camera);
		
		parallelepiped(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) {
		centre = c;
		axe1 = a1;
		axe2 = a2;
		axe3 = a3;
		camera = a0;
		Vector tmp;  // service vector
		Vector P;    // service vector
		tmp = axe1 - centre;
		edge[0] = tmp.module();
		tmp = axe2 - centre;
		edge[1] = tmp.module();
		tmp = axe3 - centre;
		edge[2] = tmp.module();

	    A = centre;   //vertices
		A1 = A + axe3;
		B = A + axe1;
		B1 = B + axe3;
		C = A + axe2;
		C1 = C + axe3;
		D = C + axe1;
	    D1 = D + axe3;

		J[0] = J_minus_one(A - camera, B - camera, C - camera);
		simplex[0][0] = A;
		simplex[0][1] = B;
		simplex[0][2] = C;
		tmp = C - A;
		normal[0] = tmp.cross(B - A);
		J[1] = J_minus_one(D - camera, B - camera, C - camera);
		simplex[1][0] = D;
		simplex[1][1] = B;
		simplex[1][2] = C;
		normal[1] = normal[0];
		J[2] = J_minus_one(A - camera, B - camera, B1 - camera);
		simplex[2][0] = A;
		simplex[2][1] = B;
		simplex[2][2] = B1;
		tmp = B - A;
		normal[2] = tmp.cross(B1 - B);
		J[3] = J_minus_one(A - camera, A1 - camera, B1 - camera);
		simplex[3][0] = A;
		simplex[3][1] = A1;
		simplex[3][2] = B1;
		normal[3] = normal[2];
		J[4] = J_minus_one(A - camera, C - camera, C1 - camera);
		simplex[4][0] = A;
		simplex[4][1] = C;
		simplex[4][2] = C1;
		tmp = A - C;
		normal[4] = tmp.cross(C1 - C);
		J[5] = J_minus_one(A - camera, A1 - camera, C1 - camera);
		simplex[5][0] = A;
		simplex[5][1] = A1;
		simplex[5][2] = C1;
		normal[5] = normal[4];
		J[6] = J_minus_one(A1 - camera, B1 - camera, C1 - camera);
		simplex[6][0] = A1;
		simplex[6][1] = B1;
		simplex[6][2] = C1;
		tmp = C1 - A1;
		normal[6] = tmp.cross(B1 - A1);
		J[7] = J_minus_one(D1 - camera, B1 - camera, C1 - camera);
		simplex[7][0] = D1;
		simplex[7][1] = B1;
		simplex[7][2] = C1;
		normal[7] = normal[6];
		J[8] = J_minus_one(C - camera, C1 - camera, D1 - camera);
		simplex[8][0] = C;
		simplex[8][1] = C1;
		simplex[8][2] = D1;
		tmp = D1 - C1;
		normal[8] = tmp.cross(C1 - C);
		J[9] = J_minus_one(C - camera, D - camera, D1 - camera);
		simplex[9][0] = C;
		simplex[9][1] = D;
		simplex[9][2] = D1;
		normal[9] = normal[8];
		J[10] = J_minus_one(B - camera, B1 - camera, D1 - camera);
		simplex[10][0] = B;
		simplex[10][1] = B1;
		simplex[10][2] = D1;
		tmp = B1 - B;
		normal[10] = tmp.cross(D1 - B1);
		J[11] = J_minus_one(B - camera, D - camera, D1 - camera);
		simplex[11][0] = B;
		simplex[11][1] = D;
		simplex[11][2] = D1;
		normal[11] = normal[10];
		
		*/