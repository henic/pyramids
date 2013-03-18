/********************************************************************************
** Form generated from reading UI file 'confirmation.ui'
**
** Created: Sun Jan 13 08:25:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMATION_H
#define UI_CONFIRMATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox_Confirmation;
    QLabel *label_Confirmatyion;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(302, 162);
        Dialog->setLayoutDirection(Qt::LeftToRight);
        buttonBox_Confirmation = new QDialogButtonBox(Dialog);
        buttonBox_Confirmation->setObjectName(QString::fromUtf8("buttonBox_Confirmation"));
        buttonBox_Confirmation->setGeometry(QRect(50, 110, 201, 32));
        buttonBox_Confirmation->setLayoutDirection(Qt::LeftToRight);
        buttonBox_Confirmation->setOrientation(Qt::Horizontal);
        buttonBox_Confirmation->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);
        buttonBox_Confirmation->setCenterButtons(true);
        label_Confirmatyion = new QLabel(Dialog);
        label_Confirmatyion->setObjectName(QString::fromUtf8("label_Confirmatyion"));
        label_Confirmatyion->setGeometry(QRect(30, 50, 241, 20));
        label_Confirmatyion->setAlignment(Qt::AlignCenter);

        retranslateUi(Dialog);
        QObject::connect(buttonBox_Confirmation, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox_Confirmation, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_Confirmatyion->setText(QApplication::translate("Dialog", "Are you sure?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMATION_H
