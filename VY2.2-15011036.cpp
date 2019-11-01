#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	struct node{																//Binary Tree i�in node olu�turuluyor
    int kimlikno;																//Kimlikleri haf�zada tutuldu�u de�i�ken
    char ad[30],soyad[30];														//Kimlik isim ve soyisimlerinin tutuldu�u de�i�ken
    struct node *left, *right;													//Sa�daki ve Soldaki nodelara eri�mek i�in
	int *friendsID;																//Ki�inin arkada�lar�n�n haf�zada tutuldu�u de�i�ken
	};
	
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct node *newNode(int kimlikno, int* friendsID, char* ad, char* soyad){	//Yeni node olu�turmak i�in fonksiyon
    	struct node *temp =  (struct node *)malloc(sizeof(struct node));		//Yeni ge�ici node olu�turuyor
    	temp->friendsID=(int*)malloc(3*sizeof(int));							//Arkada�lar i�in dinamic memory olu�turuyor
    	temp->friendsID[0]=friendsID[0];										
    	temp->friendsID[1]=friendsID[1];
    	temp->friendsID[2]=friendsID[2];										//Struct yap�s�n i�ine de�erleri at�yor
    	temp->kimlikno = kimlikno;
    	strcpy(temp->ad, ad);
    	strcpy(temp->soyad, soyad);
   		temp->left = temp->right = NULL;										//Yeni nodun sa� ve sol d���mleri olu�turuyor
    	return temp;
	}				
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
	struct node* insert(struct node* node, int* kimlikno,int** friendsID, char** ad, char** soyad, int x,int boyut, int N){
		if(x>=0 && x<N)															//insert fonksiyonu dengeli a�aca uygun yeni eleman eklemek i�in
			if(node == NULL)
			node=newNode(kimlikno[x],friendsID[x],ad[x],soyad[x]);				//her seferinde boyutun yar�s�n� x'e ekleyip ��kararak yeni
																				//yeni yerlere do�ru s�rada yerle�tirme yap�yor
    	if(boyut>0){															
    			node->right = insert(node->right, kimlikno, friendsID, ad, soyad, x+boyut, boyut/2,N);
				node->left = insert(node->left, kimlikno, friendsID, ad, soyad, x-boyut, boyut/2,N);
    	}
    	return node;
	}
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
 	void printInOrder(struct node *root){										//In order d�zeninde a�ac� okuyor
    	if (root != NULL){
       	 printInOrder(root->left);
       	 printf("%d -> %s %s Arkadaslari= %d - %d - %d\n", root->kimlikno, root->ad, root->soyad, root->friendsID[0], root->friendsID[1], root->friendsID[2]);
         printInOrder(root->right);
    	}
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	struct node* insertNewUser(struct node* node, int kimlikno, int* friendsID, char ad[20], char soyad[20]){				   //A
 																				//Yeni kullanici eklemek i�in kullanilan fonksiyon
    if (node == NULL) return newNode(kimlikno, friendsID, ad, soyad);
 	
    if (kimlikno == node->kimlikno)
        return node;
    else if (kimlikno < node->kimlikno)
        node->left  = insertNewUser(node->left, kimlikno, friendsID, ad, soyad);//E�er kimlik no k���kse sol node �a��r�l�r
        																		//��nk� sol node un b�t�n elemanlar� o node'dan k���kt�r
 	else 
 		node->right = insertNewUser(node->right, kimlikno, friendsID, ad, soyad);//E�er kimlik no k���kse sa� node �a��r�l�r
    return node;																//��nk� sa� node un b�t�n elemanlar� o node'dan k���kt�r
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	struct node* deleteUser(struct node* node, int kimlikno){					//Agactan kullanici silmek icin kullanilan fonksiyon
 		if(node == NULL) return node;	
 		else if(node->kimlikno > kimlikno)										//Do�ru node'un bulmaya �al���yor
			node->left=deleteUser(node->left,kimlikno);							
		else if(node->kimlikno < kimlikno)
			node->right=deleteUser(node->right,kimlikno);
		else if(node->kimlikno == kimlikno){
			if(node->left != NULL){
				node->kimlikno = node->left->kimlikno;							//Do�ru node bulundu�unda sol alt�ndaki node'un de�erleri
				strcpy(node->ad, node->left->ad);								//Bu node'un i�ine yaz�l�yor
    			strcpy(node->soyad, node->left->soyad);							///Ve sol alttaki nodeun kimli�i tekrar kimlikno atan�yor
    			kimlikno=node->left->kimlikno;									
    			node->friendsID[0]=node->left->friendsID[0];
    			node->friendsID[1]=node->left->friendsID[1];
    			node->friendsID[2]=node->left->friendsID[2];					
    			node->left=deleteUser(node->left, node->left->kimlikno);		//B�ylece b�t�n sol alttakiler bi sa� �ste yaz�l�yor
			}else{
				node=NULL;
			}	
	 	}
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	void contains(struct node* node, int kimlikno){								//Aranan Eleman� bulan fonksiyor
		if(node == NULL)
			printf("Aradiginiz eleman yoktur.\n");								//E�er b�y�kse sa�daki node'a k���kse soldaki node'a gidiyor
		else if (node->kimlikno == kimlikno)									//E�er e�itse o node'u ekrana yazdiriyor
			printf("Aradiginiz kimligin ad soyadi= %s %s Arkadaslari= %d - %d - %d\n", node->ad, node->soyad, node->friendsID[0], node->friendsID[1], node->friendsID[2]);
		else if(node->kimlikno > kimlikno)
			contains(node->left, kimlikno);
		else if(node->kimlikno < kimlikno)
			contains(node->right, kimlikno);
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	void findfriends(struct node* node,struct node* temp,int kimlikno){			//Verilen kimli�in arkada�lar� a�a�ta var m� kontrol ediyor
	 	if(node == NULL)														//Var ise ekrana yazd�r�yor
			printf("Aradiginiz eleman yoktur.\n");								//E�er node null kadar gidiyorsa eleman�n olmad��� yaz�yor
		else if (node->kimlikno == kimlikno){
			printf("Arkadaslari=\n");											//E�er node bulunursa contain ile arkada�lar� aran�yor
			contains(temp,node->friendsID[0]);
 			contains(temp,node->friendsID[1]);
 			contains(temp,node->friendsID[2]);
		}else if(node->kimlikno > kimlikno)										//E�er node b�y�ksa sol d���me e�er node k���kse sa� d���me gidiyor
			findfriends(node->left,temp, kimlikno);					
		else if(node->kimlikno < kimlikno)
			findfriends(node->right,temp, kimlikno);
																				  	   
	 };																							 	 			  
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 int Size(struct node* node, int size){											//A�ac�n eleman say�s�n� say�yor
 	if(node != NULL){
 	size++;
 	size=Size(node->right, size);
 	size=Size(node->left, size);
 	}
 	return size;
 }	
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void printNext(struct node* node, int kimlik){								//A�ac�n alt a�a�lar�n� yazd�ran fonksiyon
    	if(node == NULL)														//E�er node yoksa null d�n�yor ve ekrana bulunamad��� yazd�r�yor
			printf("Aradiginiz eleman yoktur.\n");					
		else if (node->kimlikno == kimlik){										//E�er bulunursa o d���m�n sa� ve sol nodelar�n� ve bu node'lar�n alt�ndaki 	
			printInOrder(node->left);											//elemanlar� ekrana yazd�r�yor
			printInOrder(node->right);
		}else if(node->kimlikno > kimlik)										//E�er node b�y�kse soldaki k���kse sa�daki node'u tekrar fonskiyona solluyor
			printNext(node->left, kimlik);
		else if(node->kimlikno < kimlik)
			printNext(node->right, kimlik);
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void printGreater(struct node* node, int kimlik){							//Verilen kimlikten b�y�k kimlik noya sahip ki�ileri ekrana yazd�ran fonksiyon
		if(node == NULL)														//E�er node yoksa null d�n�yor ve ekrana bulunamad��� yazd�r�yor
			printf("Aradiginiz eleman yoktur");
		else if(node->kimlikno < kimlik)										//E�er node k���kse sa�daki node �a��r�l�yor
			printGreater(node->right, kimlik);
		else if(node->kimlikno == kimlik)										//E�er e�itse sa� node'u ve node'un alt�ndaki elemanlar� yazd�r�yor
			printInOrder(node->right);
		else if(node->kimlikno > kimlik){										//E�er node b�y�kse node'uve node'un sol a�ac�n� ekrana yazd�r�yor
			printf("- %d -> %s %s\nArkadaslari= %d - %d - %d\n", node->kimlikno, node->ad, node->soyad, node->friendsID[0], node->friendsID[1], node->friendsID[2]);
			printInOrder(node->right);											//Ve sol a�ac� fonskiyona tekrar yolluyor
			printGreater(node->left,kimlik);
		}
	}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int main(){
    struct node *root = NULL;
    int *diziKimlik,**friends;													//diziKimlik file'dan okunanlar� tutan kimlikno,friends  
    int i,j,menu,boyut=0;														//arkada�lar� tutucu,boyut toplam eleman say�s�n�n tutucu, 
	int arklar[3];																//arklar arkada�lar� tutucu, diziAd ve diziSoyad file'dan 
    char **diziAd, **diziSoyad; 												//okunanlar� tutucu,ekleAd ve ekleSoyad 1. i�lemdeki de�i�kenleri tutar
    																			//sil kimlik 2. i�lem, friendkimlik 4. i�lem,size 7i�lem
	FILE *fp;																	//altAgacKimlik 5. i�lem, buyukKimlik 6. i�lem i�in gerekli de�i�ken
	int ekleKimlik,silKimlik,arananKimlik,friendkimlik,altAgacKimlik,buyukKimlik,size=0;
	char ekleAd[30],ekleSoyad[30];
	diziAd=(char**)malloc(35*sizeof(char*));									//Dizi ve matrislere gerekli yerler malloc ile ayr�lmaktad�r
	for(i=0;i<32;i++)
	diziAd[i]=(char*)malloc(50*sizeof(char));
	diziSoyad=(char**)malloc(35*sizeof(char*));
	for(i=0;i<32;i++)
	diziSoyad[i]=(char*)malloc(50*sizeof(char));
	friends=(int**)malloc(35*sizeof(int*));
	for(i=0;i<32;i++)
		friends[i]=(int*)malloc(4*sizeof(int));
	diziKimlik=(int*)malloc(35*sizeof(int));
	
	fp=fopen("input.txt","r");													//input.txt dosyas� okuma modunda fp file pointer�n�n i�ine at�l�yor
	char *str=(char*)malloc(50*sizeof(char));									//str de�i�keni i�in gerekli yerler malloc ile a��l�yor
	char *pch;

	 do{
    	
    fgets(str,50,fp);															//Fonksiyonun �nce ilk sat�r�n�n 50 karakteri str dizisinin i�ine at�l�yor
    																			//Sonras�nda i�inden s�ras�yla kimlik nolar, isimler, soyisimler, arkada�lar
    pch = strtok (str," ,-");													//Gerekli de�i�kenlerin i�ine at�l�yor
    diziKimlik[boyut]=atoi(pch);
    
    pch = strtok (NULL," ,-");
    strcpy(diziAd[boyut],pch);
   
    pch = strtok (NULL," ,-");
    strcpy(diziSoyad[boyut],pch);
    
    pch = strtok(NULL," ,-");
    friends[boyut][0] = atoi(pch);
    
    pch = strtok(NULL," ,-");
    friends[boyut][1] = atoi(pch);
    
    pch = strtok(NULL," ,-");
    friends[boyut][2] = atoi(pch);
    
	boyut++;
  	}while(feof(fp) == NULL);													//Dosyan�n sonuna kadar d�n�yor ve her d�n��te boyut 1 artt�r�l�yor
  	
			
	root = insert(root, diziKimlik, friends, diziAd, diziSoyad, boyut/2,(boyut/4)+1,boyut);
	for(i=0;i<boyut;i++)														//�nce dengeli bir a�a� olu�turulup sonra eksik elemanlar varsa ekleniyor
	root=insertNewUser(root,diziKimlik[i],friends[i],diziAd[i],diziSoyad[i]);
	
	do{																			//Menu yazd�r�l�yor
    printf("\n1.Kullanici ekle\n2.Kullanici silme\n3.Kullanici arama\n4.Arkadas arama\n");
	printf("5.Alt agac yazdirma\n6.Kendisinden buyuk elemanlari yazdirma\n7.Size yazdirma\n8.Binary Tree yazdirma\n9. Cikis");
	printf("\nYapmak istediginiz islemi seciniz=");
    scanf("%d",&menu);															//Menu de�i�kenine g�re i�lem yap�l�yor
    system("CLS");
    switch(menu){
    	
    case 1:																		//1. durumda kullan�c� ekleme yap�l�yor
 	printf("Eklemek istediginiz kullaniciyi giriniz\nAd=");
 	scanf("%s",ekleAd);
 	printf("Soyad=");
    scanf("%s", ekleSoyad);
    printf("Kimlik no=");
    scanf("%d", &ekleKimlik);
    printf("Arkadaslari=");
    scanf("%d %d %d",&arklar[0],&arklar[1],&arklar[2]);
 	root=insertNewUser(root,ekleKimlik,arklar,ekleAd,ekleSoyad);				//insertNewUser fonksiyonu ile ekleme yap�l�yor
 	
 	break;
 	
 	case 2:																		//2. durumda arkada� silme yap�l�yor
    printf("Silmek istediginiz kimligi giriniz=");
    scanf("%d",&silKimlik);
    root=deleteUser(root,silKimlik);											//deleteUser fonksiyonu ile silme i�lemi yap�l�yor
 	break;
 	
 	case 3:																		//3. durumda arkada� arama yap�l�yor
 	printf("Aramak istediginiz elemani giriniz=");
 	scanf("%d",&arananKimlik);
 	contains(root,arananKimlik);												//Contains fonksiyonu ile ki�i aran�yor
 	break;
 	
 	case 4:																		
 		printf("Arkadaslarini aramak istediginiz kisinin kimligini giriniz=");	//4. durumda Ki�inin arkada�lar� bulunuyor
 		scanf("%d",&friendkimlik);
 		findfriends(root,root,friendkimlik);									//findfriends fonksiyonu ile arkada�lar� ekrana yazd�r�l�yor
 	break;
 	
	case 5:																		//5. durumda Ki�inin node'unun alt a�a�lar� yazd�r�l�yor
 	printf("Alt agaci yazdirmak istediginiz kimligi giriniz=");
 	scanf("%d",&altAgacKimlik);
 	printNext(root,altAgacKimlik);												//printNext fonskiyonu ile alt a�a�lar� yazd�r�l�yor
	break;
	
 	case 6:																		//6. durumda kendisinden kimlik noya g�re b�y�k node'lar yazd�r�l�yor
 	printf("Kendisinden buyuk elemanlari yazdirmak istediginiz kimligi giriniz=");
 	scanf("%d",&buyukKimlik);
 	printGreater(root,buyukKimlik);												//printGreater fonksiyonu ile b�y�k elemanlar yazd�r�l�yor
 	break; 
 	
 	case 7:																		//7. durumda a�ac�n size � yazd�r�l�yor
 	printf("Binary Tree Size=%d\n",Size(root,size));							//size fonksinu ile size yazd�r�l�yor
 	break;
 	
 	case 8:																		//8. durumda printInOrder fonksiyonu ile elemanlar�n hepsi yazd�r�l�yor
 	printInOrder(root);
	break;
	
	case 9:																		//��k�� gelirse hatal� tu�lad� alg�lanmas� diye case 9 default'a girmiyor
	break;
	
	default :																	//1 ile 9 aras�nda tu�lan�lmad���n� g�steriyor
	printf("Listeden birini tuslayiniz!\n");
	break;
 }
 
 }while(menu != 9);																//��k��a bas�lmad��� s�rece program devam ediyor
 
    return 0;
}


