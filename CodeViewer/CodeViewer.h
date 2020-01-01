#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QString>

class CodeViewer : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeViewer(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth();
    //void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
    QList<QTextEdit::ExtraSelection> selectionsAdded;
    QList<QTextEdit::ExtraSelection> selectionsRemoved;
    QList<QTextEdit::ExtraSelection> selectionsChanged;
};

#endif // CODEEDITOR_H
