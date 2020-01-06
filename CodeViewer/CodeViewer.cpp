#include "CodeViewer.h"
#include "LineNumberArea.h"
#include <QPainter>
#include <QTextBlock>

CodeViewer::CodeViewer(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    connect(this, &CodeViewer::blockCountChanged, this, &CodeViewer::updateLineNumberAreaWidth);
    connect(this, &CodeViewer::updateRequest, this, &CodeViewer::updateLineNumberArea);    
    setLineWrapMode(LineWrapMode::NoWrap);
    updateLineNumberAreaWidth();
}

int CodeViewer::lineNumberAreaWidth()
{
    int digits = 1;
    // каждые 10 строк добавляем символ в номер строки
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    // символа * количество символов в последней строке.
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeViewer::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeViewer::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void CodeViewer::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeViewer::ResetCharFormat()
{
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::SelectionType::Document);
    QTextCharFormat defaultFotmat;
    cursor.setCharFormat(defaultFotmat);
}

void CodeViewer::HighlightLine(const int line, const QTextCharFormat& format)
{
    QTextCursor cursor(document()->findBlockByLineNumber(line));
    cursor.select(QTextCursor::SelectionType::BlockUnderCursor);
    cursor.setCharFormat(format);
}

void CodeViewer::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    // Заливаем фон
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    // Рисуем символы для каждой строки
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
         ++blockNumber;
    }
}
