/*
 * Author : Vinayak Bhargav Srinath [4866100]
 * This Headerfile lists all the structures and function prototypes that can be used
 * Certain functions that were not used have been commented out
*/



#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
 
//Allow prints for debugging 
extern int debug_print;
extern int iterations;

  //Reaction Probablities
extern float reac_prob[3];

extern int reac_num[3];       

 //Reaction breaker set
extern int reac_breaker;

 //Stop State
extern int C[3];

 //Prob Distribution Structure
struct val_prob
{
       int count;
       float prob;
};


 //State Structure
struct state
{
       int x1,x2,x3,error;
       float prob;
};

  //Find reaction Probabilities
float prob_calc(struct state* s);
      
 // Rection order
void reac_order(); 

 //Print call
 void s_print(struct state* s,char* str);

 //Just prints a line
void line_print();

 //Print Distribution list
void d_list_print(struct val_prob* vp,char* str);
 
 //Initializes the Distribution List
void val_init(struct val_prob* vp,int v);

 //Struct initializer
void initv(struct state* s,int v1, int v2, int v3);
 
 //Distribution list structure updates
void val_update(struct val_prob* vp,float p);
           
 //Reaction breaker
 void error_test(struct state* s,char* str);
 
 //Reaction Criteria
 //int reac_criteria(int xval,int limit,char* dir,int* count);
           
 //Reaction1
 struct state reac1(struct state* s,float p);
 //Reaction2      
  struct state reac2(struct state* s,float p);
   //Reaction3
  struct state reac3(struct state* s,float p);
  
 //Reaction Select  
struct state reac_select(struct state* s,int a);

#endif
