#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "WGraph.h"
#include "stack.h"
int Length=0;//Set global variables
List L;//Set global variables

//time complexity is O(n^2),The highest time complexity is a recursion nested with a loop.
void findedges(List,List,Graph,int,int);
void findedges(List path,List L,Graph g,int longnum,int oneORtwo){
	path=insertLL(path,L->v);
	longnum++;
	if (L->num==0){
		if (longnum>Length && oneORtwo==0){
			Length=longnum;			
		}
		if (longnum==Length && oneORtwo==1){
			stack s = newStack();
			for(List pa=path;pa!=NULL;pa=pa->next){
				StackPush(s, pa->v);
			}
			while(s->height>1){
				printf("%d < ",StackPop(s));
			}
			printf("%d\n",StackPop(s));	
			dropStack(s);	
		}
	}
	for(List n=L->next;n!=NULL;n=n->next){
		if (adjacent(g,L->v-1,n->v-1)==1){
			findedges(path,n,g,longnum,oneORtwo);				
		}	
	}
}
//time complexity is O(E^2),E is the maximum number of digits in each number, and in this task, maximum E is equal to 10.
int allDigitIn(int ,int);
int allDigitIn(int p,int q){
	int digitbool=1;					
	for(int d=p;d!=0;d=d/10){
		int includbool=0;
		for(int dq=q;dq!=0;dq=dq/10){
			if(dq%10==d%10){
				includbool=1;
			}
		}
		if(includbool==0){
			digitbool=0;
			return digitbool;
		}
	}
	return digitbool;
}
//time complexity is O(n^2),The highest time complexity is a for loop nested with a for loop.
Graph InputEdages(Graph);
Graph InputEdages(Graph g){
	for(List p=L;p!=NULL;p=p->next){
		printf("%d: ",p->v);
		for(List q=p->next;q!=NULL;q=q->next){
			if(q->v%p->v==0){
				if(allDigitIn(p->v,q->v)==1){
					printf("%d ",q->v);
					Edge e;
					e.v=p->v-1;
					e.w=q->v-1;
					e.weight=1;
					p->num=p->num+1;
					insertEdge(g,e);
				}										
			}
		}	
		printf("\n");
	}				
	return g;
}
//time complexity is O(n),The highest time complexity is for a loop.
int main(int argc, char *argv[]) {
	if(argc==2){
		int num = atoi(argv[1]);
		Graph g=newGraph(num);
		printf("Partial order:\n");
		g=InputEdages(g);
		for(List m=L;m->next!=NULL;m=m->next){			
			List path=NULL;
			int longnum=0;
			findedges(path,m,g,longnum,0);
		}
		printf("\nLongest monotonically increasing sequences:\n");
		for(List m=L;m!=NULL;m=m->next){	
			List path=NULL;
			int longnum=0;		
			findedges(path,m,g,longnum,1);
		}
		freeGraph(g);
		freeLL(L);
	}
}

