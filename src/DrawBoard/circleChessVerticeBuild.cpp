
#include <iostream>
using namespace std;
const double pi = 3.1415926;
int chessVerticeBuild();
int chessVerticeBuild()
{
	int n = 18;
	double de = (360 / n)* pi/180;
	for (double i = 0; i < n; ++i) {
		if (i == n - 1) {
			cout << 0.5*cos(de*i) << ", " << 0.5*sin(de*i) << "," << " -0.15, " << cos(de*i) << ", " << sin(de*i) << "," << endl;
			i = -1;
			cout << 0.5*cos(de*(i + 1)) << ", " << 0.5*sin(de*(i + 1)) << "," << " -0.15 " << cos(de*(i + 1)) << ", " << sin(de*(i + 1)) << "," << endl;
			cout << "0.0, 0.0, -0.15, 0.0, 0.0," << endl;
			break;
		}
		cout << 0.5*cos(de*i) << ", " << 0.5*sin(de*i) << "," << " -0.15, "<< cos(de*i) << ", " <<sin(de*i) << ","<<endl;
		cout << 0.5*cos(de*(i+1)) << ", " << 0.5*sin(de*(i+1)) << "," << " -0.15, "<< cos(de*(i+1)) << ", " <<sin(de*(i+1)) << ","<<endl;
		cout << "0.0, 0.0, -0.15, 0.0, 0.0," << endl;
	}
	return 0;
}
//
//int main() {
//	return chessVerticeBuild();
//}