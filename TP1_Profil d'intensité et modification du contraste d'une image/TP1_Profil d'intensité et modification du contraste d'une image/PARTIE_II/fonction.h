////********************************************************************************************////
////             TP1 2eme Partie: Programme de modification du contraste	                    ////
////																							////
////             Auteur: HOUSSOU Noudehouenou Lionel Jaderne                             		////
////             Promotion: Promotion 19 - IFI                                 					////
////																							////
////             Compilation: 1- make      												 		////
////						  2- ./amelioration_contraste										////
////																							////
////			 Description:  Ce programme permet de modifier le contraste d'une image.	    ////
////			               	 																////
////						   																	////
////																							////
////********************************************************************************************////

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

// Fonction pour la représentation de l'histogramme
Mat histogramme(Mat image);

// Fonction pour tracer le profil d'intensité
Mat ProfilIntensiteImage(Mat image, int type, int numero);

// Fonction pour faire le tracer sur l'image
Mat tracerTrait(Mat image, int type, int numero);

// Fonction pour modifier le constraste avec fonction linéaire à trois points
Mat fonctionLineaire3Points(Mat image,Point P1, Point P2, Point P3);

// Fonction pour afficher la courbe de la fonction linéaire à trois points
Mat courbeFonctionLineaire3Points(Point Point1, Point Point2, Point Point3);

// Fonction pour corriger l'image avec gamma
Mat correctionGamma(Mat image,float gamma);

// Fonction pour afficher la courbe de gamma
Mat courbeFonctionGamma(float gamma);

// Fonction pour modifier avec la fonction lineaire de saturation
Mat fonctionLineaireSaturation(Mat image, Point P1, Point P2);

//Fonction pour afficher la courbe de la fonction linéaire avec saturation
Mat courbeFonctionLineaireSaturation(Point Point1, Point Point2);
