/*
 * Author : Vinayak Bhargav Srinath [4866100]
 * This file lists out the function definitions
 * Functions not used are commented out, to enable them simply un-comment them and the corresponding prototype in functions.h
*/

#include "functions.h"
#include <stdio.h>
 
  //Find reaction Probabilities
float prob_calc(struct state* s)
{     float k1=s->x1,
            k2=s->x2,
            k3=s->x3;
      float temp1,temp2,temp3,sum;
      if(debug_print==1)printf("\nPROB_CALC:\n%.3f, %.3f, %.3f",k1,k2,k3);
      temp1 = 0.5*k1*(k1-1)*k2;
      temp2 = k1*k3*(k3-1);
      temp3 = 3.0*k2*k3;
      sum = temp1+temp2+temp3;
      if(debug_print==1)printf("\n%.3f, %.3f, %.3f",temp1,temp2,temp3);
      reac_prob[0]=(temp1/sum);
      reac_prob[1]=(temp2/sum);
      reac_prob[2]=(temp3/sum);
           
      }
      
 // Rection order
void reac_order() 
{
     int i=0;
      if( (reac_prob[0]<reac_prob[1]) && (reac_prob[0]<reac_prob[2]) ) 
          {                           reac_num[0] = 0;
                                      if (reac_prob[1]<reac_prob[2]) {reac_num[1] = 1; reac_num[2]= 2;}
                                      else {reac_num[1] = 2; reac_num[2]= 1;}
                                      }
      else if ( (reac_prob[1]<reac_prob[0]) && (reac_prob[1]<reac_prob[2]) ) 
          {                           reac_num[0] = 1;
                                      if (reac_prob[0]<reac_prob[2]) {reac_num[0] = 0; reac_num[2]= 2;}
                                      else {reac_num[1] = 2 ; reac_num[2]= 0;}
                                      }
      else  
          {                           reac_num[0] = 2;
                                      if (reac_prob[0]<reac_prob[1]) {reac_num[1] = 0; reac_num[2]=1;}
                                      else {reac_num[1] = 1; reac_num[2]= 0;}
                                      }
if (debug_print==1){
                    printf("\nREAC_ORDER:");
                    for(i=0;i<3;i++){
                                     printf("R%d: %.3f ",(reac_num[i]+1),reac_prob[reac_num[i]]);
                                     }
                    }
                                                      
}

 //Print call
 void s_print(struct state* s,char* str){
      printf("\n%s : x1=%d, x2=%d, x3=%d, prob=%.3f error=%d ",str,s->x1,s->x2,s->x3,s->prob,s->error);
 }

 //Just prints a line
void line_print()
{
     int k;
     printf("\n");
     for(k=0;k<30;k++)printf("-");
     printf("\n");
     }
 //Print Distribution list
void d_list_print(struct val_prob* vp,char* str)
{    int i;
     printf("\nDIST LIST: %s ",str);
     for(i=0;i<15;i++)
     printf("%s(%d) = count = %d, probability = %.3f\n ",str,i,(vp+i)->count,((vp+i)->count/(float)iterations)); 
     line_print();
 }
 
 //Initializes the Distribution List
void val_init(struct val_prob* vp,int v){
      vp->count=0;
      vp->prob=0;     
      }

 //Struct initializer
void initv(struct state* s,int v1, int v2, int v3){
      s->error=0;
      s->prob=1;
      s->x1=v1;
      s->x2=v2;
      s->x3=v3;      
      }
 
 //Distribution list structure updates
void val_update(struct val_prob* vp,float p){
     vp->count++;
     vp->prob = vp->prob + p;
     }
           
 //Normalize the Distribution list -Unnecessary
/*
void val_normalize(struct val_prob* vp){
     if(vp->count!=0){vp->prob=vp->prob/vp->count;}
     }      
*/      
 //Reaction breaker
 void error_test(struct state* s,char* str){
      if( (s->x1)<0 || (s->x2)<0 || (s->x3)<0)
      {          s->error=1;
                 if(debug_print==1)printf("Error:cannot proceed %s",str);
                 }
      else
      s->error=0;
      }
/*
 //Reaction Criteria
 int reac_criteria(int xval,int limit,char* dir,int* count)
 {					int flag=0;
                   if(dir==">" && xval>limit)flag=1;
                   if(dir=="<" && xval<limit)flag=1;
                   if(dir==">=" && xval>=limit)flag=1;
                   if(dir=="<=" && xval<=limit)flag=1;
                   if(dir=="=" && xval==limit)flag=1;
                   
                   if(debug_print==1)printf("\nX: %d %s %d",xval,dir,limit);
                   
                   if(flag==1) *count++;
    return flag;
     
     } 
 */          
 //Reaction1
 struct state reac1(struct state* s,float p)
 {     struct state s_new;
       if(s->error==0){
                       s_new.x1=s->x1-2;
                       s_new.x2=s->x2-1;
                       s_new.x3=s->x3+4;
                       s_new.prob=(s->prob)*p;
                       error_test(&s_new,"R1");
                       if(s_new.error==0)
                       {
                                         if(debug_print==1)s_print(&s_new,"R1");
                                         return s_new;
                       }
       }
       else
       {return s_new;}
      }
      
 //Reaction2      
  struct state reac2(struct state* s,float p)
 {     struct state s_new;
       if(s->error==0){
                       s_new.x1=s->x1-1;
                       s_new.x3=s->x3-2;
                       s_new.x2=s->x2+3;
                       s_new.prob=(s->prob)*p;
                       error_test(&s_new,"R2");
                       if(s_new.error==0)
                       {
                                         if(debug_print==1)s_print(&s_new,"R2");
                                         return s_new;
                       }
       }
       else
       {return s_new;}
      }
      
   //Reaction3
  struct state reac3(struct state* s,float p)
 {     struct state s_new;
       if(s->error==0){
                       s_new.x2=s->x2-1;
                       s_new.x3=s->x3-1;
                       s_new.x1=s->x1+2;
                       s_new.prob=(s->prob)*p;
                       error_test(&s_new,"R3");
                       if(s_new.error==0)
                       {
                                         if(debug_print==1)s_print(&s_new,"R3");
                                         return s_new;
                       }
       }
       else
       {return s_new;}
      }


struct state reac_select(struct state* s,int a)
{
     if (a==0)                  return reac1(s,reac_prob[a]);
     else if (a==1)             return reac2(s,reac_prob[a]);
     else                       return reac3(s,reac_prob[a]); 
     }


