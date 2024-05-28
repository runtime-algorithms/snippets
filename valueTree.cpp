//one more level (thus twice the size) of a BST but it also can use array indexing
//one can change the binary function to work with something other than natural numbers

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//kinda classes
typedef struct Link{
	int count;
	int depth;
	struct Link *next[2];
}Link;
Link *LINK(int count, int depth){
	Link *part=(Link*)malloc(sizeof(Link));
	part->count=count;
	part->depth=depth;
	part->next[0]=NULL;
	part->next[1]=NULL;
	return part;
}
typedef struct Binary{
	int length;
	bool *arr;
}Binary;
Binary *BINARY(int length, bool *arr){
	Binary *num=(Binary*)malloc(sizeof(Binary));
	num->length=length;
	num->arr=arr;
	return num;
}

//functions
Binary *binary(int num){
  if(num==0){
  	bool *zero=(bool*)malloc(sizeof(bool));
  	zero[0]=false;
  	return BINARY(1,zero);
  }
  int length=log2( (float)num )+1, i=length-1;
  bool *arr=(bool*)malloc(length*sizeof(bool));
  while(num!=0){
    arr[i--]=num%2;
    num=num/2;
  }
  return BINARY(length,arr);
}
Link *addTo(Link *list, Binary *num){
  Link *temp=list, *returnList=list; //LINKs
  int i=0, count=temp->count; //integers
  if(num->length>list->depth) returnList=LINK(count,num->length);
  
  list=returnList;
  if(temp->count==0){ //thus, temp->depth is 0
    for(i=0;i<num->length;i++){
      list->next[ num->arr[i] ]=LINK(count,num->length-(i+1));
      list=list->next[ num->arr[i] ];
    }
  }
  else{
    for(i=0;i<num->length-temp->depth;i++){
      list->next[ 0 ]=LINK(count,num->length-(i+1));
      list=list->next[ 0 ];
    }
  }
  list->next[0]=temp->next[0];
  list->next[1]=temp->next[1];
  returnList->count++;
  temp=returnList;
  
  for(i=0;i<returnList->depth-num->length;i++){
    if(temp->next[ 0 ]==NULL) temp->next[ 0 ]=LINK(1,returnList->depth-(i+1));
    else temp->next[0]->count++;
    temp=temp->next[0];
  }
  for(i=0;i<num->length;i++){
    if(temp->next[ num->arr[i] ]==NULL)
      temp->next[ num->arr[i] ]=LINK(1,num->length-(i+1));
    else
      temp->next[ num->arr[i] ]->count++;
    temp=temp->next[ num->arr[i] ];
  }
  return returnList;
}
Link *takeAway(Link *list, Binary *num){
  if(num->length>list->depth || list->depth==0) return list;
  bool PATH[list->depth], n; //bool
  int i, depth=list->depth, diff=depth-num->length; //integers
  Link *temp=list, *returnList=list, *number[depth+1]; //LINKs
  for(i=0;i<depth;i++){
    //diff is the list's depth (depth of its highest number) minus the depth of the number itself
    //where "depth" is the amount of bits to express a number in binary
    //thus, n encompasses the trailing 0s before the number starts based on the depth of the list
    if(i<diff) n=0;
    else n=num->arr[i-diff];
    if(temp->next[n]==NULL) return returnList;
    PATH[depth-1-i]=n;
    temp=temp->next[n];
    number[depth-1-i]=temp;
  }
  
  number[depth]=returnList;
  number[0]->count--;
  for(i=0;i<depth;i++){
    number[i+1]->count--;
    if(number[i]->count==0){
      number[i+1]->next[ PATH[i] ]=NULL;
      free(number[i]);
    }
  }
  while(returnList->next[1]==NULL && returnList->next[0]!=NULL){
    temp=returnList;
    returnList=returnList->next[0];
    free(temp);
  }
  if(returnList->count==0) returnList->depth=0;
  return returnList;
}

int equalTo(Link *list, Binary *num){
  if(num->length>list->depth || list->count==0) return 0;
  Link *temp=list; //LINK
  int i; //integer
  for(i=0;i<list->depth-num->length;i++){
    if(temp->next[0]==NULL) return 0;
    temp=temp->next[ 0 ];
  }
  for(i=0;i<num->length;i++){
    if(temp->next[ num->arr[i] ]==NULL) return 0;
    temp=temp->next[ num->arr[i] ];
  }
  return temp->count;
}
int lessThan(Link *list, Binary *num){
  Link *temp=list; //LINK
  int i, count=0; //integers
  if(num->length>list->depth) return list->count;
  for(i=0;i<list->depth-num->length;i++){
    if(temp->next[0]==NULL) return count;
    temp=temp->next[0];
  }
  for(i=0;i<num->length;i++){
    if(num->arr[i] && temp->next[0]!=NULL)
      count+=temp->next[0]->count;
    if(temp->next[ num->arr[i] ]==NULL) return count;
    temp=temp->next[ num->arr[i] ];
  }
  return count;
}
int moreThan(Link *list, Binary *num){
  Link *temp=list; //LINK
  int i, count=0; //integers
  if(num->length>list->depth) return count;
  for(i=0;i<list->depth-num->length;i++){
    if(temp->next[1]!=NULL) count+=temp->next[1]->count;
    if(temp->next[0]==NULL) return count;
    temp=temp->next[0];
  }
  for(i=0;i<num->length;i++){
    if(!num->arr[i] && temp->next[1]!=NULL)
      count+=temp->next[1]->count;
    if(temp->next[ num->arr[i] ]==NULL) return count;
    temp=temp->next[ num->arr[i] ];
  }
  return count;
}
int integer(Binary *num){
  int p, j, i, n=0;
  for(i=num->length-1;i>=0;i--){
    p=1; //power
    for(j=num->length-1;j>i;j--) p*=2;
    n+=p*num->arr[i];
  }
  return n;
}
int atIndex(Link *list, int num){
  if(num<0 || num>=list->count)
    return -2147483647; //sign for it not existing
  bool arr[list->depth], n, full; //bools
  Binary *myNumber=BINARY(list->depth,arr); //BINARY
  Link *temp=list; //LINK
  int index=0; //int
  //index is amount of locations in the list exceeded due to implied logic with the count attribute
  while(temp->depth>0){
    full=temp->next[0]!=NULL && temp->next[1]!=NULL;
    if(!full) n=(temp->next[0]==NULL);
    else n=(index+temp->next[0]->count<=num);
    if(n&&full) index+=temp->next[0]->count;
    arr[list->depth-temp->depth]=n;
    temp=temp->next[n];
  }
  return integer(myNumber);
}
int indexAt(Link *list, Binary *num){
  if(num->length>list->depth || list->count==0) return -1;
  Link *temp=list; //LINK
  int i, index=0; //integer
  for(i=0;i<list->depth-num->length;i++){
    if(temp->next[0]==NULL) return -1;
    temp=temp->next[ 0 ];
  }
  for(i=0;i<num->length;i++){
    if(temp->next[ num->arr[i] ]==NULL) return -1;
    if(num->arr[i] && temp->next[0]) index+=temp->next[0]->count;
    temp=temp->next[ num->arr[i] ];
  }
  return index;
}

void ascending(Link *list){
  int i, result, intPtr=0, length=list->count; //integers
  bool arr[list->depth], n; //bools
  Binary *num=BINARY(list->depth,arr); //binary
  Link *linkPtrs[list->depth], *temp=list; //LINKs
  for(i=0;i<list->depth;i++) arr[i]=0;
  while(length>0){
    if(length<list->count) temp=linkPtrs[intPtr];
    for(i=intPtr;i<list->depth;i++){
      n=num->arr[i]; //1 or 0
      if(temp->next[0]!=NULL && temp->next[1]!=NULL) intPtr=i;
      if(temp->next[n]==NULL) n=!n;
      linkPtrs[i]=temp;
      temp=temp->next[n];
      num->arr[i]=n;
    }
    result=integer(num);
    for(i=0;i<temp->count;i++){
      length--;
      printf("%d\n",result);
    }
    while(intPtr>=0&&  (!(linkPtrs[intPtr]->next[0]==NULL || linkPtrs[intPtr]->next[1]==NULL)? num->arr[intPtr]: true))
      intPtr--; //keep going back up until another crossroad when all numbers from crossroad evaluated
    if(!num->arr[intPtr]) num->arr[intPtr]=1;
    for(i=intPtr+1;i<list->depth;i++) num->arr[i]=0;
  }
}
void descending(Link *list){
  int i, result, intPtr=0, length=list->count; //integers
  bool arr[list->depth], n; //bools
  Binary *num=BINARY(list->depth,arr); //binary
  Link *linkPtrs[list->depth], *temp=list; //LINKs
  for(i=0;i<list->depth;i++) arr[i]=1;
  while(length>0){
    if(length<list->count) temp=linkPtrs[intPtr];
    for(i=intPtr;i<list->depth;i++){
      n=num->arr[i]; //1 or 0
      if(temp->next[0]!=NULL && temp->next[1]!=NULL) intPtr=i;
      if(temp->next[n]==NULL) n=!n;
      linkPtrs[i]=temp;
      temp=temp->next[n];
      num->arr[i]=n;
    }
    result=integer(num);
    for(i=0;i<temp->count;i++){
      length--;
      printf("%d\n",result);
    }
    while(intPtr>=0&&  (!(linkPtrs[intPtr]->next[0]==NULL || linkPtrs[intPtr]->next[1]==NULL)? !num->arr[intPtr]: true))
      intPtr--; //keep going back up until another crossroad when all numbers from crossroad evaluated
    if(num->arr[intPtr]) num->arr[intPtr]=0;
    for(i=intPtr+1;i<list->depth;i++) num->arr[i]=1;
  }
}
void recurse(Link *node, int N, int i){
	if(node==NULL) return;
	//if(node->next[0]==NULL && node->next[1]==NULL) return;
	for(int c=0;c<N;c++) printf("- ");
	printf("[%d]    count: %d    depth: %d\n",i,node->count,node->depth);
	recurse(node->next[0],N+1,0);
	recurse(node->next[1],N+1,1);
}


int main(){
	Link *list=LINK(0,0);
	list=addTo(list,binary(24));
	list=addTo(list,binary(25));
	list=addTo(list,binary(33));
	list=addTo(list,binary(33));
	list=addTo(list,binary(1));
	
	ascending(list);
	printf("\n");
	descending(list);
	printf("\n%d %d\n",indexAt(list,binary(24)),indexAt(list,binary(33)));
	
	list=takeAway(list,binary(1));
	printf("\n\n");
	
	ascending(list);
	printf("\n");
	descending(list);
	printf("\n%d %d\n",indexAt(list,binary(24)),indexAt(list,binary(33)));
	return 0;
}
