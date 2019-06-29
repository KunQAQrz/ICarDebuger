#include "MultipleInputDialog.h"

#include <QString>
#include <QLineEdit>
#include <QDebug>

MultipleInputDialog::MultipleInputDialog(const QString &name, const QString &content, QWidget* parent)
    : QDialog(parent,Qt::WindowCloseButtonHint)
{
    m_ui = dynamic_cast<ISerialUI*>(parent);
    if(m_ui)
    {
        this->setWindowTitle("热键修改");
        m_form = new QFormLayout(this);

        m_name = new QLineEdit(name,this);
        m_content = new QLineEdit(content,this);

        m_buttonBox =
                new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                     Qt::Horizontal, this);
        if(m_form && m_name && m_content && m_buttonBox)
        {
            m_form->addRow("名称:", m_name);
            m_form->addRow("发送内容:", m_content);
            m_form->addRow(m_buttonBox);

            m_buttonBox->button(QDialogButtonBox::Ok)
                    ->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);

            m_buttonBox->button(QDialogButtonBox::Cancel)
                    ->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);

            m_ui->setMainWidgetColor(*this);

            m_ui->setTextEditColor(*(reinterpret_cast<QTextEdit*>(m_name)));
            m_ui->setTextEditColor(*(reinterpret_cast<QTextEdit*>(m_content)));

            m_ui->setPushButtonColor(*m_buttonBox->button(QDialogButtonBox::Ok));
            m_ui->setPushButtonColor(*m_buttonBox->button(QDialogButtonBox::Cancel));

            connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
            connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

            m_form->setSpacing(10);
            setLayout(m_form);

            setFixedHeight(120);
        }
    }
}

QString MultipleInputDialog::getName()
{
    if(m_name)
    {
        return m_name->text();
    }

    return "";
}

QString MultipleInputDialog::getContent()
{
    if(m_content)
    {
        return m_content->text();
    }

    return "";
}
