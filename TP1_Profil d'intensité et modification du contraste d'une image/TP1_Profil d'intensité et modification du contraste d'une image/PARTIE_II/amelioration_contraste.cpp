//                                     UNIVERSITE NATIONALE DU VIETNAM
//                                   Institut Francophone pour l'Innovation	                  
//					
//                                    Cousr de Traitement d'Image																		////
//                           	         	TP1_PARTIE I
//                                           PREPARE PAR: Mongetro GOINT
//                                
//                                            Promotion:22eme                                 				
//                     
//                    Programme permetant de faire la modification du contraste d'une image.  																	////
//                              Compilation: 1- make 2- ./amelioration_contrast.cpp     						                                                       1- make		  2- ./amelioration_contraste	
//
//			               	 									


#include "fonction.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	int choix=0;
	char nomImage[100];
	Mat image_orig, histo_orig, profil_orig, trace_orig;
	Mat image_modi, histo_modi, profil_modi, trace_modi;
	Mat courbe;
	int type;
	int numero;

	if(argc!=1){
		cout << "Veuillez indiquer le nom du fichier main: ./contraste"<< endl;
	}
	else
	{
		cout << "BIENVENUE DANS LE PROGRAMME DE MODIFICATION DU CONTRASTE D'IMAGE"<<endl;
		do{
			cout << "Veuillez choisir un des trois numero pour convenable a votre choix"<<endl;
			cout << "1-- Modification avec fonction linéaire à trois points"<<endl;
			cout << "2-- Modification avec la correction gamma: fonction non linéaire"<<endl;
			cout << "3-- Modification avec fonction linéaire avec saturation"<<endl;
			cout << "4-- Quiter"<<endl;
			cout << "Faites votre choix: $ ";
			cin  >> choix;

			if((choix !=1)&&(choix!=2)&&(choix!=3)&&(choix!=4)){
				cout << "Attention! Veuillez choisir un numero valide"<<endl;
			}
			else{
				if(choix == 4){
					cout << "Bye !!!"<< endl;
					return 0;
				}
				else{
					cout << "Veuillez indiquer le nom de votre l'image"<<endl;
					cout << "$ ";
					cin  >> nomImage;
					image_orig = imread(nomImage, 1 ); // chargement de l'image
					if(!image_orig.data){
						cout << "Veuillez fournir une image valide"<<endl;
					}
					else{

						cout << "Indiquez le  type de profil que vous voulez? 1 pour ligne, 2 pour colonne" << endl;
						cin >> type;
						cout << "Donner le numero de la ligne ou de la colonne choisie"<<endl;
						cin >> numero;
						switch (choix)
						{
							case 1: // Modification fonction linéaire à deux points
							{
								//int abscisse1, ordonnee1, abscisse2, ordonnee2;
								Point Point1, Point2, Point3;
								// Collecte des informations spécifiques à la fonction linéaires
								cout << "Modification avec fonction linéaire à deux points"<<endl;
								cout << " Veuillez indiquer les coordonnées des trois points"<<endl;
								cout << "Premier Point"<<endl;
								cout << "Abscisse : $ ";
								cin  >> Point1.x;
								cout << "Ordonnée : $ ";
								cin  >> Point1.y;

								cout << "Deuxieme Point"<<endl;
								cout << "Abscisse : $ ";
								cin  >> Point2.x;
								cout << "Ordonnée : $ ";
								cin  >> Point2.y;

								cout << "Troisieme Point"<<endl;
								cout << "Abscisse : $ ";
								cin  >> Point3.x;
								cout << "Ordonnée : $ ";
								cin  >> Point3.y;

								// Traitement de l'image selon les données receuillies
								image_modi = fonctionLineaire3Points(image_orig,Point1, Point2, Point3);
								courbe = courbeFonctionLineaire3Points(Point1, Point2, Point3);

								// Affichage de la courbe de la fonction
								imshow( "Fonction linéaire à deux points", courbe );

								// Enregistrement de l'histogramme orginal dans un fichier image
								if(!imwrite("Images_Finales/fonction_lineaire.png", courbe))
									cout<<"Erreur lors de l'enregistrement"<<endl;
								break;
							}
							case 2: // Modification avec correction gamma
							{
								float gamma;
								// Collecte des informations spécifiques à la fonction linéaires
								cout << "Modification avec la correction gamma"<<endl;
								cout << " Veuillez renseigner la valeur de gamma"<<endl;
								cin  >> gamma;

								// Traitement de l'image selon la valeur de gamma
								image_modi = correctionGamma(image_orig,gamma);
								courbe = courbeFonctionGamma(gamma);

								// Affichage de la courbe de la fonction
								imshow( "Fonction gamma", courbe );

								// Enregistrement de l'histogramme orginal dans un fichier image
								if(!imwrite("Images_Finales/fonction_gamma.png", courbe))
									cout<<"!!!Erreur lors de l'enregistrement"<<endl;
								break;
							}
							case 3: // Modification linaire avec saturation
							{
								Point Point1, Point2;
								// Collecte des informations spécifiques à la fonction linéaires
								cout << "Modification avec la fonction linéaire de saturation"<<endl;
								cout << " Veuillez indiquer les abscisses des deux points"<<endl;

								cout << "Le minimum $ ";
								cin  >> Point1.x;
								Point1.y = 0;

								cout << "Le maximum $ ";
								cin  >> Point2.x;
								Point2.y = 255;

								// Traitement de l'image selon les deux points fournis
								image_modi = fonctionLineaireSaturation(image_orig,Point1, Point2);
								courbe = courbeFonctionLineaireSaturation(Point1, Point2);

								// Affichage de la courbe de la fonction
								imshow( "Fonction lineaire avec saturation", courbe );

								// Enregistrement de l'histogramme orginal dans un fichier image
								if(!imwrite("Images_Finales/fonction_saturation.png", courbe))
									cout<<"!!!Erreur lors de l'enregistrement"<<endl;
								break;
							}
						}

						// ************** Affichabe donnée originale *******************/
						profil_orig = ProfilIntensiteImage(image_orig, type, numero);

						trace_orig = tracerTrait(image_orig, type, numero);

						histo_orig = histogramme(image_orig);

						//Affichage de l'histogramme original
						imshow("Histogramme de l'image originale", histo_orig );

						// Enregistrement de l'histogramme orginal dans un fichier image
						if(!imwrite("Images_Finales/histo_original.png", histo_orig))
							cout<<"Erreur lors de l'enregistrement"<<endl;

						// Affichage du profl original
						imshow( "profil d'Intensité original", profil_orig );

						// Enregistrement du profil original dans un fichier image
						if(!imwrite("Resultats_Images/profil_Intensite_original.png", profil_orig))
							cout<<"Erreur lors de l'enregistrement"<<endl;

						// Affichage de l'image originale avec le trait du profil
						imshow( "Image originale avec trait", trace_orig );

						// Enregistrement de l'image originale avec trait dans un fichier image
						if(!imwrite("Images_Finales/image_originale_trait.png", trace_orig))
							cout<<"Erreur lors de l'enregistrement"<<endl;

						// ************* Affichage des données modifiées ***************/

						profil_modi = ProfilIntensiteImage(image_modi, type, numero);

						trace_modi = tracerTrait(image_modi, type, numero);

						histo_modi = histogramme(image_modi);

						//Affichage de l'histogramme modifié
						imshow("Histogramme de l'image modifiée", histo_modi );

						// Enregistrement de l'histogramme modifié dans un fichier image
						if(!imwrite("Images_Finales/histo_modifie.png", histo_modi))
							cout<<"Erreur lors de l'enregistrement"<<endl;

						// Affichage du profl modifié
						imshow( "profil d'Intensité modifié", profil_modi );

						// Enregistrement du profil modifié dans un fichier image
						if(!imwrite("Images_Finales/profil_Intensite_modifie.png", profil_modi))
							cout<<"Erreur lors de l'enregistrement"<<endl;

						// Affichage de l'image modifiée avec le trait du profil
						imshow( "Image Modifiee avec trait", trace_modi );

						// Enregistrement du l'image modifiée avec le trait du profil
						if(!imwrite("Images_Finales/image_modifiee_trait.png", trace_modi))
							cout<<"Erreur lors de l'enregistrement"<<endl;

						//====== Action utilisateur =======/
						// Attente d'une action de l'utilisateur
						waitKey(0);

						// Destruction des fenêtres
						cvDestroyAllWindows();

						// Quitter le programme
						return 0;
					}
				}
			}
		}while(choix!=4);
	}
}
