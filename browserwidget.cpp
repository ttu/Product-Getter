#include "browserwidget.h"
#include "ui_browserwidget.h"

BrowserWidget::BrowserWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BrowserWidget)
{
    ui->setupUi(this);
}

BrowserWidget::~BrowserWidget()
{
    delete ui;
}

void BrowserWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BrowserWidget::setUrl(QString url)
{
    // First set loading screen (clear previous) and then load selected
    ui->webView->setHtml("<html><main>Loading..</main></html>");
    ui->webView->load(QUrl(url));
    ui->webView->show();
}
