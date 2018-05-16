#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<dos.h>
//using namespace std;

const int width = 20;
const int height =20;
int gameState = 1;
int score;
int posX;
int posY;
int a[100],b[100];
int STOP = 0, UP=1, LEFT=2, RIGHT=3, DOWN=4;
int dir;

struct fruitClass {
    int x;
    int y;
}fruit;

struct node {
    int x;
    int y;
    struct node *next;
}*head,*tail;

//function to create a new node every time the snake eats the fruit
struct node * create()
 {  
    struct node * link=(struct node*)malloc(sizeof(struct node));
    link->next=NULL;
    return link;
 }
 
//Function to shift the snake with every keyboard input(eg,UP,DOWN,RIGHT,LEFT) 
 void shift(struct node *t1,struct node *t2)
{ 
int i=0;
while(t1!=NULL)
{ a[i]=t1->x;
b[i]=t1->y;
t1=t1->next;
i++;
}
t2=head->next;
i=0;
while(t2!=NULL)
{ t2->x=a[i];
t2->y=b[i];
t2=t2->next;
i++;
}
}
//Initial positon and score
 void init ()
 {

	posX=width/2;
	posY=height/2;

	head=create();
	head->x=posX;
	head->y=posY;

	tail=head;
	head->next=NULL;
	tail->next=NULL;

	fruit.x = rand() % width;
	fruit.y = rand() % height;

	//Initialise score
	score = 0;

	//Initialise direction
	dir = STOP;
    }


//Function to draw the rectangular field
 void draw()
 {
    struct node *curr;
    int i=0,j=0;
    system("cls");

    for (i = 0; i < width+2; i++)
   {  printf("#");
   }

   printf("\n");

   for ( i = 0; i < height; i++)
    {
	for ( j = 0; j < width; j++)
	{
	      int found = 0;

		if (j == 0)
		    printf("#");

		if (i == head->y && j == head->x)
		{    printf("O");
		    found = 1;
		}


		 curr=head;
	
		while (curr!=0 && found!=1) {
		    if (i == curr->y && j == curr->x)
		   {
		     printf("o");
		     found = 1;
		    }
		    curr = curr->next;
		}

		if (!found)
		{    if (i == fruit.y && j == fruit.x)
			printf("F");
		    else
			printf(" ");

		}

		if (j == width-1)
		    printf("#");
	 }

	    if (i != height-1)
	      printf("\n");
  }

  printf("\n");

	for (i = 0; i < width+2; i++)
	    printf("#");
	  printf("\n\n");


	printf("\tSCORE:%d ",score);

    }

  void input(){

	if (kbhit())
	{

	    switch(getch())
	    {
	    case 'W' : case 'w' :
		      dir = UP;
		      break;

	    case 'A' : case 'a' :
		       dir = LEFT;
		       break;

	    case 'S' : case 's' :
		      dir = DOWN;
		      break;

	    case 'D' : case 'd' :
		      dir = RIGHT;
		      break;
	    }
	}
    }

  void logic()
  {
	struct node *current=head,*s;
	struct node *t1=head,*t2=t1->next;
	int a[100],b[100];
	struct node *r1=tail;
	r1->x=tail->x;
	r1->y=tail->y;

	switch (dir)    //Shift the snake with input direction
	{
	case 1 :
	    shift(t1,t2);
	    (head->y)--;
	    break;
	case 4 :
	    shift(t1,t2);
	    (head->y)++;
	    break;
	case 2:
	    shift(t1,t2);
	    (head->x)--;
	    break;
	case 3 :
         shift(t1,t2);
	     (head->x)++;
	    break;
	}
	if (head->x == fruit.x && head->y == fruit.y)  //if snake's head and fruit position mathces....add a new node to the snake
	{
	    struct node *nn=create();
	    nn->x=r1->x;
	    nn->y=r1->y;
	    s=head;
	    while(s->next!=NULL)
	     { s=s->next;
	     }
	      s->next=nn;
	      tail=nn;
	      tail->next=NULL;

	    score += 100;

	    fruit.x = rand() % width;
	    fruit.y = rand() % height;

	}

   //If the sanke touches the wall....game over
	if (head->x > width-1 || head->x < 0 || head->y > height-1 || head->y < 0)
	    gameState = 0;

	current=head->next;
	while (current->next != NULL) {
	    if (head->x == current->x && head->y == current->y)
		gameState = 0;
	    current = current->next;
	}
    }




void Snake(){

    init();
    while (gameState) 
	{
	   draw();
       input();
       logic();
       delay(100);
	}
       printf("\n\t\t\t\tGAME OVER");
       gameState=1;
	getch();
    }
int main()
{
int ch=1;
while(ch)
{
 
 system("cls");
 
  Snake();
  system("cls");
  printf("Do u wannt to continue playing:\n[1]YES\n[0]NO\n");
  scanf("%d",&ch);

}
getch();
return 0;
}
