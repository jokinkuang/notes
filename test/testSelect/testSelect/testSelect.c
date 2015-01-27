#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
int main(void){
	fd_set fdset;
	FD_ZERO (&fdset);/*清空集合中所有的元素*/ 
	FD_SET(STDOUT_FILENO,&fdset);/*设置stdout，使集合中包含stdout*/ 
	if(FD_ISSET(STDOUT_FILENO,&fdset)!=0)/*测试stdout是否包含在集合中*/ 
		printf("stdout has been set\n"); 
	else 
		printf("stdout has not been set\n");
	FD_CLR(STDOUT_FILENO,&fdset);/*从位向量中清除stdout*/
	if(FD_ISSET(STDOUT_FILENO,&fdset)!=0)/*再次测试*/
		printf("stdout has been set\n");
	else 
		printf("stdout has not been set\n"); 
	return 0;
}