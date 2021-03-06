#include "ocrstringutils.h"

#include <QColor>

QString OCRUtils::String::removeStringBy(const QString &value, const QString &key)
{
    QString s = value;
    s.remove(key);
    if(s.contains(key))
    {
        s = removeStringBy(key);
    }
    return s;
}

QStringList OCRUtils::String::splitString(const QString &value, const QString &key)
{
    QStringList strings = value.split(QString(" %1 ").arg(key));
    if(strings.isEmpty() || strings.count() == 1)
    {
        strings = value.split(key);
    }
    return strings;
}

QStringList OCRUtils::String::illegalCharacters()
{
    QStringList acs;
    acs << "\\" << "/" << "?"  << "*" << "\"" << ":" << "<" << ">" << "|";
    return acs;
}

bool OCRUtils::String::illegalCharactersCheck(const QString &value)
{
    QStringList acs(illegalCharacters());

    foreach(const QString &ac, acs)
    {
        if(value.contains(ac))
        {
            return true;
        }
    }

    return false;
}

QString OCRUtils::String::illegalCharactersReplaced(const QString &value)
{
    QStringList acs(illegalCharacters());
    QString s(value);

    foreach(const QString &ac, acs)
    {
        if(s.contains(ac))
        {
            s.replace(ac, " ");
        }
    }

    return s;
}

QList<QColor> OCRUtils::String::readColorConfig(const QString &value)
{
    QList<QColor> colors;
    QStringList rgbs = value.split(';', QString::SkipEmptyParts);
    foreach(const QString &rgb, rgbs)
    {
        QStringList var = rgb.split(',');
        if(var.count() != 3)
        {
            continue;
        }
        colors << QColor(var[0].toInt(), var[1].toInt(), var[2].toInt());
    }
    return colors;
}

QString OCRUtils::String::writeColorConfig(const QColor &color)
{
    QString value;
    value.append(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
    return value;
}

QString OCRUtils::String::writeColorConfig(const QList<QColor> &colors)
{
    QString value;
    foreach(const QColor &rgb, colors)
    {
        value.append(writeColorConfig(rgb) + ";");
    }
    return value;
}
