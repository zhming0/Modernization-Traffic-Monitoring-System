#ifndef RECOGNIZEDIALOG_H
#define RECOGNIZEDIALOG_H

#include <QDialog>

class QProcess;

namespace Ui {
    class RecognizeDialog;
}

class RecognizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecognizeDialog(const QString fileName, QWidget *parent = 0);
    ~RecognizeDialog();

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_okAndSave_clicked();
    void on_pushButton_localize_clicked();
    void on_pushButton_recognize_clicked();
    void disableDialog();
    void readResult();

private:
    Ui::RecognizeDialog *ui;
    QString m_fileName;
    QString c_savepath;
    QString c_binpath;
    QProcess* m_process;
    int m_number;
};

#endif // RECOGNIZEDIALOG_H
