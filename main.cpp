#include <iostream>
#include <ctype.h>
using namespace std;
#define MAXWORD 100
#define BUFSIZE 100
char buf[BUFSIZE];
char bufp=0;





struct tnode * addtree(struct tnode* p,char * w);
void treeprint(struct tnode*);
struct tnode * talloc(void);
char *strdup(char*);
int getword(char *,int );
int find_max(tnode* root);
tnode* DeleteNode(tnode* node, char val);
char* find_Name(tnode* root,int count);
bool Find(tnode* root, string wrd );
tnode* InsertNode(tnode* node, char* val,int num);

struct tnode{
    char *word;
    int count;
    struct tnode* left;
    struct tnode* right;
    void setData(char* w,int c);
    void DisplayWordMeaning();
};

int main() {
    struct tnode *root;
    struct tnode *root2;
    char word[MAXWORD]="now is\0";
    root=NULL;
    root2=NULL;
    while(getword(word,MAXWORD)!='1'){
        if(isalpha(word[0])){
            root=addtree(root,word);
        }
    }

    if(!(Find(root,"vlad"))){
        cout<<"Not found"<<endl;
    }
    if(!(Find(root,"id"))){
        cout<<"Not found"<<endl;
    }
    cout<<"TREE1 : "<<endl;
    treeprint(root);
    
    char* str = new char[MAXWORD];
    while(root!=NULL){
        if(find_max(root)!=0){
        int num = find_max(root);
        str=find_Name(root, num);
        root2=InsertNode(root2,str,num);
        root = DeleteNode(root, *str);
        }
        else{
            root=NULL;
        }
    }
    cout<<"TREE2 : "<<endl;
    treeprint(root2);
    return 0;
}



struct tnode* addtree(struct tnode* p,char * w){
    int cond;
    if(p==NULL){
        p=talloc();
        p->word=strdup(w);
        p->count=1;
        p->left=p->right=NULL;
    }
        else if((cond=strcmp(w,p->word))==0){
            p->count++;
        }
        else if(cond<0){
            p->left=addtree(p->left,w);
        }
        else{
            p->right=addtree(p->right,w);
        }
    return p;
}

void treeprint(struct tnode*p){
    if(p!=NULL){
        treeprint(p->left);
        p->count = p->count+1;
        cout<<p->count<<endl<<p->word<<endl;
        treeprint(p->right);
    }
}

char* strdup(char* s){
    char * p;
    p=(char*)malloc(strlen(s)+1);
    if(p!=NULL){
        strcpy(p,s);
    }
    return p;
}

struct tnode* talloc(void){
    return(struct tnode*)malloc(sizeof(struct tnode));
}

int getch(void){
    return (bufp>0)?buf[--bufp]:getchar();
}

void ungetch(int c){
    if(bufp>=BUFSIZE){
        printf("ungetch: too many characters\n");
    }
    else{
        buf[bufp++]=c;
    }
}

int getword(char * word,int lim){
    int c,getch(void);
    void ungetch(int);
    char * w =word;
    while(isspace(c=getch()));
    if(c!=EOF){
        *w++=c;
    }
    if(!isalpha(c)){
        *w='\0';
        return c;
    }
    for(;--lim>0;w++){
        if(!isalnum(*w=getch())){
            ungetch(*w);
            break;
        }
    }
    *w='\0';
    return word[0];
}

int find_max(tnode* root) {
    if (root == NULL) {
        return 0;
    }
    int max_l = max(find_max(root->left), root->count);
    int max_r = max(find_max(root->right), root->count);
    return max(max_l, max_r);
}


char* find_Name(tnode* root,int count) {
    char* str = new char[MAXWORD];
    if(root != NULL)
    {
        if(root->count == count){
           str =root->word;
            return  str;
        }
        
        find_Name(root->left,count);
        find_Name(root->right,count);
       
    }
    
    
    return 0;
}



void DeleteDictionary(tnode* root)
{
    if(root != NULL)
    {
        DeleteDictionary(root->left);
        DeleteDictionary(root->right);
        delete root;
    }
}


tnode* DeleteNode(tnode* node, char val){
    if(node == NULL)
        return node;
 
    if(val == *node->word){
 
        tnode* tmp;
        if(node->right == NULL)
            tmp = node->left;
        else {
 
            tnode* ptr = node->right;
            if(ptr->left == NULL){
                ptr->left = node->left;
                tmp = ptr;
            } else {
 
                tnode* pmin = ptr->left;
                while(pmin->left != NULL){
                    ptr  = pmin;
                    pmin = ptr->left;
                }
                ptr->left   = pmin->right;
                pmin->left  = node->left;
                pmin->right = node->right;
                tmp = pmin;
            }
        }
 
        delete node;
        return tmp;
    } else if(val < *node->word)
        node->left  = DeleteNode(node->left, val);
    else
        node->right = DeleteNode(node->right, val);
    return node;
}

void tnode::DisplayWordMeaning()
{
    count += 1;
    cout << "Word        : "  << word << "\n" << "Count     : " << count << endl ;
    cout << "_____________________________________" << endl;
}
bool Find(tnode* root, string wrd )
{
    if(root != NULL)
    {

        if(Find(root->left, wrd ) == true)  return true;
        if(Find(root->right, wrd ) == true) return true;
        if(wrd == root->word)
        {
            cout<<root->word<<endl;
            root->count= root->count+1;
            return true;
        }
        else
            return false;

    }
    else return false;
}



void tnode::setData(char* w,int c)
{
    word = w;
    count =c;
}

void Edit(tnode* root, char* wrd , char* newWrd,int cnt)
{
    if(root != NULL)
    {
        Edit(root->left,wrd,newWrd,cnt );
        Edit(root->right,wrd,newWrd,cnt);
        if(wrd == root->word)
        {
            // edit here
            root->setData(newWrd,cnt);
        }
    }
}


tnode* InsertNode(tnode* node, char* val,int num){
    if(node == NULL){
        node = new (std::nothrow) tnode();
        if(node != NULL){
            node->word  = val;
            node->left = node->right = NULL;
        }
        return node;
    }
 
    if(num < node->count)
        node->left  = InsertNode(node->left, val,num);
    else
        node->right = InsertNode(node->right, val,num);
    return node;
}
 


