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

//! The dialog used to localize and recognize
/*!
  */
class RecognizeDialog : public QDialog
{
    Q_OBJECT

public:
    /*! Passing in a filename which the dialog will try to open, if succeeded,
     * Display image file, and await there to be recognized @param fileName The image file to open*/
    explicit RecognizeDialog(const QString fileName, QWidget *parent = 0);


    /*! Destructor */
    ~RecognizeDialog();

    /*! @return the result string.*/
    QString getResult() const;

private slots:
    /*! Called when cancel clicked */
    void on_pushButton_cancel_clicked();
    /*! Called when OK clicked */
    void on_pushButton_okAndSave_clicked();
    /*! Called when localize clicked */
    void on_pushButton_localize_clicked();
    /*! Called when recognize clicked */
    void on_pushButton_recognize_clicked();
    /*! Called to disable the dialog function except the close button */
    void disableDialog();
    /*! Called to read the result */
    void readResult();

private:
    QVector<double> imageToVector(const QImage& image);
    QChar recognize(QString imagePath,const QString& type);
    QChar recognize(QString imagePath,const QString& type, int mode);
    QImage imageNormalize(const QImage& image);
    QVector<double> imageFeatureExtraction(const QImage& image);
    QVector<double> imageToVector(const QImage& image, int mode);
    ImageWidget* getDigitImageWidget(int i);
    void clearDigitImageWidgets();

    int recognizeMode;
    QString chineseXmlPath, numberXmlPath, otherXmlPath, englishXmlPath;
    Ui::RecognizeDialog *ui;
    QString m_fileName;
    QString c_savepath;
    QString c_binpath;
    QProcess* m_process;
    int m_number;
    QString result;
};

#endif // RECOGNIZEDIALOG_H
