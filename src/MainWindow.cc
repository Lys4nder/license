#include "../include/MainWindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

ImageWindow::ImageWindow() {
    setWindowTitle("CBIR");
    setGeometry(100, 100, 700, 400);
    setAcceptDrops(true);

    // Create the main layout for the window
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Set palette
    QPalette pal = SetPalette();
    this->setPalette(pal);

    // Create and set the import button
    SetImportButton(mainLayout);

    // Create and set the text label
    SetTextLabel(mainLayout, "No picture selected");

    // Create and set the image label
    SetImageLabel(mainLayout);
}

void ImageWindow::SetImportButton(QVBoxLayout* layout) {
    // Create the import button
    importButton_ = new QPushButton("Import Image");
    connect(importButton_, &QPushButton::clicked, this, &ImageWindow::ImportImage);

    // Add the import button to the main layout
    layout->addWidget(importButton_);
}

void ImageWindow::SetImageLabel(QVBoxLayout* layout) {
    // Create a QLabel for the image
    imageLabel_ = new QLabel(this);
    imageLabel_->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    imageLabel_->setMaximumSize(QSize(300, 300));
    // Add the image label to the main layout
    layout->addWidget(imageLabel_);
}

void ImageWindow::SetTextLabel(QVBoxLayout* layout, QString text) {
    // Create a QLabel for the text
    imagePathLabel_ = new QLabel(text);
    imagePathLabel_->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    imagePathLabel_->setFixedHeight(imagePathLabel_->fontMetrics().height() + 20);

    // Allow the label to expand horizontally
    imagePathLabel_->setWordWrap(true);
    imagePathLabel_->setAlignment(Qt::AlignTop);

    // Add the text label to the main layout
    layout->addWidget(imagePathLabel_);
}

QPalette ImageWindow::SetPalette() {
     // Create Color Palette
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(45, 45, 45));

    // Text Color
    pal.setColor(QPalette::WindowText, Qt::white);

    // Button Color
    pal.setColor(QPalette::Button, QColor(70, 70, 70));
    pal.setColor(QPalette::ButtonText, Qt::white); 

    // Highlight Color (for selection)
    pal.setColor(QPalette::Highlight, QColor(41, 128, 185));
    pal.setColor(QPalette::HighlightedText, Qt::white);
    // Disabled Text Color
    pal.setColor(QPalette::Disabled, QPalette::WindowText, QColor(128, 128, 128));

    // Tooltips
    pal.setColor(QPalette::ToolTipBase, QColor(50, 50, 50));
    pal.setColor(QPalette::ToolTipText, Qt::white);

    return pal;
}

void ImageWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawImage(0, 0, image_);
}

void ImageWindow::dropEvent(QDropEvent* event) {
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();
            QImage newImage(filePath);

            if (!newImage.isNull()) {
                image_ = newImage;
                imagePathLabel_->setText(filePath);
                imagePathLabel_->setFixedSize(imagePathLabel_->sizeHint());
                // Redraw with the new image
                update(); 
            }
        }
    }
}

void ImageWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ImageWindow::ImportImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image File", QString(), "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty()) {
        QImage newImage(filePath);

        if (!newImage.isNull()) {
            // Set the text and image
            imagePathLabel_->setText(filePath);
            imageLabel_->setPixmap(QPixmap::fromImage(newImage.scaled(300,300)));
        }
    }
}