#include<stdio.h>
#define size 5 
void insert();  
void del();  
void display(); 
int front=-1,rear=-1; 
 int a[size];
void main()
{

 
 int choice;
  while(choice!=4)
  {
   printf("\n1.Insert\n2.delete\n3.display\n");
   printf("\nenter the choice\n");
   scanf("%d",&choice);
  switch(choice)
  {
   case 1:
       insert();
       break;
   case 2:
        del();
        break;
   case 3:      
        display();
        break;
   
   default:
         printf("\nenter valid choice\n");             
   } 
  }
}
void insert(int x)
 {
  int data;  
    printf("\nEnter the element\n");  
    scanf("\n%d",&data);      
    if(rear == size-1)  
    {  
        printf("\nOVERFLOW\n");  
         
    }  
    if(front == -1 && rear == -1)  
    {  
        front = 0;  
        rear = 0;  
    }  
    else   
    {  
        rear = rear+1;  
    }  
    a[rear] = data;  
    printf("\nValue inserted\n ");  
 }
void del()
   {
    if(front==-1 && rear==-1)
       {
         printf("\nQueue is empty\n");
       }
    else if(front==rear)
      {
       front=rear=-1;
      }
    else
      {
       printf("\n%d\n",a[front]);
       front ++;
      }
   }
void display()
   {
     int i;
    if(front==-1 && rear==-1)
     {
      printf("\nQueue is empty\n");
     }
   else 
    {
    for(i=front;i<rear+1;i++)
       {
         printf("\n%d\n",a[i]);
       }  
    }
   }
