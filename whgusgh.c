#include<stdio.h>
#include<iostream>
#include<fstream>
#define size 11

using namespace std;

int main()
{
	FILE *fp = fopen("input.txt", "r");
	unsigned char i, checksum = 0, fileBsum = 0, count = 0;
	unsigned char fileA[size], fileB[size + 1], fileC[size];
	ofstream output;

	printf("fileA = ");          // fileA의 값 16진수로 출력
	for (i = 0; i < size; i++)
	{
		fileA[i] = fgetc(fp);
		printf("0x%02X ", fileA[i]);
	}
	printf("\n\n");

	for (i = 0; i < size; i++)     // checksum code 생성
	{
		checksum = checksum + fileA[i];
	}
	checksum = ~checksum + 1;
	printf("checksum code = 0x%02X\n\n", checksum);

	for (i = 0; i < size; i++)    // checksum code를 포함한 fileB 생성
	{
		fileB[i] = fileA[i];
	}
	fileB[size] = checksum;

	printf("fileB = ");            // fileB의 값 16진수로 출력
	for (i = 0; i < size + 1; i++)
	{
		printf("0x%02X ", fileB[i]);
	}
	printf("\n\n");

	for (i = 0; i < size + 1; i++)     // fileB 와 checksum code 계산 및 결과값 출력
	{
		fileBsum = fileBsum + fileB[i];
	}
	printf("파일B에 대한 checksum code 계산 결과값 = 0x%02X", fileBsum);

	if (fileBsum == 0x00)          // fileB 와 checksum code 계산값에 대한 에러판단
	{                              // 정상일 경우 checksum code 제거 후 파일생성, 에러일경우 프로그램 종료
		printf("   정상!!\n\n");
		for (i = 0; i < size; i++)
		{
			fileC[i] = fileB[i];
		}

		output.open("output.txt");
		for (i = 0; i < size; i++)
		{
			output << fileC[i];
		}
		output.close();
	}
	else
	{
		printf("   에러발생!!\n\n");
		return 0;
	}

	printf("fileA = ");            // fileC의 값과 fileA의 값 비교
	for (i = 0; i < size; i++)
	{
		printf("0x%02X ", fileA[i]);
	}
	printf("\n");
	printf("fileC = ");
	for (i = 0; i < size; i++)
	{
		printf("0x%02X ", fileC[i]);
	}
	printf("\n");
	for (i = 0; i < size; i++)
	{
		if (fileA[i] == fileC[i])
			count++;
	}
	if (count == size)
		printf("fileA와 fileB는 같다!");
	printf("\n\n");

	fileB[size - 5] = 0xFF;     // 인위적으로 fileB의 내용을 변경
	fileB[size - 9] = 0xFF;

	for (i = 0; i < size + 1; i++)     // fileB 와 checksum code 계산 및 결과값 출력
	{
		fileBsum = fileBsum + fileB[i];
	}
	printf("파일B에 대한 checksum code 계산 결과값 = 0x%02X", fileBsum);

	if (fileBsum == 0x00)          // fileB 와 checksum code 계산값에 대한 에러판단
	{                              // 정상일 경우 checksum code 제거 후 파일생성, 에러일경우 프로그램 종료
		printf("   정상!!\n\n");
		for (i = 0; i < size; i++)
		{
			fileC[i] = fileB[i];
		}

		output.open("output.txt");
		for (i = 0; i < size; i++)
		{
			output << fileC[i];
		}
		output.close();
	}
	else
	{
		printf("   에러발생!!\n\n");
		return 0;
	}
}
