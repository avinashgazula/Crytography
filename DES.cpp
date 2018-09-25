#include<bits/stdc++.h>
using namespace std;
int main()
{
	int i,j,k,l,m,n;
	int IP[8][8],InvP[8][8],E[8][6],P[4][8],PC1[8][7],PC2[6][8],S[8][4][16],LS[16],input[8][8],key[8][8];
	int output[8][8],temp[8][8],subkey1[8][7],subkey2[6][8];
	

	for(i=0;i<8;i++) for(j=0;j<8;j++) cin>>IP[i][j];
	for(i=0;i<8;i++) for(j=0;j<8;j++) cin>>InvP[i][j];
	for(i=0;i<8;i++) for(j=0;j<6;j++) cin>>E[i][j];
	for(i=0;i<4;i++) for(j=0;j<8;j++) cin>>P[i][j];
	for(i=0;i<8;i++) for(j=0;j<7;j++) cin>>PC1[i][j];
	for(i=0;i<6;i++) for(j=0;j<8;j++) cin>>PC2[i][j];
	for(i=0;i<8;i++) for(j=0;j<4;j++) for(k=0;k<16;k++) cin>>S[i][j][k];
	for(i=0;i<16;i++) cin>>LS[i];
	
	for(i=0;i<8;i++) for(j=0;j<8;j++) cin>>input[i][j];
	for(i=0;i<8;i++) for(j=0;j<8;j++) cin>>key[i][j];
	
	//ENCRYPTION ALGORITHM------------------------------------------------------------------------------------------
	cout<<"Plain Text:    ";for(i=0;i<8;i++) for(j=0;j<8;j++) cout<<input[i][j];cout<<endl;
	//Initial Permutation
	for(i=0;i<8;i++) for(j=0;j<8;j++) output[i][j]=input[(IP[i][j]-1)/8][(IP[i][j]-1)%8];
	//Permutation Choice-1
	for(i=0;i<8;i++) for(j=0;j<7;j++) subkey1[i][j]=key[(PC1[i][j]-1)/8][(PC1[i][j]-1)%8];
	//SubKeys Calculation
	int subkey3[16][6][8];
	for(int round=0;round<=15;round++)
	{
		int shift=LS[round];
		for(i=0;i<4;i++)
			for(j=0;j<7;j++)
		 	{
		 		int ind=(i*7+j+shift)%28;
		 		temp[i][j]=subkey1[ind/7][ind%7];
			}
		for(i=4;i<8;i++)
			for(j=0;j<7;j++)
			{
				int ind=((i-4)*7+j+shift)%28;
		 		temp[i][j]=subkey1[4+ind/7][ind%7];
			}
		for(i=0;i<8;i++) for(j=0;j<7;j++) subkey1[i][j]=temp[i][j];									//subkey-input for next round
		for(i=0;i<6;i++) for(j=0;j<8;j++) subkey2[i][j]=subkey1[(PC2[i][j]-1)/7][(PC2[i][j]-1)%7];  //subkey for current round
		for(i=0;i<6;i++) for(j=0;j<8;j++) subkey3[round][i][j]=subkey2[i][j];
	}
	//Rounds
	for(int round=0;round<=15;round++)
	{
		for(i=0;i<6;i++) for(j=0;j<8;j++) subkey2[i][j]=subkey3[round][i][j];
		
		//Expansion Function
		for(i=0;i<6;i++) 
			for(j=0;j<8;j++) 
			{
				int Erow=(i*8+j)/6,Ecol=(i*8+j)%6;
				int val=E[Erow][Ecol];
				temp[i][j]=output[4+(val-1)/8][(val-1)%8];
			}
		//XOR-Operation
		for(i=0;i<6;i++) for(j=0;j<8;j++) temp[i][j]^=subkey2[i][j];
		//SBox-Operations
		int row=0,col=0,temp1[4][8],Ptemp1[4][8],count=0;
		for(k=0;k<48;k+=6)
		{
			row=2*temp[k/8][k%8]+temp[(k+5)/8][(k+5)%8];
			col=8*temp[(k+1)/8][(k+1)%8]+4*temp[(k+2)/8][(k+2)%8]+2*temp[(k+3)/8][(k+3)%8]+temp[(k+4)/8][(k+4)%8];
			
			int val=S[k/6][row][col];
			for(i=0;i<4;i++,count++) 
				if(val&(1<<(3-i)))	temp1[count/8][count%8]=1;
				else 			    temp1[count/8][count%8]=0;
		}
		//Permutation 
		for(i=0;i<4;i++)
			for(j=0;j<8;j++)
			Ptemp1[i][j]=temp1[(P[i][j]-1)/8][(P[i][j]-1)%8];
		//XOR-Operation
		for(i=0;i<4;i++) for(j=0;j<8;j++) Ptemp1[i][j]^=output[i][j];
		//Rearranging
		for(i=0;i<4;i++) for(j=0;j<8;j++) output[i][j]=output[i+4][j];
		for(i=0;i<4;i++) for(j=0;j<8;j++) output[i+4][j]=Ptemp1[i][j];
	}
	//32-Bit Swap
	for(i=0;i<4;i++) for(j=0;j<8;j++) swap(output[i][j],output[i+4][j]);
	//Inverse Permutation
	for(i=0;i<8;i++) for(j=0;j<8;j++) temp[i][j]=output[(InvP[i][j]-1)/8][(InvP[i][j]-1)%8];
	for(i=0;i<8;i++) for(j=0;j<8;j++) output[i][j]=temp[i][j];
	cout<<"Encrypted Text:";for(i=0;i<8;i++) for(j=0;j<8;j++) cout<<output[i][j];cout<<endl;
	
	
	//DECRYPTION ALGORITHM------------------------------------------------------------------------------------------
	for(i=0;i<8;i++) for(j=0;j<8;j++) input[i][j]=output[i][j];
	
	//Initial Permutation
	for(i=0;i<8;i++) for(j=0;j<8;j++) output[i][j]=input[(IP[i][j]-1)/8][(IP[i][j]-1)%8];
	//Permutation Choice-1
	for(i=0;i<8;i++) for(j=0;j<7;j++) subkey1[i][j]=key[(PC1[i][j]-1)/8][(PC1[i][j]-1)%8];
	//SubKeys Calculation
	for(int round=0;round<=15;round++)
	{
		int shift=LS[round];
		for(i=0;i<4;i++)
			for(j=0;j<7;j++)
		 	{
		 		int ind=(i*7+j+shift)%28;
		 		temp[i][j]=subkey1[ind/7][ind%7];
			}
		for(i=4;i<8;i++)
			for(j=0;j<7;j++)
			{
				int ind=((i-4)*7+j+shift)%28;
		 		temp[i][j]=subkey1[4+ind/7][ind%7];
			}
		for(i=0;i<8;i++) for(j=0;j<7;j++) subkey1[i][j]=temp[i][j];									//subkey-input for next round
		for(i=0;i<6;i++) for(j=0;j<8;j++) subkey2[i][j]=subkey1[(PC2[i][j]-1)/7][(PC2[i][j]-1)%7];  //subkey for current round
		for(i=0;i<6;i++) for(j=0;j<8;j++) subkey3[round][i][j]=subkey2[i][j];
	}
	//Rounds
	for(int round=0;round<=15;round++)
	{
		for(i=0;i<6;i++) for(j=0;j<8;j++) subkey2[i][j]=subkey3[15-round][i][j];
		
		//Expansion Function
		for(i=0;i<6;i++) 
			for(j=0;j<8;j++) 
			{
				int Erow=(i*8+j)/6,Ecol=(i*8+j)%6;
				int val=E[Erow][Ecol];
				temp[i][j]=output[4+(val-1)/8][(val-1)%8];
			}
		//XOR-Operation
		for(i=0;i<6;i++) for(j=0;j<8;j++) temp[i][j]^=subkey2[i][j];
		//SBox-Operations
		int row=0,col=0,temp1[4][8],Ptemp1[4][8],count=0;
		for(k=0;k<48;k+=6)
		{
			row=2*temp[k/8][k%8]+temp[(k+5)/8][(k+5)%8];
			col=8*temp[(k+1)/8][(k+1)%8]+4*temp[(k+2)/8][(k+2)%8]+2*temp[(k+3)/8][(k+3)%8]+temp[(k+4)/8][(k+4)%8];
			
			int val=S[k/6][row][col];
			for(i=0;i<4;i++,count++) 
				if(val&(1<<(3-i)))	temp1[count/8][count%8]=1;
				else 			temp1[count/8][count%8]=0;
		}
		//Permutation 
		for(i=0;i<4;i++)
			for(j=0;j<8;j++)
			Ptemp1[i][j]=temp1[(P[i][j]-1)/8][(P[i][j]-1)%8];
		//XOR-Operation
		for(i=0;i<4;i++) for(j=0;j<8;j++) Ptemp1[i][j]^=output[i][j];
		//Rearranging
		for(i=0;i<4;i++) for(j=0;j<8;j++) output[i][j]=output[i+4][j];
		for(i=0;i<4;i++) for(j=0;j<8;j++) output[i+4][j]=Ptemp1[i][j];
	}
	//32-Bit Swap
	for(i=0;i<4;i++) for(j=0;j<8;j++) swap(output[i][j],output[i+4][j]);
	//Inverse Permutation
	for(i=0;i<8;i++) for(j=0;j<8;j++) temp[i][j]=output[(InvP[i][j]-1)/8][(InvP[i][j]-1)%8];
	for(i=0;i<8;i++) for(j=0;j<8;j++) output[i][j]=temp[i][j];
	cout<<"Plain Text:    ";for(i=0;i<8;i++) for(j=0;j<8;j++) cout<<output[i][j];cout<<endl;
	
	return 0;
}
/*
58 50 42 34 26 18 10 2
60 52 44 36 28 20 12 4
62 54 46 38 30 22 14 6
64 56 48 40 32 24 16 8
57 49 41 33 25 17 9 1
59 51 43 35 27 19 11 3
61 53 45 37 29 21 13 5
63 55 47 39 31 23 15 7

40 8 48 16 56 24 64 32
39 7 47 15 55 23 63 31
38 6 46 14 54 22 62 30
37 5 45 13 53 21 61 29
36 4 44 12 52 20 60 28 
35 3 43 11 51 19 59 27
34 2 42 10 50 18 58 26
33 1 41  9 49 17 57 25

32 1 2 3 4 5
4 5 6 7 8 9
8 9 10 11 12 13
12 13 14 15 16 17
16 17 18 19 20 21
20 21 22 23 24 25
24 25 26 27 28 29
28 29 30 31 32 1

16 7 20 21 29 12 28 17
1 15 23 26 5 18 31 10
2 8 24 14 32 27 3 9
19 13 30 6 22 11 4 25

57 49 41 33 25 17 9
1 58 50 42 34 26 18
10 2 59 51 43 35 27
19 11 3 60 52 44 36
63 55 47 39 31 23 15
7 62 54 46 38 30 22
14 6 61 53 45 37 29
21 13 5 28 20 12 4

14 17 11 24 1 5 3 28
15 6 21 10 23 19 12 4
26 8 16 7 27 20 13 2
41 52 31 37 47 55 30 40
51 45 33 48 44 49 39 56
34 53 46 42 50 36 29 32

14 4 13 1 2 15 11 8 3 10 6 12 5 9 0 7
0 15 7 4 14 2 13 1 10 6 12 11 9 5 3 8 
4 1 14 8 13 6 2 11 15 12 9 7 3 10 5 0
15 12 8 2 4 9 1 7 5 11 3 14 10 0 6 13

15 1 8 14 6 11 3 4 9 7 2 13 12 0 5 10
3 13 4 7 15 2 8 14 12 0 1 10 6 9 11 5
0 14 7 11 10 4 13 1 5 8 12 6 9 3 2 15
13 8 10 1 3 15 4 2 11 6 7 12 0 5 14 9

10 0 9 14 6 3 15 5 1 13 12 7 11 4 2 8
13 7 0 9 3 4 6 10 2 8 5 14 12 11 15 1
13 6 4 9 8 15 3 0 11 1 2 12 5 10 14 7
1 10 13 0 6 9 8 7 4 15 14 3 11 5 2 12

7 13 14 3 0 6 9 10 1 2 8 5 11 12 4 15
13 8 11 5 6 15 0 3 4 7 2 12 1 10 14 9
10 6 9 0 12 11 7 13 15 1 3 14 5 2 8 4
3 15 0 6 10 1 13 8 9 4 5 11 12 7 2 14

2 12 4 1 7 10 11 6 8 5 3 15 13 0 14 9
14 11 2 12 4 7 13 1 5 0 15 10 3 9 8 6
4 2 1 11 10 13 7 8 15 9 12 5 6 3 0 14
11 8 12 7 1 14 2 13 6 15 0 9 10 4 5 3

12 1 10 15 9 2 6 8 0 13 3 4 14 7 5 11
10 15 4 2 7 12 9 5 6 1 13 14 0 11 3 8
9 14 15 5 2 8 12 3 7 0 4 10 1 13 11 6
4 3 2 12 9 5 15 10 11 14 1 7 6 0 8 13

4 11 2 14 15 0 8 13 3 12 9 7 5 10 6 1
13 0 11 7 4 9 1 10 14 3 5 12 2 15 8 6
1 4 11 13 12 3 7 14 10 15 6 8 0 5 9 2
6 11 13 8 1 4 10 7 9 5 0 15 14 2 3 12

13 2 8 4 6 15 11 1 10 9 3 4 5 0 12 7
1 15 13 8 10 3 7 4 12 5 6 11 0 14 9 2
7 11 4 1 9 12 14 2 0 6 10 13 15 3 5 8
2 1 14 7 4 10 8 13 15 12 9 0 3 5 6 11

1 1 2 2 2 2 2 2 1 2 2 2 2 2 2 1

1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0

1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0

*/
