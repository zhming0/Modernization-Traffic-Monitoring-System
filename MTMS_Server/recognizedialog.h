#ifndef RECOGNIZEDIALOG_H
#define RECOGNIZEDIALOG_H

#include <QDialog>
#include<QVector>

class QProcess;
class QImage;

namespace Ui {
    class RecognizeDialog;
}

class RecognizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecognizeDialog(const QString fileName, QWidget *parent = 0);
    ~RecognizeDialog();

private:
    QVector<double> imageToVector(const QImage& image);
    QChar recognize(QString imagePath,const QString& type);
    QImage imageNormalize(const QImage& image);
    QVector<double> imageFeatureExtraction(const QImage& image);


private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_okAndSave_clicked();
    void on_pushButton_localize_clicked();
    void on_pushButton_recognize_clicked();
    void disableDialog();
    void readResult();

private:
    int recognizeMode;
    QString chineseXmlPath, numberXmlPath, otherXmlPath;

    Ui::RecognizeDialog *ui;
    QString m_fileName;
    QString c_savepath;
    QString c_binpath;
    QProcess* m_process;
    int m_number;
};

#endif // RECOGNIZEDIALOG_H
