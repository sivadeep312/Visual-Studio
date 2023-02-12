#include"ColorRangeFinder.h"


Scalar HSVSegment(Mat MatImgHSV)
{
	vector<int>vecH(180, 0), vecS(256, 0), vecV(256, 0);
	for (int r = 0; r < MatImgHSV.rows; r++) {
		Vec3b* ptr = MatImgHSV.ptr<Vec3b>(r);
		for (int c = 0; c < MatImgHSV.cols; c++) {
			if (((int)ptr[c][0] != 0)||((int)ptr[c][1] != 0)||((int)ptr[c][2] != 0)) {
				vecH[(int)ptr[c][0]]++;
			}

			
		}
	}

	int iHmax = -1, iSmax = -1, iVmax = -1;
	int iHpos = 0, iSpos = 0, iVpos = 0;
	for (int i = 0; i < 180; i++) {
		if (vecH[i] > iHmax) {
			iHmax = vecH[i];
			iHpos = i;
		}
	}
	for (int r = 0; r < MatImgHSV.rows; r++) {
		Vec3b* ptr = MatImgHSV.ptr<Vec3b>(r);
		for (int c = 0; c < MatImgHSV.cols; c++) {

			if (((int)ptr[c][0] > (iHpos - 5)) && ((int)ptr[c][0] < (iHpos + 5))) {
				if (((int)ptr[c][0] != 0) || ((int)ptr[c][1] != 0) || ((int)ptr[c][2] != 0)) {
					vecS[(int)ptr[c][1]]++;
					vecV[(int)ptr[c][2]]++;
				}
			}
		}
	}


	for (int i = 0; i < 256; i++) {
		if (vecS[i] > iSmax) {
			iSmax = vecS[i];
			iSpos = i;
		}
		if (vecV[i] > iVmax) {
			iVmax = vecV[i];
			iVpos = i;
		}
	}

	vecH.clear(); vecS.clear(); vecV.clear();
	MatImgHSV.release();


	return Scalar(iHpos, iSpos, iVpos);
}


pair<Scalar,Scalar> HSVRange_(Mat matImgHSV) {


	vector<int>vecH(180, 0);

	for (int r = 0; r < matImgHSV.rows; r++) {
		Vec3b* ptr = matImgHSV.ptr<Vec3b>(r);
		for (int c = 0; c < matImgHSV.cols; c++) {
			if (((int)ptr[c][0] != 0) || ((int)ptr[c][1] != 0) || ((int)ptr[c][2] != 0)) {
				vecH[(int)ptr[c][0]]++;
			}


		}
	}
	int iHmax_ = -1;
	int iHpos_ = 0;
	for (int i = 0; i < 180; i++) {

		if (vecH[i] > iHmax_) {
			iHmax_ = vecH[i];
			iHpos_ = i;
		}

	}

	int iHmax = -1, iSmax = -1, iVmax = -1;
	int iHmin = INT_MAX, iSmin = INT_MAX, iVmin = INT_MAX;

	for (int r = 0; r < matImgHSV.rows; r++) {
		Vec3b* ptr = matImgHSV.ptr<Vec3b>(r);
		for (int c = 0; c < matImgHSV.cols; c++) {
			int iH = (int)ptr[c][0];
			int iS = (int)ptr[c][1];
			int iV = (int)ptr[c][2];
			if((iH > (iHpos_ - 5)) && (iH < (iHpos_ + 5))) {
				if ((iH != 0) || (iS != 0) || (iV != 0)) {

					//H Vals
					if (iH > iHmax) {
						iHmax = iH;
					}
					if (iH < iHmin) {
						iHmin = iH;
					}

					//S Vals
					if (iS > iSmax) {
						iSmax = iS;
					}
					if (iS < iSmin) {
						iSmin = iS;
					}

					//H Vals
					if (iV > iVmax) {
						iVmax = iV;
					}
					if (iV < iVmin) {
						iVmin = iV;
					}



				}
			}

		}
	}
	return make_pair(Scalar(iHmin, iSmin, iVmin), Scalar(iHmax, iSmax, iVmax));
}

vector<Scalar> HSVSegments(Mat MatImgHSV)
{
	vector<pair<int, int>>vecH;

	for (int i = 0; i < 256; i++) {
		if (i < 180) {
			vecH.push_back(make_pair(i, 0));
		}

	}

	for (int r = 0; r < MatImgHSV.rows; r++) {
		Vec3b* ptr = MatImgHSV.ptr<Vec3b>(r);
		for (int c = 0; c < MatImgHSV.cols; c++) {
			if (((int)ptr[c][0] != 0) || ((int)ptr[c][1] != 0) || ((int)ptr[c][2] != 0)) {
				vecH[(int)ptr[c][0]].second++;
			}
		}
	}

	sort(vecH.begin(),vecH.end(), [](const pair<int, int>&a, const pair<int, int>& b){
			return a.second > b.second;});

	vector<pair<int, int>>vecHVals(3);

	vecHVals[0] = vecH[0];
	int iHmaxPos = vecH[0].first;
	int iWindowSize=8;

	for (int j = 1; j < 180; j++) {
			int iPos = vecH[j].first;
			if (!((iPos > iHmaxPos - (iWindowSize)) && (iPos < iHmaxPos + (iWindowSize)))) {
				vecHVals[1] = vecH[j];			
				break;
	
			}

	}
	int iHmaxPos2 = vecHVals[1].first;
	for (int j = 1; j < 180; j++) {
		int iPos = vecH[j].first;
		if ((!((iPos > iHmaxPos - (iWindowSize)) && (iPos < iHmaxPos + (iWindowSize))))&& (!((iPos > iHmaxPos2 - (iWindowSize)) && (iPos < iHmaxPos2 + (iWindowSize))))){
			vecHVals[2] = vecH[j];
			break;

		}

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<Scalar>vecHSVs(3);

	for (int i = 0; i < 3; i++) {
		int iHpos = vecHVals[i].first;
		int iSmax = -1, iVmax = -1;
		int iSpos = 0, iVpos = 0;
		vector<int> vecS(256,0), vecV(256,0);
		for (int r = 0; r < MatImgHSV.rows; r++) {
			Vec3b* ptr = MatImgHSV.ptr<Vec3b>(r);
			for (int c = 0; c < MatImgHSV.cols; c++) {

				if (((int)ptr[c][0] > (iHpos - iWindowSize)) && ((int)ptr[c][0] < (iHpos + iWindowSize))) {
					if (((int)ptr[c][0] != 0) || ((int)ptr[c][1] != 0) || ((int)ptr[c][2] != 0)) {
						vecS[(int)ptr[c][1]]++;
						vecV[(int)ptr[c][2]]++;
					}
				}
			}
		}


		for (int i = 0; i < 256; i++) {
			if (vecS[i] > iSmax) {
				iSmax = vecS[i];
				iSpos = i;
			}
			if (vecV[i] > iVmax) {
				iVmax = vecV[i];
				iVpos = i;
			}
		}
		vecHSVs[i] = Scalar(iHpos, iSpos, iVpos);

	}
	return vecHSVs;
}