#include<string.h>
#include<stdio.h>
#include<stdlib.h>

	struct node{																//Binary Tree i�in node olu�turuluyor
    int data;																	//Kimlik no tutmak i�in de�i�ken tan�mlan�yor
    struct node *left, *right;													//Sa�daki ve Soldaki nodelara eri�mek i�in Struct node pointer yap�l�yor
	};
	
	
 	void inorder(struct node *root){											//In order d�zeninde a�ac� okuyor
    	if (root != NULL)
    	{																		//Her seferinde �nce soldaki node u �a��r�yor sonra soldakiler bitince ekrana 
       	 inorder(root->left);													//yazd�r�p sa�dakileri aramaya ba�l�yor
       	 printf("%d ", root->data);
         inorder(root->right);
    	}
	}

	struct node *newNode(int item){												//Yeni node olu�turmak i�in fonksiyon
    	struct node *temp =  (struct node *)malloc(sizeof(struct node));		//Yeni ge�ici node olu�turuyor
    	temp->data = item;														//At�lmak istenen kimlik node i�ine at�l�yor
   		temp->left = temp->right = NULL;										//Sa�daki ve soldaki nodelar NULL lan�yor
    	return temp;															//Olu�turulan node geri d�n�ypr
	}				
			
	struct node* insert(struct node* node, int* data, int x,int boyut,int N){	//A�aca eleman eklemek i�in fonksiyon
		if(x>=0 && x<N)															//E�er eleman var boyut s�n�rlar� i�inde ise
			if(node == NULL)													//ve d���m bo� ise oraya eleman yazd�r�l�yor
			node=newNode(data[x]);
		
    	if(boyut>0){															//Boyut s�f�rdan b�y�k oldu�u s�rece a�ac�n 
    																			//Sa� taraf�ndaki ortanca de�er ve sol taraf�ndaki ortanca
    			node->right = insert(node->right, data, x+boyut, boyut/2,N);	//De�er �a��r�l�p onlar yine insert fonksiyonu ile kontrol ediliyor
				node->left = insert(node->left, data, x-boyut, boyut/2,N);
    	}
    	return node;															//Geriye node'un yeni hali at�l�yor
	}
 
 	struct node* add(struct node* node, int data){								//Binary tree'nin en ucuna eleman y�klemek i�in fonksiyon
 	
    
    if (node == NULL) return newNode(data);										//E�er d���m bo� ise oraya eleman yazd�r�l�yor
 
    if (data == node->data)														//E�er d���mde verilen data e�it ise var demektir ve
        return node;															//eleman yazd�r�lmadan node geri d�ner
    else if (data < node->data)													//E�er data b�y�kse node sola gider tekrar add fonksiyonu ile aran�r
        node->left  = add(node->left, data);
 	else 																		//E�er data k���kse node sola gider tekrar add fonksiyonu ile taran�r
 		node->right = add(node->right, data);
    return node;																//Geriye node'un yeni hali d�ner
	}
 

	 
	int main(){
       
    struct node *root = NULL;													//Binary tree i�in gerekli node pointer�
    
    int *dizi;																	//Dosyadan okunan elemanlar�n int de�erinde tutulaca�� dizi
    int i,boyut=0;																//Boyut dosyadan okunan elemanlar�n say�s�n� tutan de�i�ken
    char* str;																	//Dosyadan okunan elemanlar�n char t�r�nde tutulaca�� dizi
    FILE *fp;																	//Dosyadan okuma yapmak i�in dosya pointer�
    fp=fopen("input1.txt","r");													//Dosya okuma modunda a��l�yor
    
	str=(char*)malloc(100*sizeof(char));										//Gerekli dinamik haf�za yerleri a��l�yor
    dizi=(int*)malloc(40*sizeof(int));
    
    str=fgets(str,100,fp);														//Dosyadan ilk sat�r�n 100 karakteri al�n�yor
    char *pch = strtok (str," ,.-");											//pch de�i�keninin i�ine str dizisindeki elemanlar " ,-" karakterleri olmadan
    dizi[boyut]=atoi(pch);														//dizi �eklinde s�rayla at�l�yor,atoi fonksiyonu ile pch string dizisini int
    boyut++;																	//dizisine �eviriyor ve boyut bir art�yor

  	while (pch != NULL)															//pch de�i�keni NULL g�rene kadar yani str dizisinin bitene kadar d�n�yor
  	{
    pch = strtok (NULL, " ,.-");												//pch de�i�keninin i�ine str dizisindeki elemanlar " ,-" karakterleri olmadan
    dizi[boyut]=atoi(pch);														//dizi �eklinde s�rayla at�l�yor,atoi fonksiyonu ile pch string dizisini int
    boyut++;																	//dizisine �eviriyor ve boyut her seferinde bir art�yor
  	}
  	boyut--;																	//boyut 1 fazla d�nd��� i�in 1 azalt�l�yor
	root = insert(root, dizi, boyut/2,(boyut/4)+1,boyut);						//insert fonksiyonu ile dengeli a�a� i�ine elemanlar yazd�r�l�yor
	
	for(i=0;i<boyut;i++)														//Eklenmeyen elemanlar add fonksiyonu ile dengeli bir �ekilde a�ac�n u�lar�na
	root=add(root,dizi[i]);														//ekleniyor
	
	printf("Agactan okuma\n");													//inOrder fonksiyonu ile a�a� ekrana yazd�r�l�yor
    inorder(root);
 
    return 0;
}

