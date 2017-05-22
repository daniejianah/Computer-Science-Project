#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btn_image_clicked();


    void on_Pixelize_clicked();

    void on_PixArt_clicked();


    void on_SaveImg_clicked();

private:
    Ui::MainWindow *ui;
    QString filename ;
    QImage image;
    QImage Pixelized;
    QColor color;
    QStringList ImagesPath;
    int pixelationAmount ;
    QImage PixelArtBefore;


};

#endif // MAINWINDOW_H
