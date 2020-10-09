#include "Draw.h"
#include "Mass.h"
int Width, Height;
const int MARGIN = 10;
bool isSortedArr(const int *mass){
	for (int i = 0;i<100;i++){
		if (i+1 != mass[i]){
			return false;
		}
	}
	return true;
}
void DrawDiag(const HDC hdc,int *mass,const unsigned int massSize){
	
	COLORREF color = RGB(1,1,1);
	COLORREF cmpColor = RGB(0,255,0);
	COLORREF pivColor = RGB(255,0,0);
	COLORREF sortedColor = RGB(150,150,150);
	HBRUSH pivotDiagBrush = CreateSolidBrush(pivColor);
	HBRUSH defDiagBrush = CreateSolidBrush(color);
	HBRUSH cmpDiagBrush = CreateSolidBrush(cmpColor);
	HBRUSH sortedDiagBrush = CreateSolidBrush(sortedColor);
 	HRGN Diagram[massSize];
 	
 	for (int i = 0;i<massSize;i++){
 		Diagram[i] = CreateRectRgn(
  		50+i*14, // int left upper x coord
  		400-mass[i]*2,  // left upper y coord
  		50+i*14+10, // right lower x coord
  		400); // right lower y coord
	 }
	for (int i = 0;i<massSize;i++){
		if (DRAW_COMPLETED){
			FillRgn(
  			hdc, //Handle to device context
  			Diagram[i], //handle to specifed region /init above
  			sortedDiagBrush); // Gray brush for sorted array
		}
		else if (i == FIRST_CMP || i == SECOND_CMP){
			FillRgn(
  			hdc, //Handle to device context
  			Diagram[i], //handle to specifed region /init above
  			cmpDiagBrush); // handle to brush /init above
	}
	else if (i == PIVOT_CMP){
		
		FillRgn(
  		hdc, //Handle to device context
  		Diagram[i], //handle to specifed region /init above
  		pivotDiagBrush); // handle to brush /init above
	}
	else{
		FillRgn(
  		hdc, //Handle to device context
  		Diagram[i], //handle to specifed region /init above
  		defDiagBrush); // handle to brush /init above
	}
	}
	
	for (int i = 0;i<massSize;i++){
 		DeleteObject(Diagram[i]);
 	}
	//delete[] Diagram;//
	DeleteObject(defDiagBrush);
	DeleteObject(cmpDiagBrush);
	DeleteObject(pivotDiagBrush);
	DeleteObject(sortedDiagBrush);
}


void SetWindowSize(int _Width, int _Height){
Width = _Width;
Height = _Height;
}

int Tx(double X_Log){
int X_Window;
X_Window = MARGIN + (1.0 / 2) * (X_Log + 1) * (Width - 2 * MARGIN);
return X_Window;
}

int Ty(double Y_Log){
int Y_Window;
Y_Window = MARGIN +(-1.0 / 2)*(Y_Log - 1)*(Height - 2* MARGIN);
return Y_Window;
}
