#pragma once
#include <stdlib.h>
#include "Draw.h"
int FIRST_CMP = -1;
int SECOND_CMP = -1;
int PIVOT_CMP = -1;
BOOL SORT_DONE = false;
BOOL DRAW_COMPLETED = false;
BOOL STOP = false;
using namespace std;
void invDiag(int *arr,const HWND hwnd,RECT &rect1){
	for (int l = 0;l<100;l++){
        	rect1.left = 50 + (l-1)*14;
    		rect1.right = 50 + (l-1)*14+10;
    		InvalidateRect(hwnd,&rect1,false);
    		rect1.left = 50 + (l+1)*14;
    		rect1.right = 50 + (l+1)*14+10;
    		InvalidateRect(hwnd,&rect1,false);
		}
}
void quickSort(int *arr, int left, int right,const HWND hwnd) {
	BOOL END = STOP;
	int i = left, j = right;
   	int tmp;
    int pivot = arr[(left + right) / 2];
	RECT rect1;
	rect1.bottom = 200;
	rect1.top = 400;
	FIRST_CMP = i;
	SECOND_CMP = j;
	PIVOT_CMP = pivot;

	if (!SORT_DONE){
    	
    	/* partition */
    	while (i <= j) {
       		while (arr[i] < pivot){
        		i++;
        		FIRST_CMP = i;
        		invDiag(arr,hwnd,rect1);
				SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
				if (STOP != END) return;
				Sleep(15);
				FIRST_CMP = -1;
			}
     		while (arr[j] > pivot){
        		j--;
        		SECOND_CMP = j;
        		invDiag(arr,hwnd,rect1);
    			SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
				if (STOP != END) return;
				Sleep(15);
				SECOND_CMP = -1;
			}
        

       		if (i <= j) {
       			FIRST_CMP = i;
       			SECOND_CMP = j;
				tmp = arr[i];
          	  	arr[i] = arr[j];
          	  	arr[j] = tmp;
          	  	invDiag(arr,hwnd,rect1);
    			SendMessage(
  				hwnd,
  				WM_PAINT,
  				NULL,
  				NULL
				);
				if (STOP != END) return;
				Sleep(15);
       	    	i++;
       	    	FIRST_CMP = i;
       	    	invDiag(arr,hwnd,rect1);
    		
    			SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
				if (STOP != END) return;
				Sleep(15);
        	    j--;
        	    SECOND_CMP = j;
        	    invDiag(arr,hwnd,rect1);
    		
    
    			SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
				if (STOP != END) return;
				Sleep(15); 
     	   }
    			invDiag(arr,hwnd,rect1);
    			SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
				if (STOP != END) return;
				Sleep(15);
 	   };
 	
 		if (STOP != END) return;
    	/* recursion */
    	if (left < j)
    	quickSort(arr, left, j,hwnd);
    	if (i < right)
    	quickSort(arr, i, right,hwnd);
	}
	else{
		PIVOT_CMP = -1;
		SECOND_CMP = -1;
		invDiag(arr,hwnd,rect1);
		SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
		for (int k{0};k<100;k++){
			if (STOP != END) return;
			Sleep(10);
			FIRST_CMP = k;
			rect1.left = 50 + (k)*14;
    		rect1.right = 50 + (k)*14+10;
    		InvalidateRect(hwnd,&rect1,false);
    		//
    		SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
		}
			if (STOP != END) return;
			FIRST_CMP = -1;
			rect1.left = 50 + (99)*14;
    		rect1.right = 50 + (99)*14+10;
    		InvalidateRect(hwnd,&rect1,false);
    		SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
		DRAW_COMPLETED = true;
	}    
}

void bubbleSort(int *arr,unsigned int massSize,const HWND hwnd)
{
	RECT rect1;
	rect1.bottom = 200;
	rect1.top = 400;
	if (!SORT_DONE)
	{
		int temp;
		for (int i = 0;i< massSize-1;i++)
		{
			for (int j = 0;j<massSize-i-1;j++)
			{
				FIRST_CMP = j;
				SECOND_CMP = j+1;
				invDiag(arr,hwnd,rect1);
				SendMessage(hwnd,WM_PAINT,NULL,NULL);
				Sleep(15); 
				if (arr[j]>arr[j+1])
				{
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
				invDiag(arr,hwnd,rect1);
				SendMessage(hwnd,WM_PAINT,NULL,NULL);
				Sleep(15); 
			}
		}
	}
	else
	{
		SECOND_CMP = -1;
		invDiag(arr,hwnd,rect1);
		SendMessage(hwnd,WM_PAINT,NULL,NULL);
		for (int k{0};k<100;k++){
			Sleep(10);
			FIRST_CMP = k;
			rect1.left = 50 + (k)*14;
    		rect1.right = 50 + (k)*14+10;
    		InvalidateRect(hwnd,&rect1,false);
    		//
    		SendMessage(hwnd,WM_PAINT,NULL,NULL);
		}
			FIRST_CMP = -1;
			rect1.left = 50 + (99)*14;
    		rect1.right = 50 + (99)*14+10;
    		InvalidateRect(hwnd,&rect1,false);
    		SendMessage(
  					hwnd,
  					WM_PAINT,
  					NULL,
  					NULL
				);
		DRAW_COMPLETED = true;
	}
}
void massIncInit(int *mass,unsigned int massSize){
	for (int i = 0;i<massSize;i++){
		mass[i] = i+1;
	}
}

void massIncInit(double *mass,unsigned int massSize){
	for (int i = 0;i<massSize;i++){
		mass[i] = i+1;
	}
}

void massIncInit(float *mass,unsigned int massSize){
	for (int i = 0;i<massSize;i++){
		mass[i] = i+1;
	}
}

void massQSort(int *mass,unsigned int massSize,const HWND hwnd1){
	SORT_DONE = false;
	quickSort(mass,0, massSize-1,hwnd1);
	SORT_DONE = true;
	quickSort(mass,0, massSize-1,hwnd1);
	
}
void massBubbleSort(int *mass,unsigned int massSize,const HWND hwnd1)
{
	SORT_DONE = false;
	bubbleSort(mass,massSize,hwnd1);
	SORT_DONE = true;
	bubbleSort(mass,massSize,hwnd1);
}

