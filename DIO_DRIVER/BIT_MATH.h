/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*______________________________________________________________
 * BIT MATH OPERATIONS :-
 * _____________________________________________________________
 * *************************************************************/

#define SET_BIT(VAR,BIT_NO) (VAR |= 1<<BIT_NO)        /*SET_BIT set BIT_NO with HIGH in Variable*/
#define CLR_BIT(VAR,BIT_NO) (VAR &= ~(1<<BIT_NO))     /*Clear it set BIT_NO with LOW in Variable*/
#define TOGGLE_BIT(VAR,BIT_NO) (VAR ^= (1<<BIT_NO))   /*TOGGLE if BIT_NO is HIGH it set it to LOW and Vice Versa*/
#define ASSIGN_BIT(VAR,BIT_NO,VALUE)  (VAR=(VAR &(~(1<<BIT_NO))) | (VALUE<<BIT_NO))  //ASSIGHN BIT_NO in variable to HIGH or LOW*/
#define GET_BIT(VAR,BIT_NO)  ((VAR>>BIT_NO) & 0x01)   /*GET BIT_NO Value*/

//________________________________________________________________

#endif /* BIT_MATH_H_ */
