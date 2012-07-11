#include "recognizedialog.h"
#include "ui_recognizedialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QProcess>


RecognizeDialog::RecognizeDialog(const QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecognizeDialog)
{
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
                for(int i = 1; i <= number; ++i)
                {
                    QString impath(c_savepath + QString("%1.png").arg(number));
                    QImage image(impath);
                    if(!image.isNull())
                    {

                    }
                    else
                    {

                    }
                }
            }
            this->setEnabled(true);
        }
        else if(str.startsWith("[error]"))
        {
            this->setEnabled(true);
            number = -1;
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

void RecognizeDialog::clearDigitImageWidgets()
{
    for(int i = 1; i <= 7; ++i)
    {
        getDigitImageWidget(i);
    }
}
