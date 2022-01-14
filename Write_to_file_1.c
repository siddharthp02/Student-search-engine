#include<stdio.h>
#include<stdlib.h>

struct studentinfo
{
	char *SRN;
	char *Name;
	char *SGPA;
	char *club;
	char *bg;
	char *vaccine;
	struct studentinfo *next;
};


typedef struct studentinfo sinfo;
sinfo *head = (sinfo *)NULL;

int getstring(char *s, int maxlength)
{	
	int count = 0;
	char c;
	while((c = getchar()) != '\n' && c != EOF && count < maxlength)
	{
		*s++ = c;
		count++;
	}
	*s = '\0';

	return count + 1;
}

int write_to_file()
{
	const char *null = "NULL";
	FILE *fp;
	char input[100];
	int lettercount, flag = 1;
	if((fp = fopen("Student Data.txt", "a")) == (FILE *)NULL) 
	{
		printf("Error opening the file.\n");
		return -1;
	}
	else
	{
		printf("File opened successfully.\n");
	}
	while(flag)
	{
		
		printf("\nEnter the following details - ");
		printf("\nEnter the SRN of the student - ");
		
		if((lettercount = getstring(input, 13)) == 1)
		{
			fprintf(fp, "%-13s", null);
		}
		else
		{
			fprintf(fp, "%-13s", input);
		}

		fflush(stdin);

		printf("\nEnter the name of the student - ");
		if((lettercount = getstring(input, 100)) == 1)
		{
			fprintf(fp, "%-100s", null);
		}
		else
		{
			fprintf(fp, "%-100s", input);
		}
		
		fflush(stdin);

		printf("\nEnter the previous semester gpa of the student - ");
		if((lettercount = getstring(input, 4)) == 1)
		{
			fprintf(fp, "%-4s", null);
		}
		else
		{
			fprintf(fp, "%-4s", input);
		}
		
		fflush(stdin);

		printf("\nEnter the club in which the student belongs to - ");
		if((lettercount = getstring(input, 30)) == 1)
		{
			fprintf(fp, "%-30s", null);
		}
		else
		{
			fprintf(fp, "%-30s", input);
		}

		fflush(stdin);

		printf("\nEnter the blood group of the student - ");
		if((lettercount = getstring(input, 4)) == 1)
		{
			fprintf(fp, "%-4s", null);
		}
		else
		{
			fprintf(fp, "%-4s", input);
		}

		fflush(stdin);

		printf("\nEnter if the student has been vaccinated or not - ");
		if((lettercount = getstring(input , 4)) == 1)
		{
			fprintf(fp , "%-4s", null);
		}
		else
		{
			fprintf(fp, "%-4s", input);
		}
		
		fflush(stdin);

		printf("\nEnter 1 if more entries are there and 0 if you want to stop the entry - ");
		{
			scanf("%d", &flag);
			getchar();											//To remove newline from buffer
			if(flag != 1 && flag != 0)
			{
				printf("\nInvalid input, entries are stopping...");
				flag = 0;
			}
		}
	}

	printf("\nStopping to take input and closing the file.");
	fclose(fp);
	return 0;
}

char *putstring(char *p, FILE *fp,int maxlength)
{
	char *tp = p;
	while(--maxlength)
	{
		 fscanf(fp, "%c", tp);
		 tp++;
	}
	*tp = '\0';
	return p;
}
int read_from_file_and_print()
{
	sinfo *p = head;
	FILE *fp, *fpr;
	int length;
	char a[101];
	int i = 100;
	if((fp = fopen("Student Data.txt", "r")) == (FILE *)NULL) 
	{
		printf("Error opening the file.\n");
		return -1;
	}
	else
	{
		printf("\nFile opened successfully.\n");
	}
	if((fpr = fopen("Test Read.txt", "w")) == (FILE *)NULL) 
	{
		printf("Error opening the file.\n");
		return -1;
	}
	else
	{
		printf("\nFile opened successfully.\n");
	}

	int count1 = 1;
	while(i--)
	{
		//if(p == (sinfo *)NULL)
		{
			
			//p = (sinfo *)malloc(sizeof(sinfo));
			printf("NO.%d:\n",count1);
			
			putstring(a, fp, 14);
			printf("\tSRN: %s\n",a);
			fprintf(fpr,"%s", a);
			
			putstring(a, fp, 101);
			printf("\tName: %s\n",a);
			fprintf(fpr,"%s", a);
            
			putstring(a, fp, 5);
			printf("\tSgpa: %s\n",a);
			fprintf(fpr,"%s", a);
			
			putstring(a, fp, 31);
			printf("\tClub: %s\n",a);
			fprintf(fpr,"%s", a);

			putstring(a, fp, 5);
			printf("\tBlood group: %s\n",a);
			fprintf(fpr, "%s", a);

			putstring(a, fp, 5);
			printf("\tvaccinated: %s\n",a);
			fprintf(fpr, "%s", a);
					
			
			
			
			
			//p -> next = (sinfo *)NULL;
			//p = (sinfo *)NULL;           //temporary stuff
		}
		count1++;
	}
	fclose(fp);
	fclose(fpr);
	return 0;

}


int main()
{
	int flag, pflag;
	flag = write_to_file();
	if(flag != 0)
	{
		printf("\nProgram didn't work properly");
	}
	else
	{
		printf("\nThe program worked properly");
	}
	pflag = read_from_file_and_print();
	if(pflag != 0)
	{
		printf("\nPrint didn't work properly");
	}
	else
	{
		printf("\nThe print worked properly");
	}
	return 0;
}
