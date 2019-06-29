#ifndef _KUN__BLUETOOTHAT_WINDOW_H_
#define _KUN__BLUETOOTHAT_WINDOW_H_

#include <QWidget>
#include <QString>
#include <QFormLayout>
#include "interface.h"

class BluetoothAT_Window : public QWidget
{
    Q_OBJECT

private:
    ISerialUI* m_ui;
    QFormLayout* m_fLayout;
private slots:
    void onATclicked();
    void onAbouted();
public:
    explicit BluetoothAT_Window(QWidget* parent = Q_NULLPTR, ISerialUI* ui = NULL);
};

#endif // _KUN__BLUETOOTHAT_DIALOG_H_
