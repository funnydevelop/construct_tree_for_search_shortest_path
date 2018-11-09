#include<iostream>
#include<cstdlib>
#include<list>
#include<queue>
#include<string>
#include<stack>
#include<cstdio>

using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))

struct forest {
	int value;
	forest ** next_node;
	forest * parent_node;
};
void construct_forest_root(struct forest**pf, int * tree_array, int len);
void construct_sub(struct forest *** sub, struct forest*parent, int * tree_array, int len, int value, int current_position);
void  search_from_forest(struct forest * fp,int len ,int step =0);
int main() {
	int tree_array[] = { 2,3,1,8,4 };
	int len = sizeof(tree_array) / sizeof(tree_array[0]);
	//构建森林
	forest * pf = NULL;
	construct_forest_root(&pf, tree_array, len);
	
	//打印数据
	cout << pf->next_node[0]->value << endl;
	cout << pf->next_node[1]->value << endl;
	cout << pf->next_node[0]->next_node[0]->value << endl;
	cout << pf->next_node[0]->next_node[1]->value << endl;
	cout << pf->next_node[0]->next_node[2]->value <<  endl;
	cout << pf->next_node[1]->next_node[0]->value << endl;
	search_from_forest(pf, len);
	system("pause");
	return 1;
}

void construct_forest_root(struct forest**pf, int * tree_array, int len) {

	*pf = new forest;
	(*pf)->value = 2;
	(*pf)->parent_node = NULL;
	(*pf)->next_node = NULL;
	construct_sub(&(*pf)->next_node, *pf, tree_array, len, (*pf)->value, 0);

}

void construct_sub(struct forest *** sub,
	struct forest*parent,
	int * tree_array,
	int len,
	int value,
	int current_position) {

	if (*sub == NULL) {
		*sub = new forest*[value];
	}
	for (int i = 0; i < value; i++) {
		(*sub)[i] = NULL;
		if (current_position + i + 1 < len) {
			(*sub)[i] = new forest;
			(*sub)[i]->value = tree_array[current_position + i + 1];
			(*sub)[i]->parent_node = parent;
			(*sub)[i]->next_node = NULL;
			if (tree_array[current_position + i + 1] != 4) {
				construct_sub(&((*sub)[i]->next_node),
					(*sub)[i],
					tree_array,
					len,
					tree_array[current_position + i + 1],
					current_position + i + 1);
			}
		}

	}

}
/*Next Step 遍历森林*/
void  search_from_forest(struct forest * fp,int len,int step) {
	if (fp != NULL ) {
		for (int i = 0; i < fp->value; i++) {
			if (fp->value == 4 && fp->next_node == NULL) {
				cout << "The step was : " << step << endl;
				break;
			}
			search_from_forest(fp->next_node[i], len, step+1);
		}
	}
}