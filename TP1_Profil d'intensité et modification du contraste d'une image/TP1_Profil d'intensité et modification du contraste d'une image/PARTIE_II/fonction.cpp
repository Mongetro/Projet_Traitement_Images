IVERSITE NATIONALE DU VIETNAM
//                                   Institut Francophone pour l'Innovation    
//
//                                    Cousr de Traitement d'Image                                                                             $
//                                              TP1_PARTIE I
//                                           PREPARE PAR: Mongetro GOINT
//
//                                            Promotion:22eme
//
//                    Programme permetant de faire la modification du contraste d'une image.                                                  $
//                              Compilation: 1- make 2- ./amelioration_contrast.cpp                                                           $
//
//

#include "fonction.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>


Mat histogramme(Mat image)
{
	//Les Variables
	vector<Mat> recupRGB;
	split( image, recupRGB);
	int tailleHisto = 256;
	float intervalle[] = { 0, 256 } ;
	const float* intervalleHisto = { intervalle };
	int largeurHisto = 512; int hauteurHisto = 500;
	int pas = 2;
	Mat histImage(hauteurHisto, largeurHisto, CV_8UC3, Scalar( 0,0,0));
	Mat HistRouge,HistVert,HistBleu;

	//CALCUL DE L'HISTOGRAMME ET DE LA NORMALISATION POUR CHAQUE NIVEAU RVB
	calcHist( &recupRGB[0], 1, 0, Mat(),HistBleu , 1, &tailleHisto, &intervalleHisto, true, false);
	normalize(HistBleu,HistBleu, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	calcHist( &recupRGB[1], 1, 0, Mat(), HistVert, 1, &tailleHisto, &intervalleHisto, true, false);
	normalize(HistVert,HistVert, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	calcHist( &recupRGB[2], 1, 0, Mat(), HistRouge, 1, &tailleHisto, &intervalleHisto, true, false);
	normalize(HistRouge,HistRouge, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//Tracage de l'histogramme en rectangle
	for( int i = 0; i < tailleHisto; i++ )
	{
		rectangle(histImage, Point( pas*(i), hauteurHisto) ,Point( pas*(i+1), hauteurHisto - cvRound(HistBleu.at<float>(i)) ),Scalar( 255, 0, 0), 2, 8, 0 );

		rectangle(histImage, Point( pas*(i), hauteurHisto) ,Point( pas*(i+1), hauteurHisto - cvRound(HistVert.at<float>(i)) ),Scalar( 0, 255, 0), 2, 8, 0 );

		rectangle(histImage, Point( pas*(i), hauteurHisto) ,Point( pas*(i+1), hauteurHisto - cvRound(HistRouge.at<float>(i)) ),Scalar( 0, 0, 255), 2, 8, 0 );
	}
return histImage;
}


// FONCTION PERMETTANT DE FAIRE LE CALCUL DU PROFIL D'INTENSITE
Mat ProfilIntensiteImage(Mat image, int type, int numero)
{
	Point premierPoint, deuxiemePoint;
    int largeur_fenetre_courbe;
    Vec3b valeurPixelDeb;
    Vec3b valeurPixelFin;
	// Profil d'intensité dans le cas d'une ligne horizontale
	if(type==1){
		largeur_fenetre_courbe = image.cols;
	}
	else if(type==2){
		largeur_fenetre_courbe = image.rows;
	}
		// Image du profil

		Mat courbe_profil (256,largeur_fenetre_courbe,CV_8UC3,Scalar(0,0,0));

		for(int i = 0; i < largeur_fenetre_courbe-1; i++)
		{    //Recuperation des valeurs du pixel
			if(type==1){
		    valeurPixelDeb  = image.at<Vec3b>(numero, i);
		    valeurPixelFin = image.at<Vec3b>(numero,i+1);
			}
			else if(type==2){
			valeurPixelDeb  = image.at<Vec3b>(i, numero);
			valeurPixelFin = image.at<Vec3b>(i+1,numero);
			}

			for(int j = 0; j < 3; j++)
			{
				premierPoint.x = i;
				deuxiemePoint.x = i+1;
				premierPoint.y = 255 - valeurPixelDeb.val[j];
				deuxiemePoint.y = 255 - valeurPixelFin.val[j];

				// Tracé du profil pour la couleur Bleu
				if(j==0) line(courbe_profil, premierPoint, deuxiemePoint, Scalar(255, 0, 0), 1, 8);

				// Tracé du profil pour la couleur Rouge
				if(j==1) line(courbe_profil, premierPoint, deuxiemePoint, Scalar(0, 255, 0), 1, 8);

				// Tracé du profil pour la couleur Verte
				if(j==2) line(courbe_profil, premierPoint, deuxiemePoint, Scalar(0, 0, 255), 1, 8);
			}

		}
		return courbe_profil;
	}

//FONCTION PERMETTANT DE TRACER LE TRAIT DU PROFIL D'INTENSITE SUR L'IMAGE
Mat tracerTrait(Mat image, int type, int numero){

	Point debut, fin;

	if (type==1){

		debut.x = 0;
		debut.y = numero;
		fin.x = image.cols;
		fin.y = numero;
	}
	else if(type==2){
		debut.x = numero;
		debut.y = 0;
		fin.x = numero;
		fin.y = image.rows;
	}

	//Tracé de la ligne sur l'image
	line(image, debut, fin, Scalar(0, 0, 255), 1, 8);

	return image;
}


// FONCTION PERMETTANT DE MODIFIER LE CONTRASTE AVEC LA FONCTION LINEAIRE
Mat fonctionLineaire3Points(Mat image,Point P1, Point P2, Point P3){

	Mat sortie(image.rows, image.cols, CV_8UC3, Scalar( 0,0,0));
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            for(int c = 0; c < 3; c++){
					int val = image.at<Vec3b>(i,j)[c];
					if(val>=0 && val <= P1.x) val = (int) P1.y/P1.x * val;
    				else if(P1.x < val && val <= P2.x) val =(int) ((P2.y - P1.y)/(P2.x - P1.x)) * (val - P1.x) + P1.y;
    				else if(P2.x < val && val <= P3.x) val =(int) ((P3.y - P2.y)/(P3.x - P2.x)) * (val - P2.x) + P2.y;
    				else if(P3.x < val && val <= 255) val =(int) ((255 - P3.y)/(255 - P3.x)) * (val - P3.x) + P3.y;
					sortie.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(val);
            }
        }
    }
    return sortie;
}

// FONCTION POUR REPRESENTATION DE LA FONCTION LINEAIRE
Mat courbeFonctionLineaire3Points(Point Point1, Point Point2, Point Point3){

	// Declaration de l'image de la courbe
	Mat courbe3Points(256,256,CV_8UC3,Scalar(0,0,0));

	// Déclaration et initialisation des points de début et de fin
	Point debut, fin;
	debut.x = 0 ;
	debut.y = 255 ;
	fin.x = 255;
	fin.y = 0;
	Point1.y = 255 - Point1.y;
	Point2.y = 255 - Point2.y;
	Point3.y = 255 - Point3.y;

	// Tracé des lignes de la courbe
	line(courbe3Points, debut, Point1, Scalar(255, 0, 0), 1, 8);
	line(courbe3Points, Point1, Point2, Scalar(255, 0, 0), 1, 8);
	line(courbe3Points, Point2, Point3, Scalar(255, 0, 0), 1, 8);
	line(courbe3Points, Point3, fin, Scalar(255, 0, 0), 1, 8);

	return courbe3Points;
}

// FONCTION PERMETTANT DE MODIFIER LE CONTRASTE SUIVANT LA CORRECTION GAMMA
Mat correctionGamma(Mat image,float gamma){

	Mat sortie(image.rows, image.cols, CV_8UC3, Scalar( 0,0,0));

    for(int i = 0; i < image.rows; i++){

        for(int j = 0; j < image.cols; j++){

            for(int c = 0; c < 3; c++){

					int val = image.at<Vec3b>(i,j)[c];

					if(val < 0) val = 0;
    				else if(val > 255) val =255;
    				else if(0 <= val && val <= 255)
						val = pow((val/255.0),gamma)*255.0;
               sortie.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(val);
            }
        }
    }
    return sortie;
}


// LA FONCTION PERMETTANT D'AFFICHER LA COURBE GAMMA
Mat courbeFonctionGamma(float gamma){

	Mat sortie(256, 256, CV_8UC3, Scalar( 0,0,0));

	Point Point1, Point2;
	for (float i = 0.0; i<256.0; i++){
		Point1.x = i;
		Point2.x = i+1;
		Point1.y = 255.0 - (pow((Point1.x/255.0),gamma)*255.0);
		Point2.y = 255.0 - (pow((Point2.x/255.0),gamma)*255.0);
		if(Point1.y < 0.0)  Point1.y = 0.0;
		if(Point1.y> 255.0) Point1.y = 255.0;
		if(Point2.y < 0.0)  Point2.y = 0.0;
		if(Point2.y> 255.0) Point2.y = 255.0;
		line(sortie, Point1, Point2, Scalar(255, 0, 0), 1, 8);
	}
	return sortie;
}

// FONCTION PERMETTANT DE MODIFIER LE CONTRASTE SUIVANT LES POINTS Min et Max
Mat fonctionLineaireSaturation(Mat image, Point P1, Point P2){

	Mat sortie(image.rows, image.cols, CV_8UC3, Scalar( 0,0,0));

    for(int i = 0; i < image.rows; i++){

        for(int j = 0; j < image.cols; j++){

            for(int c = 0; c < 3; c++){

					int val = image.at<Vec3b>(i,j)[c];

					if(val>=0 && val <= P1.x) val = 0;
    				else if(P1.x < val && val <= P2.x)
						val =(int) (255/(P2.x - P1.x)) * (val - P1.x);
    				else if(P2.x < val && val <= 255) val = 255;
               sortie.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(val);
            }
        }
    }
    return sortie;
}

// FONCTION PERMETTANT DE REPRESENTER LA FONCTION LINEAIRE
Mat courbeFonctionLineaireSaturation(Point Point1, Point Point2){

	// Declaration de l'image de la courbe
	Mat courbeSaturation(256,256,CV_8UC3,Scalar(0,0,0));

	// Déclaration et initialisation des points de début et de fin
	Point debut, fin;
	debut.x = 0 ;
	debut.y = 255 ;
	fin.x = 255;
	fin.y = 0;
	Point1.y = 255 - Point1.y;
	Point2.y = 255 - Point2.y;


	// Tracé des lignes de la courbe
	line(courbeSaturation, debut, Point1, Scalar(255, 0, 0), 1, 8);
	line(courbeSaturation, Point1, Point2, Scalar(255, 0, 0), 1, 8);
	line(courbeSaturation, Point2, fin, Scalar(255, 0, 0), 1, 8);

	return courbeSaturation;
}
