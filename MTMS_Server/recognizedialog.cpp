#include "recognizedialog.h"
#include "ui_recognizedialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include<QImage>
#include<QColor>
#include "neuralnetwork.h"
#include<QDir>

RecognizeDialog::RecognizeDialog(const QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecognizeDialog)
{
    this->recognizeMode = 1;
    this->chineseXmlPath = "./chinese.xml";
    this->otherXmlPath = "./other.xml";
    this->numberXmlPath = "./number.xml";
    this->englishXmlPath = "./character.xml";

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
    this->clearDigitImageWidgets();
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
    this->clearDigitImageWidgets();
    QProcess* proc = new QProcess(this);
    m_process = proc;

    QString app = c_binpath + "Localization";

    #if defined(__APPLE__) || defined(MACOSX)
        app.append(".app");
    #endif
    proc->start(app);
    qDebug() << app;
    if (!proc->waitForStarted()){
        qDebug() << "No such app";
        return;
    }
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readResult()));
    proc->write(QString("'"+m_fileName+"'").append("\n").toUtf8());
    proc->write(QString("'"+c_savepath+"'").append("\n").toUtf8());
    proc->closeWriteChannel();
    this->setEnabled(false);
}

void RecognizeDialog::on_pushButton_recognize_clicked()
{
    qDebug() << "Recognize";
    QDir dir(c_savepath);
    QStringList list = dir.entryList();
    QString s = "0000000";
    int cnt = 0;
    for (int i = 0; i < list.length() && cnt < this->m_number; i++)
    {
        QChar ret;
        if (list[i][0] == '.')
            continue;
        cnt++;
        if (list[i][0] == '1')
            ret = recognize(c_savepath +list[i], chineseXmlPath);
        else if (list[i][0] == '2')
            ret = recognize(c_savepath +list[i], englishXmlPath, 0);
        else
            ret = recognize(c_savepath +list[i], otherXmlPath, 0);
        QChar tmp = list[i][0];
        QString tmp_s(tmp);
        s[tmp_s.toInt() - 1] = ret;
    }
    this->ui->lineEdit_result->setText(s);
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
            bool error = false;
            for(int i = 1; i <= (number <= 7 ? number : 7); ++i)
            {
                QString impath(c_savepath + QString("%1.png").arg(i));
                qDebug() << impath;
                QImage image(impath);
                if(!image.isNull())
                {
                    this->getDigitImageWidget(i)->load(QPixmap::fromImage(image), "");
                }
                else
                {
                    m_number = -1;
                    this->clearDigitImageWidgets();
                    error = true;
                    break;
                }
            }
            if(!error)
            {
                m_number = number <=7 ? number : 7;
            }
            this->setEnabled(true);
        }
        else if(str.startsWith("[error]"))
        {
            this->clearDigitImageWidgets();
            this->setEnabled(true);
            m_number = -1;
        }
    }
}

ImageWidget* RecognizeDialog::getDigitImageWidget(int i)
{
    if(i > 7 || i <= 0)
    {
        return NULL;
    }
    else
    {
        switch(i)
        {
        case 1:
            return ui->widget_digit_1;
        case 2:
            return ui->widget_digit_2;
        case 3:
            return ui->widget_digit_3;
        case 4:
            return ui->widget_digit_4;
        case 5:
            return ui->widget_digit_5;
        case 6:
            return ui->widget_digit_6;
        case 7:
            return ui->widget_digit_7;
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

QVector<double> RecognizeDialog::imageToVector(const QImage &img, int mode)
{
    QImage image = imageNormalize(img);
    if (mode == 1)
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

QChar RecognizeDialog::recognize(QString imagePath, const QString &type, int mode)
{
    NeuralNetwork network(type);
    QImage image(imagePath);
    QVector<double> res = network.test(imageToVector(image, mode));
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
void RecognizeDialog::clearDigitImageWidgets()
{
    for(int i = 1; i <= 7; ++i)
    {
        ImageWidget* iw = getDigitImageWidget(i);
        QImage image(":/black.png");
        iw->load(QPixmap::fromImage(image), "");
    }
}
