/********************************************************************************
** Form generated from reading UI file 'chip_options.ui'
**
** Created: Sun Jan 13 08:25:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHIP_OPTIONS_H
#define UI_CHIP_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_chip_options
{
public:
    QDialogButtonBox *buttonBox;
    QRadioButton *radioButton_shape_round;
    QRadioButton *radioButton_shape_square;
    QRadioButton *radioButton_shape_triangle;
    QRadioButton *radioButton_shape_xo;

    void setupUi(QDialog *chip_options)
    {
        if (chip_options->objectName().isEmpty())
            chip_options->setObjectName(QString::fromUtf8("chip_options"));
        chip_options->resize(277, 215);
        buttonBox = new QDialogButtonBox(chip_options);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(60, 170, 160, 25));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        radioButton_shape_round = new QRadioButton(chip_options);
        radioButton_shape_round->setObjectName(QString::fromUtf8("radioButton_shape_round"));
        radioButton_shape_round->setGeometry(QRect(20, 30, 82, 18));
        radioButton_shape_square = new QRadioButton(chip_options);
        radioButton_shape_square->setObjectName(QString::fromUtf8("radioButton_shape_square"));
        radioButton_shape_square->setGeometry(QRect(20, 50, 82, 18));
        radioButton_shape_triangle = new QRadioButton(chip_options);
        radioButton_shape_triangle->setObjectName(QString::fromUtf8("radioButton_shape_triangle"));
        radioButton_shape_triangle->setGeometry(QRect(20, 70, 82, 18));
        radioButton_shape_xo = new QRadioButton(chip_options);
        radioButton_shape_xo->setObjectName(QString::fromUtf8("radioButton_shape_xo"));
        radioButton_shape_xo->setGeometry(QRect(20, 90, 82, 18));

        retranslateUi(chip_options);
        QObject::connect(buttonBox, SIGNAL(accepted()), chip_options, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), chip_options, SLOT(reject()));

        QMetaObject::connectSlotsByName(chip_options);
    } // setupUi

    void retranslateUi(QDialog *chip_options)
    {
        chip_options->setWindowTitle(QApplication::translate("chip_options", "Dialog", 0, QApplication::UnicodeUTF8));
        radioButton_shape_round->setText(QApplication::translate("chip_options", "Round", 0, QApplication::UnicodeUTF8));
        radioButton_shape_square->setText(QApplication::translate("chip_options", "Square", 0, QApplication::UnicodeUTF8));
        radioButton_shape_triangle->setText(QApplication::translate("chip_options", "Triangle", 0, QApplication::UnicodeUTF8));
        radioButton_shape_xo->setText(QApplication::translate("chip_options", "X/O", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chip_options: public Ui_chip_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHIP_OPTIONS_H
