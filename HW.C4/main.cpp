#include <string>

using Sequence = std::string;

int main(void)
{
	Sequence a;
	auto b = a.begin();
	return 0;
}

int LengthOfLCS_Recursive(Sequence& seq1, int pos1, Sequence seq2, int pos2)
{
	if (pos1 == -1 || pos2 == -1)
		return 0;
	auto minValue = 0;
	if (seq1[pos1] == seq2[pos2])
		minValue =  1 + LengthOfLCS_Recursive(seq1, pos1 - 1, seq2, pos2 - 1);
	else
	{
		auto result1 = LengthOfLCS_Recursive(seq1, pos1 - 1, seq2, pos2);
		auto result2 = LengthOfLCS_Recursive(seq1, pos1, seq2, pos2-1);
	}
	return minValue;
}

// maxTable은 -1로 초기화 되어있어야 한다.
int LengthOfLCS_Memo(Sequence& seq1, int pos1, Sequence seq2, int pos2,int** maxTable)
{
	if (pos1 == -1 || pos2 == -1)
		return 0;
	
	if (maxTable[pos1][pos2] != -1)
		return maxTable[pos1][pos2];

	auto minValue = 0;
	if (seq1[pos1] == seq2[pos2])
		minValue = 1 + LengthOfLCS_Memo(seq1, pos1 - 1, seq2, pos2 - 1,maxTable);
	else
	{
		auto result1 = LengthOfLCS_Memo(seq1, pos1 - 1, seq2, pos2,maxTable);
		auto result2 = LengthOfLCS_Memo(seq1, pos1, seq2, pos2 - 1,maxTable);
	}
	maxTable[pos1][pos2] = minValue;
	return minValue;
}

int LengthOfLCS_BottomUp(Sequence& seq1, Sequence& seq2, int** maxTable)
{
	// maxTable은 seq1.length+1 * seq2.length+1 크기의 배열이다.
	for (auto i = 0; i <= seq1.length(); ++i)
		maxTable[i][0] = 0;
	for (auto i = 0; i <= seq2.length(); ++i)
		maxTable[0][i] = 0;

	for (auto i = 1; i <= seq1.length(); ++i)
	{
		for (auto j = 1; j <= seq2.length(); ++j)
		{
			// 내가 같으면 지금꺼를 이전꺼+1로 바꾼다
			if (seq1[i - 1] == seq2[i - 1])
				maxTable[i][j] = maxTable[i - 1][j - 1] + 1;
			// 내가 다르면 지금꺼를 이전꺼랑 내꺼 섞은거 두개중에 하나로 바꾼다.
			else
			{
				auto result1 = maxTable[i - 1][j];
				auto result2 = maxTable[i][j - 1];
				if (result1 > result2)
					maxTable[i][j] = result1;
				else
					maxTable[i][j] = result2;
			}
		}
	}
	return maxTable[seq1.length()][seq2.length()];
}