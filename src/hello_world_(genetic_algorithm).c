#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

/*please note that this program treat type char as signed, different platform may produce different result */ 
typedef struct{
	char str[12];
	int score;
}offspring;
offspring global_child[1000][1000];


char* target = "Hello World!";
const int mutation_rate = 100;/*produces mutation with a probability of 1/100*/


void fitness(offspring* input){/*this is the fitness function that will score the child */
	int i;
	input->score = 0;
	for(i=0;i<12;i++){
		input->score -= abs(input->str[i] - target[i]);
	}

	return;
}


void string_random_create(offspring* input){
	int i;
	for(i=0;i<12;i++){
		input->str[i] = (rand()%95 + 32);/*choose character from 32 to 126*/
	}
	return;
}

void mate(offspring* parent, offspring* child){
	int pool[1000];/* We'll choose in this pool to see whether the parent has been chosen yet */
	memset(pool, 0, sizeof(pool));
	int not_chosen = 1000;
	int i;
	int j;
	int num = 0;
	int parent1 = -1;
	int parent2 = -1;
	int parent3 = -1;
	int parent4 = -1;
	int better1;
	int better2;
	while(not_chosen != 0){
		/*choose parent 1 with the number of not chosen numbers */
		parent1 = rand()%not_chosen + 1;
		/*choose parent 2 with the number of not chosen numbers*/
		parent2 = rand()%not_chosen + 1;
		while(parent2 == parent1){
			parent2 = rand()%not_chosen + 1;
		}
		j = -1;
		while(parent1 != 0){
			if(pool[j+1] == 1){
				j++;
			}
			else{
				j++;
				parent1--;
			}
		}
		parent1 = j;/*here we assign parent the number that is not used in pool randomly */
		j = -1;
		while(parent2 != 0){
			if(pool[j+1] == 1){
				j++;
			}
			else{
				j++;
				parent2--;
			}
		}
		parent2 = j;
		pool[parent1] = 1;
		pool[parent2] = 1;
		/*repeat the process to generate parent3 and parent4*/
		not_chosen -= 2;
		/*choose parent 3 with the number of not chosen numbers */
		/*choose parent 4 with the number of not chosen numbers*/
		parent3 = rand()%not_chosen + 1;
		parent4 = rand()%not_chosen + 1;
		while(parent4 == parent3){
			parent4 = rand()%not_chosen + 1;
		}
		j = -1;
		while(parent3 != 0){
			if(pool[j+1] == 1){
				j++;
			}
			else{
				j++;
				parent3--;
			}
		}
		parent3 = j;/*here we assign parent the number that is not used in pool randomly */
		j = -1;
		while(parent4 != 0){
			if(pool[j+1] == 1){
				j++;
			}
			else{
				j++;
				parent4--;
			}
		}
		parent4 = j;
		pool[parent3] = 1;
		pool[parent4] = 1;
		not_chosen -= 2;
		/*now that we have selected 4 parents, we are going to choose the better one out of parent1 and parent2, and choose one out of parent3 and parent4*/
		if(parent[parent1].score > parent[parent2].score){
			better1 = parent1;
		}
		else{
			better1 = parent2;
		}
		if(parent[parent3].score > parent[parent4].score){
			better2 = parent3;
		}
		else{
			better2 = parent4;
		}
		/*now we are going to do crossover with the selected parents */
		i = rand()%13;/*here i will be used as a separator of how we are going to do crossover with the parents */
		for(j=0;j<i;j++){
			child[num].str[j] = parent[better1].str[j];
			child[num+1].str[j] = parent[better2].str[j];
		}
		for(j=i;j<12;j++){
			child[num].str[j] = parent[better2].str[j];
			child[num+1].str[j] = parent[better1].str[j];
		}
		i = rand()%13;
		for(j=0;j<i;j++){
			child[num+3].str[j] = parent[better1].str[j];
			child[num+4].str[j] = parent[better2].str[j];
		}
		for(j=i;j<12;j++){
			child[num+3].str[j] = parent[better1].str[j];
			child[num+4].str[j] = parent[better2].str[j];
		}
		num += 4;
	}

}

void mutation(offspring* input){
	int i;
	for(i=0;i<12;i++){
		if(rand()%mutation_rate == 0){
			/*mutate*/
			input->str[i] = rand()%95 + 32;
		}
		/*don't mutate*/
	}
}

int print_best_result(int generation, offspring* child){
	int result = -1;
	int i;
	int score = -1000000;/*setting to -1000000 as it is an impossible score to reach */
	for(i=0;i<1000;i++){
		if(child[i].score > score){
			score = child[i].score;
			result = i;
		}
	}
	printf("The best score in %d turn is %d : str= ", generation, score);
	for(i=0;i<12;i++){
		printf("%c",child[result].str[i]);
	}
	printf("\n");
	return score;

}

int main(){
	srand(time(NULL));
	int i;
	int j;
	int result;
	printf("See how the string evolves into \"Hello World!\"\n");
	for(i=0;i<1000;i++){
		for(j=0;j<1000;j++){
			memset(&global_child[i][j], 0, sizeof(offspring));
		}
	}
	for(i=0;i<1000;i++){
		string_random_create(&global_child[0][i]);/*these will be the first parents*/
		fitness(&global_child[0][i]);
	}
	for(i=1;i<999;i++){/*generation*/
		mate(global_child[i-1], global_child[i]);
		for(j=0;j<1000;j++){/*mutate offspring in the ith generation */
			mutation(&global_child[i][j]);
			fitness(&global_child[i][j]);/*calculate child fitness after mutation */
		}
		result = print_best_result(i,global_child[i]);/*print the best result of the ith generation */
		if(result == 0){
			break;
		}
	}
	return 0;
}
