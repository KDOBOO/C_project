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

	printf("fileA = ");          // fileA�� �� 16������ ���
	for (i = 0; i < size; i++)
	{
		fileA[i] = fgetc(fp);
		printf("0x%02X ", fileA[i]);
	}
	printf("\n\n");

	for (i = 0; i < size; i++)     // checksum code ����
	{
		checksum = checksum + fileA[i];
	}
	checksum = ~checksum + 1;
	printf("checksum code = 0x%02X\n\n", checksum);

	for (i = 0; i < size; i++)    // checksum code�� ������ fileB ����
	{
		fileB[i] = fileA[i];
	}
	fileB[size] = checksum;

	printf("fileB = ");            // fileB�� �� 16������ ���
	for (i = 0; i < size + 1; i++)
	{
		printf("0x%02X ", fileB[i]);
	}
	printf("\n\n");

	for (i = 0; i < size + 1; i++)     // fileB �� checksum code ��� �� ����� ���
	{
		fileBsum = fileBsum + fileB[i];
	}
	printf("����B�� ���� checksum code ��� ����� = 0x%02X", fileBsum);

	if (fileBsum == 0x00)          // fileB �� checksum code ��갪�� ���� �����Ǵ�
	{                              // ������ ��� checksum code ���� �� ���ϻ���, �����ϰ�� ���α׷� ����
		printf("   ����!!\n\n");
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
		printf("   �����߻�!!\n\n");
		return 0;
	}

	printf("fileA = ");            // fileC�� ���� fileA�� �� ��
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
		printf("fileA�� fileB�� ����!");
	printf("\n\n");

	fileB[size - 5] = 0xFF;     // ���������� fileB�� ������ ����
	fileB[size - 9] = 0xFF;

	for (i = 0; i < size + 1; i++)     // fileB �� checksum code ��� �� ����� ���
	{
		fileBsum = fileBsum + fileB[i];
	}
	printf("����B�� ���� checksum code ��� ����� = 0x%02X", fileBsum);

	if (fileBsum == 0x00)          // fileB �� checksum code ��갪�� ���� �����Ǵ�
	{                              // ������ ��� checksum code ���� �� ���ϻ���, �����ϰ�� ���α׷� ����
		printf("   ����!!\n\n");
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
		printf("   �����߻�!!\n\n");
		return 0;
	}
}
