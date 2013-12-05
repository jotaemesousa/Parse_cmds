/*
 * main.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: joao
 */

// http://brnx.no-ip.com/snippets/1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum
{
	IDLE_State, CMD_ID_State, N_AGR_State, Parse_State
}ParseState;

int main(int argc, char **argv)
{
	char input;

	ParseState currentState = IDLE_State;

	while(1)
	{
		while(scanf("%c", &input))
		{
			printf("echo |%c|\n", input);

			switch (currentState)
			{
			case IDLE_State:

				if (input=='@')
				{
					currentState = CMD_ID_State;
				}
				break;






			default:
				break;
			}

		}
	}


	return 0;
}
