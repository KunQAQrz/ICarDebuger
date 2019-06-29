#ifndef _KUN__MULTIPLEINPUTDIALOG_H_
#define _KUN__MULTIPLEINPUTDIALOG_H_

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QFormLayout>
#include <QDialogButtonBox>
#include "interface.h"

class MultipleInputDialog : public QDialog
{
private:
    QLineEdit* m_name;
    QLineEdit* m_content;
    ISerialUI* m_ui;

    QFormLayout* m_form;
    QDialogButtonBox* m_buttonBox;
public:
    explicit MultipleInputDialog(const QString& name, const QString& content,QWidget* parent = Q_NULLPTR);

    QString getName();
    QString getContent();
};

#endif // _KUN__MULTIPLEINPUTDIALOG_H_
