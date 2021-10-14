#define CONSOLE (*(unsigned char *)0x400000)

int printToTrace(char* input)
{
	int i=0;
	while(input[i] != '\0') {
		CONSOLE = input[i];
		i++;
	}
}

int main()
{
	printToTrace("hello world!");
	return 0;
}

