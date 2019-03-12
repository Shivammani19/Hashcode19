#include <iostream>
#include <fstream>
using namespace std;

typedef struct photo{
    int id[2];
    char hv;
    int tagCount;
    int v;
    string tags[100];
    struct photo *next;
}photo;
photo *start=NULL;

int main(){
    // Input file
    ifstream file("e_shiny_selfies.txt");

    // Assign variables
    int n;
    file>>n;
    for(int i=0;i<n;i++){
        photo *p=new photo;
        p->id[0]=i;
        file>>p->hv>>p->tagCount;
        p->v=-1;
        string s;
        for(int i=0;i<p->tagCount;i++){
            file>>s;
            p->v++;
            p->tags[p->v]=s;
        }
        p->next=NULL;

        photo *ptr=start;
        if(ptr==NULL){
            start=p;
        }else{
            while(ptr->next!=NULL){
                ptr=ptr->next;
            }
            ptr->next=p;
        }
    }

    // Arrange photo nodes
    int merge=0,count=0;
    photo *ptr=start;
    photo *temp;
    while(ptr!=NULL){
        if(ptr->hv=='V'){
            if(merge==0){
                ptr->hv='H';
                temp=ptr;
                count++;
            }else{
                temp->id[1]=ptr->id[0];
                int tempCount=temp->tagCount;
                for(int i=0;i<ptr->tagCount;i++){
                    int f=0;
                    for(int j=0;j<tempCount;j++){
                        //cout<<ptr->tags[i]<<temp->tags[j]<<endl;
                        if(ptr->tags[i]==temp->tags[j]){
                            f=1;
                            break;
                        }
                        if(f==0 && j==tempCount-1){
                            temp->tagCount++;
                            temp->v++;
                            temp->tags[temp->v]=ptr->tags[i];
                            //cout<<temp->tags[temp->v]<<endl;
                        }
                        //cout<<temp->tagCount<<endl;
                    }
                }
                cout<<endl;
                /* for(int i=0;i<temp->tagCount;i++){
                    for(int j=0;j<ptr->tagCount;j++){
                        cout<<temp->tags[i]<<" "<<ptr->tags[j]<<endl;
                        
                    }
                } */
            }
            merge=!merge;
        }else
            count++;
        ptr=ptr->next;
    }



    // Save output file
    ofstream ofile("output5.txt");
    ofile<<count<<endl;
    ptr=start;
    while(ptr!=NULL){
        if(ptr->hv=='H'){
            ofile<<ptr->id[0];
            if(ptr->id[1]){
                ofile<<" "<<ptr->id[1];
            }
            ofile<<endl;
        }
        ptr=ptr->next;
    }
    
}
