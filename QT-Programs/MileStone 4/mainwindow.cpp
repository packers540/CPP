#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bitmap.h"
#include <fstream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>


//Include Serial Communication Library
#include "serialcom.h"


Bitmap overlayOriginal;
Bitmap overlayOverlay;
Bitmap histeqOriginal;
Bitmap imageEdit;
int MAX = 256;
bool serialEnabled = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Button to load original image
void MainWindow::on_pushButton_clicked()
{ 
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Bitmap (*.bmp)"));

        if(QString::compare(filename, QString())!=0)
        {
            QImage image;
            bool valid = image.load(filename);

            if (valid)
            {
                image = image.scaledToWidth(ui->original_image->width(), Qt::SmoothTransformation);
                ui->original_image->setPixmap(QPixmap::fromImage(image));
                string file;
                // converts Qstring filename into a Std::String
                file = filename.toStdString();
                // dynamically allocates an array of the size string and fills it with characters
                // converts a string into characters and copies it into an array (thats the size of the string) and sets a pointer to the array
                char* f = strcpy((char*)malloc(file.size()+1), file.c_str());

                overlayOriginal.loadOriginalBitmap(f, MAX);
            }

        }

}

//button to load overlay image
void MainWindow::on_pushButton_2_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Bitmap (*.bmp)"));

        if(QString::compare(filename, QString())!=0)
        {
            QImage image;
            bool valid = image.load(filename);

            if (valid)
            {
                image = image.scaledToWidth(ui->overlay_image->width(), Qt::SmoothTransformation);
                ui->overlay_image->setPixmap(QPixmap::fromImage(image));
                string file;
                file = filename.toStdString();                        // converts Qstring filename into a Std::String
                char* f = strcpy((char*)malloc(file.size()+1), file.c_str());        // dynamically allocates an array of the size string and fills it with characters
                                                                                     // converts a string into characters and copies it into an array (thats the size of the string) and sets a pointer to the array
                overlayOverlay.loadOverlayBitmap(f, MAX);
            }

        }

}


//Button to overlay the two above images
void MainWindow::on_pushButton_3_clicked()
{

    unsigned char* original = overlayOriginal.getOriginal();
    unsigned char* overlay = overlayOverlay.getOverlay();
    unsigned char* overlay_output;


    //Make sure original and overlay dimensions are the same
    if (overlayOriginal.getHeight() == overlayOverlay.getOverlayHeight() &&
            overlayOriginal.getWidth() == overlayOverlay.getOverlayWidth())
    {
        overlay_output = overlayOriginal.overLayImages(original, overlay);

        overlayOriginal.saveBitmap("OverlayFinal.bmp", overlay_output, MAX);

        QString filename = "OverlayFinal.bmp";

        if(QString::compare(filename, QString())!=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if (valid)
            {
                image = image.scaledToWidth(ui->overlayed->width(), Qt::SmoothTransformation);
                ui->overlayed->setPixmap(QPixmap::fromImage(image));
            }
        }
    }

    //Ouput dialog box to warn user of incorrect image dimensions
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Dimension Matching Error");
        msgBox.setText("Image dimensions must be the same.");
        msgBox.exec();

    }



}


//Button to load original histogram image
void MainWindow::on_pushButton_4_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Bitmap (*.bmp)"));

     if(QString::compare(filename, QString())!=0)
     {
         QImage image;
         bool valid = image.load(filename);

         if (valid)
         {
             image = image.scaledToWidth(ui->orig_eq_image->width(), Qt::SmoothTransformation);
             ui->orig_eq_image->setPixmap(QPixmap::fromImage(image));
             string file;
             file = filename.toStdString();                        // converts Qstring filename into a Std::String
             char* f = strcpy((char*)malloc(file.size()+1), file.c_str());        // dynamically allocates an array of the size string and fills it with characters
                                                                                  // converts a string into characters and copies it into an array (thats the size of the string) and sets a pointer to the array
             histeqOriginal.loadHistogramImage(f, MAX);
         }

     }

}


//Button to perform histogram equalization
void MainWindow::on_pushButton_5_clicked()
{
    unsigned char* original = histeqOriginal.getHistogram();
    unsigned char* equalized;


    //load histogram image, perform equalization, output image to file
    equalized = histeqOriginal.histEqualization(original);
    histeqOriginal.saveHistBitmap("equalized.bmp", equalized, MAX);


    //display output image
    QString filename = "equalized.bmp";

    if(QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);

        if (valid)
        {
            image = image.scaledToWidth(ui->eq_image->width(), Qt::SmoothTransformation);
            ui->eq_image->setPixmap(QPixmap::fromImage(image));
        }

    }


}

//button to load an image to edit
void MainWindow::on_pushButton_6_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Bitmap (*.bmp)"));

     if(QString::compare(filename, QString())!=0)
     {
         QImage image;
         bool valid = image.load(filename);

         if (valid)
         {
             image = image.scaledToWidth(ui->adjustImage->width(), Qt::SmoothTransformation);
             ui->adjustImage->setPixmap(QPixmap::fromImage(image));
             string file;
             file = filename.toStdString();                        // converts Qstring filename into a Std::String
             char* f = strcpy((char*)malloc(file.size()+1), file.c_str());        // dynamically allocates an array of the size string and fills it with characters
                                                                                  // converts a string into characters and copies it into an array (thats the size of the string) and sets a pointer to the array
             imageEdit.loadEditImage(f, MAX);
         }

     }
}


//slider to adjust brightness
void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    imageEdit.adjustBrightness(value);
    imageEdit.saveHistBitmap("adjusted.bmp", imageEdit.getEditImageBrightness(), MAX);


    //display output image
    QString filename = "adjusted.bmp";

    if(QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);

        if (valid)
        {
            image = image.scaledToWidth(ui->adjustImage->width(), Qt::SmoothTransformation);
            ui->adjustImage->setPixmap(QPixmap::fromImage(image));
        }

    }

    //Serial Communication Starts Here!!
    if (serialEnabled){
        //Number of bytes sent
        DWORD bytesSent;

        int baudRate = ui->lineEdit_2->text().toInt();

        //Convert QString to LPCWSTR
        LPCWSTR comPort = (const wchar_t*)ui->lineEdit->text().utf16();

        //Initialize serial connection
        serialCOM serial(comPort, baudRate);

        //Send Data
        bytesSent = serial.sendSerial(value);

        //Close Connection
        serial.closeSerial();
    }



}

//slider to adjust contrast
void MainWindow::on_contrastSlider_valueChanged(int value)
{
    imageEdit.adjustContrast(value);
    imageEdit.saveHistBitmap("adjusted.bmp", imageEdit.getEditImageContrast(), MAX);


    //display output image
    QString filename = "adjusted.bmp";

    if(QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);

        if (valid)
        {
            image = image.scaledToWidth(ui->adjustImage->width(), Qt::SmoothTransformation);
            ui->adjustImage->setPixmap(QPixmap::fromImage(image));
        }

    }

}


//reset button
void MainWindow::on_pushButton_7_clicked()
{
    //reset slider values to origin
    ui->brightnessSlider->setValue(10);
    ui->contrastSlider->setValue(950);
    imageEdit.reset();


    //apply origin values of sliders then save and display original image
    imageEdit.adjustContrast(10);
    imageEdit.adjustContrast(950);
    imageEdit.saveHistBitmap("adjusted.bmp", imageEdit.getEditImageContrast(), MAX);


    //display output image
    QString filename = "adjusted.bmp";

    if(QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);

        if (valid)
        {
            image = image.scaledToWidth(ui->adjustImage->width(), Qt::SmoothTransformation);
            ui->adjustImage->setPixmap(QPixmap::fromImage(image));
        }

    }

}

//button to save image
void MainWindow::on_pushButton_8_clicked()
{
    //ask user where to save image, get name and path
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Edited Image"), "", tr("Bitmap Image (*.bmp);;All Files (*)"));
    //since program is constantly updating a file called "adjusted.bmp" when edits are made
    //simple copy adjusted.bmp to user soecified location with specified name
    ifstream src("adjusted.bmp", ios::binary);
    ofstream dest(filename.toStdString().c_str(), ios::binary);
    dest << src.rdbuf();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked)
        serialEnabled = true;
    else
        serialEnabled = false;
}
