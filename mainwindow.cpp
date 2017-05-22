
//*******************************   COMPUTER SCIENCE PROJECT *********************************************
// Author : Danie Jianah SONIZARA
// Advisor : Yamid Espinel , Khoi Nhat , Anirudh Pulingandla, Antoine Merlet
//********************************************************************************************************

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <Qstring>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <iostream>
#include <QVector>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pixelationAmount=5;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//@----------------------------------LOAD AND DISPLAY AN IMAGE -------------------------------------------

//Reference : https://www.youtube.com/watch?v=TxjlDTYgoqw
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void MainWindow::on_btn_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)")) ;

    if (QString::compare(filename, QString()) != 0 )
    {
        bool valid = image.load(filename) ;

        if (valid)
        {
            image = image.scaledToWidth(ui->label_image->width(), Qt::SmoothTransformation);    // To keep the ratio of the image
            ui->label_image->setPixmap(QPixmap::fromImage(image));  //To display the image
            ui->FilePathLabel->setText(filename);

        }
        else
        {
            //Error handling
        }
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// -----------------------------------------PIXELIZE AN IMAGE--------------------------------------
// References:              http://stackoverflow.com/questions/15547125/pixelate-image-in-code
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void MainWindow::on_Pixelize_clicked()
{
    int width = image.width();      //Get the width of the image
    int height = image.height();    //Get the height of the image


    Pixelized = image ;             // Make a copy of the original image

    // ----- Calculate the colours------
    // Loop through every pixels of the image
    for (int x = 0; x < width - pixelationAmount; x += pixelationAmount){ //Loop through the x coordinate : Width
        for (int y = 0; y < height - pixelationAmount; y += pixelationAmount){  //Loop through the y coordinate : Height

            int avR = 0, avG = 0 , avB = 0; // Initialize the value of red, blue and green

            // loop through every pixels of the pixel cube
            for (int xx = x; xx < x + pixelationAmount; xx++){
                for (int yy = y; yy < y + pixelationAmount; yy++){
                    QColor currentPixel = image.pixel(x,y);
                    avR += currentPixel.red();
                    avG += currentPixel.green();
                    avB += currentPixel.blue();
                }
            }

            avR /= pixelationAmount * pixelationAmount;
            avG /= pixelationAmount * pixelationAmount;
            avB /= pixelationAmount * pixelationAmount;
            QColor mean(avR,avG,avB);

            for (int xx = x; xx < x + pixelationAmount; xx++){
                for (int yy= y; yy < y + pixelationAmount; yy++){

                    Pixelized.setPixel(xx,yy,mean.rgb());
                }
            }
        }
    }
    ui->label_image->clear();
    ui->label_image->setPixmap(QPixmap::fromImage(Pixelized));
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//----------------------------------------- PIXEL ART ---------------------------------------------------------
// References :              Vector:        http://www.cplusplus.com/reference/vector/vector/resize/
//              Open multiple files:        http://stackoverflow.com/questions/13720763/how-to-make-an-array-of-images-in-qt
//                                          http://stackoverflow.com/questions/32909483/qfiledialog-open-multiple-files
//                  Resize an image:        http://doc.qt.io/qt-4.8/qimage.html
//              Euclidean-Distance :        https://www.codeproject.com/Articles/1172815/Finding-Nearest-Colors-using-Euclidean-Distance
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void MainWindow::on_PixArt_clicked()
{

    // Select and open a set of images (database for the PixelArt)
    vector <QImage> images;

    PixelArtBefore = Pixelized ;    // Make a copy of the pixelised image

    // Carefull use Qstringlist and getOpenFilenames
    // Use QFileDialog to open multiple files
    ImagesPath =  QFileDialog::getOpenFileNames(this,tr("Select database of images "),"",
                                                tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)")) ;

    // ----- Here we use a vector to load multiples images at the same times and resize them
    if( !ImagesPath.isEmpty() )
    {
        for (int i =0;i<ImagesPath.count();i++) {
            QImage tempImg;
            tempImg.load(ImagesPath.at(i)) ;
            // Resize the images
            // set some initial content:
            tempImg=tempImg.scaled(pixelationAmount,pixelationAmount);
            images.push_back(tempImg);
        }
    }




    for (int x = 0; x < PixelArtBefore.width() - pixelationAmount; x += pixelationAmount){ //Loop through the x coordinate : Width
        for (int y = 0; y < PixelArtBefore.height() - pixelationAmount; y += pixelationAmount){  //Loop through the y coordinate : Height

            int BestMatchedImage = 0;
            int diffRed=0,diffGreen=0,diffBlue=0,totalAllDiff=0; // Initialize all the difference color
            int MaxDiff=255*3; // Here the maximum difference that we assign for the 3 channels
            QColor colorBig(PixelArtBefore.pixel(x,y));


            // Loop through every image inside the database
            for (int i =0;i<ImagesPath.count();i++) {
                int red=0,green=0,blue=0; // Initialize the value of red, blue and green

                for(int r = 0; r < images.at(i).width(); ++r){
                    for(int c = 0; c < images.at(i).height(); ++c){

                        QColor color(images.at(i).pixel(r,c));
                        // extract color channels
                        red += color.red();
                        green += color.green();
                        blue += color.blue();

                    }
                }
                // ---- Get the average
                red/= pixelationAmount*pixelationAmount; // Divide all by the amount of samples taken to get an average
                green/= pixelationAmount*pixelationAmount;
                blue/= pixelationAmount*pixelationAmount;
                QColor mean(red,green,blue);

                //Extract the difference using eucludian distance
                diffRed = abs(colorBig.red()-red);
                diffGreen = abs(colorBig.green()-green);
                diffBlue = abs(colorBig.blue()-blue);

                // Using Euclidian distance to get the nearest color value
                totalAllDiff = diffRed + diffGreen +diffBlue ;

                if(totalAllDiff < MaxDiff){
                    MaxDiff = totalAllDiff;
                    BestMatchedImage = i;
                }
            }
            // loop through every pixels of the pixel cube
            for (int xx = x; xx < x + pixelationAmount; xx++){
                for (int yy = y; yy < y + pixelationAmount; yy++){

                    PixelArtBefore.setPixel(xx,yy,(images.at(BestMatchedImage).pixel((xx-x),(yy-y))));
                }
            }
        }
    }
    ui->label_image->clear();
    ui->label_image->setPixmap(QPixmap::fromImage(PixelArtBefore));
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//----------------------------------------- SAVE THE FINAL IMAGE  ---------------------------------------------
// Reference :          http://www.qtcentre.org/threads/14579-How-to-save-file-with-QFileDialog
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void MainWindow::on_SaveImg_clicked()
{

        QString SaveChosenImg = QFileDialog::getSaveFileName(this, tr("Save the picture that you want to save"),
                                    "",
                                    tr("Images (*.png *.jpeg *.jpg)"));

        ui->label_image->pixmap()->save(SaveChosenImg); //Whatever the image inside the label

}
