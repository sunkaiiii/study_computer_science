/*films2.c -- 使用链表*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TSIZE 45

struct film
{
    char title[TSIZE];
    int rating;
    struct file *next;
};

char *s_gets(char *st, int n);

int main(void)
{
    struct film *head=NULL;
    struct film *prev,*current;

    char input[TSIZE];

    puts("Enter first move title:");
    while(s_gets(input,TSIZE)!=NULL&&input[0]!='\0')
    {
        current=(struct file *)malloc(sizeof(struct film));
        if(head==NULL)
            head=current;
        else
            prev->next=current;
        current->next=NULL;
        strcpy(current->title,input);
        puts("Enter your rating <0-1)>:");
        scanf("%d",&current->rating);
        while(getchar()!='\n')
            continue;
        puts("Enter next movie title (empty line to stop):");
        prev=current;
    }
    if(head==NULL)
        printf("No data entered.");
    else
    {
        printf("Here is the move list:\n");
    }
    current=head;
    while (current!=NULL)
    {
        printf("move: %s Rating:%d\n",current->title,current->rating);
        current=current->next;
    }
    current=head;
    while(current!=NULL)
    {
        free(current);
        head=current->next;
    }
    printf("Bye!\n");

    return 0;
    
    
}

char* s_gets(char *st,int n)
{
    char *ret_val;
    int i=0;

    ret_val=fgets(st,n,stdin);
    if(ret_val)
    {
        while(st[i]!='\n'&&st[i]!='\0')
            i++;
        if(st[i]=='\n')
            st[i]='\0';
        else
            while(getchar()!='\n')
                continue;
    }
    return ret_val;
}