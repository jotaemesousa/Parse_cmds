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

#define DELIMITER_CHAR		','
#define END_CHAR			'e'

typedef enum
{
	IDLE_State, CMD_ID_State, N_ARG_State, Parse_State, Delimiter_State
}ParseState_Typedef;

typedef enum
{
	INVALID = '0', VELOCITY = '1', GPM = '2'
}Command_Typedef;

int main(int argc, char **argv)
{
	char input;

	int16_t tab[] = {0,0,0,0,0,0,0,0,0};

	ParseState_Typedef currentState = IDLE_State;
	int8_t n_arg = -1;
	Command_Typedef cmd;
	uint8_t arg_temp[10];
	uint8_t index_parse = 0;
	uint8_t var_index = 0;
	memset(arg_temp,0,10);

	while(1)
	{
		while(scanf("%c%*c", &input))
		{
			static int index_n_arg = 0;

			printf("echo |%c|\n", input);

			switch (currentState)
			{
			case IDLE_State:

				if (input=='@')
				{
					currentState = CMD_ID_State;
				}
				break;

			case CMD_ID_State:

				if(input >= VELOCITY && input <= GPM)
				{
					cmd = (Command_Typedef)input;
					currentState = N_ARG_State;
					index_n_arg = 0;
				}
				else
				{
					currentState = IDLE_State;
				}
				break;

			case N_ARG_State:

				if(index_n_arg < 1)
				{
					arg_temp[index_n_arg] = input;
					index_n_arg++;
				}
				else
				{
					arg_temp[index_n_arg] = input;
					arg_temp[2] = 0;


					n_arg = atoi((const char*)arg_temp);

					if(n_arg >= 0 && n_arg < 127)
					{
						currentState = Parse_State;
						index_parse = 0;
						var_index = 0;
					}
					else
					{
						currentState = IDLE_State;
					}
				}
				break;

			case Parse_State:

				switch (cmd)
				{

				case VELOCITY:
					if((input != DELIMITER_CHAR) && (input != END_CHAR))
					{
						arg_temp[index_parse] = input;
						index_parse++;
					}
					else
					{
						currentState = Delimiter_State;

						arg_temp[index_parse] = 0;
						tab[var_index] = atoi((const char*)arg_temp);
						index_parse = 0;
						var_index++;

						if(var_index >= n_arg && input == END_CHAR)
						{
							currentState = IDLE_State;
						}
						else
						{
							currentState = Parse_State;
						}
					}
					break;

				case GPM:

					break;
				default:
					currentState = IDLE_State;
					break;
				}

				break;


				default:
					currentState = IDLE_State;
					break;
			}
		}
	}

	return 0;
}
