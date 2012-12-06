#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

typedef struct _mytype_{
		unsigned int id;
		unsigned int age;
		struct rb_node node;
}mytype;

typedef struct _linknode_{
	struct _linknode_ *next;
	mytype node;
}linknode;

static struct rb_root mytree;
//Insert
int my_insert(struct rb_root *root,mytype *data){
		struct rb_node **new = &(root->rb_node);
		struct rb_node *parent=NULL;
		mytype *this ;
		while(*new){
				parent = *new;
				//		mytype *this = container_of(*new,mytype,node);
				this = rb_entry(parent,mytype,node);
				int result = data->age - this->age;

				if(result<0)
						new = &((*new)->rb_left);
				else if(result>0)
						new = &((*new)->rb_right);
//				else return 0;
				else{
					new = &((*new)->rb_right);								
				}
		}

		rb_link_node(&data->node,parent,new);
		rb_insert_color(&data->node,root);
		return 1;
}


//Search,return the id
mytype *my_search(struct rb_root *root,int age){
		struct rb_node *mynode =root->rb_node;
		while(mynode){
				mytype *mydata = rb_entry(mynode,mytype,node);
				int result = age-mydata->age;
				if(result<0) 
						mynode=mynode->rb_left;
				else if(result>0)
						mynode=mynode->rb_right;
				else return mydata;

		}
		return NULL;
}

//Delete the node according to the age
int my_delete(struct rb_root *root,int age){
		mytype *to_del=my_search(root,age);
		if(to_del){
			while((to_del=my_search(root,age))!=NULL){
				rb_erase(&to_del->node,&mytree);
				free(to_del);
			}
			return 1;
		}	//	printf("NO no no");
		return 0;
}


int main(void){
		int id_tem=0;
		for(id_tem=0;id_tem<20;id_tem++){
				mytype *mydata=(mytype*)malloc(sizeof(mytype));
				mydata->id=id_tem;
				mydata->age=rand()%100;
				my_insert(&mytree,mydata);  //inset each node into the tree
		}
		mytype *newdata=(mytype*)malloc(sizeof(mytype));
		newdata->id=id_tem+1;
		newdata->age=20;
		my_insert(&mytree,newdata);
		mytype *nedata=(mytype*)malloc(sizeof(mytype));
		nedata->id=id_tem+2;
		nedata->age=20;
		my_insert(&mytree,nedata);
		struct rb_node *node;
		for(node=rb_first(&mytree); node; node=rb_next(node))
				printf("%d  ",rb_entry(node,mytype,node)->age);
		printf("\n");
		int toDel = 20;
		int res = my_delete(&mytree,toDel);
		if(res==0)
			printf("No such node");

		else{
				struct rb_node *node;
				for(node=rb_first(&mytree);node;node=rb_next(node))
						printf("%d  ",rb_entry(node,mytype,node)->age);
				printf("\n");
		}
		linknode *head = (linknode *)malloc(sizeof(linknode));
		head->node = *rb_entry(rb_first(&mytree),mytype,node);
		head->next=NULL;	
		linknode *pre=head;
		for(node=rb_next(rb_first(&mytree));node;node=rb_next(node)){
			linknode *tmp = (linknode *)malloc(sizeof(linknode));
			tmp->node=*rb_entry(node,mytype,node);
			tmp->next=NULL;
			pre->next=tmp;
			pre=tmp;
		}
		linknode *ln=head;
		while(ln){
			printf("%d  ",(&(ln->node))->age);
			ln=ln->next;

		}
		return 1;
}


