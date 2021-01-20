#ifndef W_PAGE_H
#define W_PAGE_H

#include <Arduino.h>
#include "WebServer.h"
#include "WStringStream.h"

class WPage
{
public:
    WPage *next;
    WPage(const char *id, const char *title)
    {
        this->next = nullptr;
        this->id = id;
        this->title = title;
        this->onPrintPage = nullptr;
        this->onSubmittedPage = nullptr;
    }

    ~WPage()
    {
        delete this->id;
        delete this->title;
    }
    typedef std::function<void(WebServer *, WStringStream *)> TCommandPage;

    virtual void printPage(WebServer *webServer, WStringStream *page)
    {
        if (onPrintPage)
            onPrintPage(webServer, page);
    }

    virtual void submittedPage(WebServer *webServer, WStringStream *page)
    {
        if (onSubmittedPage)
            onSubmittedPage(webServer, page);
    }

    void setPrintPage(TCommandPage onPrintPage)
    {
        this->onPrintPage = onPrintPage;
    }

    void setSubmittedPage(TCommandPage onSubmittedPage)
    {
        this->onSubmittedPage = onSubmittedPage;
    }

    const char *getId()
    {
        return id;
    }

    const char *getTitle()
    {
        return title;
    }

protected:
private:
    const char *id;
    const char *title;
    TCommandPage onPrintPage;
    TCommandPage onSubmittedPage;
};

#endif
