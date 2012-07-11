#ifndef RECOGNIZEDIALOG_H
#define RECOGNIZEDIALOG_H

#include <QDialog>
#include<QVector>

class QProcess;
class ImageWidget;
class QImage;

namespace Ui {
    class RecognizeDialog;
}

/* The dialog used to localize and recognize */
class RecognizeDialog : public QDialog
{
    Q_OBJECT

public:
    /* Passing in a filename which the dialog will try to open, if succeeded,
     * Display image file, and await there to be recognized */
    explicit RecognizeDialog(const QString fileName, QWidget *parent = 0);

    /* Destructor */
    ~RecognizeDialog();

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_okAndSave_clicked();
    void on_pushButton_localize_clicked();
    void on_pushButton_recognize_clicked();
    void disableDialog();
    void readResult();

private:
    QVector<double> imageToVector(const QImage& image);
    QChar recognize(QString imagePath,const QString& type);
    QImage imageNormalize(const QImage& image);
    QVector<double> imageFeatureExtraction(const QImage& image);

    int recognizeMode;
    QString chineseXmlPath, numberXmlPath, otherXmlPath;
    Ui::RecognizeDialog *ui;
    QString m_fileName;
    QString c_savepath;
    QString c_binpath;
    QProcess* m_process;
    ImageWidget* getDigitImageWidget(int i);
    void clearDigitImageWidgets();
    int m_number;
};

#endif // RECOGNIZEDIALOG_H
