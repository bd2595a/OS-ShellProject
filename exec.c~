#include <stdio.h>
#include <elf.h>


int main()
{
	char elfFileName[99];
	while(elfFileName[0]!='e' && elfFileName[1] != 'x' && elfFileName[2] !='i')
	{
		
		scanf("%s",elfFileName);
		char elfFileContent[99999];
		printf("\n");//add a space for readability
		FILE* file = (FILE*) fopen(elfFileName, "r");//open the file
		if(file == NULL)
		{
			printf("FAILED %s \n", elfFileName);
		}
		else
		{
			int characterC = 0;//character from file
			int i=0;
			while(i<100)
			{
				characterC = fgetc(file);//get a char from the file
				if(characterC != EOF)//if it's not end of file, print it
				{
					elfFileContent[i]= characterC;
					//printf("%x", elfFileContent[i]);
					i++;
				}
				else
				{
					elfFileContent[i]='\0';//close it so that it doesn't break
					//printf("%x",elfFileContent[i]);
					//fclose(file);
					break;
				}
			
			}
		}
		if(elfFileContent[0]==0x7f && elfFileContent[1]==0x45 && elfFileContent[2]==0x4c && elfFileContent[3]==0x46)
			{
			printf("Elf file\n");
			int counter = 4;
			//value comes in as two hex, which are flipped
			char hexStore[10];//something to store the hex values as a string since it's too big
			sprintf(hexStore,"%hhx",elfFileContent[41]);
			sprintf(hexStore,"%s%hhx",hexStore,elfFileContent[40]);					
			int sectionStart=(int)strtol(hexStore,NULL,16);
			printf("section start: %i\n",sectionStart);
			for(sectionStart;sectionStart<(4724);sectionStart++)
			{
				printf("%hhx", elfFileContent[sectionStart]);
			}
			/*
			for(counter; counter<100; counter++)
			{
				if(counter==4 && elfFileContent[counter]==2)
				{
					printf("\n3 architecture = 64 bit");
				}
				if(counter==5 && elfFileContent[counter]==1)
				{
					printf("\n4 little-endian",elfFileContent[counter]);
				}
				if(counter==6 && elfFileContent[counter]==1)
				{
					printf("\n5 current version");
				}
				if(counter==7 && elfFileContent[counter]==0)
				{
					printf("\n6 operating system");
				}
				if(counter==8 && elfFileContent[counter]==0)
				{
					printf("\n7 version of ABI");
				}
				if(counter>8 && counter <16)//padding
				{
					continue;
				}
				if(counter==16 && elfFileContent[counter]==2)
				{
					printf("\n15 executable");
				}
				if(counter==17 && elfFileContent[counter]==0)
				{
					printf("\n16 extra 0?");
				}
				if(counter==18 && elfFileContent[counter]==0x3e)
				{
					printf("\n17 AMD x86-64");
				}
				if(counter==19)
				{
					printf("\n18 version: %x",elfFileContent[counter]);
				}
				if(counter==20)
				{
					printf("%x",elfFileContent[counter]);
				}
				if(counter>20 && counter <24)//3 sets of extra 0s
				{
					continue;
				}
				if(counter==24)
				{
					printf("\n19 address of entry: %hhx", elfFileContent[counter]);//because its unsigned but C is trying to make it the same size as an int, it casts the upper bits as ffff, so hh gets rid of that
				}
				if(counter>24 && counter <27)
				{
					printf(" %x",elfFileContent[counter]);
				}
				if(counter>27 && counter <32)//magic 0's
				{
					continue;
				}
				if(counter == 32)
				{
					printf("\n20 header start: %d",elfFileContent[counter]);
				}
				if(counter >32 && counter <40)
				{
					continue; //flag bytes
				}
				
				if(counter==40)
				{	//value comes in as two hex, which are flipped
					char hexStore[10];//something to store the hex values as a string since it's too big
					sprintf(hexStore,"%hhx",elfFileContent[41]);
					sprintf(hexStore,"%s%hhx",hexStore,elfFileContent[40]);					
					int hexInt=(int)strtol(hexStore,NULL,0);
					printf("\n21 section start: %i",hexInt);
				}
				if(counter>41 && counter <52)//flags
				{
					continue; 
				}
				if(counter==52)//after this there are 00 for spacing, or 2 hex numbers if a number is bigger
				{
					printf("\n22 size of this header: %i",elfFileContent[counter]);
				}
				if(counter==54)
				{
					printf("\n23 size of program headers : %i",elfFileContent[counter]);
				}
				if(counter==56)
				{
					printf("\n24 Number of program headers : %i",elfFileContent[counter]);
				}
				if(counter==58)
				{
					printf("\n25 size of section headers : %i",elfFileContent[counter]);
				
				}
				if(counter==60)
				{
					printf("\n26 Number of section headers : %i",elfFileContent[counter]);
				}
				if(counter==62)
				{
				printf("\n27 section header string table index : %i",elfFileContent[counter]);
				}
			}	*/	
		}
	}
	return 0;
}
