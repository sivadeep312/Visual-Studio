#include<iostream>
#include <opencv2/opencv.hpp>
#include<vector>
//#include <algorithm>



using namespace std;
using namespace cv;

int main() {
	vector<Point> crd = { Point(-4,-1),Point(-5,-2),Point(1,0),Point(1,2),Point(1,-2),Point(-6,-3),Point(-7,-4),Point(-6,1),Point(-2,3),Point(0,2) , Point(2, 1),Point(3, -3),Point(4, -5),Point(2, -4) };///, Point(5, 3),Point(3, 1)
	vector<Point> dele;
	vector<Point>lin;
	vector<Point>sam;
	vector<int>Line_Pos;
	vector<int>length;



	

	for (int i = 0; i <= crd.size()-3; i++) {
		int t = 0;
		int u = 0;
		//cout << endl;
			Point A = crd[i] - crd[i + 1];
			double X = A.x;
			double Y = A.y;
			double ang;
			if ((X != 0) && (Y != 0)) {
				ang = Y / X;
			}
			else { ang = 90; }
		
		for (int j = i + 2;j<crd.size();j++){
			Point B = crd[i] - crd[j];
			double X1 = B.x;
			double Y1 = B.y;
			double ang1;
			if ((X1 != 0) && (Y1 != 0)) {
				ang1 = Y1 / X1;
			}
			else {
				ang1 = 90;
			}
			if (ang1 == ang) {
				t++;
				Line_Pos.push_back(j);
			}
			else {
				u++;
			}
		}
		if (t != 0) {
			sam.push_back(crd[i]);
			sam.push_back(crd[i + 1]);
			for (int v = 0; v < Line_Pos.size(); v++) {
				sam.push_back(crd[Line_Pos[v]]);

			}
		}
	}
	dele = sam;
	
	vector<int>D;
	for (int m = 0; m < sam.size() - 1; m++) {
		int l = 0;
		for (int n = m + 1; n < sam.size(); n++) {
			if (sam[m] == sam[n]) {
				//cout << n << endl;
				for (int d = 0; d < D.size(); d++) {
					if (n == D[d]) {
						l++;
					}
				}
				if (l == 0) {
					D.push_back(n);
				}


			}
		}

	}

	sort(D.begin(), D.end());
	D.erase(unique(D.begin(), D.end()), D.end());
	reverse(D.begin(), D.end());
	for (int m = 0; m < D.size(); m++) {
		//cout << D[m] << endl;
		dele.erase(dele.begin() + (D[m]));
	}


	cout << "LINE POINTS : ";
	for (int m = 0; m < dele.size(); m++) {
		cout << dele[m] << "";
	}



	for (int p = 0; p < dele.size()-2; p++) {
		int L;
		Point A1 = dele[p] - dele[p + 1];
		int len1 = sqrt((A1.x * A1.x) + (A1.y * A1.y));
		double X2 = A1.x;
		double Y2 = A1.y;
		double ang3;
		if ((X2 != 0) && (Y2 != 0)) {
			ang3 = Y2 / X2;
		}
		else {
			ang3 = 90; 
		}
		Point B = dele[p] - dele[p + 2];
		int len2 = sqrt((B.x * B.x) + (B.y * B.y));
		double X1 = B.x;
		double Y1 = B.y;
		double ang4;
		if ((X1 != 0) && (Y1 != 0)) {
			ang4 = Y1 / X1;
		}
		else {
			ang4 = 90;
		}
		if (ang3 == ang4) {
			cout << endl;
			cout << "Distance b/w " << dele[p] << " & " << dele[p + 1] << " is " << len1<<endl;
			cout << "Distance b/w " << dele[p] << " & " << dele[p + 2] << " is " << len2<<endl;
			L = len1 + len2;
			length.push_back(L);
		}
		//else { p = p + 2; }
	}
	/*for (int p = 0; p < dele.size()-2; p++) {;
			Point A =  dele[i] -  dele[i + 1];
			double X = A.x;
			double Y = A.y;
			double ang;
			if ((X != 0) && (Y != 0)) {
				ang = Y / X;
			}
			else { ang = 90; }
		
		for (int q = p + 2;q<crd.size();q++){
			Point B = crd[p] - crd[q];
			double X1 = B.x;
			double Y1 = B.y;
			double ang1;
			if ((X1 != 0) && (Y1 != 0)) {
				ang1 = Y1 / X1;
			}
			else {
				ang1 = 90;
			}
			if (ang1 == ang) {
				L1+L2///Mag
				Line_Pos.push_back(j);
			}
			else {
			}
		}*/

	cout << endl << "Lenghts : " <<endl;
	for (size_t e = 0; e < length.size(); e++) {
		cout << length[e] << ",";
	}

return 0;

}
