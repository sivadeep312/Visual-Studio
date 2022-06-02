#include<iostream>
#include <opencv2/opencv.hpp>
#include<vector>



using namespace std;
using namespace cv;

int main() {

	vector<Point> sam = { Point(-8,-5),Point(-8,-5),Point(-6,-3),Point(-6,-3),Point(-2,1),Point(-4,-1),Point(-8,-5) };///, Point(5, 3),Point(3, 1)
	vector<Point>dele = sam;
	vector<int>D;
	for (int m = 0; m < sam.size()-1; m++) {
		int l = 0;
		for (int n = m+1; n < sam.size(); n++) {
			if (sam[m] == sam[n]) {
				//cout << n << endl;
				for (int d = 0; d < D.size(); d++) {
					if (n == D[d]) {
						l++;
					}
				}
				if(l==0){
					D.push_back(n);
					//cout << n<<endl;
				}
				
				
			}
		}

	}

	sort(D.begin(), D.end());
	D.erase(unique(D.begin(), D.end()), D.end());
	reverse(D.begin(), D.end());
	for (int m = 0; m < D.size(); m++) {
		cout << D[m] << endl;
		dele.erase(dele.begin() + (D[m] ));
		//dele.erase(dele.begin() + (D[m]-1));
	}

	for (int m = 0; m < dele.size(); m++) {
		cout << dele[m]<<"";
	}


	
	return 0;

}