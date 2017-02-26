/*Programmer Name-Anish Niranjan Hemmady
Multimedia Assignment on hsv transformation*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include<conio.h>
#include <math.h>  
#define PI 3.14159265

struct HSV{
	double H;
	double S;
	double V;
};
struct RGB{
	double R;
	double G;
	double B;
};
static double Minz(double p, double q){
	if (p < q){
		return p;
	}
	else{
		return q;
	}
}
static double Maxz(double p, double q){
	if (p>q){
		return p;
	}
	else{
		return q;
	}
}
struct HSV rgbtohsv(struct RGB rgb){
	double lightness;
	struct HSV hsv;
	lightness = rgb.R + rgb.G + rgb.B;
	if (rgb.R == rgb.G == rgb.B){
		hsv.H = 0;
	}
	else{
		double minm = Minz(Minz(rgb.R, rgb.G), rgb.B);
		minm = 3.0*(minm);
		hsv.S = 1.0 - (minm / lightness);
		double numertr = (rgb.R - rgb.G) + (rgb.R - rgb.B);
		double temp1 = (rgb.R - rgb.B)*(rgb.G - rgb.B);
		double temp2 = pow((rgb.R - rgb.G), 2.0);
		double denom = 2.0*(sqrt(temp2 + temp1));
		hsv.H = numertr / denom;
	}
	if (rgb.G >= rgb.B){
		hsv.H = acos(hsv.H) * 180.0 / PI;

	}
	else{
		hsv.H = 360.0 - acos(hsv.H)*180.0 / PI;
	}
	return hsv;
}
struct HSV rgb2hsv(struct RGB rgb){
	double diff, minm;
	double h;
	double s, maxm;
	//normalize the r,g,b values
	rgb.R = (rgb.R) / 255.0;
	rgb.G = (rgb.G) / 255.0;
	rgb.B = (rgb.B) / 255.0;
	// find minimum and maximum among r,g,b values
	minm = Minz(Minz(rgb.R, rgb.G), rgb.B);
	maxm = Maxz(Maxz(rgb.R, rgb.G), rgb.B);
	//calculate delta i.e. difference between minimum and maximum
	diff = maxm - minm;
	if (maxm == minm){
		h = 0;
	}
	else if (maxm == rgb.G){
		h = 60 * ((rgb.B - rgb.R) / diff) + 120;
		h = fmod(h, 360);

	}
	else if (maxm == rgb.R){
		h = 60 * ((rgb.G - rgb.B) / diff) + 360;
		h = fmod(h, 360);
	}
	else if (maxm == rgb.B){
		h = 60 * ((rgb.R - rgb.G) / diff) + 360;
		h = fmod(h, 360);
	}

	if (maxm == 0){
		s = 0.0;
	}
	else{
		s = diff / maxm;
	}
	struct HSV hsv;
	hsv.H = h;
	hsv.S = s;
	hsv.V = maxm;
	return hsv;
}
int main(){
	const int rows = 600;
	const int columns = 574;
	FILE *fp;
	fp = fopen("IMG1000.raw", "rb");
	if (!fp){
		printf("ERROR");
	}

	//output hsv image
	FILE *output_hsv = fopen("outpt_hsv.raw", "wb");
	//output hue image
	FILE *hue = fopen("outpt_hue.raw", "wb");
	//output satutration image
	FILE *satu = fopen("output_satu.raw", "wb");
	// Seek to the end of the file to get file length
	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);

	// Seek back to the beginning of the file
	fseek(fp, 0, SEEK_SET);
	int i = 0;
	unsigned char R, G, B;
	while (i <= length - 3)
	{
		R = (unsigned char)fgetc(fp);
		G = (unsigned char)fgetc(fp);
		B = (unsigned char)fgetc(fp);
		struct RGB dat = { R, G, B };
		struct HSV val = rgb2hsv(dat);
		/*activate this method to see professors formula for hue and saturation */
		//struct HSV val = rgbtohsv(dat);
		/*map h,s,v value back to 0-255*/
		val.H = (val.H / 360)*255.0;
		val.S *= 255;
		val.V *= 255;
		unsigned char Hue = (unsigned char)(val.H);
		unsigned char Satu = (unsigned char)(val.S);
		unsigned char Value = (unsigned char)(val.V);

		// Put the result into output file
		fputc(Satu, satu);
		fputc(Hue, hue);
		fputc(Hue, output_hsv);
		fputc(Satu, output_hsv);
		fputc(Value, output_hsv);

		i = i + 3;
	}
	//close all the files
	fclose(fp);
	fclose(satu);
	fclose(hue);
	fclose(output_hsv);



}