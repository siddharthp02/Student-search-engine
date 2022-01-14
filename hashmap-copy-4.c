#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define RECORD_SIZE 155
#define NAME_SIZE 100
#define SRN_SIZE 13
#define CGPA_SIZE 4
#define BG_SIZE 4
#define CLUB_SIZE 30
#define VACCINE_SIZE 4

int disp_count = 0;

struct student_node
{
	char SRN[14];
	int rec_no;
	struct student_node *next;
}*hash_array[100] = { (struct student_node *)NULL };

struct student_treenode
{
	char Name[101];
	char SRN[14];
	struct student_treenode *left;
	struct student_treenode *right;
}*root = (struct student_treenode *)NULL;




typedef struct student_node Snode;
typedef struct student_treenode STnode;

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

int hashfunction(char *SRN, FILE *fp)
{
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	int no_of_records = ftell(fp) / RECORD_SIZE;

	if(no_of_records >= 100)
	{
		int max_bucket_size = no_of_records / 100;
		return (atoi(SRN + 10) / max_bucket_size);
	}
	else
	{
		return (atoi(SRN + 10) / no_of_records);
	}
}

void add_to_map(char *SRN, int count, Snode **a, FILE *fp)
{
	int hashval = hashfunction(SRN, fp);

		Snode *temp = (Snode *)malloc(sizeof(Snode));
		strcpy(temp -> SRN, SRN);
		temp -> rec_no = count;
		temp -> next = (Snode *)NULL;

		if(a[hashval] == (Snode *) NULL)
		{
			a[hashval] = temp;
		}
		else
		{
			Snode *p = a[hashval];
			while(p -> next != (Snode *)NULL)
			{
				p = p -> next;
			}

			p -> next = temp; 
		}
}

STnode *add_to_tree(char *name, char *SRN, STnode *p)
{
	if(p == (STnode *)NULL)
	{
		STnode *temp = (STnode *)malloc(sizeof(STnode));
		strcpy(temp -> Name, name);
		strcpy(temp -> SRN, SRN);
		temp -> left = (STnode *)NULL;
		temp -> right = (STnode *)NULL;
		p = temp;
	}
	else if(strcmp(name,p -> Name) < 0)
	{
		p -> left = add_to_tree(name, SRN, p -> left);
	}
	else
	{
		p -> right = add_to_tree(name, SRN, p -> right);
	}

	return p;
}

void create_map_and_tree(FILE *fp, Snode **a)
{
	long int temp_current = 0;
	int count = 0;
	char SRN[14];
	char stud_name[101];

	rewind(fp);
	fseek(fp, 0, SEEK_END);

	while(temp_current != ftell(fp))						//Check if EOF is reached since fp is set to end of the file
	{
		fseek(fp, temp_current, SEEK_SET);

		putstring(SRN, fp, 14);
		putstring(stud_name,fp, 101);
		
		add_to_map(SRN, count, a, fp);
		root = add_to_tree(stud_name, SRN, root);

		fseek(fp, (count + 1) * RECORD_SIZE , SEEK_SET);	//Getting the file pointer to just before the next record starts
		temp_current = ftell(fp);				//Storing this byte info in a temp variable
		count++;
		fseek(fp, 0, SEEK_END);					//To check if EOF is reached int the while test condition we put fp to the end of the file
	}
	return;
}

void display(char *data)
{
	char *copy = data;

	disp_count++;

	for(int i = 0; i < 13; i++)
	{
		putchar(*copy++);
	}
	printf("  ");
	for(int i = 0; i < 100; i++)
	{
		putchar(*copy++);
	}
	printf("  ");
	for(int i = 0; i < 4; i++)
	{
		putchar(*copy++);
	}
	printf("  ");
	for(int i = 0; i< 30; i++)
	{
		putchar(*copy++);
	}
	for(int i = 0; i < 4; i++)
	{
		putchar(*copy++);
	}
	for(int i = 0; i < 4; i++)
	{
		putchar(*copy++);
	}
	printf("\n");
	return;
}


void search_SRN(char *SRN, FILE *fp)
{
	char data[RECORD_SIZE + 1];
	rewind(fp);
	//char data[156];
	int hashval = hashfunction(SRN, fp);
	Snode *p = hash_array[hashval];
	while(p != (Snode *)NULL)
	{
		if(strcmp(p -> SRN, SRN) == 0)
		{
			fseek(fp, (p -> rec_no) * RECORD_SIZE, SEEK_SET);
			putstring(data, fp, RECORD_SIZE + 1);
			display(data);
			//printf("%s", data);
			return;
		}
		p = p -> next;
	}
	if(p == (Snode *)NULL)
	{
		printf("No such data present in the database\n");
	}
	return;
}

void search_name(char *name, STnode *p, int name_length,FILE *fp)
{
	if(p != (STnode *)NULL)
	{
		if(strncmp(name, p -> Name, name_length) == 0)
		{
			
			search_name(name, p -> left, name_length, fp);
			search_SRN(p -> SRN, fp);
			printf("\n");
			search_name(name, p -> right, name_length, fp);
		}
		else if(strncmp(name, p -> Name, name_length) < 0)
		{
			search_name(name, p -> left, name_length, fp);
		}
		else
		{
			search_name(name, p -> right, name_length, fp);
		}
	}

	return;
}



int main()
{
	FILE *fp = fopen("Student Data.txt","r");
	int flag = 1;
	char input[101];
	char *search_entry = input;	

	if(fp == (FILE *)NULL)
	{
		printf("The file could not be opened...");
		return 0;
	}
	else{
		printf("worked");
	}

	create_map_and_tree(fp, hash_array);

	//Temporary
	//char name[] = "SID";
	//search_name(name, root, strlen(name),fp);

	while(flag)
	{
		int c;
		printf("\nEnter a name or SRN to search or EOF to exit - ");
		while((c = getchar()) != EOF && c != '\n')
		{
			*search_entry++ = toupper(c);
		}
		*search_entry = '\0';

		if(c == EOF)
		{
			printf("\nExiting...");
			flag = 0;
		}
		else
		{
			printf("SRN            Name                                                                                                  SGPA  Club                          B/G Vaccinated\n\n");
			if(strncmp(input,"PES1",4) == 0 || strncmp(input, "PES2", 4) == 0 || strncmp(input, "PES3", 4) == 0)
			{
				search_SRN(input, fp);
			}
			else
			{
				search_name(input, root, strlen(input), fp);
			}
			if(disp_count == 0)
			{
				printf("\nNo results found...\n");
			}
		}
		search_entry = input;
		disp_count = 0;
	}

	fclose(fp);
	return 0;
}
