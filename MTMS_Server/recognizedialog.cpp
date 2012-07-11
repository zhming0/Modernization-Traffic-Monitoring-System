#include "recognizedialog.h"
#include "ui_recognizedialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include<QImage>
#include<QColor>
#include "neuralnetwork.h"

RecognizeDialog::RecognizeDialog(const QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecognizeDialog)
{
    this->recognizeMode = 0;
    this->chineseXmlPath = "./chinese.xml";
    this->otherXmlPath = "./other.xml";
    this->numberXmlPath = "./number.xml";

    c_savepath = "./workspace/";
    c_binpath = "./bin/";
    ui->setupUi(this);
    // Trying to open the image and put it into the widget
    // if failed, disable the dialog after a warning.
    QImage image(fileName);
    qDebug() << fileName;
    if(!image.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->widget_targetImage->load(pixmap, "");
        //Keeps the fileName
        m_fileName = fileName;
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Image file does not exist!");
        disableDialog();
    }
    m_number = -1;
}

RecognizeDialog::~RecognizeDialog()
{
    delete ui;
}

void RecognizeDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}

void RecognizeDialog::on_pushButton_okAndSave_clicked()
{
    this->accept();
}

void RecognizeDialog::on_pushButton_localize_clicked()
{
    QProcess* proc = new QProcess(this);
    m_process = proc;
    QString app = c_binpath + "Localization";
    proc->start(app);
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readResult()));
    proc->write(QString("'"+m_fileName+"'").append("\n").toUtf8());
    proc->write(QString("'"+c_savepath+"'").append("\n").toUtf8());
    proc->closeWriteChannel();
    this->setEnabled(false);
}

void RecognizeDialog::on_pushButton_recognize_clicked()
{
    qDebug() << "Recognize";
}

void RecognizeDialog::disableDialog()
{
    ui->pushButton_localize->setEnabled(false);
    ui->pushButton_localize->setEnabled(false);
    ui->pushButton_okAndSave->setEnabled(false);
    ui->pushButton_recognize->setEnabled(false);
    ui->lineEdit_matchRate->setEnabled(false);
    ui->lineEdit_result->setEnabled(false);
    ui->widget_targetImage->setEnabled(false);
    ui->widget_digit_1->setEnabled(false);
    ui->widget_digit_2->setEnabled(false);
    ui->widget_digit_3->setEnabled(false);
    ui->widget_digit_4->setEnabled(false);
    ui->widget_digit_6->setEnabled(false);
    ui->widget_digit_5->setEnabled(false);
    ui->widget_digit_7->setEnabled(false);
    ui->pushButton_cancel->setText("&Close");
}

void RecognizeDialog::readResult()
{
    if(m_process != NULL)
    {
        QString str(m_process->readAllStandardOutput());
        qDebug() << str;
        if(str.startsWith("[num]"))
        {
            int number = str.mid(5).toInt();
            qDebug() << number;
            if(number <= 7)
            {
                for(int i = 0; i < number; ++i)
                {

                }
            }
            this->setEnabled(true);
        }
        else if(str.startsWith("[error]"))
        {
            this->setEnabled(true);
        }
    }
}

QImage RecognizeDialog::imageNormalize(const QImage &image)
{
    //return image.scaled(15, 30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    return image.scaled(10, 16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}

QVector<double> RecognizeDialog::imageToVector(const QImage &img)
{
    QImage image = imageNormalize(img);
    if (recognizeMode == 1)
        return imageFeatureExtraction(image);
    else {
        QVector<double> res;
        QSize size=image.size();
        for(int x=0;x<size.width();x++)
            for(int y=0;y<size.height();y++)
            {
                res<<qGray(image.pixel(x,y));
            }
        return res;
    }
}

QChar RecognizeDialog::recognize(QString imagePath, const QString &type)
{
    NeuralNetwork network(type);
    QImage image(imagePath);
    QVector<double> res = network.test(imageToVector(image));
    QString alphaString = network.getNetworkString();
    int maxI=0;
    for (int i = 0; i < res.size(); i++) {
        QString percent;
        percent.sprintf("%f",res[i]);
        if(i<alphaString.length())
        {
            qDebug() << alphaString[i] << " : " << percent;
        }else
        {
            qDebug() << "[" << i << "] : " << percent;
        }
        if(res[i]>res[maxI])
            maxI=i;
    }
    qDebug()<<"I suppose its:"<<alphaString[maxI];
    return alphaString[maxI];
}

QVector<double> RecognizeDialog::imageFeatureExtraction(const QImage &image)
{
    //----------features-------------
        static double features[12][4] = {
            {0,1,0,1}, //0
            {1,0,1,0}, //1
            {0,0,1,1}, //2
            {1,1,0,0}, //3
            {0,0,0,1}, //4
            {1,0,0,0}, //5
            {1,1,1,0}, //6
            {0,1,1,1}, //7
            {0,0,1,0}, //8
            {0,1,0,0}, //9
            {1,0,1,1}, //10
            {1,1,0,1}  //11
        };
        static int featuresLength = 12;
        //------------features-------------
        QSize size = image.size();
        double array[size.width() + 2][size.height() + 2];
        for (int x = 0; x < size.width(); x++)
            for (int y = 0; y < size.height(); y++) {
                array[x + 1][y + 1] = qGray(image.pixel(x, y)) / 255.0;
            }
        for (int x = 0; x < size.width() + 2; x++)
            array[x][0] = array[x][size.height() + 1] = 1.0;
        for (int y = 0; y < size.height() + 2; y++)
            array[0][y] = array[size.width() + 1][y] = 1.0;

        int w = size.width() + 2, h = size.height() + 2;

        QVector<double> ret(featuresLength * 4);
        ret.fill(0);
        for (int i = 0; i < featuresLength; i++)
        {
            for (int x = 0; x < w - 1; x++)
                for (int y = 0; y < h - 1; y++)
                {
                    double match = 0;
                    match += qAbs(array[x][y] - features[i][0]);
                    match += qAbs(array[x + 1][y] - features[i][1]);
                    match += qAbs(array[x][y + 1] - features[i][2]);
                    match += qAbs(array[x + 1][y + 1] - features[i][3]);

                    int bias = 0;
                    if (x >= w / 2) bias += featuresLength;
                    if (y >= h / 2) bias += featuresLength * 2;
                    ret[bias + i] += (match < 0.05 ? 1 : 0);
                }
        }
        return ret;
}
