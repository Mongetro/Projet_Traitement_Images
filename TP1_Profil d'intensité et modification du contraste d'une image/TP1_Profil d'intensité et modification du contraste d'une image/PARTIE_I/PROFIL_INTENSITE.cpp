//                               UNIVERSITE NATIONALE DU VIETNAM (UNV)
//                               Institut Francophone pour l'Innovation (IFI)
//
//                                      COURS DE TRAITEMENT D'IMAGE
//                                            TP1-PARTIE_I
//             
//                      Programme permettant de Calculer le Profil d'intensité d'une image         
//				           Préparé par Mongetro GOINT                          		
//                                    Promotion: Promotion 22eme                                					
//																							////
//                                    COMMANDES DE COMPILLATION: 
//                        1- g++ PROFIL_INTENSITE.cpp -o out `pkg-config --cflags --libs opencv`   										                                           
//                        2- ./out « image » L ou C « numero_de_ligne »	
//																							////
//    ***Le programme consiste a tracer le profil d'intensite pour une ligne ou pour une colonne sur une image***             	

																					////

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


// La fonction permettant de déterminer le profil d'intensite de l'image

void ProfilIntensiteImg(Mat img, char* type, int numero)
{
	Point Point1, Point2;
    int largeur_fenetre_courbe;
    Vec3b valeurPixelDeb;
    Vec3b valeurPixelFin;
	// Profil d'intensité pour tracer une ligne horizontale
	if(strcasecmp(type,"L")==0){
		largeur_fenetre_courbe = img.cols;
	}
	else if(strcasecmp(type,"C")==0){
		largeur_fenetre_courbe = img.rows;
	}
		// Image du profil de l'image

		Mat courbe_profil (256,largeur_fenetre_courbe,CV_8UC3,Scalar(0,0,0));

		for(int i = 0; i < largeur_fenetre_courbe-1; i++)
		{    //Recuperation des valeurs des pixel de l'image
			if(strcasecmp(type,"L")==0){
		    valeurPixelDeb  = img.at<Vec3b>(numero, i);
		    valeurPixelFin = img.at<Vec3b>(numero,i+1);
			}
			else if(strcasecmp(type,"C")==0){
			valeurPixelDeb  = img.at<Vec3b>(i, numero);
			valeurPixelFin = img.at<Vec3b>(i+1,numero);
			}

			for(int j = 0; j < 3; j++)
			{
				Point1.x = i;
				Point2.x = i+1;
				Point1.y = 255 - valeurPixelDeb.val[j];
				Point2.y = 255 - valeurPixelFin.val[j];

				// Tracé du profil pour la couleur Bleu
				if(j==0) line(courbe_profil, Point1, Point2, Scalar(255, 0, 0), 1, 8);

				// Tracé du profil pour la couleur Rouge
				if(j==1) line(courbe_profil, Point1, Point2, Scalar(0, 255, 0), 1, 8);

				// Tracé du profil pour la couleur Verte
				if(j==2) line(courbe_profil, Point1, Point2, Scalar(0, 0, 255), 1, 8);
			}

		}
		imshow( "profil d'Intensité", courbe_profil );
		// Enregistrement du profil d'intensité dans un fichier image
		if(!imwrite("Profil_Intensite_Image.png", courbe_profil))
			cout<<"Erreur lors de l'enregistrement"<<endl;
	}


// Fonction pour tracer le trait sur l'image
void tracerTrait(Mat img, char* type, int numero){

	Point pointInit, pointEnd;

	if (strcasecmp(type,"L")==0){

		pointInit.x = 0;
		pointInit.y = numero;
		pointEnd.x = img.cols;
		pointEnd.y = numero;
	}
	else if(strcasecmp(type,"C")==0){
		pointInit.x = numero;
		pointInit.y = 0;
		pointEnd.x = numero;
		pointEnd.y = img.rows;
	}

	//Traçage de la ligne sur l'image
	line(img, pointInit, pointEnd, Scalar(0, 0, 255), 1, 8);

	//Affichage du résultat

	imshow("Image avec la ligne du Profil",img);

	// Enregistrement dans un fichier image
	if(!imwrite("Image_Ligne_Profil.png", img)) cout<<"Erreur lors de l'enregistrement de l'image"<<endl;
}

// Main
int main( int argc, char** argv )
{
	Mat image_entree; // Variable permettant de stocker l'image
	int numero; // Le numero de la ligne ou de la colonne

	image_entree = imread( argv[1], 1 ); // chargement de l'image Initiale

	if( argc != 4 )
	{
		cout << "Veuillez saisir les trois arguments respectivement dans lordre: nom_fichier type_profil(L ou C) numero_ligne_ou_colonne\n"<<endl;
	}
	else
	{
		if(!image_entree.data){
			cout<<"Le fichier image fournit est invalide, veuillez fournir un autre  \n"<<endl;
			return 0;
		}
		else
		{
			if((strcasecmp(argv[2],"L")==0)||(strcasecmp(argv[2],"C")==0))
			{
				int test=0;
				numero = atoi(argv[3]);
				// Vérification du numéro entré par l'utilisateur
				if((strcasecmp(argv[2],"L")==0)&&(image_entree.rows < numero)){
					cout<<"Veuillez saisir un numero de ligne inférieur à "<< image_entree.rows<<endl;
					test =1;
				}
				else if((strcasecmp(argv[2],"C")==0)&&(image_entree.cols < numero)){
					cout <<"Veuillez saisir un numero de colonne inférieur à"<<image_entree.cols<<endl;
					test = 1;
				}
				if(test==0)
				{
					// Tracé de la courbe du profil d'intensité
					ProfilIntensiteImg(image_entree, argv[2],numero);

					// Tracé sur l'image
					tracerTrait(image_entree, argv[2],numero);

					waitKey(0);

					cvDestroyAllWindows();

					return 0;
				}
			}
			else
			{
				cout<<"Syntaxe incorrect\n"<<endl; // syntaxe incorrecte
				return 0;
			}
		}
	}
}
