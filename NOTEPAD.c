#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int passoword();
void content();
int previous();
int delete();
int edit();

struct notepad
{
    char inputpass[50];
    char savedpass[50];
    char content[500];
    char date[100];
    char sdate[100];
    char ncontent[500];
    char ndate[100];

};

int main()
{
        passoword();

        printf("--NOTEPAD--");
        printf("\nwhat do you prefer to do?\n1.Entry content\n2.show previous contents\n3.delete entry\n4.edit\n5.exit\n");

        while(1)
        {
            int choice;
            printf("\nEnter your choice:");
            scanf("%d", &choice);
            getchar();

            switch(choice)
            {
                case 1:
                    content();
                    break;
                case 2:
                    previous();
                    break;
                case 3:
                    delete();
                    break;
                case 4:
                    edit();
                    break;
                case 5:
                    return 0;

                default:
                    printf("invalid choice number");
            }

        }

        return 0;
}

int passoword()
{
        FILE *fp;
        fp = fopen("password.txt","r");

        struct notepad spass,ipass;

        if(fp == NULL)
       {
            printf("Create password for your notepad:");
            scanf("%s",spass.savedpass);

            fp = fopen("password.txt","w");
            fprintf(fp,"%s",spass.savedpass);
            fclose(fp);

            printf("password saved! restart the program");
            exit(0);
       }

        fscanf(fp,"%s",spass.savedpass);
        fclose(fp);

        int attempts=3;

        while(attempts>0)
        {
            printf("enter notepad passoword: ");
            scanf("%s",ipass.inputpass);

            if(strcmp(spass.savedpass,ipass.inputpass)==0)
            {
                printf("\nAccess granted!\n");
                return 0;
            }
            else
            {
                attempts--;
                printf("attempts left: %d\n",attempts);
            }
        }
        printf("too many failed attempts. youve been locked out");
        exit(0);
}

void content()
{
        FILE *fp;
        fp = fopen("notepad.txt","a");

        struct notepad entry;

        printf("enter date:");
        fgets(entry.date,sizeof(entry.date),stdin);
        fprintf(fp,"Date: %s",entry.date);

        printf("enter content:");
        fgets(entry.content,sizeof(entry.content),stdin);
        fprintf(fp, "Content: %s",entry.content);

        fclose(fp);

        printf("SAVED!\n");
}

int previous()
{
       FILE *fp;
       fp = fopen("notepad.txt","r");

       if(fp == NULL)
       {
           printf("your notepad doesnt have any content\n");
           return 0;
       }

       char ch;
       while( (ch=fgetc(fp)) != EOF)
       {
           printf("%c",ch);
       }

       fclose(fp);

       return 0;

}

int delete()
{
       int found = 0;
       FILE *fp;
       fp = fopen("notepad.txt","r");

       FILE *temp;
       temp = fopen("temp.txt","w");

       if(fp == NULL)
       {
           printf("your notepad doesnt have any content\n");
           return 0;
       }

       struct notepad tempo,entry;

       printf("enter exact date of the content you want to delete:");
       fgets(tempo.sdate,sizeof(tempo.sdate),stdin);

       while(fgets(entry.date,sizeof(entry.date),fp)!=NULL)
       {
           fgets(entry.content,sizeof(entry.content),fp);

           if(strstr(entry.date,tempo.sdate)!=NULL)
           {
               printf("Entry found and deleted.\n");
               found = 1;
           }
           else
           {
               fprintf(temp, "%s", entry.date);
               fprintf(temp, "%s", entry.content);
           }
       }
       fclose(fp);
       fclose(temp);

       if(found)
       {
           remove("notepad.txt");
           rename("temp.txt","notepad.txt");
       }
       else
       {
           remove("temp.txt");
           printf("date not found\n");
       }

        return 0;
}

int edit()
{
       int found = 0;
       FILE *fp;
       fp = fopen("notepad.txt","r");

       FILE *temp;
       temp = fopen("temp.txt","w");

       if(fp == NULL)
       {
           printf("your notepad doesnt have any content\n");
           return 0;
       }

       struct notepad tempo,entry,ncontent,ndate;

       printf("enter exact date of the entry you want edit:");
       fgets(tempo.sdate,sizeof(tempo.sdate),stdin);

       while(fgets(entry.date,sizeof(entry.date),fp)!=NULL)
       {
           fgets(entry.content,sizeof(entry.content),fp);

           if(strstr(entry.date,tempo.sdate)!=NULL)
           {
               printf("Entry found. your old date & content was:\n %s %s",entry.date,entry.content);

               printf("enter new date:");
               fgets(entry.ndate,sizeof(entry.ndate),stdin);
               fprintf(temp, "date: %s",entry.ndate);

               printf("enter new content:");
               fgets(entry.ncontent,sizeof(entry.ncontent),stdin);
               fprintf(temp, "Content: %s",entry.ncontent);

               printf("notepad updated");
               found = 1;
           }
           else
           {
               fprintf(temp, "%s", entry.date);
               fprintf(temp, "%s", entry.content);
           }
       }
       fclose(fp);
       fclose(temp);

       if(found)
       {
           remove("notepad.txt");
           rename("temp.txt","notepad.txt");
       }
       else
       {
           remove("temp.txt");
           printf("date not found\n");
       }

        return 0;
}

