#include"acllib.h"
#include <stdio.h>
const int winWidth = 800, winHeight = 480;
ACL_Image img1,img2,img3,img4,img5;
ACL_Sound sound1;
const char* head = "head.jpg";
const char* kid = "kid.jpg";
const char* bullet = "1.jpg";
const char* Fence = "fence.jpg";
const char* begin = "start.gif";
const char* music = "music.mp3";
void timerEvent(int id);
void keyEvent(int key, int e);
int moveid = 0, movetimerInterval = 50;
int createid = 1, createtimerInterval = 2000;
int fence = 200;
const int maxNum = 10;
const int clip = 100;
int score = 0;
int life = 2;
int endid = 2, endtimerInterval = 50;
void start(int x,int y,int button,int event);
int s = 0;
typedef struct rect
{
	int x, y;
	int w, h;

}rect;
int collision(rect r1, rect r2);
struct sprite
{
	int width, height;
	int x;
	int y;
	int dist;
	int dist1;
};
struct sprite girlSprite, * bulletSprite[clip] = { NULL }, *kidSprite[maxNum] = { NULL };
int NumZ = 0;
void paint1();
int NumB = 0;
                                                                                                                                 
int Setup()
{
	initWindow("my first window", DEFAULT, DEFAULT,winWidth,winHeight);
	loadImage(head, &img1);
	loadImage(kid, &img2);
	loadImage(bullet, &img3);
	loadImage(Fence, &img4);
	loadImage(begin, &img5);
	loadSound(music, &sound1);
	registerMouseEvent(start);
	playSound(sound1, 1);
	beginPaint();
	
	putImageScale(&img5, 0, 0, winWidth, winHeight);
	endPaint();
		return 0;
		}
	

void timerEvent(int id)//¶¨Ê±Æ÷º¯Êý
{
	int i;
	switch (id)
	{
	case(0):

	{for (i = 0; i < NumZ; ++i) 
	{
		if (kidSprite[i])
		{
			kidSprite[i]->x -= kidSprite[i]->dist;


			paint1();
		}
	}
	for (i = 0; i < NumB; ++i)
	{
		if (bulletSprite[i])
		{
			bulletSprite[i]->x += bulletSprite[i]->dist;


			paint1();
		}
	}
	rect r1, r2;


	for (int i = 0; i < NumZ; ++i)
	{
		if (kidSprite[i])
		{
			r2.x = kidSprite[i]->x;
			r2.y = kidSprite[i]->y;
			r2.w = kidSprite[i]->width;
			r2.h = kidSprite[i]->height;
			for (int j = 0; j < NumB; ++j)
			{
				if (bulletSprite[j])
				{
					r1.x = bulletSprite[j]->x;
					r1.y = bulletSprite[j]->y;
					r1.w = bulletSprite[j]->width;
					r1.h = bulletSprite[j]->height;

					int c = collision(r1, r2);
					if (c)
					{
						score++;
						kidSprite[i] = NULL;
						bulletSprite[j] = NULL;

					}
					if (kidSprite[i])
					{
						if (kidSprite[i]->x <= fence)
						{
							life--;
							kidSprite[i] = NULL;
						}
					}
				}
			}
		}
	}
	paint1();
	
	break;
	}
	case(1):
		if (NumZ < (maxNum-1))
		{
			NumZ++;
			kidSprite[NumZ] = (struct sprite*)malloc(sizeof(struct sprite));
			kidSprite[NumZ]->x = (winWidth - 50);
			kidSprite[NumZ]->y = rand() % (winHeight - 50);
			kidSprite[NumZ]->width = 50;
			kidSprite[NumZ]->height = 50;
			kidSprite[NumZ]->dist = 2;
			
		}
		if (NumB < clip)
		{
			NumB++;
			bulletSprite[NumB] = (struct sprite*)malloc(sizeof(struct sprite));
			bulletSprite[NumB]->x = girlSprite.x+ girlSprite.width;
			bulletSprite[NumB]->y = girlSprite.y;
			bulletSprite[NumB]->width = 50;
			bulletSprite[NumB]->height = 25;
			bulletSprite[NumB]->dist = 2;
			bulletSprite[NumB]->dist1 = 2;
		}
	case 2:
		if (life == 0)
		{
			
			cancelTimer(moveid);
			cancelTimer(createid);
			beginPaint();
			
			char arr[50];
			sprintf_s(arr,"YOU ARE DEAD");
			setTextSize(50);
			paintText(400, 240, arr);
			endPaint();
			break;
		}
	default: break;
	}
}
void paint1()
{
	beginPaint();
	//putImage(&img, 0, 0);
	clearDevice();
	putImageScale(&img1, girlSprite.x, girlSprite.y, girlSprite.width, girlSprite.height);
	putImageScale(&img4, fence-50, 0, 50, winHeight);
	for(int i=0;i<NumZ;++i)if (kidSprite[i] != NULL)
	putImageScale(&img2, kidSprite[i]->x, kidSprite[i]->y, kidSprite[i]->width, kidSprite[i]->height);
	for (int i = 0; i < NumB; ++i)if (bulletSprite[i] != NULL)
		putImageScale(&img3, bulletSprite[i]->x, bulletSprite[i]->y, bulletSprite[i]->width, bulletSprite[i]->height);
	char str[50];
	sprintf_s(str, "score:%d life:%d", score,life);
	setTextSize(30);
	paintText(10, 10, str);
	endPaint();
}


void keyEvent(int key, int e)//¼üÅÌÒÆ¶¯º¯Êý
{
	
	switch (key)
	{
	case VK_UP:
		girlSprite.y-=girlSprite.dist;
		if (girlSprite.y <= 0)	girlSprite.y = 0;
		break;
	case VK_DOWN:
		girlSprite.y += girlSprite.dist;
		if (girlSprite.y + girlSprite.height >= winHeight)	girlSprite.y = (winHeight - girlSprite.height);
		break;
	case VK_LEFT:
		girlSprite.x-= girlSprite.dist;
		if (girlSprite.x <= 0)girlSprite.x = 0;
		break;
	case VK_RIGHT:
		girlSprite.x+= girlSprite.dist;
		if (girlSprite.x + girlSprite.width >= fence)girlSprite.x = (fence - girlSprite.width);
		break;
	default:
		break;
	

	}
	/*rect r1, r2;
	
	
	for (int i = 0; i < NumZ; ++i)
	{
		if (kidSprite[i])
		{
			r2.x = kidSprite[i]->x;
			r2.y = kidSprite[i]->y;
			r2.w = kidSprite[i]->width;
			r2.h = kidSprite[i]->height;
			for (int j = 0; j < NumB; ++j)
			{
				if (bulletSprite[j])
				{
					r1.x = bulletSprite[j]->x;
					r1.y = bulletSprite[j]->y;
					r1.w = bulletSprite[j]->width;
					r1.h = bulletSprite[j]->height;

					int c = collision(r1, r2);
					if (c)
					{
						score++;
						kidSprite[i] = NULL;
						bulletSprite[j] = NULL;
						
					}
					if (kidSprite[i])
					{
						if (kidSprite[i]->x <= fence)
						{
							life--;
							kidSprite[i] = NULL;
						}
					}
				}
			}
		}
	}*/
	paint1();

		
}
int collision(rect r1, rect r2)  //Åö×²¼ì²âº¯Êý
{
	
	/*if (r1.x<r2.x && r1.x + r1.w>r2.x)
	{
		if (r1.y > r2.y && r1.y < r2.y + r2.h)return c;
		if (r1.y<r2.y && r1.y + r1.h>r2.y)return c;

	}
	else {
		if (r1.x > r2.x && r2.x + r2.w > r1.x)
		{
			if (r1.y > r2.y && r1.y < r2.y + r2.h)return c;
			if (r1.y<r2.y && r1.y + r1.h>r2.y)return c;
		}*/
	if (r1.x > r2.x)
	{
		if (r1.y>r2.y&&r1.y<(r2.y+r2.h))
		{
			return 1;
		}
		if ((r1.y+r1.h) > r2.y && (r1.y+r2.h) < (r2.y + r2.h))
		{
			return 1;
		}
	}
			
		return 0;
	
}
void start(int x, int y, int button, int event)
{
	if (event == BUTTON_DOUBLECLICK)
	{

		girlSprite.x = rand() % (fence);
		girlSprite.y = rand() % winHeight;
		girlSprite.width = 100;
		girlSprite.height = 100;
		girlSprite.dist = 3;
		kidSprite[NumZ] = (struct sprite*)malloc(sizeof(struct sprite));
		kidSprite[NumZ]->x = (winWidth - 50);
		kidSprite[NumZ]->y = rand() % (winHeight - 50);
		kidSprite[NumZ]->width = 50;
		kidSprite[NumZ]->height = 50;
		kidSprite[NumZ]->dist = 2;
		kidSprite[NumZ]->dist1 = 2;

		registerTimerEvent(timerEvent);
		startTimer(moveid, movetimerInterval);
		startTimer(createid, createtimerInterval);
		startTimer(endid, endtimerInterval);
		registerKeyboardEvent(keyEvent);
	};
}

