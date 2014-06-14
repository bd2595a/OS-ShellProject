#include <stdio.h>
#include <elf.h>
#define ANSI_COLOR_CYAN    "\x1b[36m" //color for cyan
#define ANSI_COLOR_RED     "\x1b[31m"//color for red
#define ANSI_COLOR_RESET   "\x1b[0m" //reset the color back to white.

main()
{
	CommandShell();
	return 0;
}

int CommandShell(char* input)
{
	int pid;//process id
	while(shellinput[0] != 'e' || shellinput[1] != 'x' && shellinput[2] != 'i' && shellinput[3] != 't')//if they type exit, exit
	{
		shellinput[0]='\0';//clear it
		printf(ANSI_COLOR_CYAN "\nPlease enter a command:" ANSI_COLOR_RESET "\n");
		scanf("%99[^\n]%*c", shellinput);//read in all of the characters until there is a new line
		if(shellinput[0] == 't' && shellinput[1] == 'y' && shellinput[2] == 'p' && shellinput[3] == 'e' && shellinput[4] == ' ')//type
		{
			int counter = 5;//set to 5 cause the first 5 characters of shell input is 'type '
			char typeFilename[45];//file name of file we want to open			
			char typeFileContent[1];//contents of file we want to open. stores only 1 char because we print it out 1 char at a time, and if we 									//don't save it , it complains
			
			//clear the file name in case it's been used
			int j;
			for(j=0;j<45;j++)
			{
				typeFilename[j]='\0';
			}
			
			//read in the file name
			while(shellinput[counter] != '\n' && shellinput[counter] != '\0' && shellinput[counter] != '\r')
			{
				typeFilename[counter-5]=shellinput[counter];
				counter++;
			} 
			typeFilename[counter-5] = '\0';//close the string 

			FILE* file = (FILE*) fopen(typeFilename, "r");//open the file
			if(file == NULL)//file doesn't exist
			{
	 			printf( ANSI_COLOR_RED "\nFile '%s' does not exist" ANSI_COLOR_RESET "\n", typeFilename); 
			} 
			else//read it!
			{ 
				int characterC = 0;//character from file
				printf("\n");//add a space for readability
				while(1) //EOF = -1
				{
					characterC = fgetc(file);//get a char from the file
					if(characterC != EOF)//if it's not end of file, print it
					{
						typeFileContent[0]=(char) characterC;
						printf("%c", typeFileContent[0]);
					}
					else
					{
						typeFileContent[0]='\0';//close it so that it doesn't break
						break;
					}
				}
			} 
		}
		else if(shellinput[0]=='c' && shellinput[1] == 'o' && shellinput[2] == 'p' && shellinput[3] == 'y' && shellinput[4] == ' ')//copy
		{
			int counter = 5;//counter is basically the index after 'copy '
			int letterCount=0;
			char firstFileName[100];//first file
			char secondFileName[100];//second file
			
			//make sure this clears
			int j;
			for(j=0;j<100;j++)
			{
				firstFileName[j]='\0';
			}	
			
			//while we haven't reached a space/end of line
			while((shellinput[counter] != '\n'&& shellinput[counter] != '\0'&& shellinput[counter] != '\r')&& shellinput[counter] != ' ') 
			{
				firstFileName[letterCount]=shellinput[counter];
				letterCount++;
				counter++;
			} 
			firstFileName[letterCount]='\0';//end the first file name
			counter++;//move past the space
			letterCount=0;//variable to set secondFileName's index
			
			for(j=0;j<100;j++)//just in case this doesn't clear like it likes to do randomly
			{
				secondFileName[j]='\0';
			}	
			
			//read in the second file name
			while((shellinput[counter] != '\n'&& shellinput[counter] != '\0'&& shellinput[counter] != '\r')&& shellinput[counter] != ' ') 
			{	
				secondFileName[letterCount]=shellinput[counter];
				letterCount++;
				counter++;
			} 
			secondFileName[letterCount]='\0';			
			
			FILE* fileToCopyFrom = (FILE*) fopen(firstFileName, "r");//open the first file to copy from
			if(fileToCopyFrom==NULL)//make sure we have a file to copy from
			{
				printf( ANSI_COLOR_RED "\nFile '%s' does not exist" ANSI_COLOR_RESET"\n",firstFileName);
			}
			
			else if(letterCount==0)//if we don't have a second file, since we never even read in 1 character in the previous while loop
			{
				printf( ANSI_COLOR_RED "\n A second file name is needed to copy the first one into" ANSI_COLOR_RESET"\n");
			}
			else//copy the file!
			{
				FILE* fileToMake = (FILE*) fopen(secondFileName, "w"); //"w" creates the file as well as writes to it
				char chr = fgetc(fileToCopyFrom);//get the char
				while(chr != EOF && chr != '\0') //while we haven't reached the end of file
				{
					fputc(chr,fileToMake);	//copy the character
					chr = fgetc(fileToCopyFrom); //get a new character
				}
				
				fclose(fileToMake); //close the file like good people do
				fclose(fileToCopyFrom); //close the other file we used
				printf(ANSI_COLOR_CYAN "%s has been copied into %s"ANSI_COLOR_RESET "\n", firstFileName, secondFileName);	//user should know something happened
			}	
		}
		
		//remove
		else if(shellinput[0]=='r' && shellinput[1]=='e' && shellinput[2] =='m' && shellinput[3]=='o' && shellinput[4]=='v' && shellinput[5]=='e' && shellinput[6]==' ')
		{
			int counter = 7; //we want 7 spaces after 'remove '
			char removeFileName[99];
			int i=0;
			for(i;i<99;i++)//clear it
			{
				removeFileName[i]='\0';
			}
			//while we haven't reached a space/end of line
			while((shellinput[counter] != '\n'&& shellinput[counter] != '\0'&& shellinput[counter] != '\r')&& shellinput[counter] != ' ') 
			{
				removeFileName[counter-7]=shellinput[counter];
				counter++;
			}
			removeFileName[counter-7]='\0';
			int success=remove(removeFileName);
			if(success == 0)
			{
				printf(ANSI_COLOR_CYAN "\nFile '%s' was deleted sucessfully" ANSI_COLOR_RESET "\n",removeFileName);
			}
		    else
			{
				printf( ANSI_COLOR_RED "\nFile '%s' does not exist" ANSI_COLOR_RESET"\n",removeFileName);
   			}
		}
		
		//elf headers
		else if(shellinput[0]=='e' && shellinput[1] =='l' && shellinput[2] =='f' && shellinput[3] ==' ')
		{
			//objdump -x hi.o
			char elfFileName[999];
			char elfFileContent[99999];
			int counter=4;
			while((shellinput[counter] != '\n'&& shellinput[counter] != '\0'&& shellinput[counter] != '\r')&& shellinput[counter] != ' ') 
			{
				elfFileName[counter-4]=shellinput[counter];
				counter++;
			}
			elfFileName[counter-4]='\0';
			FILE* elfFile = (FILE*) fopen(elfFileName, "r");//open the file
			if(elfFile == NULL)
			{
				printf( ANSI_COLOR_RED "\nFile '%s' does not exist" ANSI_COLOR_RESET"\n",elfFileName);
			}
			else
			{
				int characterC = 0;//character from file
				int i=0;
				while(i<100)
				{
					characterC = fgetc(elfFile);//get a char from the file
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
		
				if(elfFileContent[0]==0x7f && elfFileContent[1]==0x45 && elfFileContent[2]==0x4c && elfFileContent[3]==0x46)
				{
					int counter = 4;
					//value comes in as two hex, which are flipped
					char hexStore[10];//something to store the hex values as a string since it's too big
					sprintf(hexStore,"%hhx",elfFileContent[41]);
					sprintf(hexStore,"%s%hhx",hexStore,elfFileContent[40]);					
					int sectionStart=(int)strtol(hexStore,NULL,16);
					printf("section start: %i\n",sectionStart);
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
		}
		else
		{	
			char command[99];
			char argument1[99];
			char argument2[99];
			char argument3[99];
			char argument4[99];
			char* args[6];
			if(shellinput[0] != '.' && shellinput[1] != '/')
			{	
				
				int counter=0;
				while(shellinput[counter] != ' ' && shellinput[counter] != '\n' && shellinput[counter] != '\0' && shellinput[counter] != 					'\r')
				{
					command[counter]=shellinput[counter];
					counter++;
				}
				command[counter]='\0';
				if(shellinput[counter]=='\n' || shellinput[counter]=='\0' )//no more arguments
				{
					args[0]=command;
					args[1]=NULL;
				}
				else//at least 1 more argument
				{
					
					int argument1Counter=0;
					counter++;
					while(shellinput[counter] != ' ' && shellinput[counter] != '\n' && shellinput[counter] != '\0' && shellinput[counter] != 					'\r')
					{
						argument1[argument1Counter]=shellinput[counter];
						counter++;
						argument1Counter++;
					}
					argument1[counter]='\0';
					if(shellinput[counter]=='\n' || shellinput[counter]=='\0' )//no more arguments
					{
						args[0]=command;
						args[1]=argument1;
						args[2]=NULL;
					}
					else//there's two arguments
					{
						int argument2Counter=0;
						counter++;//get past the space
						while(shellinput[counter] != ' ' && shellinput[counter] != '\n' && shellinput[counter] != '\0' && shellinput[counter] != 					'\r')
						{
							argument2[argument2Counter]=shellinput[counter];
							counter++;
							argument2Counter++;
						}
						argument2[counter]='\0';
						if(shellinput[counter]=='\n' || shellinput[counter]=='\0' )//no more arguments
						{
							args[0]=command;
							args[1]=argument1;
							args[2]=argument2;
							args[3]=NULL;
						}
						
						else//3 arguments.
						{
							int argument3Counter=0;
							counter++;//get past the space
							while(shellinput[counter] != ' ' && shellinput[counter] != '\n' && shellinput[counter] != '\0' && shellinput[counter] != 					'\r')
							{
								argument3[argument3Counter]=shellinput[counter];
								counter++;
								argument3Counter++;
							}
							argument2[counter]='\0';
							if(shellinput[counter]=='\n' || shellinput[counter]=='\0' )//no more arguments
							{
								args[0]=command;
								args[1]=argument1;
								args[2]=argument2;
								args[3]=argument3;
								args[4]=NULL;
							}
						}
					}
				}
			}
			else
			{
			args[0]=shellinput;
			args[1]=NULL;
			}
			
			
			pid=fork();
			if(pid==0)
			{
				execvp(args[0],args);
			}
			else
			{
				waitpid(pid);	
			}
		}
	}
	if(pid!=0)//make sure to only exit if you're the right process
	{
		printf(ANSI_COLOR_CYAN "\n Good Bye \n" ANSI_COLOR_RESET);
	}
}
