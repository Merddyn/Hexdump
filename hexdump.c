#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning(disable : 4996) // Coding this in Visual Studio, was necessary to make it not complain about fread being depracated.
// Coded in VS to simplify the testing process. ... Partly because PuTTY kept kicking me out.

/*
  Please note! This implementation includes printing the last partial line in ASCII, although
  that is skipped in the example output. I figured it was more useful to print this than to
  specifically NOT print it. However, there is a commented out if statement that will include
  this functionality if desired.
*/

/* Program Description: Displays the contents of a file in both hexadecimal and ASCII.
 * Author: Merddyn Sheeley	 EUID: rcs0215
 * Creation Date: 01/16/2020
 * Revisions:
 * Date:			Modified by:
 *
 * */

int main(int argc, char* argv[]) // Can alternatively use char **argv instead of *argv[]
{
	FILE* f;
	unsigned char i; // These are unsigned because isprint errored when it was signed.
	unsigned char ascii[17]; // +1 for null termination!
	unsigned int pos = 0;
	// printf("there are %d command line arguments.\n", argc);
	if (argc > 1)
	{
		f = fopen(argv[1], "r");
		if (f == NULL)
		{
			perror(argv[1]);
			printf("Error opening %s)\n", argv[1]);

			exit(1);
		}

	}
	else
	{
		exit(1);
	}
	/*
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	*/
	while (!feof(f))
	{
		pos = ftell(f); // Stores beginning read address.
		printf("%08x    ", pos); // Apparently, this errors on the CSE machines if not unsigned int.
		int j = 0; // Declared out of loop to access position later.
		for (; j < 16; j++)
		{
			if (!feof(f))
			{
				if (fread(&i, 1, 1, f) == 0)
				{
					break;
				}
				printf("%02x ", i);
				if (isprint(i))
				{
					ascii[j] = i;
				}
				else
				{
					ascii[j] = '.';
				}
			}
			else
			{
				break;
			}
		}
		ascii[j] = '\0'; // For future reference, putting "\0" here instead will drive you insane trying to figure out what's wrong with it.
		
		// If you want to make it NOT print the last line of ASCII, simply uncomment this if 
		// statement and the corresponding curly braces.
		// if (j == 16)
		// {

		printf("  |");
//		printf(ascii);
		for (int k = 0; (ascii[k] != '\0') && k < 16; k++)
		{
			printf("%c", ascii[k]); // %c formats as a character.

		}
		printf("|");
		// }
		printf("\n");
	}
	return 0;
}

