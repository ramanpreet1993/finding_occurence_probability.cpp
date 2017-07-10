#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int poly1[]={1,0,0,0,0,0,1}; // feedback polynomial of degree 7
int poly2[]={0,0,0,1,0,0,0,0,1}; // feedback polynomial of degree 9
int poly3[]={0,1,0,0,0,0,0,0,0,0,1};  // feedback polynomial of degree 11
int poly4[]={1,0,1,1,0,0,0,0,0,0,0,0,1};  // feedback polynomial of degree 13
int *arr1,*arr2,*arr3,*arr4;
int LFSR(int length,int* &arr,int poly[])
{
           int i,fb;
           fb=0;
           for(i=0;i<length;i++)
           fb^=(poly[i]*arr[length-i-1]);
	for(i=0;i<length-1;i++)
	arr[i]=arr[i+1];
	arr[length-1]=fb;
	return (arr[0]);
}
int main()
{
	FILE *ifp,*ofp,*ofp1,*ofp2,*ofp3,*ofp4;
	int no_lfsr,l1,l2,l3,l4,no_clk;
	int *init_st1,*init_st2,*init_st3,*init_st4;
	int i,j,k,x1,x2,x3,x4,f;
	int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
	
/**************OPENING THE DATA FILES*****************/
	ifp=fopen("inp.txt","r");
	if(ifp==NULL)
	{
		printf("\n Unable to open input file.\n");
		exit(0);
	}
	ofp=fopen("key_seq.txt","w");
	if(ofp==NULL)
	{
		printf("\n Unable to open output file.\n");
		exit(0);
	}
	ofp1=fopen("lfsr_seq1.txt","w");
	if(ofp1==NULL)
	{
		printf("\n Unable to open output file-1.\n");
		exit(0);
          }
	ofp2=fopen("lfsr_seq2.txt","w");
	if(ofp2==NULL)
	{
		printf("\n Unable to open output file-2.\n");
		exit(0);
	}
	ofp3=fopen("lfsr_seq3.txt","w");
	if(ofp3==NULL)
	{
		printf("\n Unable to open output file.-3\n");
		exit(0);
	}
	ofp4=fopen("lfsr_seq4.txt","w");
	if(ofp4==NULL)
	{
		printf("\n Unable to open output file.-4\n");
		exit(0);
	}
	
	
/*****************READING THE INPUT FILE******************/
	
	fscanf(ifp,"%d",&no_lfsr);
	fscanf(ifp,"%d",&l1);
	init_st1=new int[l1];
	arr1=new int[l1];
	for(i=l1-1;i>=0;i--)
	{
		fscanf(ifp,"%d",&init_st1[i]);
		arr1[i]=init_st1[i];
	}
	fscanf(ifp,"%d",&l2);
	init_st2=new int[l2];
	arr2=new int[l2];
	for(i=l2-1;i>=0;i--)
	{
		fscanf(ifp,"%d",&init_st2[i]);
		arr2[i]=init_st2[i];
	}
	fscanf(ifp,"%d",&l3);
	init_st3=new int[l3];
	arr3=new int[l3];
	for(i=l3-1;i>=0;i--)
	{
		fscanf(ifp,"%d",&init_st3[i]);
		arr3[i]=init_st3[i];
	}
	fscanf(ifp,"%d",&l4);
	init_st4=new int[l4];
	arr4=new int[l4];
	for(i=l4-1;i>=0;i--)
	{
		fscanf(ifp,"%d",&init_st4[i]);
		arr4[i]=init_st4[i];
	}
	fscanf(ifp,"%d",&no_clk);
	
	/******************************CLOCKING THE LFSRs*******************/
	int period1=0,period2=0,period3=0,period4=0;
	for(k=0;k<no_clk;k++)
	{
		x1=LFSR(l1,arr1,poly1);
		fprintf(ofp1,"%d",x1);
		x2=LFSR(l2,arr2,poly2);
		fprintf(ofp2,"%d",x2);
	           x3=LFSR(l3,arr3,poly3);
		fprintf(ofp3,"%d",x3);
		x4=LFSR(l4,arr4,poly4);
		fprintf(ofp4,"%d",x4);
		f=1^(x1*x2*x3)^(x1*x3)^(x1*x4)^(x3*x4)^(x1)^(x4)^(x2)^(x3);
		fprintf(ofp,"%d",f);
		if(f==x1) cnt1++;
		if(f==x2) cnt2++;
		if(f==x3) cnt3++;
		if(f==x4) cnt4++;
		for(j=0;j<l1;j++)
		if(arr1[j]!=init_st1[j])
		break;
		if(j==l1 && period1==0)
		period1=k+1;
		for(j=0;j<l2;j++)
		if(arr2[j]!=init_st2[j])
		break;
		if(j==l2 && period2==0)
		period2=k+1;
		for(j=0;j<l3;j++)
		if(arr3[j]!=init_st3[j])
		break;
		if(j==l3 && period3==0)
		period3=k+1;
		for(j=0;j<l4;j++)
		if(arr4[j]!=init_st4[j])
		break;
		if(j==l4 && period4==0)
		period4=k+1;
	}
	printf("\n p(z(t)=x1(t))= %0.2f....%d",(float)cnt1/no_clk,cnt1);
	printf("\n p(z(t)=x2(t))= %0.2f....%d",(float)cnt2/no_clk,cnt2);
	printf("\n p(z(t)=x3(t))= %0.2f....%d",(float)cnt3/no_clk,cnt3);
	printf("\n p(z(t)=x4(t))= %0.2f....%d",(float)cnt4/no_clk,cnt4);
	printf("\n Minimum period of LFSR1= %d\n",period1);
	printf("\n Minimum period of LFSR2= %d\n",period2);
	printf("\n Minimum period of LFSR3= %d\n",period3);
	printf("\n Minimum period of LFSR4= %d\n",period4);
	fclose(ifp);
	fclose(ofp);
	fclose(ofp1);
	fclose(ofp2);
	fclose(ofp3);
	fclose(ofp4);
	delete[] init_st1;
	delete[] init_st2;
	delete[] init_st3;
	delete[] init_st4;
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	return 0;
}

