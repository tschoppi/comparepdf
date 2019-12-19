/*
    Copyright (c) 2011 Qtrac Ltd. All rights reserved.

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 2 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#if QT_VERSION >= 0x040600
#include <QSharedPointer>
#else
#include <tr1/memory>
#endif
#include <poppler-version.h>
#include <poppler-qt5.h>
#include <QApplication>
#include <QImage>
#include <QTextStream>
#include "option_parser.hpp"

#if QT_VERSION >= 0x040600
typedef QSharedPointer<Poppler::Document> PdfDocument;
typedef QSharedPointer<Poppler::Page> PdfPage;
typedef QSharedPointer<Poppler::TextBox> PdfTextBox;
#else
typedef std::tr1::shared_ptr<Poppler::Document> PdfDocument;
typedef std::tr1::shared_ptr<Poppler::Page> PdfPage;
typedef std::tr1::shared_ptr<Poppler::TextBox> PdfTextBox;
#endif
typedef QList<PdfTextBox> TextBoxList;

enum Difference{
    Same, DifferentPageCount, DifferentTexts, DifferentAppearance,
    Error};

PdfDocument getPdf(const QString &filename, QString *error);
TextBoxList getTextBoxes(PdfPage page);
Difference compareFiles(const QString &file1, const QString &file2,
        bool compareText, QString *error);


const QString Version("1.0.1");


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AQP::OptionParser parser(app.arguments(),
            QObject::tr("usage: {program} [options] <pdf1> <pdf2>\n"
            "\nA program to compare two PDF files.\n"),
            QObject::tr("\nA return value of 0 means no differences "
            "detected; 1 or 2 signifies an error; 10 means they differ "
            "visually, 13 means they differ textually, and 15 means "
            "they have different page counts.\n"
            "\nVersion %1 Copyright (c) 2011-12 Qtrac Ltd. "
            "All rights reserved.\nTo see detailed page by page "
            "differences in a GUI application, use DiffPDF: see "
            "http://www.qtrac.eu").arg(Version));
    AQP::StringOptionPtr comparisonModeOpt = parser.addStringOption(
            QObject::tr("c"), QObject::tr("compare"));
    comparisonModeOpt->setDefaultValue("text");
    comparisonModeOpt->setAcceptableValues(QStringList()
            << QObject::tr("appearance") << QObject::tr("a")
            << QObject::tr("text") << QObject::tr("t"));
    comparisonModeOpt->setHelp(QObject::tr("comparison mode"));
    AQP::IntegerOptionPtr verboseOpt = parser.addIntegerOption(
            QObject::tr("v"), QObject::tr("verbose"));
    verboseOpt->setDefaultValue(1);
    verboseOpt->setAcceptableValues(QSet<int>() << 0 << 1 << 2);
    verboseOpt->setHelp(QObject::tr("0 = quiet; 1 = report differences; "
                "2 = report same and different"));
    AQP::BooleanOptionPtr versionOpt = parser.addBooleanOption("",
            QObject::tr("version"));
    versionOpt->setHelp(QObject::tr("show version information and "
                "terminate"));
    if (!parser.parse())
        return 2;
    QTextStream out(stdout);
    if (versionOpt->boolean()) {
        out << QObject::tr("comparepdf ") << Version << "\n"
            << QObject::tr("poppler ") << POPPLER_VERSION << "\n";
        return 0;
    }
    QStringList files = parser.remainder();
    if (files.count() != 2 || !files[0].toLower().endsWith(".pdf") ||
            !files[1].toLower().endsWith(".pdf")) {
        out << QObject::tr("Two PDF files must be specified\n");
        return 1;
    }

    bool compareText = comparisonModeOpt->value()[0] == 't';
    QString error;
    Difference difference = compareFiles(files[0], files[1], compareText,
            &error);
    if (!error.isEmpty()) {
        out << error << "\n";
        return 1;
    }
    int result = Same; // 0
    if (difference == DifferentPageCount)
        result = 15;
    else if (difference == DifferentTexts)
        result = 13;
    else if (difference == DifferentAppearance)
        result = 10;
    if (!result && verboseOpt->value() == 2) {
        out << QObject::tr("No differences detected.\n");
    } else if (result && verboseOpt->value() > 0) {
        if (comparisonModeOpt->value()[0] == 't')
            out << QObject::tr("Files have different texts.\n");
        else
            out << QObject::tr("Files look different.\n");
    }
    return result;
}


Difference compareFiles(const QString &filename1, const QString &filename2,
        bool compareText, QString *error)
{
    PdfDocument pdf1 = getPdf(filename1, error);
    if (!error->isEmpty())
        return Error;
    PdfDocument pdf2 = getPdf(filename2, error);
    if (!error->isEmpty())
        return Error;
    int count = pdf1->numPages();
    if (count != pdf2->numPages())
        return DifferentPageCount;
    for (int page = 0; page < count; ++page) {
        PdfPage page1(pdf1->page(page));
        if (!page1) {
            *error = QObject::tr("Failed to read page %1 from '%2'.")
                          .arg(page + 1).arg(filename1);
            return Error;
        }
        PdfPage page2(pdf2->page(page));
        if (!page2) {
            *error = QObject::tr("Failed to read page %1 from '%2'.")
                          .arg(page + 1).arg(filename2);
            return Error;
        }
        if (compareText) {
            TextBoxList list1 = getTextBoxes(page1);
            TextBoxList list2 = getTextBoxes(page2);
            QStringList words1;
            QStringList words2;
            foreach (const PdfTextBox &box, list1)
                words1 << box->text();
            foreach (const PdfTextBox &box, list2)
                words2 << box->text();
            if (words1.join("") != words2.join(""))
                return DifferentTexts;
        } else {
            QImage image1 = page1->renderToImage();
            QImage image2 = page2->renderToImage();
            if (image1 != image2)
                return DifferentAppearance;
        }
    }
    return Same;
}


PdfDocument getPdf(const QString &filename, QString *error)
{
    PdfDocument pdf(Poppler::Document::load(filename));
    if (!pdf) {
        *error = QObject::tr("Cannot load '%1'.").arg(filename);
    }
    else if (pdf->isLocked()) {
        *error = QObject::tr("Cannot read a locked PDF ('%1').").arg(
                filename);
#if QT_VERSION >= 0x040600
        pdf.clear();
#else
        pdf.reset();
#endif
    }
    return pdf;
}


TextBoxList getTextBoxes(PdfPage page)
{
    TextBoxList boxes;
    foreach (Poppler::TextBox *box, page->textList()) {
        PdfTextBox box_ptr(box);
        boxes.append(box_ptr);
    }
    return boxes;
}
