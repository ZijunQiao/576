//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************

#include "Image.h"
#include <vector>



// Constructor and Desctructors
MyImage::MyImage() 
{
	Data = NULL;
	Data2 = NULL;
	Width = -1;
	Height = -1;
	Width2 = -1;
	Height2 = -1;
	ImagePath[0] = 0;

}

MyImage::~MyImage()
{
	if ( Data )
		delete Data;
	if (Data2)
		delete Data2;
}


// Copy constructor
MyImage::MyImage( MyImage *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	Height2 = Height;
	Width2 = Width;
	Data   = new char[Width*Height*3];
	strcpy(otherImage->ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage->Data[i];
	}


}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	Height2 = Height;
	Width2 = Width;
	Data   = new char[Width*Height*3];
	strcpy( (char *)otherImage.ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage.Data[i];
	}
	
	return *this;

}


// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Width*Height; i ++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}
	
	// Allocate Data structure and copy
	Data = new char[Width*Height*3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(IN_FILE);

	return true;

}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}

	
	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}
	
	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(OUT_FILE);

	return true;

}

//void averageData(char* Data, char*& Data3, const int &Height, const int &Width) {
//	for (int i = 0; i < Width*Height; i++)
//	{
//		std::vector<int> temp;
//		 if(Data[3 * i]==0 && i >= Width && i < (Width * Height - Width) && (i % Width != 0) && (i + 1) % Width != 0) {
//			 temp = { Data[3 * (i + 1)], Data[3 * (i - 1)],
//				 Data[3 * (i - Width)], Data[3 * (i - Width - 1)], Data[3 * (i - Width + 1)],
//				 Data[3 * (i + Width - 1)], Data[3 * (i + Width)], Data[3 * (i + Width + 1)] };
//			 std::sort(temp.begin(), temp.end());
//			 Data3[3 * i] = (temp[4] + temp[3]) / 2;
//			 temp = { Data[3 * (i + 1) + 1], Data[3 * (i - 1) + 1], Data[3 * (i - Width) + 1], Data[3 * (i - Width - 1)+1],
//				 Data[3 * (i - Width + 1) + 1],Data[3 * (i + Width - 1) + 1], Data[3 * (i + Width) + 1], Data[3 * (i + Width + 1) + 1] };
//			 std::sort(temp.begin(), temp.end());
//			 Data3[3 * i + 1] = (temp[4] + temp[3]) / 2;
//			 temp = { Data[3 * (i + 1) + 2], Data[3 * (i - 1) + 2], Data[3 * (i - Width) + 2], Data[3 * (i - Width - 1) + 2], 
//				 Data[3 * (i - Width + 1) + 2],Data[3 * (i + Width - 1) + 2], Data[3 * (i + Width) + 2], Data[3 * (i + Width + 1) + 2] };
//			 std::sort(temp.begin(), temp.end());
//			 Data3[3 * i + 2] = (temp[4]+ temp[3])/2;
//		}
//		else {
//			Data3[3 * i] = Data[3 * i];
//			Data3[3 * i + 1] = Data[3 * i + 1];
//			Data3[3 * i + 2] = Data[3 * i + 2];
//		}
//	}
//}

void ToHSV(char*& Data, const int& Height, const int& Width) {
	float CMAX;
	float CMIN;
	float delt;
	float* Data3 = new float[Width * Height * 3];//HSV
	for (int i = 0; i < Height * Width; i++) {

		CMAX = max(max(Data[3 * i], Data[3 * i + 1]), Data[3 * i + 2]);
		CMIN = min(min(Data[3 * i], Data[3 * i + 1]), Data[3 * i + 2]);
		delt = CMAX - CMIN;
		if (delt != 0) {
			if (Data[3 * i+2]==CMAX) {
				//Data3[3 * i] = 60 * ((Data[3 * i + 1] - Data[3 * i]) / delt);
				Data3[3 * i] = 60 * fmod(((Data[3 * i + 1] - Data[3 * i]) / delt), 6) ;
			}
			else if (Data[3 * i + 1] == CMAX) {
				Data3[3 * i] = 60 * (((Data[3 * i] - Data[3 * i + 2]) / delt)+2);
			}
			else {				
				Data3[3 * i] = 60 * (((Data[3 * i + 2] - Data[3 * i + 1]) / delt)+4);
			}
		}
		if (CMAX != 0) { //s
			Data3[3 * i + 1] = delt / CMAX;
		}
		else {
			Data3[3 * i] = -1;
			Data3[3 * i + 1] = 0; }
		//Data3[3 * i ] = Data3[3 * i ] * 0.5;
		//Data3[3 * i + 1] = Data3[3 * i + 1]*0.75;//S
		Data3[3 * i + 2] = CMAX/255 *1; //V
		if (Data3[3 * i] < 0) {
			Data3[3 * i] = Data3[3 * i] + 360;
		}
	}
	//TORGB
	for (int i = 0; i < Height * Width; i++) {
		//if (Data3[3 * i + 1]== 0){
		//	Data[3 * i] = 0;
		//	Data[3 * i + 1] = 0;
		//	Data[3 * i + 2] = 0;
		//	continue;
		//}
		//Data3[3 * i] /= 60;
		//double v = Data3[3 * i + 2];
		//int j = floor(Data3[3 * i]);
		//double f = Data3[3 * i] - j;
		//int p = min(max(round(v * (1 - Data3[3 * i + 1])),0),255);
		//int q = min(max(round(v * (1 - Data3[3 * i + 1] * f)), 0),255);
		//int t = min(max(round(v * (1 - Data3[3 * i + 1]*(1-f))), 0),255);
		//v = min(max(v, 0), 255);
		//switch (j) {
		//case 0:
		//	Data[3 * i] = p;
		//	Data[3 * i + 1] = t;
		//	Data[3 * i + 2] = int(v);
		//	continue;
		//case 1:
		//	Data[3 * i] = p;
		//	Data[3 * i + 1] = int(v);
		//	Data[3 * i + 2] = q;
		//	continue;
		//case 2:
		//	Data[3 * i] = t;
		//	Data[3 * i + 1] = int(v);
		//	Data[3 * i + 2] = p;
		//	continue;
		//case 3:
		//	Data[3 * i] = int(v);
		//	Data[3 * i + 1] = q;
		//	Data[3 * i + 2] = p;
		//	continue;
		//case 4:
		//	Data[3 * i] = int(v);
		//	Data[3 * i + 1] = p;
		//	Data[3 * i + 2] = t;
		//	continue;
		//default:
		//	Data[3 * i] = q;
		//	Data[3 * i + 1] = p;
		//	Data[3 * i + 2] = int(v);
		//	continue;
		//}
		
		float C = Data3[3 * i + 1] * Data3[3 * i + 2];
		float m = Data3[3 * i + 2] - C;
		float h = fmod(Data3[3 * i] / 60.0, 6);
		float X = C * (1 - fabs(fmod(h, 2) - 1));
		m = max(min(m,255),0);
		if (h >= 0 && h < 1) {
			Data[3 * i] = m * 255;
			Data[3 * i + 1] = max(min((X + m) * 255,255),0);
			Data[3 * i + 2] = max(min((C + m) * 255, 255),0);
		}
		else if (h >= 1 && h < 2) {
			Data[3 * i] = m * 255;
			Data[3 * i + 1] = max(min((C + m) * 255, 255), 0);
			Data[3 * i + 2] = max(min((X + m) * 255, 255), 0);
		}
		else if (h >= 2 && h < 3) {
			Data[3 * i] = max(min((X + m) * 255, 255), 0);
			Data[3 * i + 1] = max(min((C + m) * 255, 255), 0);
			Data[3 * i + 2] = m * 255;
		}
		else if (h >= 3 && h < 4) {
			Data[3 * i] = max(min((C + m) * 255, 255), 0);
			Data[3 * i + 1] = max(min((X + m) * 255, 255), 0);
			Data[3 * i + 2] = m * 255;
		}
		else if (h >= 4 && h < 5) {
			Data[3 * i] = max(min((C + m) * 255, 255), 0);
			Data[3 * i + 1] = m * 255;
			Data[3 * i + 2] = max(min((X + m) * 255, 255), 0);
		}
		else if (h >= 5 && h < 6) {
			Data[3 * i] = max(min((X + m) * 255, 255), 0);
			Data[3 * i + 1] = m * 255;
			Data[3 * i + 2] = max(min((C + m) * 255, 255), 0);
		}
		else {
			Data[3 * i] = m * 255;
			Data[3 * i + 1] = m * 255;
			Data[3 * i + 2] = m * 255;
		}
		
	}
	delete Data3;
}
void Bright(char*& Data, const int& Height, const int& Width) {
	// l = (max(rgb) + min(rgb)) / 2
    //Brightness = 0.3 * R + 0.6 * G + 0.1 * B
	int i;
	char* Rbuf = new char[Height * Width];
	char* Gbuf = new char[Height * Width];
	char* Bbuf = new char[Height * Width];
	double* Y = new double[Height * Width];

	for (i = 0; i < Height * Width; i++)
	{
		Bbuf[i] = Data[3 * i];
		Gbuf[i] = Data[3 * i + 1];
		Rbuf[i] = Data[3 * i + 2];
		Y[i] = (0.114 * Bbuf[i] + 0.587 * Gbuf[i] + 0.299 * Rbuf[i]) / 0.75;
	}
	for (int i = 0; i < Height * Width; i++) {

		//Data[3 * i] = Bbuf[i] ;
		//Data[3 * i + 1] = Gbuf[i] ;
		//Data[3 * i + 2] = Rbuf[i] ;
		Data[3 * i] = round(Y[i] /(0.114 + 0.299 * Rbuf[i] / Bbuf[i] + 0.587 * Gbuf[i] / Bbuf[i]));
		Data[3 * i + 1]= round(Y[i] /(0.587 + 0.299 *Rbuf[i] / Gbuf[i] + 0.114 * Bbuf[i] / Gbuf[i]));
		Data[3 * i + 2]= round(Y[i] / (0.299 + 0.587 * Gbuf[i] / Rbuf[i] + 0.114 *Bbuf[i] / Rbuf[i]));
		if (Data[3 * i] >= 255) { Data[3 * i] = 255; }
		if (Data[3 * i+1] >= 255) { Data[3 * i + 1] = 255; }
		if (Data[3 * i + 2] >= 255) { Data[3 * i + 2] = 255; }
	}
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	delete Y;
}

void Resize(char*& Data, char*& Data2, const int& Height, const int& Width, const double& ratio) {
	int i;
	int newi;
	int newj;
	int newpos;
	int Height2 = int(Height * ratio);
	int Width2 = int(Width * ratio);
	for (i = 0; i < Height2; i++) {
		for (int j = 0; j < Width2; j++)
		{
			//Data2[3 * (i * Width2 + j)] = Data[3 * (i * Width2 + j)];
			//Data2[3 * (i * Width2 + j) + 1] = Data[3 * (i * Width2 + j) + 1];
			//Data2[3 * (i * Width2 + j) + 2] = Data[3 * (i * Width2 + j) + 2];
			newi = max(int((i + 1) / ratio + 0.5) - 1, 0);
			newj = max(int((j + 1) / ratio + 0.5) - 1, 0);
			newpos = newi * Width + newj;
			Data2[3 * (i * Width2 + j)] = Data[3 * newpos];
			Data2[3 * (i * Width2 + j) + 1] = Data[3 * newpos + 1];
			Data2[3 * (i * Width2 + j) + 2] = Data[3 * newpos + 2];
		}
	}
}

bool MyImage::Modify(const int& mode, const double& ratio, const int& antiAlising)
{

	int i;
	int newi;
	int newj;
	int newpos;
	if (mode == 1) {
		Height2 = int(Height * ratio);
		Width2 = int(Width * ratio);
		//Data2 = new char[Height * Width * 3];
		Data2 = new char[Height2 * Width2 * 3];
		if (antiAlising == 0) {
			Resize(Data, Data2, Height, Width, ratio);
		}
		else {
			char* Data3 = new char[Height * 2 * Width * 2 * 3];
			//antiAlising
			Resize(Data, Data3, Height, Width, 2);
			Resize(Data3, Data, Height * 2, Width * 2, 0.5);
			//Resize
			Resize(Data, Data2, Height, Width, ratio);
			delete Data3;
		}
	}
	else if (mode == 2) {
		Height2 = int(Height * ratio);
		Width2 = int(Width * ratio);
		Data2 = new char[Width2 * Height2 * 3];
		//WIDTHBYTES(bi.biWidth*bi.biBitCount)
		if (antiAlising == 0) {
			Resize(Data, Data2, Height, Width, ratio);
		}
		else {
			char* Data3 = new char[Height * 2 * Width * 2 * 3];
			//antiAlising
			Resize(Data, Data3, Height, Width, 2);
			Resize(Data3, Data, Height * 2, Width * 2, 0.5);
			//Resize
			Resize(Data, Data2, Height, Width, ratio);
			delete Data3;
		}
		ToHSV(Data, Height, Width);

	}
	else {
		//Data2 = new char[Width * Height * 3];
		//std::vector<int> errors;
		//for (i = 0; i < Height * Width; i++)
		//{
		//	Data2[3 * i] = Data[3 * i];
		//	Data2[3 * i + 1] = Data[3 * i + 1];
		//	Data2[3 * i + 2] = Data[3 * i + 2];
		//}
		//// Data2 salty picture
		//int remove;
		//char* Data3 = new char[Height * Width * 3];
		//for (int percent = 1; percent <= 50; percent++) {
		//	std::random_device rd;  //Will be used to obtain a seed for the random number engine
		//	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		//	std::uniform_int_distribution<> distrib(1, Height * Width);
		//	for (i = 0; i < round(Height * Width * percent / 100); i++) {
		//		remove = distrib(gen);
		//		Data2[3 * remove] = 0;
		//		Data2[3 * remove + 1] = 0;
		//		Data2[3 * remove + 2] = 0;
		//	}
		//	averageData(Data2, Data3, Height, Width);
		//	int error = 0;
		//	for (i = 0; i < Height * Width; i++)
		//	{
		//		error += abs(Data3[3 * i] - Data[3 * i]) / 3 + abs(Data3[3 * i + 1] - Data[3 * i + 1]) / 3 + abs(Data3[3 * i + 2] - Data[3 * i + 2]) / 3;
		//	}
		//	errors.push_back(error);
		//}
		//delete Data3;
		//std::random_device rd;  //Will be used to obtain a seed for the random number engine
		//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		//std::uniform_int_distribution<> distrib(1, Height * Width);
		//for (i = 0; i < round(Height * Width * ratio); i++) {
		//	remove = distrib(gen);
		//	Data2[3 * remove] = 0;
		//	Data2[3 * remove + 1] = 0;
		//	Data2[3 * remove + 2] = 0;
		//}
		//averageData(Data2, Data3, Height, Width);
		////average efficiency
		////int error2 = 0;
		////for (i = 0; i < Height * Width; i++)
		////{
		////	error2 += abs(Data2[3 * i] - Data3[3 * i]) / 3 + abs(Data2[3 * i + 1] - Data3[3 * i + 1]) / 3 + abs(Data2[3 * i + 2] - Data3[3 * i + 2]) / 3;
		////}
		//for (int i = 0; i < Width * Height; i++)
		//{
		//	Data2[3 * i] = Data3[3 * i];
		//	Data2[3 * i + 1] = Data3[3 * i + 1];
		//	Data2[3 * i + 2] = Data3[3 * i + 2];
		//}
		//int error = 0;		
		//for (i = 0; i < Height * Width; i++)
		//{
		//	error += abs(Data2[3 * i] - Data[3 * i])/3 + abs(Data2[3 * i + 1] - Data[3 * i + 1])/3 + abs(Data2[3 * i + 2] - Data[3 * i + 2])/3;
		//}

		//delete Data3;
	}

	return false;
}

