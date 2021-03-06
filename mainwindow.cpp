#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Re = 6378.137; //km , earth radius
    setWindowTitle("Compute Observation Range");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_run_clicked()
{
     double E = ui->doubleSpinBox_E->value();
     double longitude = ui->doubleSpinBox_longitude->value();
     double latitude = ui->doubleSpinBox_latitude->value();
     double H = ui->doubleSpinBox_orbitHeight->value();

     double lanmuda = longitude*M_PI /180.0;
     double fai = latitude * M_PI /180.0;

     E = E * M_PI/180.0;
     QList<double > resultList_Lon;
     QList<double > resultList_Lat;
     double sita  =  0.0;
     for(sita =0.0 ;sita<360.0 ;sita = sita +0.5)
     {
         double A = sita * M_PI/180.0;
         double B = asin(Re*cos(E)/(Re+H));

         double alfa = M_PI /2.0 - E - B;

         double  earth_fai;
         double  earth_lanmuda;


         earth_fai = asin(sin(fai)*cos(alfa) + cos(fai)*sin(alfa)*cos(A));
         earth_lanmuda = lanmuda + asin(sin(A)*sin(alfa)/cos(earth_fai));

         earth_fai = earth_fai *180.0 / M_PI;
         earth_lanmuda = earth_lanmuda *180.0 / M_PI;
         resultList_Lat.append(earth_fai); // wei du
         resultList_Lon.append(earth_lanmuda); // jing  du

     }


     for(int i=0;i<resultList_Lat.size();i++)
     {
         qDebug()<<"["<<resultList_Lon[i]<<","<<resultList_Lat[i]<<"],";
     }
}

void MainWindow::on_pushButton_clicked()
{
    QString tle1 = ui->lineEdit_tle1->text();
    QString tle2 = ui->lineEdit_tle2->text();

    double  u = 3.98600441800e+14;
    QString zhou_qi_str =  tle2.mid(52,10);
    zhou_qi_str = zhou_qi_str.trimmed();
    double zhou_qi = zhou_qi_str.toDouble();

    double T = 86400.0/zhou_qi;

    double A = T/(2*M_PI);

    double r = pow(A*A*u,1.0/3.0);

    r = r/1000.0;
     qDebug()<<zhou_qi_str<<T/60.0<<r<<QString::number(zhou_qi,'f',6);
    double h = r-Re;
    ui->doubleSpinBox_orbitHeight->setValue(h);

}
