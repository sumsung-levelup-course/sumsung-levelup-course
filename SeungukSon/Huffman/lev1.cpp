#define MAX_TEXT_LENGTH 5000

char inText[MAX_TEXT_LENGTH + 1];
void Initialize()
{
	return;
}

void setText(const char text[MAX_TEXT_LENGTH + 1])
{
	int i = 0;
	for (; i < MAX_TEXT_LENGTH + 1; i++)
	{
		if (text[i] != 0) inText[i] = text[i];
		else break;
	}
	inText[i] = 0;
	return;
}

unsigned int getCount(char ch)
{
	unsigned int ret = 0;
	int i = 0;
	while (inText[i])
	{
		if (inText[i] == ch) ret++;
		i++;
	}

	return ret;
}