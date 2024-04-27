#ifndef QT_GUI_MAINWINDOW_H
#define QT_GUI_MAINWINDOW_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "../include/ServerConnection.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void ImportImage();
    void QueryImage();

protected:
    QImage image_;
    QImage toBeSentImage_;
    QPushButton* importButton_; // New QPushButton for image import
    QLabel *imagePathLabel_;
    QLabel *imageLabel_; // QLabel for displaying the image
    QPushButton* queryButton_;
    QLabel* statusLabel_;


    Client::ServerConnection connection_ = Client::ServerConnection();

    void dropEvent(QDropEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    QPalette SetPalette();
    void SetImportButton(QHBoxLayout* layout);
    void SetQueryButton(QHBoxLayout* layout);
    void SetImageLabel(QHBoxLayout* layout);
    void SetTextLabel(QVBoxLayout* layout, QString text);
    void SetStatusLabel(QHBoxLayout* layout, QString text);

};
#endif // QT_GUI_MAINWINDOW_H