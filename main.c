#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include"City_data.h"

/*模拟退火算法 求最优短路径 TSP问题
(无约束条件)
author:YXP
e-mail:276003961@qq.com*/

int main(int argc, char *argv[]) {
	time_t start,finish;
	start = clock();
	
	init ();
	srand ((unsigned)time(NULL));
	double T = T_start;
	
	int* Route_test;
	Route_test = (int*)malloc(sizeof(int)*Node_num);
	copy_route (City_route,Route_test);
	
	int i,counter=0,cp=0;
	double r,R_len_CR,R_len_Rt,deta;
	while (T>T_end){
		for (i=0;i<COUNTER;i++){
			recombine_route (Route_test);
			R_len_CR=route_len(City_route);
			R_len_Rt=route_len(Route_test);
			deta = R_len_CR-R_len_Rt;
			if (deta>0){ 
				copy_route(Route_test,City_route);
			}else{
				if (exp(deta/T)>((double)rand()/(RAND_MAX+1.0))){
					copy_route(Route_test,City_route);
					cp++;
				}
			}
			counter ++;
		}
		T=T*k;
	}
	
	for (i=0;i<Node_num;i++){
		printf ("%d->",City_route[i]);
	}
	printf ("\n>>总路程长度为%lf\n",route_len(City_route));
	double rate = (1.0*cp)/counter;
	printf (">>测试次数%d\n>>概率下降次数%d\n>>其中频率为%lf\n",counter,cp,rate);
	finish = clock();
	double duration = ((double)(finish-start) )/CLOCKS_PER_SEC;
	printf (">>程序用时%lf\n",duration);
	return 0;
}

int copy_route (int* from_arr,int* to_arr)
{
	int change_counter=0,i;
	for (i=0;i<Node_num;i++){
		if(from_arr[i]!=to_arr[i]){
			to_arr[i] = from_arr[i];
			change_counter++;
		}
	}
	return change_counter;
} 

double route_len (int *Route)
{
	double len;
	int i;
	for (i=0;i<Node_num-1;i++){
		len += Distance(Route[i],Route[i+1]);
	}
	return len;
}

int recombine_route (int *Route)
{
	double p1=((double)rand()/(RAND_MAX+1.0));//Posibility_1
	double p2=((double)rand()/(RAND_MAX+1.0)) ;  
	int Node_1 = p1*Node_num;
	int Node_2 = p2*Node_num;
	int temp = Route [Node_1];
	Route [Node_1] = Route [Node_2];
	Route [Node_2] = temp;
	return Node_1*100+Node_2;
}

void init (void)
{
	int i;
	for (i=0;i<Node_num;i++){
		City_route[i] = i;
	}
}

double Distance (int From_node,int To_node)
{
	double distance;
	distance = sqrt((city_node[From_node][0]-city_node[To_node][0])*(city_node[From_node][0]-city_node[To_node][0])
	+(city_node[From_node][1]-city_node[To_node][1])*(city_node[From_node][1]-city_node[To_node][1]));
	return distance;
}
