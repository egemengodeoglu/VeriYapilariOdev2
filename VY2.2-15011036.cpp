#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	struct node{																//Binary Tree için node oluþturuluyor
    int kimlikno;																//Kimlikleri hafýzada tutulduðu deðiþken
    char ad[30],soyad[30];														//Kimlik isim ve soyisimlerinin tutulduðu deðiþken
    struct node *left, *right;													//Saðdaki ve Soldaki nodelara eriþmek için
	int *friendsID;																//Kiþinin arkadaþlarýnýn hafýzada tutulduðu deðiþken
	};
	
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct node *newNode(int kimlikno, int* friendsID, char* ad, char* soyad){	//Yeni node oluþturmak için fonksiyon
    	struct node *temp =  (struct node *)malloc(sizeof(struct node));		//Yeni geçici node oluþturuyor
    	temp->friendsID=(int*)malloc(3*sizeof(int));							//Arkadaþlar için dinamic memory oluþturuyor
    	temp->friendsID[0]=friendsID[0];										
    	temp->friendsID[1]=friendsID[1];
    	temp->friendsID[2]=friendsID[2];										//Struct yapýsýn içine deðerleri atýyor
    	temp->kimlikno = kimlikno;
    	strcpy(temp->ad, ad);
    	strcpy(temp->soyad, soyad);
   		temp->left = temp->right = NULL;										//Yeni nodun sað ve sol düðümleri oluþturuyor
    	return temp;
	}				
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
	struct node* insert(struct node* node, int* kimlikno,int** friendsID, char** ad, char** soyad, int x,int boyut, int N){
		if(x>=0 && x<N)															//insert fonksiyonu dengeli aðaca uygun yeni eleman eklemek için
			if(node == NULL)
			node=newNode(kimlikno[x],friendsID[x],ad[x],soyad[x]);				//her seferinde boyutun yarýsýný x'e ekleyip çýkararak yeni
																				//yeni yerlere doðru sýrada yerleþtirme yapýyor
    	if(boyut>0){															
    			node->right = insert(node->right, kimlikno, friendsID, ad, soyad, x+boyut, boyut/2,N);
				node->left = insert(node->left, kimlikno, friendsID, ad, soyad, x-boyut, boyut/2,N);
    	}
    	return node;
	}
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
 	void printInOrder(struct node *root){										//In order düzeninde aðacý okuyor
    	if (root != NULL){
       	 printInOrder(root->left);
       	 printf("%d -> %s %s Arkadaslari= %d - %d - %d\n", root->kimlikno, root->ad, root->soyad, root->friendsID[0], root->friendsID[1], root->friendsID[2]);
         printInOrder(root->right);
    	}
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	struct node* insertNewUser(struct node* node, int kimlikno, int* friendsID, char ad[20], char soyad[20]){				   //A
 																				//Yeni kullanici eklemek için kullanilan fonksiyon
    if (node == NULL) return newNode(kimlikno, friendsID, ad, soyad);
 	
    if (kimlikno == node->kimlikno)
        return node;
    else if (kimlikno < node->kimlikno)
        node->left  = insertNewUser(node->left, kimlikno, friendsID, ad, soyad);//Eðer kimlik no küçükse sol node çaðýrýlýr
        																		//Çünkü sol node un bütün elemanlarý o node'dan küçüktür
 	else 
 		node->right = insertNewUser(node->right, kimlikno, friendsID, ad, soyad);//Eðer kimlik no küçükse sað node çaðýrýlýr
    return node;																//Çünkü sað node un bütün elemanlarý o node'dan küçüktür
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	struct node* deleteUser(struct node* node, int kimlikno){					//Agactan kullanici silmek icin kullanilan fonksiyon
 		if(node == NULL) return node;	
 		else if(node->kimlikno > kimlikno)										//Doðru node'un bulmaya çalýþýyor
			node->left=deleteUser(node->left,kimlikno);							
		else if(node->kimlikno < kimlikno)
			node->right=deleteUser(node->right,kimlikno);
		else if(node->kimlikno == kimlikno){
			if(node->left != NULL){
				node->kimlikno = node->left->kimlikno;							//Doðru node bulunduðunda sol altýndaki node'un deðerleri
				strcpy(node->ad, node->left->ad);								//Bu node'un içine yazýlýyor
    			strcpy(node->soyad, node->left->soyad);							///Ve sol alttaki nodeun kimliði tekrar kimlikno atanýyor
    			kimlikno=node->left->kimlikno;									
    			node->friendsID[0]=node->left->friendsID[0];
    			node->friendsID[1]=node->left->friendsID[1];
    			node->friendsID[2]=node->left->friendsID[2];					
    			node->left=deleteUser(node->left, node->left->kimlikno);		//Böylece bütün sol alttakiler bi sað üste yazýlýyor
			}else{
				node=NULL;
			}	
	 	}
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	void contains(struct node* node, int kimlikno){								//Aranan Elemaný bulan fonksiyor
		if(node == NULL)
			printf("Aradiginiz eleman yoktur.\n");								//Eðer büyükse saðdaki node'a küçükse soldaki node'a gidiyor
		else if (node->kimlikno == kimlikno)									//Eðer eþitse o node'u ekrana yazdiriyor
			printf("Aradiginiz kimligin ad soyadi= %s %s Arkadaslari= %d - %d - %d\n", node->ad, node->soyad, node->friendsID[0], node->friendsID[1], node->friendsID[2]);
		else if(node->kimlikno > kimlikno)
			contains(node->left, kimlikno);
		else if(node->kimlikno < kimlikno)
			contains(node->right, kimlikno);
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	void findfriends(struct node* node,struct node* temp,int kimlikno){			//Verilen kimliðin arkadaþlarý aðaçta var mý kontrol ediyor
	 	if(node == NULL)														//Var ise ekrana yazdýrýyor
			printf("Aradiginiz eleman yoktur.\n");								//Eðer node null kadar gidiyorsa elemanýn olmadýðý yazýyor
		else if (node->kimlikno == kimlikno){
			printf("Arkadaslari=\n");											//Eðer node bulunursa contain ile arkadaþlarý aranýyor
			contains(temp,node->friendsID[0]);
 			contains(temp,node->friendsID[1]);
 			contains(temp,node->friendsID[2]);
		}else if(node->kimlikno > kimlikno)										//Eðer node büyüksa sol düðüme eðer node küçükse sað düðüme gidiyor
			findfriends(node->left,temp, kimlikno);					
		else if(node->kimlikno < kimlikno)
			findfriends(node->right,temp, kimlikno);
																				  	   
	 };																							 	 			  
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 int Size(struct node* node, int size){											//Aðacýn eleman sayýsýný sayýyor
 	if(node != NULL){
 	size++;
 	size=Size(node->right, size);
 	size=Size(node->left, size);
 	}
 	return size;
 }	
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void printNext(struct node* node, int kimlik){								//Aðacýn alt aðaçlarýný yazdýran fonksiyon
    	if(node == NULL)														//Eðer node yoksa null dönüyor ve ekrana bulunamadýðý yazdýrýyor
			printf("Aradiginiz eleman yoktur.\n");					
		else if (node->kimlikno == kimlik){										//Eðer bulunursa o düðümün sað ve sol nodelarýný ve bu node'larýn altýndaki 	
			printInOrder(node->left);											//elemanlarý ekrana yazdýrýyor
			printInOrder(node->right);
		}else if(node->kimlikno > kimlik)										//Eðer node büyükse soldaki küçükse saðdaki node'u tekrar fonskiyona solluyor
			printNext(node->left, kimlik);
		else if(node->kimlikno < kimlik)
			printNext(node->right, kimlik);
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void printGreater(struct node* node, int kimlik){							//Verilen kimlikten büyük kimlik noya sahip kiþileri ekrana yazdýran fonksiyon
		if(node == NULL)														//Eðer node yoksa null dönüyor ve ekrana bulunamadýðý yazdýrýyor
			printf("Aradiginiz eleman yoktur");
		else if(node->kimlikno < kimlik)										//Eðer node küçükse saðdaki node çaðýrýlýyor
			printGreater(node->right, kimlik);
		else if(node->kimlikno == kimlik)										//Eðer eþitse sað node'u ve node'un altýndaki elemanlarý yazdýrýyor
			printInOrder(node->right);
		else if(node->kimlikno > kimlik){										//Eðer node büyükse node'uve node'un sol aðacýný ekrana yazdýrýyor
			printf("- %d -> %s %s\nArkadaslari= %d - %d - %d\n", node->kimlikno, node->ad, node->soyad, node->friendsID[0], node->friendsID[1], node->friendsID[2]);
			printInOrder(node->right);											//Ve sol aðacý fonskiyona tekrar yolluyor
			printGreater(node->left,kimlik);
		}
	}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int main(){
    struct node *root = NULL;
    int *diziKimlik,**friends;													//diziKimlik file'dan okunanlarý tutan kimlikno,friends  
    int i,j,menu,boyut=0;														//arkadaþlarý tutucu,boyut toplam eleman sayýsýnýn tutucu, 
	int arklar[3];																//arklar arkadaþlarý tutucu, diziAd ve diziSoyad file'dan 
    char **diziAd, **diziSoyad; 												//okunanlarý tutucu,ekleAd ve ekleSoyad 1. iþlemdeki deðiþkenleri tutar
    																			//sil kimlik 2. iþlem, friendkimlik 4. iþlem,size 7iþlem
	FILE *fp;																	//altAgacKimlik 5. iþlem, buyukKimlik 6. iþlem için gerekli deðiþken
	int ekleKimlik,silKimlik,arananKimlik,friendkimlik,altAgacKimlik,buyukKimlik,size=0;
	char ekleAd[30],ekleSoyad[30];
	diziAd=(char**)malloc(35*sizeof(char*));									//Dizi ve matrislere gerekli yerler malloc ile ayrýlmaktadýr
	for(i=0;i<32;i++)
	diziAd[i]=(char*)malloc(50*sizeof(char));
	diziSoyad=(char**)malloc(35*sizeof(char*));
	for(i=0;i<32;i++)
	diziSoyad[i]=(char*)malloc(50*sizeof(char));
	friends=(int**)malloc(35*sizeof(int*));
	for(i=0;i<32;i++)
		friends[i]=(int*)malloc(4*sizeof(int));
	diziKimlik=(int*)malloc(35*sizeof(int));
	
	fp=fopen("input.txt","r");													//input.txt dosyasý okuma modunda fp file pointerýnýn içine atýlýyor
	char *str=(char*)malloc(50*sizeof(char));									//str deðiþkeni için gerekli yerler malloc ile açýlýyor
	char *pch;

	 do{
    	
    fgets(str,50,fp);															//Fonksiyonun önce ilk satýrýnýn 50 karakteri str dizisinin içine atýlýyor
    																			//Sonrasýnda içinden sýrasýyla kimlik nolar, isimler, soyisimler, arkadaþlar
    pch = strtok (str," ,-");													//Gerekli deðiþkenlerin içine atýlýyor
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
  	}while(feof(fp) == NULL);													//Dosyanýn sonuna kadar dönüyor ve her dönüþte boyut 1 arttýrýlýyor
  	
			
	root = insert(root, diziKimlik, friends, diziAd, diziSoyad, boyut/2,(boyut/4)+1,boyut);
	for(i=0;i<boyut;i++)														//Önce dengeli bir aðaç oluþturulup sonra eksik elemanlar varsa ekleniyor
	root=insertNewUser(root,diziKimlik[i],friends[i],diziAd[i],diziSoyad[i]);
	
	do{																			//Menu yazdýrýlýyor
    printf("\n1.Kullanici ekle\n2.Kullanici silme\n3.Kullanici arama\n4.Arkadas arama\n");
	printf("5.Alt agac yazdirma\n6.Kendisinden buyuk elemanlari yazdirma\n7.Size yazdirma\n8.Binary Tree yazdirma\n9. Cikis");
	printf("\nYapmak istediginiz islemi seciniz=");
    scanf("%d",&menu);															//Menu deðiþkenine göre iþlem yapýlýyor
    system("CLS");
    switch(menu){
    	
    case 1:																		//1. durumda kullanýcý ekleme yapýlýyor
 	printf("Eklemek istediginiz kullaniciyi giriniz\nAd=");
 	scanf("%s",ekleAd);
 	printf("Soyad=");
    scanf("%s", ekleSoyad);
    printf("Kimlik no=");
    scanf("%d", &ekleKimlik);
    printf("Arkadaslari=");
    scanf("%d %d %d",&arklar[0],&arklar[1],&arklar[2]);
 	root=insertNewUser(root,ekleKimlik,arklar,ekleAd,ekleSoyad);				//insertNewUser fonksiyonu ile ekleme yapýlýyor
 	
 	break;
 	
 	case 2:																		//2. durumda arkadaþ silme yapýlýyor
    printf("Silmek istediginiz kimligi giriniz=");
    scanf("%d",&silKimlik);
    root=deleteUser(root,silKimlik);											//deleteUser fonksiyonu ile silme iþlemi yapýlýyor
 	break;
 	
 	case 3:																		//3. durumda arkadaþ arama yapýlýyor
 	printf("Aramak istediginiz elemani giriniz=");
 	scanf("%d",&arananKimlik);
 	contains(root,arananKimlik);												//Contains fonksiyonu ile kiþi aranýyor
 	break;
 	
 	case 4:																		
 		printf("Arkadaslarini aramak istediginiz kisinin kimligini giriniz=");	//4. durumda Kiþinin arkadaþlarý bulunuyor
 		scanf("%d",&friendkimlik);
 		findfriends(root,root,friendkimlik);									//findfriends fonksiyonu ile arkadaþlarý ekrana yazdýrýlýyor
 	break;
 	
	case 5:																		//5. durumda Kiþinin node'unun alt aðaçlarý yazdýrýlýyor
 	printf("Alt agaci yazdirmak istediginiz kimligi giriniz=");
 	scanf("%d",&altAgacKimlik);
 	printNext(root,altAgacKimlik);												//printNext fonskiyonu ile alt aðaçlarý yazdýrýlýyor
	break;
	
 	case 6:																		//6. durumda kendisinden kimlik noya göre büyük node'lar yazdýrýlýyor
 	printf("Kendisinden buyuk elemanlari yazdirmak istediginiz kimligi giriniz=");
 	scanf("%d",&buyukKimlik);
 	printGreater(root,buyukKimlik);												//printGreater fonksiyonu ile büyük elemanlar yazdýrýlýyor
 	break; 
 	
 	case 7:																		//7. durumda aðacýn size ý yazdýrýlýyor
 	printf("Binary Tree Size=%d\n",Size(root,size));							//size fonksinu ile size yazdýrýlýyor
 	break;
 	
 	case 8:																		//8. durumda printInOrder fonksiyonu ile elemanlarýn hepsi yazdýrýlýyor
 	printInOrder(root);
	break;
	
	case 9:																		//Çýkýþ gelirse hatalý tuþladý algýlanmasý diye case 9 default'a girmiyor
	break;
	
	default :																	//1 ile 9 arasýnda tuþlanýlmadýðýný gösteriyor
	printf("Listeden birini tuslayiniz!\n");
	break;
 }
 
 }while(menu != 9);																//Çýkýþa basýlmadýðý sürece program devam ediyor
 
    return 0;
}


