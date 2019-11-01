#include<string.h>
#include<stdio.h>
#include<stdlib.h>

	struct node{																//Binary Tree için node oluþturuluyor
    int data;																	//Kimlik no tutmak için deðiþken tanýmlanýyor
    struct node *left, *right;													//Saðdaki ve Soldaki nodelara eriþmek için Struct node pointer yapýlýyor
	};
	
	
 	void inorder(struct node *root){											//In order düzeninde aðacý okuyor
    	if (root != NULL)
    	{																		//Her seferinde önce soldaki node u çaðýrýyor sonra soldakiler bitince ekrana 
       	 inorder(root->left);													//yazdýrýp saðdakileri aramaya baþlýyor
       	 printf("%d ", root->data);
         inorder(root->right);
    	}
	}

	struct node *newNode(int item){												//Yeni node oluþturmak için fonksiyon
    	struct node *temp =  (struct node *)malloc(sizeof(struct node));		//Yeni geçici node oluþturuyor
    	temp->data = item;														//Atýlmak istenen kimlik node içine atýlýyor
   		temp->left = temp->right = NULL;										//Saðdaki ve soldaki nodelar NULL lanýyor
    	return temp;															//Oluþturulan node geri dönüypr
	}				
			
	struct node* insert(struct node* node, int* data, int x,int boyut,int N){	//Aðaca eleman eklemek için fonksiyon
		if(x>=0 && x<N)															//Eðer eleman var boyut sýnýrlarý içinde ise
			if(node == NULL)													//ve düðüm boþ ise oraya eleman yazdýrýlýyor
			node=newNode(data[x]);
		
    	if(boyut>0){															//Boyut sýfýrdan büyük olduðu sürece aðacýn 
    																			//Sað tarafýndaki ortanca deðer ve sol tarafýndaki ortanca
    			node->right = insert(node->right, data, x+boyut, boyut/2,N);	//Deðer çaðýrýlýp onlar yine insert fonksiyonu ile kontrol ediliyor
				node->left = insert(node->left, data, x-boyut, boyut/2,N);
    	}
    	return node;															//Geriye node'un yeni hali atýlýyor
	}
 
 	struct node* add(struct node* node, int data){								//Binary tree'nin en ucuna eleman yüklemek için fonksiyon
 	
    
    if (node == NULL) return newNode(data);										//Eðer düðüm boþ ise oraya eleman yazdýrýlýyor
 
    if (data == node->data)														//Eðer düðümde verilen data eþit ise var demektir ve
        return node;															//eleman yazdýrýlmadan node geri döner
    else if (data < node->data)													//Eðer data büyükse node sola gider tekrar add fonksiyonu ile aranýr
        node->left  = add(node->left, data);
 	else 																		//Eðer data küçükse node sola gider tekrar add fonksiyonu ile taranýr
 		node->right = add(node->right, data);
    return node;																//Geriye node'un yeni hali döner
	}
 

	 
	int main(){
       
    struct node *root = NULL;													//Binary tree için gerekli node pointerý
    
    int *dizi;																	//Dosyadan okunan elemanlarýn int deðerinde tutulacaðý dizi
    int i,boyut=0;																//Boyut dosyadan okunan elemanlarýn sayýsýný tutan deðiþken
    char* str;																	//Dosyadan okunan elemanlarýn char türünde tutulacaðý dizi
    FILE *fp;																	//Dosyadan okuma yapmak için dosya pointerý
    fp=fopen("input1.txt","r");													//Dosya okuma modunda açýlýyor
    
	str=(char*)malloc(100*sizeof(char));										//Gerekli dinamik hafýza yerleri açýlýyor
    dizi=(int*)malloc(40*sizeof(int));
    
    str=fgets(str,100,fp);														//Dosyadan ilk satýrýn 100 karakteri alýnýyor
    char *pch = strtok (str," ,.-");											//pch deðiþkeninin içine str dizisindeki elemanlar " ,-" karakterleri olmadan
    dizi[boyut]=atoi(pch);														//dizi þeklinde sýrayla atýlýyor,atoi fonksiyonu ile pch string dizisini int
    boyut++;																	//dizisine çeviriyor ve boyut bir artýyor

  	while (pch != NULL)															//pch deðiþkeni NULL görene kadar yani str dizisinin bitene kadar dönüyor
  	{
    pch = strtok (NULL, " ,.-");												//pch deðiþkeninin içine str dizisindeki elemanlar " ,-" karakterleri olmadan
    dizi[boyut]=atoi(pch);														//dizi þeklinde sýrayla atýlýyor,atoi fonksiyonu ile pch string dizisini int
    boyut++;																	//dizisine çeviriyor ve boyut her seferinde bir artýyor
  	}
  	boyut--;																	//boyut 1 fazla döndüðü için 1 azaltýlýyor
	root = insert(root, dizi, boyut/2,(boyut/4)+1,boyut);						//insert fonksiyonu ile dengeli aðaç içine elemanlar yazdýrýlýyor
	
	for(i=0;i<boyut;i++)														//Eklenmeyen elemanlar add fonksiyonu ile dengeli bir þekilde aðacýn uçlarýna
	root=add(root,dizi[i]);														//ekleniyor
	
	printf("Agactan okuma\n");													//inOrder fonksiyonu ile aðaç ekrana yazdýrýlýyor
    inorder(root);
 
    return 0;
}

