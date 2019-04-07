#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"ppm.h"
#include"image.h"



double convert_degre_radian(double angle_degre)
{
	double pi= 4*atan(1);
	double angle_radian=0;
	 
	angle_radian=(angle_degre*pi)/180;
	return angle_radian;
}

int rotation (const Image* imageSrc, Image* imageDest,double angle)
{
	int x=0,y=0;
	int X=0,Y=0,W=0;
	int cx=imageSrc->height/2;
	int cy=imageSrc->width/2;
	int ax=0,ay=0;
	double cosinus=0,sinus=0,angle_rad=0;
	double w=0,h=0;
	char r=0,g=0,b=0;
	double c=0, d=0,dx=0,dy=0;
	int e=imageSrc->width,f=imageSrc->height;

	
	if (imageSrc==NULL)
	{
		fprintf(stderr,"erreur fonction rotation,l'image passe n'existe pas");
		return 0;
	}
	
	angle_rad=convert_degre_radian(angle);
	cosinus=cos(angle_rad);
	sinus=sin(angle_rad);

	w=abs(imageSrc->width*cosinus)+abs(imageSrc->height*sinus);
	h=abs(imageSrc->width*sinus)+abs(imageSrc->height*cosinus);

	imageDest->width=(unsigned int)w;
	imageDest->height=(unsigned int)h;
	printf("cest bon  %d %d\n",imageDest->width,imageDest->height);
	
	ax=h/2;
	ay=w/2;
	create(imageDest);
	for(X=0;X<h;X++)
	{
		for(Y=0;Y<w;Y++)
		{
			c=(X-ax)*cosinus+(Y-ay)*sinus+cx;
			d=-(X-ax)*sinus+(Y-ay)*cosinus+cy;
			
			x=(int)c;
			y=(int)d;
			dx=c-x;
			dy=d-y;
			W=imageSrc->width;
			
			if((c<0)||(d<0)||(x>f-1)||(y>e-1))
			{
				imageDest->R[X*(imageDest->width)+Y]=0;
				imageDest->G[X*(imageDest->width)+Y]=0;
				imageDest->B[X*(imageDest->width)+Y]=0;
			}
			
			else if((int)dx!=0||(int)dy!=0)
			{
				r=(1-dx)*(1-dy)*(imageSrc->R[x*W+y])+(dy)*(1-dx)*(imageSrc->R[(x-1)*W+y]);
				r+=(dx)*(dy)*(imageSrc->R[(x-1)*W+y+1])+(dx)*(1-dy)*(imageSrc->R[x*W+y+1]);
				r/=4;
	
				g=(1-dx)*(1-dy)*(imageSrc->G[x*W+y])+(dy)*(1-dx)*(imageSrc->G[(x-1)*W+y]);
				g+=(dx)*(dy)*(imageSrc->G[(x-1)*W+y+1])+(dx)*(1-dy)*(imageSrc->G[x*W+y+1]);
				g/=4;
	
				b=(1-dx)*(1-dy)*(imageSrc->B[x*W+y])+(dy)*(1-dx)*(imageSrc->B[(x-1)*W+y]);
				b+=(dx)*(dy)*(imageSrc->B[(x-1)*W+y+1])+(dx)*(1-dy)*(imageSrc->B[x*W+y+1]);
				b/=4;
				
				imageDest->R[X*(imageDest->width)+Y]=r;
				imageDest->G[X*(imageDest->width)+Y]=g;
				imageDest->B[X*(imageDest->width)+Y]=b;
			}
			
			
			else
			{
				imageDest->R[X*(imageDest->width)+Y]=imageSrc->R[x*(imageSrc->width)+y];
				imageDest->G[X*(imageDest->width)+Y]=imageSrc->G[x*(imageSrc->width)+y];
				imageDest->B[X*(imageDest->width)+Y]=imageSrc->B[x*(imageSrc->width)+y];
			}
			dx=0;
			dy=0;
			r=0;
			g=0;
			b=0;
		}
	}
	return 0;
}


int main()
{
	Image imageSrc;
	Image imageDest;
	
	read_file("profil.ppm",&imageSrc);
	rotation(&imageSrc,&imageDest,180);
	write_file(&imageDest,"zahi180.ppm",3);
	
	return 0;
}
	
	