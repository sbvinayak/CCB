/*
 * Author : Vinayak Bhargav Srinath
 * This .c file finds out the possible number of occurances of a given limiting condition for the following equations
	Equations given:
	R1: 2x1+x2 = 4x3 
	R2: x1+2x3 = 3x2 
	R3: x2+x3 = 2x1     
	*/

	# include <stdio.h>
	# include <stdlib.h>
	# include <time.h>
	# include "functions.h"  
	# define R1 1 , R2 2 , R3 3
	//----- declarations
	int debug_print=0;
	int iterations;

	int reac_num[3] = {1,2,3};       

	  //Reaction Probablities
	float reac_prob[3];

	 //Reaction breaker set
	int reac_breaker=0;

	 //Stop State
	int C[3] = {0,0,0};

	//----end declarations

	int main()
	 {   int i=0,j=0,k1=0,k2=0,k3=0,counter=0;
		 struct val_prob X1[15],X2[15],X3[15];
		 float k;
		 struct state s_new;
		 char check='n';
		 
		 //User inputs
		 printf("\nEnter the number of iterations:");
		 scanf("%d",&iterations);
		 do{
		 printf("\nDo you want to turn on debug_print? (Enter (y/n)):");
		 scanf("%s",&check);
		 
		 if(check=='y') debug_print=1;
		 }while (check!='y' && check!='n');
		 
	  
		 //initialize Dist table
		 for(i=0;i<15;i++){
		 val_init(&X1[i],0);val_init(&X2[i],0);val_init(&X3[i],0);
		 }
		 
		 for(j=0;j<iterations;j++)
		 {
		
		 if(debug_print==1)line_print();
		 
		 //Reset to initial state
		 reac_breaker=0;
		 initv(&s_new,3,5,7);
			  
		 if(debug_print==1)s_print(&s_new,"init");

		 while(reac_breaker!=1)
		 { 
			 
			  // three decimal place random number generator
			  k=((float)(rand()%1000))/1000;
			  
			  
			  if(debug_print==1)printf("\n\n--RANDOM_NUM GENERATED: %.3f",k);
			  prob_calc(&s_new);
			  reac_order();
			  
			  if (k<reac_prob[reac_num[0]])
			  { 
			  s_new=reac_select(&s_new,reac_num[0]); 
				}
			  else if (k<(reac_prob[reac_num[0]] + reac_prob[reac_num[1]]))
			  { s_new=reac_select(&s_new,reac_num[1]);
				 }
			  else
			  { s_new=reac_select(&s_new,reac_num[2]);
			   }
			   
			   
				if(s_new.x1>5)C[0]++;
				if(s_new.x2>=7)C[1]++;
				if(s_new.x3<5)C[2]++;
				
				if(debug_print==1)s_print(&s_new,"CURR_STATE:");
				if(debug_print==1)printf("\nBREAK_FLAGS: %d %d %d ",s_new.x1>5, s_new.x2>=7, s_new.x3<5);
				
				 if(s_new.x1>5 ||  s_new.x2>=7 || s_new.x3<5)reac_breaker=1;
			 
		  }	
		 
			val_update(&X1[s_new.x1],s_new.prob);
			val_update(&X2[s_new.x2],s_new.prob);
			val_update(&X3[s_new.x3],s_new.prob);
			
		 }
		 line_print();
		 printf("\nC1(%d) C2(%d) C3(%d)\n",C[0],C[1],C[2]);
			
		 return 0;
	 }
	 
	 

